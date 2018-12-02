//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <stddef.h>
#include <stdio.h>
#include "../engine/colors.h"
#include "creditsScene.h"
#include "mainMenuScene.h"

static int robber,exclamation,idle1,idle2,idle3,idle4,walk2,walk3,walk4,walk5,walk6,betelgeuseLogo;
static int aBtnIconA, aBtnIconB;
static float walk = -10;


static void creditsOnEnter(Game *game, int frame) {

    betelgeuseLogo = loadImageAsset("splash_betelgeuse.png");
	playSoundtrack(game, "credits.ogg");
	idle1       = loadImageAsset("robber_idle_1.png");
	idle2       = loadImageAsset("robber_idle_2.png");
	idle3       = loadImageAsset("robber_idle_3.png");
	idle4       = loadImageAsset("robber_idle_4.png");
	walk2       = loadImageAsset("robber_walk_2.png");
	walk3       = loadImageAsset("robber_walk_3.png");
	walk4       = loadImageAsset("robber_walk_4.png");
	walk5       = loadImageAsset("robber_walk_5.png");
	walk6       = loadImageAsset("robber_walk_6.png");
	aBtnIconA	= loadImageAsset("main_a_btn_icon_a.png");
	aBtnIconB	= loadImageAsset("main_a_btn_icon_b.png");
}

static void creditsOnFrame(Game *game, int frame) {

    int robberEnters = 5400;
    if (frame <= robberEnters) fillRGB(game, BLACK);

    if (game->keyState.a == KEY_IS_RELEASED) {
        changeScene(game, makeMainMenuScene(game));
    }

    if (frame > 1) {
        setTextRGBColor(LIGHT_BLUE);
        drawImageAsset(betelgeuseLogo, 74, 150 - frame/12.0);
        drawCentralizedText("Projeto: Desenvolvimento;de jogos em 2D", 110, 230 - frame/12.0);
        drawCentralizedText("***Grupo***; ;Ana \"BlackWitch\" França;Kauê \"Beorn\" Sales;Lucas \"Brê\" Breur;Luiz \"Lino\" Lino;Vinycius \"Zaartis\" Zanardi", 110, 266 - frame/12.0);
        drawCentralizedText("***Software***; ;Biblioteca Allegro 5.0;Code::Blocks 17.12;pxtone;Audacity", 110, 374 - frame/12.0);
    }

    if (frame > robberEnters && frame <= robberEnters + 480){
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

    if (frame > robberEnters + 540){
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

        if (frame % 120 >= 60) drawImageAsset(aBtnIconB, 195, 150);
        else drawImageAsset(aBtnIconA, 195, 150);
    }

}

static void creditsOnExit(Game *game, int frame) {
	unloadImageAsset(betelgeuseLogo);
    unloadImageAsset(idle1);
	unloadImageAsset(idle2);
	unloadImageAsset(idle3);
	unloadImageAsset(idle4);
	unloadImageAsset(walk2);
	unloadImageAsset(walk3);
	unloadImageAsset(walk4);
	unloadImageAsset(walk5);
	unloadImageAsset(walk6);
    unloadImageAsset(aBtnIconA);
	unloadImageAsset(aBtnIconB);
}

Scene makeCreditsScene(Game *game) {
	Scene credits;
	credits.onEnter = creditsOnEnter;
	credits.onFrame = creditsOnFrame;
	credits.onExit  = creditsOnExit;
	return credits;
}
