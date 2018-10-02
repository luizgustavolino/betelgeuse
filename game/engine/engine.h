//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// engine.h
// centraliza os imports do motor do jogo, ou seja
// tudo que não é conteúdo ou regra do jogo

#ifndef betelgeuse_engine_engine_h
#define betelgeuse_engine_engine_h

#include <stddef.h>
#include <stdio.h>

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
    int widht;
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
    ScreenSetup screenSetup;
    Scene currentScene;
    GameplayContext gameplayContext;
} Game;
 
// Funções de apoio ao motor do jogo
Game createNewGame();
void endGame(Game *game);

// Asset drawing
int loadAsset(char* name);
void drawAsset(int tag);
void unloadAsset(int tag);

#endif