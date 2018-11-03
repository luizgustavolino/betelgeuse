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
	bgAsset = loadImageAsset("report_bg.png");
	paperAsset = loadImageAsset("report_paper.png");
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
		drawText("Tesouro Nacional roubado", 34, 38 + delta);
		drawText("bado em Belo Horizonte.", 34, 48 + delta);
		drawText("Obra de Antônio Francisco", 34, 58 + delta);
		drawText("Lisboa (Aleijadinho).", 34, 68 + delta);

		drawText("Investigação em anda-", 34, 88 + delta);
		drawText("mento. Suspeito avistado", 34, 98 + delta);
		drawText("na região.", 34, 108 + delta);

		drawText("Agentes no local.", 34, 128 + delta);
		
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