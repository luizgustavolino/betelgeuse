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

    //Game levels
    int LEVEL_1[5];
    int LEVEL_2[5];
    int LEVEL_3[5];

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
    for(i = 1; i < 5; i++){
        LEVEL_1[i] = array[i];
    }

    LEVEL_2[0] = LEVEL_1[1]; // Destino certo é a nova cidade atual
    for(i = 5; i < 9; i++){
        LEVEL_2[i-4] = array[i];
    }

    LEVEL_3[0] = LEVEL_2[1]; // Destino certo é a nova cidade atual
    for(i = 9; i < 13; i++){
        LEVEL_3[i-8] = array[i];
    }

    loadGameLevel(game, LEVEL_1);

}

void loadGameLevel(Game *game, int level[]){

    //CRIMES -> Arquivo: crime.txt; Definir parâmetro LINE da função 'readTXT'
    //INFO CIDADES + CIDADE + IMAGEM -> Arquivo: cidade.txt; Definir parâmetro LINE da função 'readTXT'
    //DICAS -> Arquivo: dica.txt; Definir parâmetro LINE para input da função 'readTXT'


	Logger.info("loading game data");
    game->gameplayContext.stolenItemText = readTXT(game, "data/crime.txt", 3*level[0] - 2); // Line jump = 3x - 2
	game->gameplayContext.currentTime.dayOfWeek = WEEKDAY_MON;
	game->gameplayContext.currentTime.hour 		= 9;
	game->gameplayContext.currentTime.minutes 	= 0;
	game->gameplayContext.currentCity = 0;

	// City A:
	City firstCity;
    firstCity.name = readTXT(game, "data/crime.txt", 3*level[0] - 3); // Line jump = 3x - 3
    firstCity.flavorText[0] = readTXT(game, "data/cidade.txt", 6*level[0] - 4); // Line jump = 6x - 4
    firstCity.flavorText[1] = readTXT(game, "data/cidade.txt", 6*level[0] - 3); // Line jump = 6x - 3
    firstCity.flavorText[2] = readTXT(game, "data/cidade.txt", 6*level[0] - 2); // Line jump = 6x - 2

    firstCity.imageName = "cities/saopaulo.png";
    firstCity.imageAlignX = -73;
    firstCity.imageAlignY = 29;
    firstCity.latitude  = atoi(readTXT(game, "data/coordenadas.txt", 4*level[0]-3)); // Line jump = 4x - 3
    firstCity.longitude = atoi(readTXT(game, "data/coordenadas.txt", 4*level[0]-2)); // Line jump = 4x - 2
	game->gameplayContext.cities[0] = firstCity;

	// Pontos de interesse

	Place p0;
	p0.name = readTXT(game, "data/dica.txt", 1);
	p0.hint = readTXT(game, "data/dica.txt", 2);
	p0.hintImageName 	= "hint-citizen-a.png";
	p0.citizenImageName = readTXT(game, "data/dica.txt", 4);
	p0.minutesRequired 	= 120;
	game->gameplayContext.cities[0].pointsOfInterest[0] = p0;

	Place p1;
	p1.name = readTXT(game, "data/dica.txt", 8);
	p1.hint = readTXT(game, "data/dica.txt", 9);
	p1.hintImageName 	= "hint-citizen-b.png";
	p1.citizenImageName = readTXT(game, "data/dica.txt", 11);
	p1.minutesRequired 	= 90;
	game->gameplayContext.cities[0].pointsOfInterest[1] = p1;

	Place p2;
	p2.name = readTXT(game, "data/dica.txt", 14);
	p2.hint = readTXT(game, "data/dica.txt", 15);
	p2.hintImageName 	= "hint-citizen-c.png";
	p2.citizenImageName = readTXT(game, "data/dica.txt", 17);
	p2.minutesRequired 	= 140;
	game->gameplayContext.cities[0].pointsOfInterest[2] = p2;

	// Destinos

	Destination d0;
	d0.name = readTXT(game, "data/crime.txt", 3*level[1] - 3); // Line jump = 3x - 3
    d0.imageName = "city-bh.png";
    d0.rightChoice = true;
    d0.latitude  = atoi(readTXT(game, "data/coordenadas.txt", 4*level[1]-3)); // Line jump = 4x - 3
    d0.longitude = atoi(readTXT(game, "data/coordenadas.txt", 4*level[1]-2)); // Line jump = 4x - 2
    d0.minutesRequired = travelTime(firstCity.latitude, firstCity.longitude, d0.latitude, d0.longitude);
    game->gameplayContext.cities[0].destinations[0] = d0;

    Destination d1;
	d1.name = readTXT(game, "data/crime.txt", 3*level[2] - 3); // Line jump = 3x - 3
    d1.imageName = "city-brasilia.png";
    d1.rightChoice = false;
    d1.latitude  = atoi(readTXT(game, "data/coordenadas.txt", 4*level[2]-3)); // Line jump = 4x - 3
    d1.longitude = atoi(readTXT(game, "data/coordenadas.txt", 4*level[2]-2)); // Line jump = 4x - 2
    d1.minutesRequired = travelTime(firstCity.latitude, firstCity.longitude, d1.latitude, d1.longitude);
    game->gameplayContext.cities[0].destinations[1] = d1;

    Destination d2;
	d2.name = readTXT(game, "data/crime.txt", 3*level[3] - 3); // Line jump = 3x - 3
    d2.imageName = "city-recife.png";
    d2.rightChoice = false;
    d2.latitude  = atoi(readTXT(game, "data/coordenadas.txt", 4*level[3]-3)); // Line jump = 4x - 3
    d2.longitude = atoi(readTXT(game, "data/coordenadas.txt", 4*level[3]-2)); // Line jump = 4x - 2
    d2.minutesRequired = travelTime(firstCity.latitude, firstCity.longitude, d2.latitude, d2.longitude);
    game->gameplayContext.cities[0].destinations[2] = d2;

    Destination d3;
	d3.name = readTXT(game, "data/crime.txt", 3*level[4] - 3); // Line jump = 3x - 3
    d3.imageName = "city-maceio.png";
    d3.rightChoice = false;
    d3.latitude  = atoi(readTXT(game, "data/coordenadas.txt", 4*level[4]-3)); // Line jump = 4x - 3
    d3.longitude = atoi(readTXT(game, "data/coordenadas.txt", 4*level[4]-2)); // Line jump = 4x - 2
    d3.minutesRequired = travelTime(firstCity.latitude, firstCity.longitude, d3.latitude, d3.longitude);
    game->gameplayContext.cities[0].destinations[3] = d3;

}
