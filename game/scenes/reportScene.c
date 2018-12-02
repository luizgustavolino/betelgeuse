//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "reportScene.h"
#include "cityScene.h"

#include "../engine/colors.h"


static int pathAsset, pathDenseAsset;
static int bgAsset, paperAsset;
static int action_btn_a, action_btn_b;

static void reportOnEnter(Game *game, int frame) {
	bgAsset 		= loadImageAsset("report_bg.png");
	paperAsset 		= loadImageAsset("report_paper.png");
	pathAsset 		= loadImageAsset("menu_overlay_path.png");
	pathDenseAsset 	= loadImageAsset("menu_overlay_path_dense.png");

	action_btn_a = loadImageAsset("btn_a_from_right_a.png");
	action_btn_b = loadImageAsset("btn_a_from_right_b.png");

	playSoundtrack(game, "mission.ogg");
}

static void reportOnFrame(Game *game, int frame) {

	if (frame == 1) fillRGB(game, BLACK);
	if (frame < 60) return;

	if (frame == 120) {
		drawImageAsset(bgAsset, 0, 0);
		for(int x = 0; x < 11; x++) for(int y = 0; y < 11; y++)
			drawImageAsset(pathDenseAsset, x*20, y*20);

	} else if (frame == 180) {
		drawImageAsset(bgAsset, 0, 0);
		for(int x = 0; x < 11; x++) for(int y = 0; y < 11; y++)
			drawImageAsset(pathAsset, x*20, y*20);

	} else if (frame >= 240 && frame <= 820) {
		drawImageAsset(bgAsset, 0, 0);

		float delta = 170 - applyCubicEaseOut(520, 720, frame, 170);
		drawImageAsset(paperAsset, 17, 10 + delta);

		setTextRGBColor(GRAY);

	    drawText(game->gameplayContext.stolenItemText, 34, 38 + delta);

	} else if (frame > 820) {
		float delta = applyCubicEaseOut(820, 950, frame, 80);
		if ( frame % 170 >= 100) {
			drawImageAsset(action_btn_a, 220 - delta , 145);
		} else {
			drawImageAsset(action_btn_b, 220 - delta , 145);
		}

		if ( frame > 950) {
			setTextRGBColor(61, 140, 222);
			drawText("investigar", 168, 150);

			if (game->keyState.a == KEY_IS_RELEASED) {
				changeScene(game, makeCityScene(game));
			}
		}
	}

}

static void reportOnExit(Game *game, int frame) {
	unloadImageAsset(bgAsset);
	unloadImageAsset(paperAsset);
	unloadImageAsset(pathAsset);
	unloadImageAsset(pathDenseAsset);
	unloadImageAsset(action_btn_a);
	unloadImageAsset(action_btn_b);
}

Scene makeReportScene(Game *game) {
	Scene report;
	report.onEnter = reportOnEnter;
	report.onFrame = reportOnFrame;
	report.onExit  = reportOnExit;
	return report;
}
