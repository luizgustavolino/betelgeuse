//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// splashScene.c
// estruturas da Cena de abertura
//
#include <stddef.h>
#include <stdio.h>
#include "../game.h"

static void splashOnEnter(Game *game) {
	printf("%s\n", "splashOnEnter");
}

static void splashOnFrame(Game *game) {
	printf("%s\n", "splashOnFrame");	
}

static void splashOnExit(Game *game) {
	printf("%s\n", "splashOnExit");		
}

Scene makeSplashScene(Game *game) {
	Scene splash;
	splash.onEnter = splashOnEnter;
	splash.onFrame = splashOnFrame;
	splash.onExit  = splashOnExit;
	return splash;
}
