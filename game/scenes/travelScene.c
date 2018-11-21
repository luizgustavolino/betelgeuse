//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "travelScene.h"

#include "../engine/colors.h"

//Input 1,2,3 or 4
//1 Leads to the next LEVEL
//2,3 or 4 have the "Go back" option

static int fromCity,toCity,jet,jet1,jet2,jet3;
char *fromLabel,*toLabel;
float delta;
static float fly = 60, pan = 0;

static int flightTime = 1400; //Can be adjusted to match the music

static void travelOnEnter(Game *game, int frame) {

    int current = game->gameplayContext.currentCity;
    fromLabel = game->gameplayContext.cities[current].imageName;

    //Checks what choice the player made
    toLabel = game->gameplayContext.cities[0].destinations[game->gameplayContext.playerDestinationChoice].imageName;

	jet1	    = loadImageAsset("jet1.png");
	jet2	    = loadImageAsset("jet2.png");
	jet3        = loadImageAsset("jet3.png");

	fromCity    = loadImageAsset(fromLabel);
	toCity      = loadImageAsset(toLabel);

}

static void travelOnFrame(Game *game, int frame) {

	if (frame == 1) fillRGB(game, BLACK);

    if (frame <= 100){
        delta = applyCubicEaseOut(60, 100, frame, 70);
        drawImageAsset(fromCity, 0, 0);
        drawImageAsset(jet1, delta - fly, 60);
    }

    if (frame == 100) fly = delta - fly; //Determines the starting position of the jet animation
    if (frame > 100 && frame <= flightTime){
        if (frame % 600 >= 0 && frame % 600 < 270) {
            jet = jet1;
        } if (frame % 600 >= 270 && frame % 600 < 300) {
            jet = jet2;
        } if (frame % 600 >= 300 && frame % 600 < 570) {
            jet = jet3;
        } if (frame % 600 >= 570 && frame % 600 < 600) {
            jet = jet2;
        }
        drawImageAsset(fromCity, 0 - pan,0);
        drawImageAsset(toCity, 220 - pan,0);
        drawImageAsset(jet, fly, 60);
        //x-position of the jet
        fly = fly + 0.12;

        if(pan < 220) pan = pan + 0.20;
    }

    if (frame > flightTime && frame < flightTime + 40){
        delta = applyCubicEaseOut(flightTime, flightTime + 40, frame, 70);
        drawImageAsset(toCity, 0, 0);
        drawImageAsset(jet, delta + fly, 60);
    }

//    if (frame > flightTime + 40){
//        changeScene(game, makeCityScene(game));
//    }
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

