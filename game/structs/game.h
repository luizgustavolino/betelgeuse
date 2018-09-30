//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// game.h
// estruturas de suporte ao jogo 
//
#include <stddef.h>
#include <stdio.h>

// Protótipos, que serão detalhados mais à frente
struct GameplayContext;
struct Scene;
struct Game;

// Estrutura de Cena e funções de ciclo
// de vida de uma cena
typedef void (*gameloopControl)(struct Game* game);
 
typedef struct Scene {
    gameloopControl onEnter;
    gameloopControl onFrame;
    gameloopControl onExit;
} Scene;

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
void changeScene(Game *game, Scene *newScene);
