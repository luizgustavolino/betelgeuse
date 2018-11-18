//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "winScene.h"

#include "../engine/colors.h"

static int bgAsset, pathAsset, pathDenseAsset, mobile, popup, windowPopup, smoke_1, smoke_2, smoke_3;
static int aBtnIconA, aBtnIconB;
//Animation
static int startDly = 500;


static void winOnEnter(Game *game, int frame) {
    bgAsset 		= loadImageAsset("report_bg.png");
	pathAsset 		= loadImageAsset("menu_overlay_path.png");
	pathDenseAsset 	= loadImageAsset("menu_overlay_path_dense.png");
	mobile      	= loadImageAsset("mobile.png");
	popup      	    = loadImageAsset("popup.png");
	windowPopup     = loadImageAsset("window.png");
	smoke_1      	= loadImageAsset("smoke_1.png");
	smoke_2      	= loadImageAsset("smoke_2.png");
	smoke_3     	= loadImageAsset("smoke_3.png");

	aBtnIconA	= loadImageAsset("main_a_btn_icon_a.png");
	aBtnIconB	= loadImageAsset("main_a_btn_icon_b.png");

}

static void winOnFrame(Game *game, int frame) {

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
		if ( frame % 360 >= 0 && frame % 360 < 90) {
			drawImageAsset(smoke_1, 36, 103);
		} else if ( frame % 360 >= 90 && frame % 360 < 180) {
			drawImageAsset(smoke_2, 36, 103);
        } else if ( frame % 360 >= 180 && frame % 360 < 270) {
			drawImageAsset(smoke_3, 36, 103);
        } else if ( frame % 360 >= 270 && frame % 360 < 360) {
			drawImageAsset(smoke_2, 36, 103);

        } if (frame >= startDly && frame < startDly + 400) {
            if(frame == startDly) playSfx(game, "mobile.wav");
            if ( frame % 40 >= 20) {
                drawImageAsset(mobile, 62, 117);
            }
        } else if (frame >= startDly + 900 && frame < startDly + 1300) {
            if(frame == startDly + 900) playSfx(game, "mobile.wav");
            if ( frame % 40 >= 20) {
                drawImageAsset(mobile, 62, 117);
            }
        } if (frame >= startDly + 1400) {
            if(frame == startDly + 1400) playSfx(game, "popup.wav");
            drawImageAsset(popup, 110, 78);

        }
    }

    if (frame >= startDly + 1800){
        if(frame == startDly + 1800) playSfx(game, "gameLoss.wav");
        float delta = 170 - applyCubicEaseOut(startDly + 1800, startDly + 1930, frame, 170);
		drawImageAsset(windowPopup, 0, 0 + delta);

		setTextRGBColor(LIGHT_BLUE);

		char* text = "O bandido escapou e foi visto pela;ultima vez na cidade Belo Horizonte.; ;Voce esta DEMITIDO, recruta.; ;; ;; ;ABIN;Agencia Brasileira de Inteligencia";
	    drawText(text, 20, 34 + delta);
    }
}

static void winOnExit(Game *game, int frame) {
    unloadImageAsset(bgAsset);
	unloadImageAsset(pathAsset);
	unloadImageAsset(pathDenseAsset);
	unloadImageAsset(mobile);
	unloadImageAsset(popup);
	unloadImageAsset(windowPopup);
	unloadImageAsset(smoke_1);
	unloadImageAsset(smoke_2);
	unloadImageAsset(smoke_3);
	unloadImageAsset(aBtnIconA);
	unloadImageAsset(aBtnIconB);
}


Scene makeWinScene(Game *game){
	Scene win;
	win.onEnter = winOnEnter;
	win.onFrame = winOnFrame;
	win.onExit  = winOnExit;
	return win;
}
