//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// game.c
//
#include "engine.h"

// # função createNewGame
// Preenche uma nova estrutura de jogo, com os valores
// iniciais e ainda sem cena  
Game createNewGame(){

    struct Game game;

#ifdef PLATFORM_POKITTO
    game.screenSetup.scaleFactor = 1;
#else
    game.screenSetup.scaleFactor = 3;
#endif

    game.screenSetup.widht  = 220 * game.screenSetup.scaleFactor;
    game.screenSetup.height = 176 * game.screenSetup.scaleFactor;

    game.gameplayContext.citiesRemaining = 3;
    game.gameplayContext.day  = 1;
    game.gameplayContext.hour = 9;

    game.currentScene.onEnter = NULL;
    game.currentScene.onFrame = NULL;
    game.currentScene.onExit  = NULL;

    return game;
}

// # função createNewGame
// Precisa ser chamada no fim do jogo, para gestão 
// correta da memória
void endGame(Game *game){

	// Avisa a cena anterior que o jogo acabou	
	if (game->currentScene.onExit != NULL){
		game->currentScene.onExit(game);
    }
}
