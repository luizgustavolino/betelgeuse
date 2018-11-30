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
static void drawHint(Game *game, int startFrame, int frame);
static void drawTime(int day, int hour, int minute);

static int abin_bg, city_image, city_box, place_name, place_eta, hint_text_bg, hint_face;
static int select_left, select_right, action_btn_a, action_btn_b;
static int loc_pin, loc_pin_gray;
static int instructions;

static int rewindFrames = 0;
static int startFrame;
static int currentPlace = 0;
bool showCurrentHint;

static void hintsOnEnter(Game *game, int frame) {

    showCurrentHint = game->hint.showHint;

	abin_bg = loadImageAsset("abin_pc_bg.png");
	city_box = loadImageAsset("city_box.png");
	//panorama = loadImageAsset("panoramas/pano_campogrande.png");
	int current     = game->gameplayContext.currentCity;
	char *city_image_label = game->gameplayContext.cities[current].imageName;
	city_image = loadImageAsset(city_image_label);
	place_name = loadImageAsset("jet_destiny_name.png");
	place_eta  = loadImageAsset("jet_destiny_eta.png");
	select_left  = loadImageAsset("jet_select_l.png");
	select_right = loadImageAsset("jet_select_r.png");
	loc_pin = loadImageAsset("loc_pin.png");
	loc_pin_gray = loadImageAsset("loc_pin_gray.png");
	instructions = loadImageAsset("jet_instructions.png");
	hint_text_bg = loadImageAsset("hint_text_bg.png");
	hint_face = loadImageAsset("hint_face.png");
	action_btn_a = loadImageAsset("btn_a_from_right_a.png");
	action_btn_b = loadImageAsset("btn_a_from_right_b.png");
}

static void hintsOnFrame(Game *game, int frame) {

    if (showCurrentHint == false) {

        if (rewindFrames > 0) {

            drawInterface(game, (rewindFrames--)/2, frame);
            if (rewindFrames == 1){
                changeScene(game, makeCityScene(game));
                return;
            }

        } else {
            drawInterface(game, frame/2, frame);
        }

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
                startFrame = frame;
                showCurrentHint = true;
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

    } if (showCurrentHint == false) { //Wipes the instructions when the hints show
        drawImageAsset(instructions, 146, 129);

        setTextRGBColor(LIGHT_BLUE);
        drawText("confirma", 164, 131);
        drawText("cancela", 164, 149);

    } if (showCurrentHint) {
        drawHint(game, startFrame, frame);
	}
}

static void hintsOnExit(Game *game, int frame) {
	unloadImageAsset(abin_bg);
}

static void drawInterface(Game *game, int completion, int frame){

	int current = game->gameplayContext.currentCity;

	drawImageAsset(abin_bg, 0, 0);
	if (completion > 30) drawImageAsset(city_box, 7, 31), drawImageAsset(city_image, 8, 36);

	setTextRGBColor(YELLOW);
    drawText("ABIN PANORAMA", 85, 11);

	if (completion > 40 && completion <= 240) {
        int i;
        float delta;
        for (i = 0; i < POINTS_OF_INTEREST_COUNT; i++) {
            Place p = game->gameplayContext.cities[current].pointsOfInterest[i];
            delta = applyBounceEaseOut(completion + i*5, completion + 180 + i*5, frame, 180);
            int loc_x = p.pinX;
			int loc_y = p.pinY;
//			int loc_x = 56;
//			int loc_y = 60;
            drawImageAsset(loc_pin_gray, loc_x, delta - loc_y);
        }
    }

    if (completion > 240) {
        int i;
		for (i = 0; i < POINTS_OF_INTEREST_COUNT; i++) {
            Place p = game->gameplayContext.cities[current].pointsOfInterest[i];
            int loc_x = p.pinX;
			int loc_y = p.pinY;
//          int loc_x = 94;
//			int loc_y = 92;
            if (i != currentPlace) drawImageAsset(loc_pin_gray, loc_x, 180 - loc_y);
		}

        Place p = game->gameplayContext.cities[current].pointsOfInterest[currentPlace];
        int loc_x = p.pinX;
        int loc_y = p.pinY;
        if (frame % 180 > 0 && frame % 180 < 90) {
            drawImageAsset(loc_pin, loc_x, 180 - loc_y);
        } else {
            drawImageAsset(loc_pin, loc_x, 178 - loc_y);
        }
	}

    if (completion >  60) drawImageAsset(place_name, 108, 38);
    if (completion >  90) drawImageAsset(place_eta, 158, 65);
}

static void drawHint(Game *game, int startFrame, int frame){

    int localFrame = frame - startFrame;

	int current = game->gameplayContext.currentCity;
	Place place = game->gameplayContext.cities[current].pointsOfInterest[currentPlace];

    setTextRGBColor(LIGHT_BLUE);
	drawImageAsset(hint_text_bg, 15, 38);
	drawText(place.hint, 21, 48);

	if (localFrame > 100) drawImageAsset(hint_face, 30, 98);

    if (localFrame > 170){
        float delta = applyCubicEaseOut(170, 300, localFrame, 70);
		if (localFrame % 170 >= 100) {
			drawImageAsset(action_btn_a, 220 - delta , 145);
		} else {
			drawImageAsset(action_btn_b, 220 - delta , 145);
		} if (localFrame > 300) {
            setTextRGBColor(61, 140, 222);
			drawText("voltar", 178, 150);

        } if (game->keyState.a == KEY_IS_RELEASED) {
            showCurrentHint = false;
        }
    }
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
