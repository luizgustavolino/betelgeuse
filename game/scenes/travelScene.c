//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "travelScene.h"
#include "cityScene.h"

#include "../engine/colors.h"

static void drawMessage(Game *game, int startFrame, int frame);

static int fromCity,toCity,jet,jet1,jet2,jet3,hint_text_bg,hint_face,action_btn_a,action_btn_b; //Assets
static int startFrame;
static char *fromLabel,*toLabel;
static float delta, increment, flyPosHor, flyPosVer, bgPos;
static int width, flightTime, airplaneInOutTime; //Animation parameters
bool flyForward;
static int currentTime, minutesRequired;
static int overlay;
static int targetTime;

static void travelOnEnter(Game *game, int frame) {

    currentTime = game->gameplayContext.currentTime;
    int playerChoice = game->gameplayContext.playerDestinationChoice;
    minutesRequired = game->gameplayContext.cities[game->gameplayContext.currentCity].destinations[playerChoice].minutesRequired;
    targetTime = game->gameplayContext.currentTime + minutesRequired;

    hint_text_bg = loadImageAsset("hint_text_bg.png");
    hint_face = loadImageAsset("hint_face.png");
    action_btn_a = loadImageAsset("btn_a_from_right_a.png");
	action_btn_b = loadImageAsset("btn_a_from_right_b.png");
    overlay = loadImageAsset("jet_overlay.png");

    flyForward = game->travel.travelForward;
    int current = game->gameplayContext.currentCity;
    fromLabel = game->gameplayContext.cities[current].imageName;

    playSfx(game, "plane.wav");

    //Checks what choice the player made
    toLabel = game->gameplayContext.cities[current].destinations[game->gameplayContext.playerDestinationChoice].imageName;

    flyPosVer = 60; //Jet vertical position
    bgPos = 0; //Background position
    width = 220; //Screen width
    airplaneInOutTime = 320; //Time in frames, can be adjusted to match sound. Declared as float for animation purposes
    flightTime = 1220; //Time in frames, can be adjusted to match sound. Declared as float for animation purposes
    increment = (float)width / ((float)flightTime - (float)airplaneInOutTime); //Increment for the background position

    if(flyForward){
        playSoundtrack(game, game->gameplayContext.cities[game->gameplayContext.currentCity].destinations[playerChoice].ost);
    } else{
        playSoundtrack(game, game->gameplayContext.cities[game->gameplayContext.currentCity].ost);
    }

    if (flyForward){

        jet1	    = loadImageAsset("jet1.png");
        jet2	    = loadImageAsset("jet2.png");
        jet3        = loadImageAsset("jet3.png");

        fromCity    = loadImageAsset(fromLabel);
        toCity      = loadImageAsset(toLabel);

        flyPosHor = 60; //Jet horizontal position

    } else {

        jet1	    = loadImageAsset("jet1inverted.png");
        jet2	    = loadImageAsset("jet2inverted.png");
        jet3        = loadImageAsset("jet3inverted.png");

        fromCity    = loadImageAsset(toLabel); //Inverted the destinations for traveling back
        toCity      = loadImageAsset(fromLabel); //Inverted the destinations for traveling back

        flyPosHor = 230; //Jet horizontal position
    }



}

