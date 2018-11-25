//
// SENAC BCC PI 2
// Projeto Betelgeuse
//
// engine-gameplay.c
// preenche a struct de jogo com as cidades, crimes, dicas
// locais de interesse, dia da semana e horário

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "engine.h"


void loadGameLevel(Game *game, int level[]);

void loadGameData(Game *game){

    //RANDOMIZE LEVELS
    //BASE: [CRIME = ATUAL,CERTO,ERRADO,ERRADO,ERRADO] [DICA1,DICA2,DICA3] -> referente ao destino certo
    //Números são referentes aos índices da array original
    //LEVEL 1:      [0,1*,2,3,4]     *destino certo
    //LEVEL 2:      [1,5*,6,7,8]     *destino certo
    //LEVEL 3:      [5,9*,10,11,12]  *fim de jogo

    int size = 16;
    int array[size];
    int i;

    //Preenche o vetor com 1-16 (Número de cidades no jogo)
    for (i = 0; i < size; i++) {
        array[i] = i + 1;
    }

    //Embaralha o vetor
    srand(time(NULL));
    for(i = size-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&array[i], &array[j]);
    }

    //Preenche o level seguindo a descrição no início da função
    LEVEL_1[0] = array[0]; // Cidade atual é a cidade onde o crime aconteceu
    LEVEL_2[0] = array[1]; // Destino certo é a nova cidade atual
    LEVEL_3[0] = array[5]; // Destino certo é a nova cidade atual
    for(i = 1; i < 5; i++){
        LEVEL_1[i] = array[i];
        LEVEL_2[i] = array[i+4];
        LEVEL_3[i] = array[i+8];
    }

    game->gameplayContext.currentTime.dayOfWeek = WEEKDAY_MON;
	game->gameplayContext.currentTime.hour 		= 9;
	game->gameplayContext.currentTime.minutes 	= 0;
	game->gameplayContext.currentCity = 0;
}

