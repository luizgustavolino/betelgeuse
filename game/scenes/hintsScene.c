//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "time.h"
#include "hintsScene.h"
#include "cityScene.h"


#include "../engine/colors.h"

static void drawInterface(Game *game, int completion, int frame);
static void drawTime(int day, int hour, int minute);

static int abin_bg, panorama, place_name, place_eta;
static int select_left, select_right;
static int pano_pin, pano_pin_gray, placePin_x[3], placePin_y[3], loc_x[5], loc_y[5];
static int instructions;

static int rewindFrames = 0;
static int currentPlace = 0;

static void hintsOnEnter(Game *game, int frame) {

	abin_bg = loadImageAsset("abin_pc_bg.png");
	panorama = loadImageAsset("car_map.png");
	place_name = loadImageAsset("jet_destiny_name.png");
	place_eta  = loadImageAsset("jet_destiny_eta.png");
	select_left  = loadImageAsset("jet_select_l.png");
	select_right = loadImageAsset("jet_select_r.png");
	pano_pin = loadImageAsset("pano_pin.png");
	pano_pin_gray = loadImageAsset("pano_pin_gray.png");
	instructions = loadImageAsset("jet_instructions.png");

	if (game->randomize.notRandom){

        int pos_x[8] = {10, 22, 34, 46, 58, 70, 82, 94}; //No specific locations. The purpose is purely aesthetic
        int pos_y[8] = {10, 22, 34, 46, 58, 70, 82, 94}; //No specific locations. The purpose is purely aesthetic

        srand(time(NULL));
        for(int i = 7; i > 0; i--) {
            int j = rand() % (i+1);
            swap(&pos_x[i], &pos_x[j]);
            j = rand() % (i+1);
            swap(&pos_y[i], &pos_y[j]);
        }

        //Preenche os vetores de local
        for(int i = 0; i < 5; i++){
            if (i < 3){
                placePin_x[i] = pos_x[i];
                placePin_y[i] = pos_y[i] + 30;
            }
            loc_x[i] = pos_x[i+3];
            loc_y[i] = pos_y[i+3] + 30;
        }
        game->randomize.notRandom = false;
	}
}

static void hintsOnFrame(Game *game, int frame) {

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
	drawText("ABIN ROTAS 3D", 85, 11);

	int current = game->gameplayContext.currentCity;
	Place place = game->gameplayContext.cities[current].pointsOfInterest[currentPlace];

	drawTime(game->gameplayContext.currentTime.dayOfWeek,
			 game->gameplayContext.currentTime.hour,
			 game->gameplayContext.currentTime.minutes);

	if (rewindFrames) return;

	if (frame >  80*3) {
		setTextRGBColor(LIGHT_BLUE);
		drawCentralizedText(place.name, 167, 48);
	}

	if (frame >  80*4) {

		drawImageAsset(select_left,  111 + ((frame/30) % 3), 50);
		drawImageAsset(select_right, 214 - ((frame/30) % 3), 50);

		if (rewindFrames == 0 && game->keyState.b == KEY_IS_RELEASED){
            game->gameplayContext.playerDestinationChoice = 1; //Prevents cityScene to load a new level
			rewindFrames = 200;
		}

		else if (game->keyState.a == KEY_IS_RELEASED) {
            //Shows hint popup
		}
	}

	if (frame >  80*5) {

		setTextRGBColor(RED);
		int minutes = place.minutesRequired % 60;
		int hours   = place.minutesRequired / 60;

		char buffer[12];
  		sprintf(buffer, "+%02dh%02d", hours, minutes);
		drawCentralizedText(buffer, 186, 75);

		if (game->keyState.right == KEY_IS_RELEASED)
			currentPlace = (currentPlace + 1) % POINTS_OF_INTEREST_COUNT;
		if (game->keyState.left  == KEY_IS_RELEASED)
			currentPlace = (currentPlace + POINTS_OF_INTEREST_COUNT - 1) % POINTS_OF_INTEREST_COUNT;

	}

}

static void hintsOnExit(Game *game, int frame) {
	unloadImageAsset(abin_bg);
}

static void drawInterface(Game *game, int completion, int frame){

	int current = game->gameplayContext.currentCity;
	Place place = game->gameplayContext.cities[current].pointsOfInterest[currentPlace];

	drawImageAsset(abin_bg, 0, 0);
	if (completion > 30) drawImageAsset(panorama, 7, 31);

	if (completion > 40 && completion <= 240) {
        int i;
        float delta;
        for (i=0; i<8; i++) {
            if (i > 2) {
                delta = applyBounceEaseOut(completion + i*5, completion + 180 + i*5, frame, 180);
                drawImageAsset(pano_pin_gray, loc_x[i-3], delta - loc_y[i-3]);
            } else {
                delta = applyBounceEaseOut(completion + i*5, completion + 180 + i*5, frame, 180);
                drawImageAsset(pano_pin_gray, placePin_x[i], delta - placePin_y[i]);
            }
        }
    }

    if (completion > 240) {
        int i;
		for (i=0; i<8; i++) {
            if (i > 2) {
                drawImageAsset(pano_pin_gray, loc_x[i-3], 180 - loc_y[i-3]);
            } else if (i < 3 && i != currentPlace) {
                drawImageAsset(pano_pin_gray, placePin_x[i], 180 - placePin_y[i]);
            }

            if (frame % 180 > 0 && frame % 180 < 90) {
                drawImageAsset(pano_pin, placePin_x[currentPlace], 180 - placePin_y[currentPlace]);
            } else {
                drawImageAsset(pano_pin, placePin_x[currentPlace], 178 - placePin_y[currentPlace]);
            }
        }
	}

		drawImageAsset(instructions, 146, 129);

		setTextRGBColor(LIGHT_BLUE);
		drawText("confirma", 164, 131);
		drawText("cancela", 164, 149);

	if (completion >  60) drawImageAsset(place_name, 108, 38);
	if (completion >  90) drawImageAsset(place_eta, 158, 65);
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

Scene makeHintsScene(Game *game){
	Scene hints;
	hints.onEnter = hintsOnEnter;
	hints.onFrame = hintsOnFrame;
	hints.onExit  = hintsOnExit;
	return hints;
}
