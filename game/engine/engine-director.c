//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include "engine.h"

// # função changeScene
// Troca a cena atual, respeitando o ciclo de vida
void changeScene(Game *game, Scene newScene){

	Logger.info("director is changing scene");
	int frame = game->frame - game->sceneFrame;

	// Avisa a cena anterior que saimos dela ...
	if (game->currentScene.onExit != NULL) {
		game->currentScene.onExit(game, frame);
	}
	
	// ... e a nova que vamos entrar e começar a atualiza
	game->currentScene.onEnter = newScene.onEnter;
	game->currentScene.onFrame = newScene.onFrame;
	game->currentScene.onExit  = newScene.onExit;
	game->sceneFrame = game->frame;

	if (game->currentScene.onEnter != NULL) {
		game->currentScene.onEnter(game, 0);
	}

}
