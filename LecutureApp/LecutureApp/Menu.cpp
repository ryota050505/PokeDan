#pragma once
#include "all.h"
#include "allVariableName.h"
#include "Message.h"

void drawMenu() {
	int x = 0;
	if (c->x < SCREEN_WIDTH / 2) { x = 530; }
	else { x = 100; }
	DrawRotaGraph(x+20, 160, 1, 0, skillBox, true);
	DrawFormatString(x, 98, WHITE, "%s (%d/%d)", c->skill[0].name, c->skill[0].count, c->skill[0].maxCount);
	DrawFormatString(x, 149, WHITE, "%s (%d/%d)", c->skill[1].name, c->skill[1].count, c->skill[1].maxCount);
	DrawFormatString(x, 199, WHITE, "%s (%d/%d)", c->skill[2].name, c->skill[2].count, c->skill[2].maxCount);
	DrawFormatString(x, 250, WHITE, "%s (%d/%d)", c->skill[3].name, c->skill[3].count, c->skill[3].maxCount);
	if (keyState[KEY_INPUT_1]) { c->attackNum = 0; menuflag = false; }
	else if (keyState[KEY_INPUT_2]) { c->attackNum = 1; menuflag = false; }
	else if (keyState[KEY_INPUT_3]) { c->attackNum = 2; menuflag = false; }
	else if (keyState[KEY_INPUT_4]) { c->attackNum = 3; menuflag = false; }
}

void showMenu() {
	/*わざ表を消去*/
	if (menuflag && keyState[KEY_INPUT_I] == 1) {
		menuflag = false;
	}

	/*わざ表を表示*/
	else if (!menuflag && keyState[KEY_INPUT_I] == 1) {
		menuflag = true;
	}

	if (menuflag) {
		initMessage();
		drawMenu();
	}
}