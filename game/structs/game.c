//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// game.c
//
#include "game.h"

// # função changeScene
// Troca a cena atual, respeitando o ciclo de vida
void changeScene(Game *game, Scene newScene){
	// Avisa a cena anterior que saimos dela ...
	if (game->currentScene.onExit != NULL) game->currentScene.onExit(game);
	
	// ... e a nova que vamos entrar e começar a atualiza
	game->currentScene.onEnter = newScene.onEnter;
	game->currentScene.onFrame = newScene.onFrame;
	game->currentScene.onExit  = newScene.onExit;

	if (game->currentScene.onEnter != NULL) game->currentScene.onEnter(game);

}

// # função createNewGame
// Preenche uma nova estrutura de jogo, com os valores 
// iniciais 
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


void endGame(Game *game){
	// Avisa a cena anterior que o jogo acabou
	if (game->currentScene.onExit != NULL) game->currentScene.onExit(game);
}
