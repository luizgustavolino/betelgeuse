//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "lossScene.h"

#include "../engine/colors.h"

// Robber assets. Goes from idle1 to walk2.
static int robber,exclamation,idle1,idle2,idle3,idle4,walk2,walk3,walk4,walk5,walk6;
static int aBtnIconA, aBtnIconB;
static float walk = -10;

static void lossOnEnter(Game *game, int frame) {

	aBtnIconA	= loadImageAsset("main_a_btn_icon_a.png");
	aBtnIconB	= loadImageAsset("main_a_btn_icon_b.png");
	idle1       = loadImageAsset("robber_idle_1.png");
	idle2       = loadImageAsset("robber_idle_2.png");
	idle3       = loadImageAsset("robber_idle_3.png");
	idle4       = loadImageAsset("robber_idle_4.png");
	walk2       = loadImageAsset("robber_walk_2.png");
	walk3       = loadImageAsset("robber_walk_3.png");
	walk4       = loadImageAsset("robber_walk_4.png");
	walk5       = loadImageAsset("robber_walk_5.png");
	walk6       = loadImageAsset("robber_walk_6.png");
	exclamation = loadImageAsset("exclamation.png");
}

static void lossOnFrame(Game *game, int frame) {

	if (frame == 1) fillRGB(game, BLACK);
    if (frame > 60 && frame <= 600){
        if (frame % 180 >= 0 && frame % 180 < 30) {
            robber = idle1;
        }
        if (frame % 180 >= 30 && frame % 180 < 60) {
            robber = walk2;
        }
        if (frame % 180 >= 60 && frame % 180 < 90) {
            robber = walk3;
        }
        if (frame % 180 >= 90 && frame % 180 < 120) {
            robber = walk4;
        }
        if (frame % 180 >= 120 && frame % 180 < 150) {
            robber = walk5;
        }
        if (frame % 180 >= 150 && frame % 180 < 180) {
            robber = walk6;
        }
        fillRGB(game, BLACK);
        drawImageAsset(robber, walk, 100);
        //x-position of the robber
        walk = walk + 0.2;
    }

    if (frame > 600){
        if (frame % 120 >= 0 && frame % 120 < 30) {
            robber = idle1;
        }
        if (frame % 120 >= 30 && frame % 120 < 60) {
            robber = idle2;
        }
        if (frame % 120 >= 60 && frame % 60 < 90) {
            robber = idle3;
        }
        if (frame % 120 >= 90 && frame % 120 < 120){
            robber = idle4;
        }

        fillRGB(game, BLACK);
        drawImageAsset(robber, walk, 100);
    }

    if (frame > 1200) {
        setTextRGBColor(LIGHT_BLUE);
        drawText("VOCE PERDEU!", 24, 28);
    }

}

//   if (frame % 120 > 60) {
//			drawimageasset(aBtnIconA, 190, 145);
//		} else {
//			drawimageasset(aBtnIconB, 190, 145);
//		}


static void lossOnExit(Game *game, int frame) {
	unloadImageAsset(aBtnIconA);
	unloadImageAsset(aBtnIconB);
	unloadImageAsset(idle1);
	unloadImageAsset(idle2);
	unloadImageAsset(idle3);
	unloadImageAsset(idle4);
	unloadImageAsset(walk2);
	unloadImageAsset(walk3);
	unloadImageAsset(walk4);
	unloadImageAsset(walk5);
	unloadImageAsset(walk6);
	unloadImageAsset(exclamation);
}


Scene makeLossScene(Game *game){
	Scene loss;
	loss.onEnter = lossOnEnter;
	loss.onFrame = lossOnFrame;
	loss.onExit  = lossOnExit;
	return loss;
}

