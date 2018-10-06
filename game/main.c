#include <stdio.h>
#include "engine/engine.h"
#include "scenes/splashScene.h"

int main(){
    
    // estrutura de jogo 
    Game game = createNewGame();
    printf("new game created! screen info:\n");
    printf("w:%d x h:%d\n", game.screenSetup.widht, game.screenSetup.height);

    // teste de cena
    Scene splash = makeSplashScene();
    changeScene(&game, splash);
    game.currentScene.onFrame(&game);
    endGame(&game);

    loadAsset("splash.bmp");
 
    return 0;
}
