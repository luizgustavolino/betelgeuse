//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "cityScene.h"
#include "destinationsScene.h"
#include "hintsScene.h"
#include "finalScene.h"
#include "mainMenuScene.h"

#include "../engine/colors.h"

// ### Declarações de variáveis e funções

static int current_page;


static int abin_bg;

static int city_foreground, city_background;
static int action_btn_a, action_btn_b;
static int page_off, page_on;

static void drawInterface(Game *game, int frame);
static void drawPage(Game *game, int pageNum);

static char* menuOptionsDatasource(Game *game, int option);
static void menuCallback(Game *game, int choosenOption);

// ### Ciclo de vida da cena

static void cityOnEnter(Game *game, int frame) {

	//***CHECKS FOR END OF GAME***//
	// - LOSE: if current time bigger than limit
	if (game->gameplayContext.currentTime >= WORKING_HOURS_IN_DAY * WORKING_DAYS) {
		changeScene(game, makeFinalScene(game));
		return;
	}

	// - WIN: if current city is the last city
	if (game->gameplayContext.playerDestinationChoice == 0 && game->gameplayContext.currentCity == CITIES_UNTIL_VICTORY - 1){
        changeScene(game, makeFinalScene(game));
        return;
    }

    //***LOADS NEXT LEVEL***//

    if (game->gameplayContext.playerDestinationChoice == 0 && game->gameplayContext.currentCity == 0){
        game->gameplayContext.currentCity = game->gameplayContext.currentCity + 1;
        loadGameLevel(game, LEVEL_2);
    }

    else if (game->gameplayContext.playerDestinationChoice == 0 && game->gameplayContext.currentCity == 1){
        game->gameplayContext.currentCity = game->gameplayContext.currentCity + 1;
        loadGameLevel(game, LEVEL_3);
    }

    //***NEW LEVEL LOADED***//

	int current     = game->gameplayContext.currentCity;
	char *background_image = game->gameplayContext.cities[current].smallImageName;
	city_background = loadImageAsset(background_image);

	abin_bg = loadImageAsset("abin_pc_bg.png");
	city_foreground = loadImageAsset("city_foreground.png");
	current_page = 0;

	action_btn_a = loadImageAsset("btn_a_from_right_a.png");
	action_btn_b = loadImageAsset("btn_a_from_right_b.png");

	page_off = loadImageAsset("page_indic_off.png");
	page_on = loadImageAsset("page_indic_on.png");

	//playSoundtrack(game, "intro.wav");
}

static void cityOnFrame(Game *game, int frame) {

	// desenha a interface e fundo
	drawInterface(game, frame);

	// desenhando texto da cidade
	drawPage(game, current_page);

	// desenhando hora
	drawTime(game->gameplayContext.currentTime);

	// botão de opções
	setTextRGBColor(BLUE);
  	drawText("opções", 130, 153);
  	if ( frame % 170 >= 100) drawImageAsset(action_btn_a, 103, 147);
  	else drawImageAsset(action_btn_b, 103, 147);

  	// indicador de página
  	for (int i = 0; i < 3; i++) {
  		if (i == current_page) drawImageAsset(page_on, 188+(7*i), 143);
  		else drawImageAsset(page_off, 188+(7*i), 143);
  	}

  	// input: troca de página
	if (game->keyState.right == KEY_IS_RELEASED && current_page < 2) current_page++;
	if (game->keyState.left  == KEY_IS_RELEASED && current_page > 0) current_page--;
	if (game->keyState.a     == KEY_IS_RELEASED) showMenu(game, 4, menuOptionsDatasource, menuCallback);

}

static void cityOnExit(Game *game, int frame) {

	unloadImageAsset(city_background);
	unloadImageAsset(city_foreground);

	unloadImageAsset(action_btn_a);
	unloadImageAsset(action_btn_b);
	unloadImageAsset(page_off);
	unloadImageAsset(page_on);
}


// ### Funções de apoio

// desenha a interface e fundo
static void drawInterface(Game *game, int frame){

	drawImageAsset(city_background, 9, 33);
	//drawImageAsset(abin_bg, 0, 0);

	drawImageAsset(city_foreground, 0, 0);
}

static void drawPage(Game *game, int pageNum){

	int current = game->gameplayContext.currentCity;

	setTextRGBColor(YELLOW);
	drawText(game->gameplayContext.cities[current].name, 85, 11);

	setTextRGBColor(LIGHT_BLUE);
	drawText(game->gameplayContext.cities[current].flavorText[current_page], 107, 37);

}

// #-- Menu options & callbacks
#define CITY_MENU_OPT_INVESTIGATE 		0
#define CITY_MENU_OPT_FLY 				1
#define CITY_MENU_OPT_ABORT 			2
#define CITY_MENU_OPT_BACK				3

char* menuOptionsDatasource(Game *game, int option){
	switch (option) {
		case CITY_MENU_OPT_INVESTIGATE: return "Investigar";
		case CITY_MENU_OPT_FLY: return "Viajar";
		case CITY_MENU_OPT_ABORT: return "Abortar";
		case CITY_MENU_OPT_BACK: return "Voltar";
		default: return NULL;
	}
}

void menuCallback(Game *game, int choosenOption) {
	switch (choosenOption) {
		case CITY_MENU_OPT_INVESTIGATE:
		    changeScene(game, makeHintsScene(game));
			break;
		case CITY_MENU_OPT_FLY:
			changeScene(game, makeDestinationsScene(game));
			break;
		case CITY_MENU_OPT_ABORT:
			changeScene(game, makeMainMenuScene(game));
			break;
		case CITY_MENU_OPT_BACK:
			break;
		default: break;
	}
}


Scene makeCityScene(Game *game) {
	Scene city;
	city.onEnter = cityOnEnter;
	city.onFrame = cityOnFrame;
	city.onExit  = cityOnExit;
	return city;
}
