//
// SENAC BCC PI 2
// Projeto Betelgeuse
//
// engine-gameplay.c
// preenche a struct de jogo com as cidades, crimes, dicas
// locais de interesse, dia da semana e horário

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

// Função que lê a linha escolhida do arquivo .txt selecionado. Retorna a string utilizando a váriavel temporária 'holder'

char *readTXT(Game *game, char *filename, int line){
    FILE *fp;
    char *holder = (char *)malloc(MAXCHAR * sizeof(char));

    // Abre o arquivo .txt
    fp = fopen(filename, "r");

    if (fp == NULL){
        // Se o arquivo estiver vazio retorna 0
        Logger.info("Could not open file %s", filename);
        return 0;
    }
    else{
        Logger.info("File %s loaded successfully", filename);
    }
    int i = 0;
    while(i <= line){
        // Lê o arquivo linha por linha até chegar na linha escolhida e retorna a string
        fgets(holder, MAXCHAR, fp);
        if(i == line){
            return holder;
        }
        i++;
    }
}

void loadGameData(Game *game, int level[]){
    //CRIMES -> Arquivo: crime.txt; Definir parâmetro LINE da função 'readTXT'
    //INFO CIDADES + CIDADE + IMAGEM -> Arquivo: cidade.txt; Definir parâmetro LINE da função 'readTXT'
    //DICAS -> Arquivo: dica.txt; Definir parâmetro LINE para input da função 'readTXT'


	Logger.info("loading game data");
    game->gameplayContext.stolenItemText = readTXT(game, "crime.txt", 3*level[0] - 2); // Line jump = 3x - 2
	game->gameplayContext.currentTime.dayOfWeek = WEEKDAY_MON;
	game->gameplayContext.currentTime.hour 		= 9;
	game->gameplayContext.currentTime.minutes 	= 0;
	game->gameplayContext.currentCity = 0;

	// City A:
	City firstCity;
    firstCity.name = readTXT(game, "crime.txt", 3*level[0] - 3); // Line jump = 3x - 3
    firstCity.flavorText[0] = readTXT(game, "cidade.txt", 6*level[0] - 4); // Line jump = 6x - 4
    firstCity.flavorText[1] = readTXT(game, "cidade.txt", 6*level[0] - 3); // Line jump = 6x - 3
    firstCity.flavorText[2] = readTXT(game, "cidade.txt", 6*level[0] - 2); // Line jump = 6x - 2

    firstCity.imageName = "cities/saopaulo.png";
    firstCity.imageAlignX = -73;
    firstCity.imageAlignY = 29;
	game->gameplayContext.cities[0] = firstCity;

	// Pontos de interesse

	Place p0;
	p0.name = readTXT(game, "dica.txt", 1);
	p0.hint = readTXT(game, "dica.txt", 2);
	p0.hintImageName 	= "hint-citizen-a.png";
	p0.citizenImageName = readTXT(game, "dica.txt", 4);
	p0.minutesRequired 	= 120;
	game->gameplayContext.cities[0].pointsOfInterest[0] = p0;

	Place p1;
	p1.name = readTXT(game, "dica.txt", 8);
	p1.hint = readTXT(game, "dica.txt", 9);
	p1.hintImageName 	= "hint-citizen-b.png";
	p1.citizenImageName = readTXT(game, "dica.txt", 11);
	p1.minutesRequired 	= 90;
	game->gameplayContext.cities[0].pointsOfInterest[1] = p1;

	Place p2;
	p2.name = readTXT(game, "dica.txt", 14);
	p2.hint = readTXT(game, "dica.txt", 15);
	p2.hintImageName 	= "hint-citizen-c.png";
	p2.citizenImageName = readTXT(game, "dica.txt", 17);
	p2.minutesRequired 	= 140;
	game->gameplayContext.cities[0].pointsOfInterest[2] = p2;

	// Destinos

	Destination d0;
	d0.name = readTXT(game, "crime.txt", 3*level[1] - 3); // Line jump = 3x - 3
    d0.imageName = "city-bh.png";
    d0.minutesRequired = 300;
    d0.rightChoice = true;
    game->gameplayContext.cities[0].destinations[0] = d0;

    Destination d1;
	d1.name = readTXT(game, "crime.txt", 3*level[2] - 3); // Line jump = 3x - 3
    d1.imageName = "city-brasilia.png";
    d1.minutesRequired = 660;
    d1.rightChoice = false;
    game->gameplayContext.cities[0].destinations[1] = d1;

    Destination d2;
	d2.name = readTXT(game, "crime.txt", 3*level[3] - 3); // Line jump = 3x - 3
    d2.imageName = "city-recife.png";
    d2.minutesRequired = 720;
    d2.rightChoice = false;
    game->gameplayContext.cities[0].destinations[2] = d2;

    Destination d3;
	d3.name = readTXT(game, "crime.txt", 3*level[4] - 3); // Line jump = 3x - 3
    d3.imageName = "city-maceio.png";
    d3.minutesRequired = 780;
    d3.rightChoice = false;
    game->gameplayContext.cities[0].destinations[3] = d3;

}
