//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "finalScene.h"
#include "creditsScene.h"

#include "../engine/colors.h"

//!!!TO-DO!!! READ RESULT AND DEFINE OUTCOME
//-> If win: play win song and write win text. Else: play loss song and write loss text.

static int bgAsset, pathAsset, pathDenseAsset, mobile, popup, windowPopup, smoke_1, smoke_2, smoke_3;
static int action_btn_a, action_btn_b;
//Animation
static int startDly = 500, endFrame; //Delay till the phone starts ringing. Could play an intro song or write some story text

static void finalOnEnter(Game *game, int frame) {
    bgAsset 		= loadImageAsset("report_bg.png");
	pathAsset 		= loadImageAsset("menu_overlay_path.png");
	pathDenseAsset 	= loadImageAsset("menu_overlay_path_dense.png");
	mobile      	= loadImageAsset("mobile.png");
	popup      	    = loadImageAsset("popup.png");
	windowPopup     = loadImageAsset("window.png");
	smoke_1      	= loadImageAsset("smoke_1.png");
	smoke_2      	= loadImageAsset("smoke_2.png");
	smoke_3     	= loadImageAsset("smoke_3.png");

	action_btn_a	= loadImageAsset("btn_a_from_right_a.png");
	action_btn_b	= loadImageAsset("btn_a_from_right_b.png");

}

static void finalOnFrame(Game *game, int frame) {

    endFrame = startDly + 2400;

	if (frame == 1) fillRGB(game, BLACK);
	if (frame == 120) {
		drawImageAsset(bgAsset, 0, 0);
		for(int x = 0; x < 11; x++) for(int y = 0; y < 11; y++)
			drawImageAsset(pathDenseAsset, x*20, y*20);

	} else if (frame == 180) {
		drawImageAsset(bgAsset, 0, 0);
		for(int x = 0; x < 11; x++) for(int y = 0; y < 11; y++)
			drawImageAsset(pathAsset, x*20, y*20);

    } else if (frame >= 240 && frame < endFrame) {
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

    if (frame >= startDly + 1800 && frame < endFrame){
        if(frame == startDly + 1800) playSfx(game, "gameLoss.wav");
        if(frame == startDly + 2220) playSoundtrack(game, "gameOver.wav");
        float delta = 170 - applyCubicEaseOut(startDly + 1800, startDly + 1930, frame, 170);
		drawImageAsset(windowPopup, 0, delta - 14);

		setTextRGBColor(LIGHT_BLUE);

		char* text = "     *** O bandido escapou ***; ;    Foi visto pela ultima vez na;    cidade Belo Horizonte.; ;    Voce esta DEMITIDO, recruta.; ;Ass.;ABIN;Agencia Brasileira de Inteligencia";
	    drawText(text, 20, 14 + delta);
    }

    if (frame >= startDly + 2400){
        float delta = applyCubicEaseOut(startDly + 2400, startDly + 2530, frame, 70);
		if ( frame % 170 >= 100) {
			drawImageAsset(action_btn_a, 215 - delta , 145);
		} else {
			drawImageAsset(action_btn_b, 215 - delta , 145);
		} if ( frame > startDly + 2530) {
            setTextRGBColor(61, 140, 222);
			drawText("creditos", 173, 150);

        } if (game->keyState.a == KEY_IS_RELEASED) {
            changeScene(game, makeCreditsScene(game));
        }
    }
}

static void finalOnExit(Game *game, int frame) {
    unloadImageAsset(bgAsset);
	unloadImageAsset(pathAsset);
	unloadImageAsset(pathDenseAsset);
	unloadImageAsset(mobile);
	unloadImageAsset(popup);
	unloadImageAsset(windowPopup);
	unloadImageAsset(smoke_1);
	unloadImageAsset(smoke_2);
	unloadImageAsset(smoke_3);
	unloadImageAsset(action_btn_a);
	unloadImageAsset(action_btn_b);
}


Scene makeFinalScene(Game *game){
	Scene final;
	final.onEnter = finalOnEnter;
	final.onFrame = finalOnFrame;
	final.onExit  = finalOnExit;
	return final;
}
