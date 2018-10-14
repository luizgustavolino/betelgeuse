//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include "engine.h"

// Forward declaration de
// Funções de ambiente (macOS, Linux etc)
bool setupEnvironment(Game *game);
void loopEnvironmentBeforeFrame(Game *game, bool *redraw);
void loopEnvironmentAfterFrame(Game *game, bool redrawing);
void quitEnvironment(Game *game);

// # função createNewGame
// Preenche uma nova estrutura de jogo, com os valores
// iniciais e ainda sem cena  
Game createNewGame(){

    struct Game game;

#ifdef PLATFORM_POKITTO
    game.screenSetup.scaleFactor = 1;
#else
    game.screenSetup.scaleFactor = 4;
#endif

    game.screenSetup.width  = 220 * game.screenSetup.scaleFactor;
    game.screenSetup.height = 176 * game.screenSetup.scaleFactor;
    game.screenSetup.fps    = 320;

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
    
    bool redraw = false;
    loopEnvironmentBeforeFrame(game, &redraw);

    if (redraw) {
        game->frame++;
        int frame = game->frame - game->sceneFrame;
        if (game->currentScene.onFrame != NULL)
            game->currentScene.onFrame(game, frame);
    }
    
    loopEnvironmentAfterFrame(game, redraw);
}

// # função createNewGame
// Precisa ser chamada no fim do jogo, para gestão 
// correta da memória
void endGame(Game *game){

	// Avisa a cena anterior que o jogo acabou	
    // & platform specifcs
    int frame = game->frame - game->sceneFrame;
	if (game->currentScene.onExit != NULL) game->currentScene.onExit(game, frame);
    quitEnvironment(game);
}
