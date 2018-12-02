#include <stdio.h>
#include "engine/logger.h"
#include "engine/engine.h"
#include "scenes/splashScene.h"

int main(int argc, char **argv){

    // informações da plataforma
    setupLogger();
    Logger.info("### SENAC BCC PI 2 // Projeto Betelgeuse ###");

    // setup do ambiente + cena inicial
    Game game = createNewGame();

    changeScene(&game, makeSplashScene(&game));


    // game lyfecycle
    while (game.running) nextFrame(&game);
    endGame(&game);

    return 0;
}
