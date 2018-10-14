//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "splashScene.h"

int senacLogo;

static void splashOnEnter(Game *game, int frame) {
	senacLogo = loadImageAsset("splash_senac.png");
}

static void splashOnFrame(Game *game, int frame) {
	unsigned char color = min(frame, 255);
	if (frame < 360) fillRGB( color, color, color);
	else drawImageAsset(senacLogo, 74, 52);
}

static void splashOnExit(Game *game, int frame) {
	unloadImageAsset(senacLogo);
}

Scene makeSplashScene(Game *game) {
	Scene splash;
	splash.onEnter = splashOnEnter;
	splash.onFrame = splashOnFrame;
	splash.onExit  = splashOnExit;
	return splash;
}
