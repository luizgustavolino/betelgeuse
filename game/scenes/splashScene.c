//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "splashScene.h"

int bgAsset;

static void splashOnEnter(Game *game) {
	Logger.info("splashOnEnter");
	bgAsset = loadImageAsset("splashbg.png");
}

static void splashOnFrame(Game *game) {
	drawImageAsset(bgAsset, 0, 0);
}

static void splashOnExit(Game *game) {
	Logger.info("splashOnExit");
	unloadImageAsset(bgAsset);
}

Scene makeSplashScene(Game *game) {
	Scene splash;
	splash.onEnter = splashOnEnter;
	splash.onFrame = splashOnFrame;
	splash.onExit  = splashOnExit;
	return splash;
}