void loadGameLevel(Game *game, int level[]){

    //CRIMES -> Arquivo: crime.txt; Definir parâmetro LINE da função 'readTXT'
    //INFO CIDADES + CIDADE + IMAGEM -> Arquivo: cidade.txt; Definir parâmetro LINE da função 'readTXT'
    //DICAS -> Arquivo: dica.txt; Definir parâmetro LINE para input da função 'readTXT'

	Logger.info("loading game data");
    game->gameplayContext.stolenItemText = readTXT(game, "data/crime.txt", 3*level[0] - 2); // Line jump = 3x - 2

	// City A:
	City correctCity;
    correctCity.name = readTXT(game, "data/cidade.txt", 6*level[0] - 6); // // Line jump = 6x - 4
    correctCity.flavorText[0] = readTXT(game, "data/cidade.txt", 6*level[0] - 4); // Line jump = 6x - 4
    correctCity.flavorText[1] = readTXT(game, "data/cidade.txt", 6*level[0] - 3); // Line jump = 6x - 3
    correctCity.flavorText[2] = readTXT(game, "data/cidade.txt", 6*level[0] - 2); // Line jump = 6x - 2

    correctCity.imageName = readTXT(game, "data/cidade.txt", 6*level[0] - 5); // // Line jump = 6x - 4
    correctCity.imageAlignX = -73;
    correctCity.imageAlignY = 29;
    correctCity.latitude  = atof(readTXT(game, "data/coordenadas.txt", 4*level[0]-3)); // Line jump = 4x - 3
    correctCity.longitude = atof(readTXT(game, "data/coordenadas.txt", 4*level[0]-2)); // Line jump = 4x - 2
	game->gameplayContext.cities[game->gameplayContext.currentCity] = correctCity;

	// Pontos de interesse

	Place p0;
	p0.name = readTXT(game, "data/dica.txt", 1);
	p0.hint = "''Ele foi para uma cidade de ''edifícios;baixos'', onde raramente atingem qua-;renta andares, e a média é de vinte;andares.''";
	p0.hintImageName 	= "hint-citizen-a.png";
	p0.citizenImageName = readTXT(game, "data/dica.txt", 4);
	p0.minutesRequired 	= 120;
	game->gameplayContext.cities[game->gameplayContext.currentCity].pointsOfInterest[0] = p0;

	Place p1;
	p1.name = readTXT(game, "data/dica.txt", 7);
	p1.hint = "Ele foi para uma cidade de 'edifícios;baixos', onde raramente atingem qua-;renta andares, e a média é de vinte;andares.";
	p1.hintImageName 	= "hint-citizen-b.png";
	p1.citizenImageName = readTXT(game, "data/dica.txt", 11);
	p1.minutesRequired 	= 100;
	game->gameplayContext.cities[game->gameplayContext.currentCity].pointsOfInterest[1] = p1;

	Place p2;
	p2.name = readTXT(game, "data/dica.txt", 13);
	p2.hint = "Ele foi para uma cidade de 'edifícios;baixos', onde raramente atingem qua-;renta andares, e a média é de vinte;andares.";
	p2.hintImageName 	= "hint-citizen-c.png";
	p2.citizenImageName = readTXT(game, "data/dica.txt", 17);
	p2.minutesRequired 	= 140;
	game->gameplayContext.cities[game->gameplayContext.currentCity].pointsOfInterest[2] = p2;

	// Destinos

	Destination d0;
	d0.name = readTXT(game, "data/cidade.txt", 6*level[1] - 6); // // Line jump = 6x - 4
    d0.imageName = readTXT(game, "data/cidade.txt", 6*level[1] - 5); // // Line jump = 6x - 4
    d0.rightChoice = true;
    d0.latitude  = atof(readTXT(game, "data/coordenadas.txt", 4*level[1]-3)); // Line jump = 4x - 3
    d0.longitude = atof(readTXT(game, "data/coordenadas.txt", 4*level[1]-2)); // Line jump = 4x - 2
    d0.minutesRequired = travelTime(correctCity.latitude, correctCity.longitude, d0.latitude, d0.longitude);
    game->gameplayContext.cities[game->gameplayContext.currentCity].destinations[0] = d0;

    Destination d1;
	d1.name = readTXT(game, "data/cidade.txt", 6*level[2] - 6); // // Line jump = 6x - 4
    d1.imageName = readTXT(game, "data/cidade.txt", 6*level[2] - 5); // // Line jump = 6x - 4
    d1.rightChoice = false;
    d1.latitude  = atof(readTXT(game, "data/coordenadas.txt", 4*level[2]-3)); // Line jump = 4x - 3
    d1.longitude = atof(readTXT(game, "data/coordenadas.txt", 4*level[2]-2)); // Line jump = 4x - 2
    d1.minutesRequired = travelTime(correctCity.latitude, correctCity.longitude, d1.latitude, d1.longitude);
    game->gameplayContext.cities[game->gameplayContext.currentCity].destinations[1] = d1;

    Destination d2;
	d2.name = readTXT(game, "data/cidade.txt", 6*level[3] - 6); // // Line jump = 6x - 4
    d2.imageName = readTXT(game, "data/cidade.txt", 6*level[3] - 5); // // Line jump = 6x - 4
    d2.rightChoice = false;
    d2.latitude  = atof(readTXT(game, "data/coordenadas.txt", 4*level[3]-3)); // Line jump = 4x - 3
    d2.longitude = atof(readTXT(game, "data/coordenadas.txt", 4*level[3]-2)); // Line jump = 4x - 2
    d2.minutesRequired = travelTime(correctCity.latitude, correctCity.longitude, d2.latitude, d2.longitude);
    game->gameplayContext.cities[game->gameplayContext.currentCity].destinations[2] = d2;

    Destination d3;
	d3.name = readTXT(game, "data/cidade.txt", 6*level[4] - 6); // // Line jump = 6x - 4
    d3.imageName = readTXT(game, "data/cidade.txt", 6*level[4] - 5); // // Line jump = 6x - 4
    d3.rightChoice = false;
    d3.latitude  = atof(readTXT(game, "data/coordenadas.txt", 4*level[4]-3)); // Line jump = 4x - 3
    d3.longitude = atof(readTXT(game, "data/coordenadas.txt", 4*level[4]-2)); // Line jump = 4x - 2
    d3.minutesRequired = travelTime(correctCity.latitude, correctCity.longitude, d3.latitude, d3.longitude);
    game->gameplayContext.cities[game->gameplayContext.currentCity].destinations[3] = d3;

}
