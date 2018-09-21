#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "funcoes.h"

//Funcao principal

int main(void){
    inicializarComandos();
    if(!inicializarComandos()){
        fprintf(stderr, "Falha ao inicializarComandos().\n");
        return -1;
    }
    configurarVariaveis();
    if(!configurarVariaveis()){
        fprintf(stderr, "Falha ao configurarVariaveis().\n");
        return -1;
    }

    iniciarJogo();

    return 0;
}
