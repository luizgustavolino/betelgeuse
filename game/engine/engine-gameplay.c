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

int roundFloatToInt(float x){
    int y;

    y = (int)(x + 0.5);

    return y;
}

float deg2rad(float deg) {
  return (deg * PI / 180);
}

float rad2deg(float rad) {
  return (rad * 180 / PI);
}

//Capture the thief before FRYDAY
//Can work from 9:00 to 18:00, so after 18:00 PM change day

//Function that calculates the travel time between cities and returns time in hour and minutes.
//Input should be (City A Latitude, City A Longitude, City B Latitude, City B Longitude)
//Max travel time based on: Max distance 4.394km (North to South), JET average speed 2.000 km/h. -> MAX TIME: 130 minutes
//I added up the airport times to it to make it more believable. So each flight is equal to 3 hours + Jet travel time.
//We can tweak these numbers for balance purposes.
int travelTime(float lat1, float lon1, float lat2, float lon2){

    //***CODE FROM GEODATASOURCE -> https://www.geodatasource.com/developers/c***
    float theta, dist;

    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    //Distance in km
    dist = dist * 1.609344;
    //***End of code from source***

    const int airportTime = 180; //Airport time in minutes. Same for every flight

    int size = 310; //Based on Max travel time + airport time
    int *minutes;

    minutes = (int*) malloc(size * sizeof(int));
	minutes = roundFloatToInt(airportTime + dist * 60/2000); //1 hour (in minutes) divided by the speed of the JET times the travel distance
	return minutes;
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
    firstCity.Latitude  = atoi(readTXT(game, "coordenadas.txt", 4*level[0]-3)); // Line jump = 4x - 3
    firstCity.Longitude = atoi(readTXT(game, "coordenadas.txt", 4*level[0]-2)); // Line jump = 4x - 2
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
    d0.rightChoice = true;
    d0.Latitude  = atoi(readTXT(game, "coordenadas.txt", 4*level[1]-3)); // Line jump = 4x - 3
    d0.Longitude = atoi(readTXT(game, "coordenadas.txt", 4*level[1]-2)); // Line jump = 4x - 2
    d0.minutesRequired = travelTime(firstCity.Latitude, firstCity.Longitude, d0.Latitude, d0.Longitude);
    game->gameplayContext.cities[0].destinations[0] = d0;

    Destination d1;
	d1.name = readTXT(game, "crime.txt", 3*level[2] - 3); // Line jump = 3x - 3
    d1.imageName = "city-brasilia.png";
    d1.rightChoice = false;
    d1.Latitude  = atoi(readTXT(game, "coordenadas.txt", 4*level[2]-3)); // Line jump = 4x - 3
    d1.Longitude = atoi(readTXT(game, "coordenadas.txt", 4*level[2]-2)); // Line jump = 4x - 2
    d1.minutesRequired = travelTime(firstCity.Latitude, firstCity.Longitude, d1.Latitude, d1.Longitude);
    game->gameplayContext.cities[0].destinations[1] = d1;

    Destination d2;
	d2.name = readTXT(game, "crime.txt", 3*level[3] - 3); // Line jump = 3x - 3
    d2.imageName = "city-recife.png";
    d2.rightChoice = false;
    d2.Latitude  = atoi(readTXT(game, "coordenadas.txt", 4*level[3]-3)); // Line jump = 4x - 3
    d2.Longitude = atoi(readTXT(game, "coordenadas.txt", 4*level[3]-2)); // Line jump = 4x - 2
    d2.minutesRequired = travelTime(firstCity.Latitude, firstCity.Longitude, d2.Latitude, d2.Longitude);
    game->gameplayContext.cities[0].destinations[2] = d2;

    Destination d3;
	d3.name = readTXT(game, "crime.txt", 3*level[4] - 3); // Line jump = 3x - 3
    d3.imageName = "city-maceio.png";
    d3.rightChoice = false;
    d3.Latitude  = atoi(readTXT(game, "coordenadas.txt", 4*level[4]-3)); // Line jump = 4x - 3
    d3.Longitude = atoi(readTXT(game, "coordenadas.txt", 4*level[4]-2)); // Line jump = 4x - 2
    d3.minutesRequired = travelTime(firstCity.Latitude, firstCity.Longitude, d3.Latitude, d3.Longitude);
    game->gameplayContext.cities[0].destinations[3] = d3;

}
