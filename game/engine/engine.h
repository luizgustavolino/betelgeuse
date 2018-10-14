//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// engine.h
// centraliza as declarações do motor do jogo, ou seja
// tudo que não é conteúdo ou regra específica do jogo.

#ifndef betelgeuse_engine_engine_h
#define betelgeuse_engine_engine_h

// std includes
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h> 

// 'platform' to 'render' definitions
#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
    #define ENGINE_ALLEGRO
#elif defined(PLATFORM_POKITTO)
    #define ENGINE_POKITTO
#endif

// platform specifics globals
#ifdef ENGINE_ALLEGRO
    #include <allegro5/allegro.h>
    ALLEGRO_DISPLAY *window;
    ALLEGRO_EVENT_QUEUE *queue;
#endif

// engine droplets includes
#include "logger.h"
#include "utils.h"

/// ----------------------------- STRUCTS and DEFINITIONS

// forward declarations
typedef struct Game Game;

// Funções de ciclo de vida de uma cena
typedef void (*gameloopControl)(Game *game, int frame);
 
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
    unsigned int height;
    unsigned int width;
    unsigned int scaleFactor;
    unsigned int fps;
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
    unsigned int sceneFrame;
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
void drawImageAsset(IMAGE_ASSET tag, double x, double y);
void unloadImageAsset(IMAGE_ASSET tag);
void fillRGB(unsigned char r, unsigned char g, unsigned char b);

#endif