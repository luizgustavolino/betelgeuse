//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "colors.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

static ALLEGRO_BITMAP *backBuffer = NULL;
extern ALLEGRO_DISPLAY *window;

static int startFrame, closingMenuFrames;
static int pathAsset, pathDenseAsset, abinHeader, aBtnIconA, aBtnIconB;

static optionsDatasource currentDatasource	= NULL;
static optionsCallback currentCallback 		= NULL;
static int currentOptionsCount				= 0;
static int currentOption					= 0;

static int randomTiles[100] = {
	40, 50, 57,  6, 10, 93, 25, 62, 85, 60, 
	80, 21, 76, 94, 67, 92, 74, 63, 79, 88, 
	35, 29, 91, 15, 89, 69,  5, 14, 17,  0, 
	27, 53, 28, 65, 64, 55, 37, 44, 70, 78, 
	 2, 59, 11, 22, 41, 99, 54,  8,  9, 42, 
	48, 51, 86, 97, 81, 24, 20, 52, 77, 39, 
	16,  1, 30, 73, 56, 72, 12,  4, 66, 68, 
	47, 31, 32,  7, 18, 33, 98, 71, 95, 46, 
	58, 38, 61, 75, 43, 82, 84, 87, 23, 19, 
	13, 49, 83, 36,  3, 90, 45, 26, 96, 34
};


void preloadMenuAssets(Game *game) {
	pathAsset 		= loadImageAsset("menu_overlay_path.png");
	pathDenseAsset 	= loadImageAsset("menu_overlay_path_dense.png"); 
	abinHeader 	= loadImageAsset("menu_header_abin.png");
	aBtnIconA	= loadImageAsset("main_a_btn_icon_a.png");
	aBtnIconB	= loadImageAsset("main_a_btn_icon_b.png");
}

void unloadMenuAssets(Game *game) {

	unloadImageAsset(pathAsset);
	unloadImageAsset(pathDenseAsset);
	unloadImageAsset(abinHeader);
	unloadImageAsset(aBtnIconA);
	unloadImageAsset(aBtnIconB);

	if (backBuffer != NULL) {
		al_destroy_bitmap(backBuffer);
		backBuffer = NULL;
	}
}


void closeMenu(Game *game, int optionsCount, optionsDatasource datasource, optionsCallback callback){

}

void showMenu(Game *game, int optionsCount, optionsDatasource datasource, optionsCallback callback){

	game->menuOverlay.visible = true;
	closingMenuFrames = 0;
	currentOption = 0;
	startFrame = game->frame;

	currentDatasource 	= datasource;
	currentCallback 	= callback;
	currentOptionsCount = optionsCount;

	if (pathAsset == 0)  pathAsset = loadImageAsset("menu_overlay_path.png");
	if (abinHeader == 0) abinHeader = loadImageAsset("menu_header_abin.png");

	playSfx(game, "menu_open.wav");

}

void menuOverlayOnFrame(Game *game, int frame){

	if (closingMenuFrames > 0 ) {

		if (--closingMenuFrames == 0) {
			game->menuOverlay.visible = false;
			currentCallback(game, currentOption);
			al_destroy_bitmap(backBuffer);
			backBuffer = NULL;

		} else if (closingMenuFrames == 60) {
			for(int x = 0; x < 11; x++) for(int y = 0; y < 11; y++)
				drawImageAsset(pathAsset, x*20, y*20);

		} else if (closingMenuFrames == 30) {
			for(int x = 0; x < 11; x++) for(int y = 0; y < 11; y++)
				drawImageAsset(pathDenseAsset, x*20, y*20);

		}

		return;
	}

	int localFrame = game->frame - startFrame;
	int totalTiles = 100;
	int index = min(localFrame, totalTiles);
	int showMenuDuration = 180;

	if (index < totalTiles) {

		int currentTile = randomTiles[index];
		int x = currentTile%11;
		int y = currentTile/11;
		drawImageAsset(pathAsset, x*20, y*20);

	} else if (localFrame < totalTiles + showMenuDuration) {

		if (backBuffer == NULL) backBuffer = al_clone_bitmap(al_get_backbuffer(window));

		int width 	= game->screenSetup.width;
		int height 	= game->screenSetup.height;

		int dx 	= game->screenSetup.fullscreen_dx;
		int dy 	= game->screenSetup.fullscreen_dy;
		int scale   = game->screenSetup.scaleFactor;

		al_draw_scaled_bitmap(backBuffer, dx, dy, width*scale, height*scale,
										  0, 0, width, height, 0);

		int inner_height = 27 * currentOptionsCount + 10;
		int delta = 160 - applyCubicEaseOut(totalTiles, totalTiles + showMenuDuration, localFrame, 160);

		drawRect((Rect){42, 28 + delta, 136, 21 + inner_height}, C_GRAY);
		drawRect((Rect){41, 27 + delta, 136, 21 + inner_height}, C_LIGHT_BLUE);
		
		drawRect((Rect){42, 28 + delta, 134,  16}, C_GRAY);
		drawRect((Rect){42, 45 + delta, 134, inner_height + 2}, C_GRAY);

		drawRect((Rect){43, 29 + delta, 133,  15}, C_BLACK);
		drawRect((Rect){43, 46 + delta, 133, inner_height + 1}, C_BLACK);
		
		drawImageAsset(abinHeader, 46, 32 + delta);

		setTextRGBColor(220, 245, 255);
		for (int i = 0; i < currentOptionsCount; i ++){
			drawText(currentDatasource(game, i), 58, 59 + i * 27 + delta);
			drawLine((Point){ 54, 56 + i * 27 + delta}, (Point){146, 56 + i * 27 + delta}, C_GRAY);
			drawLine((Point){ 53, 57 + i * 27 + delta}, (Point){ 53, 71 + i * 27 + delta}, C_GRAY);
			drawLine((Point){147, 57 + i * 27 + delta}, (Point){147, 71 + i * 27 + delta}, C_GRAY);
			drawLine((Point){ 54, 72 + i * 27 + delta}, (Point){146, 72 + i * 27 + delta}, C_GRAY);
		}

	} else if (localFrame > 110) {

		for (int i = 0; i < currentOptionsCount; i ++){

			Color strokeColor;

			if (currentOption == i) {
				int asset = localFrame % 120 > 60 ? aBtnIconA : aBtnIconB;
				drawImageAsset(asset, 151, 56 + i * 27);
				strokeColor = C_BLUE;
			} else {
				drawRect((Rect){151, 56 + i * 27, 15, 15}, C_BLACK);
				strokeColor = C_GRAY;
			}

			drawLine((Point){ 54, 56 + i * 27}, (Point){146, 56 + i * 27}, strokeColor);
			drawLine((Point){ 53, 57 + i * 27}, (Point){ 53, 71 + i * 27}, strokeColor);
			drawLine((Point){147, 57 + i * 27}, (Point){147, 71 + i * 27}, strokeColor);
			drawLine((Point){ 54, 72 + i * 27}, (Point){146, 72 + i * 27}, strokeColor);
		}

		if (game->keyState.down == KEY_IS_RELEASED && currentOption < currentOptionsCount - 1){
			currentOption += 1;
			playSfx(game, "menu_up_down.wav");
		} else if (game->keyState.up == KEY_IS_RELEASED && currentOption > 0) {
			currentOption -= 1;
			playSfx(game, "menu_up_down.wav");
		} else if (game->keyState.a == KEY_IS_RELEASED) {
			closingMenuFrames = 90;
			playSfx(game, "menu_a.wav");
		}

	}

}
