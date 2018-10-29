//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "mainMenuScene.h"
#include "splashScene.h"

static int menu_bg, cicle, ribbon;
static int action_btn_a, action_btn_b;

static void mainMenuDidChooseOption(){

}

static void mainMenuOnEnter(Game *game, int frame) {
	menu_bg  	= loadImageAsset("main_menu_bg.png");
	cicle 	 	= loadImageAsset("main_menu_circle.png");
	ribbon 	 	= loadImageAsset("main_menu_ribbon.png");
	action_btn_a = loadImageAsset("btn_a_from_right_a.png");
	action_btn_b = loadImageAsset("btn_a_from_right_b.png");
	fillRGB(220, 245, 255);
}

static void mainMenuOnFrame(Game *game, int frame) {

	if (frame < 860) {

		float delta = applyCubicEaseOut(0, 520, frame, 184);
		drawImageAsset(menu_bg, 0, 170 - delta);

		delta = applyBounceEaseOut(390, 690, frame, 160);
		drawImageAsset(cicle, 59 , delta - 135);

		delta = applyBackEaseOut(575, 860, frame, 110);
		drawImageAsset(ribbon, 34 , 95 + (100 - delta));

	} else {

		float delta = applyCubicEaseOut(860, 990, frame, 64);
		if ( frame % 170 >= 100) { 
			drawImageAsset(action_btn_a, 220 - delta , 145);
		} else {
			drawImageAsset(action_btn_b, 220 - delta , 145);
		}

		if ( frame > 990) { 
			setTextRGBColor(61, 140, 222);
			drawText("opções", 184, 147);

			if (game->keyState.a == KEY_IS_RELEASED) {
				showMenu(game);
			}
		}
	}
	
}


static void mainMenuOnExit(Game *game, int frame) {
	unloadImageAsset(menu_bg);
	unloadImageAsset(cicle);
	unloadImageAsset(ribbon);
	unloadImageAsset(action_btn_a);
	unloadImageAsset(action_btn_b);
}

Scene makeMainMenuScene(Game *game){
	Scene mainMenu;
	mainMenu.onEnter = mainMenuOnEnter;
	mainMenu.onFrame = mainMenuOnFrame;
	mainMenu.onExit  = mainMenuOnExit;
	return mainMenu;
}