//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "../engine/colors.h"
#include "creditsScene.h"
#include "mainMenuScene.h"

static int senacLogo, senacTitle;
static int bccLogo, bccTitle;
static int betelgeuseLogo;
static int action_btn_a, action_btn_b;

static void creditsOnEnter(Game *game, int frame) {

	senacLogo  = loadImageAsset("splash_senac_logo.png");
	playSoundtrack(game, "credits.ogg");
	action_btn_a	= loadImageAsset("btn_a_from_right_a.png");
	action_btn_b	= loadImageAsset("btn_a_from_right_b.png");
}

static void creditsOnFrame(Game *game, int frame) {


	if (frame == 1){
		fillRGB(game, BLACK);
        drawImageAsset(senacLogo,100,100);
	}

	if (frame > 170){
        float delta = applyCubicEaseOut(170, 300, frame, 70);
		if (frame % 170 >= 100) {
			drawImageAsset(action_btn_a, 220 - delta , 145);
		} else {
			drawImageAsset(action_btn_b, 220 - delta , 145);
		} if (frame > 300) {

            setTextRGBColor(61, 140, 222);
            drawText("menu", 167, 150);

        } if (game->keyState.a == KEY_IS_RELEASED) {
            changeScene(game, makeMainMenuScene(game));
        }
	}
}

static void creditsOnExit(Game *game, int frame) {
	unloadImageAsset(senacLogo);
	unloadImageAsset(action_btn_a);
	unloadImageAsset(action_btn_b);
}

Scene makeCreditsScene(Game *game) {
	Scene credits;
	credits.onEnter = creditsOnEnter;
	credits.onFrame = creditsOnFrame;
	credits.onExit  = creditsOnExit;
	return credits;
}
