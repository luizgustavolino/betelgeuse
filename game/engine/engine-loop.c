//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

extern ALLEGRO_EVENT_QUEUE *queue;
int game_overlay_asset = 0;

void loopEnvironmentBeforeFrame(Game *game, bool *shouldDraw){
	
	bool redraw = false;

	while (!al_is_event_queue_empty(queue)){
		
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
 	
 		if(event.type == ALLEGRO_EVENT_TIMER) {      		
      		redraw = true;

    	} else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			game->running = false;
        }

    }

    if (redraw) {
    	if(!game_overlay_asset) game_overlay_asset = loadImageAsset("game_overlay.png");
    	drawImageAsset(game_overlay_asset, -220, -176);
    	al_flip_display();
    }

    (*shouldDraw) = redraw;
    
}

void loopEnvironmentAfterFrame(Game *game, bool redrawing) {
	garbageCollectAudioSfxPool();
	
}
