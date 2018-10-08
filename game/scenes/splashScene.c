//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "splashScene.h"

int bgAsset;

static void splashOnEnter(Game *game, int frame) {
	bgAsset = loadImageAsset("splashbg.png");
}

static void splashOnFrame(Game *game, int frame) {
	drawImageAsset(bgAsset, 0, 0);

	if (frame == 50) {
		changeScene(game, makeSplashScene());
	}
}

static void splashOnExit(Game *game, int frame) {
	unloadImageAsset(bgAsset);
}

Scene makeSplashScene(Game *game) {
	Scene splash;
	splash.onEnter = splashOnEnter;
	splash.onFrame = splashOnFrame;
	splash.onExit  = splashOnExit;
	return splash;
}
