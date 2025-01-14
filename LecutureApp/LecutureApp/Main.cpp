#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include "allVariableName.h"
#include "allMethod.h"

/***********************      Mainの処理      *********************************/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	bool over;
	bool clear;
	bool story;
	int tmp_mx = m->x;
	int tmp_my = m->y;
	int d_num = 0;
	int tempTime = 0;
	int hpColor = 0;
	/*初期化処理*/
	if (init() == -1) { return -1; }

	while (true) {


		prologue();

		charaInit();

		SetFontSize(16);
		SetFontThickness(4);

		ClearDrawScreen();
		/*bgm再生開始*/
		if (m->floor != 2) {
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		}
		else {
			PlaySoundMem(boss_bgm, DX_PLAYTYPE_LOOP);
		}
		for (int i = 0; i < 256; i++) {
			SetDrawBright(i, i, i);
			allView(d_num);
			wait(10);
		}
		if (!continueflag) {
			talk(c, "「ここは...?」");
			initMessage();
			drawExplain();
		}
		isReturn = true;
		over = false;
		clear = false;
		story = false;
		messageflag = false;
		continueflag = false;
		endflag = false;
		/*描画する*/
		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア,フレームカウント)
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0 && m->floor != 2) {

			tmp_mx = m->x;
			tmp_my = m->y;

			/*500ms(0.5秒)に一度画像更新(歩いているように見える)*/
			if (GetNowCount() - tempTime > 500)
			{
				if (d_num == 1)d_num = 0;
				else d_num = 1;
				tempTime = GetNowCount();
			}

			//地図やキャラなどの描画関数
			allView(d_num);
			

			//自分が死んだら
			if (c->hp == 0) { over = true; break; }

			/*主人公の動き、移動や攻撃、階段移動*/
			mainCharaMove();
			if (m->floor != 2) {
				allView(d_num);
			}
			/*敵の動き、移動や攻撃*/
			if (m->floor != 2) {
				mainEnemyMove(tmp_mx, tmp_my);
			}
			/*メッセージは常に出力*/
			outMessage();
			/*iを押すとメニュー表示、再度押すか技を選ぶと消去*/
			showMenu();

			if (endflag) { break; }
		}
		if (m->floor == 2 && !isReturn) {
			for (int i = 0; i < 256; i++) {
				SetDrawBright(i, i, i);
				allView(d_num);
				wait(10);
			}
			
			talk(lastboss, "よくここまで来たな");
			wait(10);
			talk(lastboss, "さあ、私を倒してみろ");
			wait(10);
			ClearDrawScreen();
			allView(d_num);
			talk(c, "ラスボス早いな...");
			
		}

		//ボス用
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && getCountFrame() == 0 && m->floor == 2) {
			tmp_mx = m->x;
			tmp_my = m->y;

			/*500ms(0.5秒)に一度画像更新(歩いているように見える)*/
			if (GetNowCount() - tempTime > 500)
			{
				if (d_num == 1)d_num = 0;
				else d_num = 1;
				tempTime = GetNowCount();
			}

			//地図やキャラなどの描画関数
			allView(d_num);


			if (!lastboss->isLive) { clear = true; break; }

			//自分が死んだら
			if (c->hp == 0) { over = true; break; }


			/*主人公の動き、移動や攻撃、階段移動*/
			mainCharaMove();
			allView(d_num);
			/*敵の動き、移動や攻撃*/
			mainBossMove(tmp_mx, tmp_my);

			/*メッセージは常に出力*/
			outMessage();
			/*iを押すとメニュー表示、再度押すか技を選ぶと消去*/
			showMenu();

			/*spaceキーで終わり*/
			if (endflag) { break; }
		}
		StopSoundMem(boss_bgm);
		StopSoundMem(bgm);
		if (endflag && !isReturn)break;
		else if (over)gameover();
		else if(clear)gameClear();
		if (endflag && !isReturn)break;
	}
	DxLib::DxLib_End();    // DXライブラリ終了処理
	
	return 0;
}







