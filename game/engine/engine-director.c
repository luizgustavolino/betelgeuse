//
// SENAC BCC PI 2 
// Projeto Betelgeuse
//
// director.c
// implementa as funções de cena
#include "engine.h"

// # função changeScene
// Troca a cena atual, respeitando o ciclo de vida
void changeScene(Game *game, Scene newScene){
	// Avisa a cena anterior que saimos dela ...
	if (game->currentScene.onExit != NULL) {
		game->currentScene.onExit(game);
	}
	
	// ... e a nova que vamos entrar e começar a atualiza
	game->currentScene.onEnter = newScene.onEnter;
	game->currentScene.onFrame = newScene.onFrame;
	game->currentScene.onExit  = newScene.onExit;

	if (game->currentScene.onEnter != NULL) {
		game->currentScene.onEnter(game);
	}

}
