//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "mainMenuScene.h"

static int menu_bg;

static void mainMenuOnEnter(Game *game, int frame) {
	menu_bg  = loadImageAsset("main_menu_bg.png");
	fillRGB(220, 245, 255);
}

static void mainMenuOnFrame(Game *game, int frame) {

	float delta = applyCubicEaseOut(0, 520, frame, 184);
	drawImageAsset(menu_bg, 0, 170 - delta);
}

static void mainMenuOnExit(Game *game, int frame) {
	unloadImageAsset(menu_bg);
}

Scene makeMainMenuScene(Game *game){
	Scene mainMenu;
	mainMenu.onEnter = mainMenuOnEnter;
	mainMenu.onFrame = mainMenuOnFrame;
	mainMenu.onExit  = mainMenuOnExit;
	return mainMenu;
}