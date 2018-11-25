//
// SENAC BCC PI 2
// Projeto Betelgeuse

#include <time.h>
#include "engine.h"

// Forward declaration de
// Funções de ambiente (macOS, Linux etc)
bool setupEnvironment(Game *game);
void loopEnvironmentBeforeFrame(Game *game, bool *redraw);
void loopEnvironmentAfterFrame(Game *game, bool redrawing);
void updateEnvironmentKeys(Game *game);
void quitEnvironment(Game *game);
void menuOverlayOnFrame(Game *game, int frame);

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
    game.screenSetup.fps    = 320;

    game.currentScene.onEnter = NULL;
    game.currentScene.onFrame = NULL;
    game.currentScene.onExit  = NULL;
    game.running              = true;

    game.keyState.a       = KEY_IS_UP;
    game.keyState.b       = KEY_IS_UP;
    game.keyState.up      = KEY_IS_UP;
    game.keyState.right   = KEY_IS_UP;
    game.keyState.down    = KEY_IS_UP;
    game.keyState.left    = KEY_IS_UP;

    game.menuOverlay.visible = false;
    game.travel.travelForward = true;
    game.randomize.notRandom = true;
    game.hint.showHint = false;


    setupEnvironment(&game);
    preloadMenuAssets(&game);
    return game;
}

// # função nextFrame
void nextFrame(Game *game){

    bool shouldRedraw = false;
    loopEnvironmentBeforeFrame(game, &shouldRedraw);

    if (shouldRedraw) {
        int sceneFrame = (++game->frame - game->sceneFrame);
        updateEnvironmentKeys(game);

        if (game->menuOverlay.visible == true) {
            menuOverlayOnFrame(game, game->frame);
        } else if (game->currentScene.onFrame != NULL){
            game->currentScene.onFrame(game, sceneFrame);
        }
    }

    loopEnvironmentAfterFrame(game, shouldRedraw);
}

// # função createNewGame
// Precisa ser chamada no fim do jogo, para gestão
// correta da memória
void endGame(Game *game){

	// Avisa a cena anterior que o jogo acabou
    // & platform specifcs
    int frame = game->frame - game->sceneFrame;
	if (game->currentScene.onExit != NULL) game->currentScene.onExit(game, frame);
    unloadMenuAssets(game);
    quitEnvironment(game);
}
