//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include "engine.h"

// Forward declaration de
// Funções de ambiente (macOS, Linux etc)
bool setupEnvironment(Game *game);
void loopEnvironmentBeforeFrame(Game *game);
void loopEnvironmentAfterFrame(Game *game);
void quitEnvironment(Game *game);

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

    game.screenSetup.width  = 220 * game.screenSetup.scaleFactor;
    game.screenSetup.height = 176 * game.screenSetup.scaleFactor;

    game.gameplayContext.citiesRemaining = 3;
    game.gameplayContext.day  = 1;
    game.gameplayContext.hour = 9;

    game.currentScene.onEnter = NULL;
    game.currentScene.onFrame = NULL;
    game.currentScene.onExit  = NULL;
    game.running              = true;

    setupEnvironment(&game);

    return game;
}

// # função nextFrame
void nextFrame(Game *game){
    
    game->frame++;
    loopEnvironmentBeforeFrame(game);

    if (game->currentScene.onFrame != NULL)
        game->currentScene.onFrame(game);

    loopEnvironmentAfterFrame(game);
}

// # função createNewGame
// Precisa ser chamada no fim do jogo, para gestão 
// correta da memória
void endGame(Game *game){

	// Avisa a cena anterior que o jogo acabou	
    // & platform specifcs
	if (game->currentScene.onExit != NULL) game->currentScene.onExit(game);
    quitEnvironment(game);
}
