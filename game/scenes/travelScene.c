//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "travelScene.h"
#include "missScene.h"
#include "cityScene.h"

#include "../engine/colors.h"

static int fromCity,toCity,jet,jet1,jet2,jet3; //Assets
static char *fromLabel,*toLabel;
static float delta, increment, flyPosHor, flyPosVer, bgPos;
static int width, flightTime, airplaneInOutTime; //Animation parameters

static void travelOnEnter(Game *game, int frame) {

    int current = game->gameplayContext.currentCity;
    fromLabel = game->gameplayContext.cities[current].imageName;

    //Checks what choice the player made
    toLabel = game->gameplayContext.cities[current].destinations[game->gameplayContext.playerDestinationChoice].imageName;

	jet1	    = loadImageAsset("jet1.png");
	jet2	    = loadImageAsset("jet2.png");
	jet3        = loadImageAsset("jet3.png");

	fromCity    = loadImageAsset(fromLabel);
	toCity      = loadImageAsset(toLabel);

    flyPosHor = 60; //Jet horizontal position
    flyPosVer = 60; //Jet vertical position
	bgPos = 0; //Background position
	width = 220; //Screen width
	airplaneInOutTime = 320; //Time in frames, can be adjusted to match sound. Declared as float for animation purposes
    flightTime = 1220; //Time in frames, can be adjusted to match sound. Declared as float for animation purposes

    increment = (float)width / ((float)flightTime - (float)airplaneInOutTime); //Increment for the background position

}

static void travelOnFrame(Game *game, int frame) {

	if (frame == 1) fillRGB(game, BLACK);

    if (frame < airplaneInOutTime){
        delta = applyCubicEaseInOut(0, airplaneInOutTime, frame, 145);

        //Draw assets
        drawImageAsset(fromCity, 0, 0);
        drawImageAsset(jet1, delta - flyPosHor, flyPosVer);
    }

    if (frame == airplaneInOutTime) flyPosHor = delta - flyPosHor; //Determines the horizontal position of the jet animation
    if (frame > airplaneInOutTime && frame <= flightTime){
        if (frame % 600 >= 0 && frame % 600 < 270) {
            jet = jet1;
        } else if (frame % 600 >= 270 && frame % 600 < 300) {
            jet = jet2;
        } else if (frame % 600 >= 300 && frame % 600 < 570) {
            jet = jet3;
        } else if (frame % 600 >= 570 && frame % 600 < 600) {
            jet = jet2;
        }
        //Draw assets
        drawImageAsset(fromCity, 0 - bgPos,0);
        drawImageAsset(toCity, width - bgPos,0);
        drawImageAsset(jet, flyPosHor, flyPosVer);

        if(bgPos < width) bgPos = bgPos + increment;
    }

    if (frame > flightTime && frame <= flightTime + airplaneInOutTime){
        delta = applyCubicEaseInOut(flightTime, flightTime + airplaneInOutTime, frame, 145);
        drawImageAsset(toCity, 0, 0);
        drawImageAsset(jet, delta + flyPosHor, flyPosVer);
    }

    if (frame > flightTime + airplaneInOutTime){
        if (game->gameplayContext.playerDestinationChoice == 0){
            changeScene(game, makeCityScene(game));
        } else {
            changeScene(game, makeMissScene(game));
        }
    }
}

static void travelOnExit(Game *game, int frame) {

	unloadImageAsset(jet1);
	unloadImageAsset(jet2);
	unloadImageAsset(jet3);
	unloadImageAsset(fromCity);
	unloadImageAsset(toCity);
}


Scene makeTravelScene(Game *game){
	Scene travel;
	travel.onEnter = travelOnEnter;
	travel.onFrame = travelOnFrame;
	travel.onExit  = travelOnExit;
	return travel;
}

