//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "reportScene.h"

#include "../engine/colors.h"


static int pathAsset, pathDenseAsset;
static int bgAsset, paperAsset;

static void reportOnEnter(Game *game, int frame) {
	bgAsset 		= loadImageAsset("report_bg.png");
	paperAsset 		= loadImageAsset("report_paper.png");
	pathAsset 		= loadImageAsset("menu_overlay_path.png");
	pathDenseAsset 	= loadImageAsset("menu_overlay_path_dense.png"); 
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

	} else if (frame >= 240) {
		drawImageAsset(bgAsset, 0, 0);

		float delta = 170 - applyCubicEaseOut(520, 720, frame, 170);
		drawImageAsset(paperAsset, 17, 10 + delta);

		setTextRGBColor(GRAY);
		
		int len = strlen(game->gameplayContext.stolenItemText);
		char str[len];

		strcpy(str, game->gameplayContext.stolenItemText);
	    char *token = strtok(str, ";"); 
	    int line = 0;

	    while (token != NULL) { 
	    	drawText(token, 34, 38 + delta + line * 10);
	        token = strtok(NULL, ";"); 
	        line ++;
	    } 

	}

}

static void reportOnExit(Game *game, int frame) {
	unloadImageAsset(bgAsset);
}

Scene makeReportScene(Game *game) {
	Scene report;
	report.onEnter = reportOnEnter;
	report.onFrame = reportOnFrame;
	report.onExit  = reportOnExit;
	return report;
}