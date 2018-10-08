//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

#ifdef ENGINE_ALLEGRO

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

extern ALLEGRO_EVENT_QUEUE *queue;

static double deltaTime();
const int FPS = 30;
double initialTime;

void loopEnvironmentBeforeFrame(Game *game){

	while (!al_is_event_queue_empty(queue)){
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
 
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			game->running = false;
        }
    }

    initialTime = al_get_time();
}

void loopEnvironmentAfterFrame(game) {
	al_flip_display();
	double sleepTime = deltaTime();
	if (sleepTime > 0) al_rest(sleepTime);
}

static double deltaTime(){
    return al_get_time() - initialTime;
}

#endif