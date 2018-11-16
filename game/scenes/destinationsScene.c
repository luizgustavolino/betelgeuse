//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "destinationsScene.h"
#include "cityScene.h"

#include "../engine/colors.h"

static void drawInterface(Game *game, int completion);
static void drawTime(int day, int hour, int minute);

static int abin_bg, map, destiny_name, destiny_eta;
static int select_left, select_right;

static int rewindFrames = 0;

static void destinationsOnEnter(Game *game, int frame) {
	abin_bg = loadImageAsset("abin_pc_bg.png");
	map = loadImageAsset("jet_map.png");
	destiny_name = loadImageAsset("jet_destiny_name.png");
	destiny_eta  = loadImageAsset("jet_destiny_eta.png");
	select_left  = loadImageAsset("jet_select_l.png");
	select_right = loadImageAsset("jet_select_r.png");
}

static void destinationsOnFrame(Game *game, int frame) {

	if (rewindFrames > 0) {
		
		drawInterface(game, (rewindFrames--)/2);
		if (rewindFrames == 1){
			changeScene(game, makeCityScene(game));
			return;
		}

	} else {
		drawInterface(game, frame/2);	
	}

	setTextRGBColor(YELLOW);
	drawText("Viajar pela ABIN JET", 85, 11);

	drawTime(game->gameplayContext.currentTime.dayOfWeek,
			 game->gameplayContext.currentTime.hour,
			 game->gameplayContext.currentTime.minutes);

	if (rewindFrames) return;

	if (frame >  80*3) {
		setTextRGBColor(LIGHT_BLUE);
		drawCentralizedText("MANAUS", 169, 52);
	}

	if (frame >  80*4) {
		drawImageAsset(select_left,  118 + ((frame/30) % 3), 54);
		drawImageAsset(select_right, 214 - ((frame/30) % 3), 54);

		if (rewindFrames == 0 && game->keyState.b == KEY_IS_RELEASED){
			rewindFrames = 200;
		}
	}

	if (frame >  80*5) {
		setTextRGBColor(RED);
		drawCentralizedText("+ 6h00", 190, 79);
	}
}

static void destinationsOnExit(Game *game, int frame) {
	unloadImageAsset(abin_bg);
}

static void drawInterface(Game *game, int completion){
	drawImageAsset(abin_bg, 0, 0);
	if (completion >  30) drawImageAsset(map, 7, 31);
	if (completion >  60) drawImageAsset(destiny_name, 115, 42);
	if (completion >  90) drawImageAsset(destiny_eta, 163, 69);
}

static void drawTime(int day, int hour, int minute){

	char buffer[16];
	char* dayAsText;

	switch(day) {
		case WEEKDAY_MON: dayAsText = "SEG"; break;
		case WEEKDAY_TUE: dayAsText = "TER"; break;
		case WEEKDAY_WED: dayAsText = "QUA"; break;
		case WEEKDAY_THU: dayAsText = "QUI"; break;
		case WEEKDAY_FRI: dayAsText = "SEX"; break;
		default: break;
	}

  	sprintf(buffer, "%s - %02dh%02d", dayAsText, hour, minute);
  	setTextRGBColor(YELLOW);
  	drawText(buffer, 11, 11);
}

Scene makeDestinationsScene(Game *game){
	Scene destinations;
	destinations.onEnter = destinationsOnEnter;
	destinations.onFrame = destinationsOnFrame;
	destinations.onExit  = destinationsOnExit;
	return destinations;
}
