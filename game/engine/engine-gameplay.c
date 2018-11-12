//
// SENAC BCC PI 2
// Projeto Betelgeuse
//
// engine-gameplay.c
// preenche a struct de jogo com as cidades, dicas
// locais de interesse, tempo
//
// só a ana altera aqui :B

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

void loadGameData(Game *game){

	Logger.info("loading game data");

	game->gameplayContext.currentTime.dayOfWeek = WEEKDAY_MON;
	game->gameplayContext.currentTime.hour 		= 9;
	game->gameplayContext.currentTime.minutes 	= 0;
	game->gameplayContext.currentCity = 0;

	// TODO ana: carregar estes valores
	game->gameplayContext.stolenItemText =  "        ***URGENTE***; ;\
                                            A fórmula do pão de;queijo acaba de ser;roubada!; ;\
                                            A receita faz parte do;patrimônio nacional.;\
                                            Palmirinha está;desesperada! Rápido!;Minas depende de;você!";

	// City A:
	City firstCity;
    firstCity.name = "SP, São Paulo";
    firstCity.flavorText[0] = "Fundada em 1554;por padres jesuítas,;a cidade exerce;influência nacional;e internacional, seja;do ponto de vista;cultural, econômico;ou político.";
    firstCity.flavorText[1] = "O município possui o;decimo maior PIB do;mundo. Representa,;isoladamente, 10%;do PIB brasileiro;e 36% de toda a;produção de bens e;serviços do estado.;";
    firstCity.flavorText[2] = "O mês mais quente;do ano é fevereiro,;com média de 23ºC.;Mais frio é julho,;16ºC. A precipitação;média é de 1600mm;anuais, concentra-;dos no verão.";

    firstCity.imageName = "cities/saopaulo.png";
    firstCity.imageAlignX = -73;
    firstCity.imageAlignY = 29;
	game->gameplayContext.cities[0] = firstCity;

	// Pontos de interesse

	Place p0;
	p0.name = "Museu";
	p0.hint = "Essa pessoa gosta;muito de pão de;queijo!";
	p0.hintImageName 	= "hint-citizen-a.png";
	p0.citizenImageName = "Guardinha";
	p0.minutesRequired 	= 120;
	game->gameplayContext.cities[0].pointsOfInterest[0] = p0;

	Place p1;
	p1.name = "Biblioteca";
	p1.hint = "Vi alguém suspeito;falando algo sobre;pescar. Algo;sobre Furnas";
	p1.hintImageName 	= "hint-citizen-b.png";
	p1.citizenImageName = "Bibliotecaria";
	p1.minutesRequired 	= 90;
	game->gameplayContext.cities[0].pointsOfInterest[1] = p1;

	Place p2;
	p2.name = "Praia";
	p2.hint = "Humm... alguém;assim passou por;aqui. Perguntou sobre;produção de leite.";
	p2.hintImageName 	= "hint-citizen-c.png";
	p2.citizenImageName = "Turista";
	p2.minutesRequired 	= 140;
	game->gameplayContext.cities[0].pointsOfInterest[2] = p2;

	// Destinos

	Destination d0;
	d0.name = "Belo Horizonte";
    d0.imageName = "city-bh.png";
    d0.minutesRequired = 300;
    d0.rightChoice = true;
    game->gameplayContext.cities[0].destinations[0] = d0;

    Destination d1;
	d1.name = "Brasilia";
    d1.imageName = "city-brasilia.png";
    d1.minutesRequired = 660;
    d1.rightChoice = false;
    game->gameplayContext.cities[0].destinations[1] = d1;

    Destination d2;
	d2.name = "Recife";
    d2.imageName = "city-recife.png";
    d2.minutesRequired = 720;
    d2.rightChoice = false;
    game->gameplayContext.cities[0].destinations[2] = d2;

    Destination d3;
	d3.name = "Maceió";
    d3.imageName = "city-maceio.png";
    d3.minutesRequired = 780;
    d3.rightChoice = false;
    game->gameplayContext.cities[0].destinations[3] = d3;

}
