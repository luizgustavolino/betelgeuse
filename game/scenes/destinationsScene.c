//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "destinationsScene.h"
#include "cityScene.h"

#include "../engine/colors.h"

static void drawInterface(Game *game, int completion, int frame);
static void drawTime(int day, int hour, int minute);

static int abin_bg, map, destiny_name, destiny_eta;
static int select_left, select_right;
static int current_city_pin, d_city_pin;
static int t_city_pin_a, t_city_pin_b;
static int instructions;

static int rewindFrames = 0;
static int currentDestination = 0;

static void destinationsOnEnter(Game *game, int frame) {

	abin_bg = loadImageAsset("abin_pc_bg.png");
	map = loadImageAsset("jet_map.png");
	destiny_name = loadImageAsset("jet_destiny_name.png");
	destiny_eta  = loadImageAsset("jet_destiny_eta.png");
	select_left  = loadImageAsset("jet_select_l.png");
	select_right = loadImageAsset("jet_select_r.png");
	current_city_pin = loadImageAsset("jet_current_city_pin.png");
	d_city_pin 	 = loadImageAsset("jet_d_city_pin.png");
	t_city_pin_a = loadImageAsset("jet_t_city_pin_a.png");
	t_city_pin_b = loadImageAsset("jet_t_city_pin_b.png");
	instructions = loadImageAsset("jet_instructions.png");
}

static void destinationsOnFrame(Game *game, int frame) {

	if (rewindFrames > 0) {
		
		drawInterface(game, (rewindFrames--)/2, frame);
		if (rewindFrames == 1){
			changeScene(game, makeCityScene(game));
			return;
		}

	} else {
		drawInterface(game, frame/2, frame);	
	}

	setTextRGBColor(YELLOW);
	drawText("Viajar pela ABIN JET", 85, 11);

	int current = game->gameplayContext.currentCity;
	Destination destination = game->gameplayContext.cities[current].destinations[currentDestination];

	int currentCity = game->gameplayContext.currentCity;
	City city = game->gameplayContext.cities[currentCity];

	drawTime(game->gameplayContext.currentTime.dayOfWeek,
			 game->gameplayContext.currentTime.hour,
			 game->gameplayContext.currentTime.minutes);

	if (rewindFrames) return;

	if (frame >  80*3) {
		setTextRGBColor(LIGHT_BLUE);
		drawCentralizedText(destination.name, 167, 48);
	}

	if (frame >  80*4) {

		drawImageAsset(select_left,  111 + ((frame/30) % 3), 50);
		drawImageAsset(select_right, 214 - ((frame/30) % 3), 50);

		if (rewindFrames == 0 && game->keyState.b == KEY_IS_RELEASED){
			rewindFrames = 200;
		}
	}

	if (frame >  80*5) {

		setTextRGBColor(RED);
		int minutes = destination.minutesRequired % 60;
		int hours   = destination.minutesRequired / 60;

		char buffer[12];
  		sprintf(buffer, "+%02dh%02d", hours, minutes);
		drawCentralizedText(buffer, 186, 75);

		if (game->keyState.right == KEY_IS_RELEASED)
			currentDestination = (currentDestination + 1)%DESTINATIONS_COUNT;
		if (game->keyState.left  == KEY_IS_RELEASED)
			currentDestination = (currentDestination + DESTINATIONS_COUNT - 1)%DESTINATIONS_COUNT;

	}

}

static void destinationsOnExit(Game *game, int frame) {
	unloadImageAsset(abin_bg);
}

static void drawInterface(Game *game, int completion, int frame){

	int current = game->gameplayContext.currentCity;
	Destination destination = game->gameplayContext.cities[current].destinations[currentDestination];

	int currentCity = game->gameplayContext.currentCity;
	City city = game->gameplayContext.cities[currentCity];

	drawImageAsset(abin_bg, 0, 0);
	if (completion > 30) drawImageAsset(map, 7, 31);

	if (completion > 40) {

		// Transferencia de equação da reta:
		// lat/lon: {-69.58, -0.86}  / {-48.48, -27.44}
		// x/y:     {    21,    56}  / {    85,    146}

		int loc_x = (int) (city.longitude *  3.03) + 232.048;
		int loc_y = (int) (city.latitude  * -3.38) +  55.008;
		drawImageAsset(current_city_pin, loc_x - 2, loc_y - 2);

		drawImageAsset(instructions, 146, 129);

		setTextRGBColor(LIGHT_BLUE);
		drawText("confirma", 164, 131);
		drawText("cancela", 164, 149);
	}

	if (completion > 50) {

		for (int i = 0; i < DESTINATIONS_COUNT; i++) {
			Destination d = game->gameplayContext.cities[current].destinations[i];
			int loc_x = (int) (d.longitude *  3.03) + 232.048;
			int loc_y = (int) (d.latitude  * -3.38) +  55.008;
			if (i != currentDestination) drawImageAsset(d_city_pin, loc_x - 2, loc_y - 2);
		}

		Destination d = game->gameplayContext.cities[current].destinations[currentDestination];
		int loc_x = (int) (d.longitude *  3.03) + 232.048;
		int loc_y = (int) (d.latitude  * -3.38) +  55.008;
		drawImageAsset( frame % 180 > 90 ? t_city_pin_a : t_city_pin_b, loc_x - 12, loc_y - 12);

	}

	if (completion >  60) drawImageAsset(destiny_name, 108, 38);
	if (completion >  90) drawImageAsset(destiny_eta, 158, 65);
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
