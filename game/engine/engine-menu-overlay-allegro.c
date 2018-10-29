//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

#ifdef ENGINE_ALLEGRO

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

static int startFrame;
static int pathAsset = 0;

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

void showMenu(Game *game){

	game->menuOverlay.visible = true;
	startFrame = game->frame;

	if (pathAsset == 0) pathAsset = loadImageAsset("menu_overlay_path.png");

}

void menuOverlayOnFrame(Game *game, int frame){

	int localFrame = game->frame - startFrame;
	int index = localFrame/2;

	if (index < 100) {
		int currentTile = randomTiles[index];
		int x = currentTile%11;
		int y = currentTile/11;
		drawImageAsset(pathAsset, x*20, y*20);
	}
}

#endif