static void travelOnFrame(Game *game, int frame) {

    if (frame <= flightTime + airplaneInOutTime) fillRGB(game, BLACK);

    if (frame <= airplaneInOutTime){
        delta = applyCubicEaseInOut(0, airplaneInOutTime, frame, 145);

        //Draw assets
        drawImageAsset(fromCity, 8, 39);
        if (flyForward) {
            drawImageAsset(jet1, delta - flyPosHor, flyPosVer);
        } else {
            drawImageAsset(jet1, flyPosHor - delta, flyPosVer);
        }
    }

    if (frame == airplaneInOutTime) flyPosHor = 85; //Plane is in the middle of the screen

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
        drawImageAsset(jet, flyPosHor, flyPosVer);

        if (flyForward) {
            drawImageAsset(fromCity, 8 - bgPos, 39);
            drawImageAsset(toCity, width + 8 - bgPos, 39); //+ 8 for the border
        } else {
            drawImageAsset(fromCity, 8 + bgPos, 39);
            drawImageAsset(toCity, bgPos - width + 8, 39); //+ 8 for the border
        }

        drawImageAsset(jet, flyPosHor, flyPosVer);

        if(bgPos < width) bgPos = bgPos + increment;
    }

    if (frame > flightTime && frame <= flightTime + airplaneInOutTime){
        delta = applyCubicEaseInOut(flightTime, flightTime + airplaneInOutTime, frame, 145);
        drawImageAsset(toCity, 8, 39);
        if (flyForward) {
            drawImageAsset(jet, delta + flyPosHor, flyPosVer);
        } else {
            drawImageAsset(jet, flyPosHor - delta, flyPosVer);
        }
    }

    if (game->gameplayContext.currentTime < targetTime) {
        if (frame%5 == 0) game->gameplayContext.currentTime++;
        if (frame%40 == 0) playSfx(game, "pi.wav");
    }

    drawImageAsset(overlay, 0, 0);
    drawTime(game->gameplayContext.currentTime);
    drawText("Voando pela ABIN JET", 85, 11);

    if (frame > flightTime + airplaneInOutTime){
        if (game->gameplayContext.playerDestinationChoice == 0){
            startFrame = flightTime + airplaneInOutTime;
            drawMessage(game, startFrame, frame);
        } else if (game->gameplayContext.playerDestinationChoice != 0 && flyForward == true){
            startFrame = flightTime + airplaneInOutTime;
            drawMessage(game, startFrame, frame);
        } else {
            changeScene(game, makeCityScene(game));
            game->travel.travelForward = true;
        }
    }


}

static void drawMessage(Game *game, int startFrame, int frame){

    int localFrame = frame - startFrame;
    int btnLength;

	int current = game->gameplayContext.currentCity;
	Destination destination = game->gameplayContext.cities[current].destinations[game->gameplayContext.playerDestinationChoice];

    setTextRGBColor(LIGHT_BLUE);
	drawImageAsset(hint_text_bg, 15, 30);

	if (game->gameplayContext.playerDestinationChoice != 0) {
	    setTextRGBColor(BLUE);
	    drawText("Aeroporto.", 21, 40);
        drawText(destination.name, 78, 40);
        setTextRGBColor(LIGHT_BLUE);
        drawText("Suspeito? Hmm... não, não vi ninguém;com essa descrição pousar aqui. Você;tem certeza que este é o destino?", 21, 54);
        if(localFrame == 1)
            playSfx(game, "travel_fail.wav");
        btnLength = 220;
	} else {
	    setTextRGBColor(BLUE);
	    drawText("Aeroporto.", 21, 40);
        drawText(destination.name, 78, 40);
        setTextRGBColor(LIGHT_BLUE);
        if(localFrame == 1)
            playSfx(game, "travel_fail.wav");
        drawText("Suspeito? Sim! Vi uma pessoa com essa;descrição pousar aqui. Você vai adorar;a cidade!", 21, 54);
        btnLength = 209;
	}

	if (localFrame > 100) drawImageAsset(hint_face, 30, 92);

	if (localFrame > 170){
        float delta = applyCubicEaseOut(170, 300, localFrame, 80);
		if (localFrame % 170 >= 100) {
			drawImageAsset(action_btn_a, btnLength - delta , 145);
		} else {
			drawImageAsset(action_btn_b, btnLength - delta , 145);
		} if (localFrame > 300) {

            setTextRGBColor(61, 140, 222);
            if (game->gameplayContext.playerDestinationChoice != 0) drawText("voltar", 169, 150);
            else drawText("continuar", 156, 150);

        } if (game->keyState.a == KEY_IS_RELEASED) {
            if (game->gameplayContext.playerDestinationChoice != 0){
                game->travel.travelForward = false; //Ensures the plane travels backwards
                changeScene(game, makeTravelScene(game));
            } else {
                changeScene(game, makeCityScene(game));
            }
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

