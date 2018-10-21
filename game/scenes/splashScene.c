//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "splashScene.h"

int senacLogo, senacTitle;
int bccLogo, bccTitle;
int betelgeuseLogo;

static void splashOnEnter(Game *game, int frame) {
	
	senacLogo  = loadImageAsset("splash_senac_logo.png");
	senacTitle = loadImageAsset("splash_senac_label.png");

	bccLogo = loadImageAsset("splash_bcc_logo.png");
	bccTitle = loadImageAsset("splash_bcc_title.png");

	betelgeuseLogo = loadImageAsset("splash_betelgeuse.png");
}

static void splashOnFrame(Game *game, int frame) {
	
	unsigned char color = min(frame, 255);
	int waitTime 	= 260;
	int exposeTime 	= 400;
	int totalFrames	= waitTime + 3 * exposeTime + waitTime;

	if (frame < waitTime){
		fillRGB( color, color, color );

	} else if (frame < waitTime + 1 * exposeTime){
		drawImageAsset(senacLogo, 107, 59);
		drawImageAsset(senacTitle, 76, 75);

	} else if (frame == waitTime + 1 * exposeTime) {
		fillRGB( color, color, color );

	} else if (frame < waitTime + 2 * exposeTime){
		drawImageAsset(bccLogo, 82, 64);
		drawImageAsset(bccTitle, 80, 94);

	} else if (frame < waitTime + 2 * exposeTime){
		fillRGB( color, color, color );

	}else if (frame < waitTime + 3 * exposeTime){
		drawImageAsset(betelgeuseLogo, 74, 52);

	} else if (frame < totalFrames){
		color = min(255, totalFrames - frame);
		fillRGB( color, color, color);

	} else {
		changeScene(game, makeSplashScene(game));
	}
}

static void splashOnExit(Game *game, int frame) {
	unloadImageAsset(senacLogo);
	unloadImageAsset(bccLogo);
	unloadImageAsset(betelgeuseLogo);
}

Scene makeSplashScene(Game *game) {
	Scene splash;
	splash.onEnter = splashOnEnter;
	splash.onFrame = splashOnFrame;
	splash.onExit  = splashOnExit;
	return splash;
}
