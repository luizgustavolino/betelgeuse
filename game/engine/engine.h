//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// engine.h
// centraliza as declarações do motor do jogo, ou seja
// tudo que não é conteúdo ou regra específica do jogo.

#ifndef betelgeuse_engine_engine_h
#define betelgeuse_engine_engine_h

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h> 

#include "logger.h"
#include "utils.h"

// 'platform' to 'render' definitions
#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
    #define ENGINE_ALLEGRO
#elif defined(PLATFORM_POKITTO)
    #define ENGINE_POKITTO
#endif

// forward declarations
typedef struct Game Game;

// Funções de ciclo de vida de uma cena
typedef void (*gameloopControl)(Game *game);
 
// Estrutura de Cena
typedef struct Scene {
    gameloopControl onEnter;
    gameloopControl onFrame;
    gameloopControl onExit;
} Scene;
 
void changeScene(Game *game, Scene newScene);

// Estrutura que guarda todas as informações
// da tela, largura, algura e escala
typedef struct ScreenSetup {
    int height;
    int width;
    int scaleFactor;
} ScreenSetup;
 
// Estrutura que controla as regras do jogo
// e mantém o estado atual da partida
typedef struct GameplayContext {
    int citiesRemaining;
    int day;
    int hour;
} GameplayContext;

// Estrutura que agrupa toda as outras
// e representa o jogo atual
typedef struct Game {
    bool running;
    unsigned int frame;

    ScreenSetup screenSetup;
    Scene currentScene;
    GameplayContext gameplayContext;
} Game;
 
// Funções de apoio ao motor do jogo
Game createNewGame();
void nextFrame(Game *game);
void endGame(Game *game);

// Asset drawing
typedef unsigned int IMAGE_ASSET;

IMAGE_ASSET loadImageAsset(char* name);
void drawImageAsset(IMAGE_ASSET tag, unsigned int x, unsigned int y);
void unloadImageAsset(IMAGE_ASSET tag);

#endif