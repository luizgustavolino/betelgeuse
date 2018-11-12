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

static void creditsOnEnter(Game *game, int frame) {

	senacLogo  = loadImageAsset("splash_senac_logo.png");
}

static void creditsOnFrame(Game *game, int frame) {


	if (frame == 1){
		fillRGB(game, BLACK);
        drawImageAsset(senacLogo,100,100);
	}
}

static void creditsOnExit(Game *game, int frame) {
	unloadImageAsset(senacLogo);
}

Scene makeCreditsScene(Game *game) {
	Scene credits;
	credits.onEnter = creditsOnEnter;
	credits.onFrame = creditsOnFrame;
	credits.onExit  = creditsOnExit;
	return credits;
}
