#include <stdio.h>
#include "engine/logger.h"
#include "engine/engine.h"
#include "scenes/splashScene.h"

// platform specifics
// available is: 
// - PLATFORM_POKITTO
// - PLATFORM_WIN
// - PLATFORM_MAC
// - PLATFORM_LINUX
// engines:
// - ENGINE_ALLEGRO
// - ENGINE_POKITTO
#ifdef ENGINE_ALLEGRO
#include <allegro5/allegro.h>
#endif

int main(int argc, char **argv){
    
    // informações da plataforma
    setupLogger();
    Logger.info("### SENAC BCC PI 2 // Projeto Betelgeuse ###");

    // setup do ambiente + cena inicial
    Game game = createNewGame();
    changeScene(&game, makeSplashScene());

    // game lyfecycle
    while (game.running) nextFrame(&game);
    endGame(&game);

    return 0;
}
