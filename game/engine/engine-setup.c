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

ALLEGRO_DISPLAY 	*window = NULL;
ALLEGRO_TIMER   	*timer 	= NULL;
ALLEGRO_EVENT_QUEUE *queue  = NULL;
ALLEGRO_TRANSFORM   game_scale_transform;

// forward declaration, will be implemented
// on engine-drawing by allegro
void setupImageAssetPool();

static void shutdownAllegro();
static bool loadAllegro(Game *game);

bool setupEnvironment(Game *game){
	return loadAllegro(game);
}

void quitEnvironment(Game *game) {
	Logger.info("environment is now quitting!");
	shutdownAllegro();
}

static bool loadAllegro(Game *game){

	#if defined(PLATFORM_MAC)
        Logger.info("host platform is MAC");
    #elif defined(PLATFORM_LINUX)
        Logger.info("host platform is LINUX");
    #elif defined(PLATFORM_WIN)
        Logger.info("host platform is WINDOWS");
    #endif
	
	bool setupIsOK = true;
	char *errorMessage = NULL;

	setupIsOK = setupIsOK ? al_init() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro!";

	setupIsOK = setupIsOK ? al_install_keyboard() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro keyboard!";

	setupIsOK = setupIsOK ? al_init_primitives_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro primitives addon!";
	
	setupIsOK = setupIsOK ? al_init_image_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro image addon!";

	al_init_font_addon();

	setupIsOK = setupIsOK ? al_init_ttf_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro install tff addon!";

	setupIsOK = setupIsOK ? al_install_audio() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro install audio!";

	setupIsOK = setupIsOK ? al_init_acodec_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro acodec addon!";

	setupIsOK = setupIsOK ? al_reserve_samples(4) : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro acodec addon!";

	setupImageAssetPool();

	int width  = game->screenSetup.width;
	int height = game->screenSetup.height;
	
	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 1, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_SUPPORT_NPOT_BITMAP, 1, ALLEGRO_REQUIRE);
	
	window = al_create_display(width, height);

	int scale = game->screenSetup.scaleFactor;
	if (scale != 1) {
		al_identity_transform(&game_scale_transform);
		al_scale_transform(&game_scale_transform, scale, scale);
		al_use_transform(&game_scale_transform);
	}

   	if(!window) {
   		errorMessage = "failed to create display!";
      	setupIsOK = false;
   	}

   	if(!setupIsOK) {
		errorMessage = errorMessage == NULL ? "Unknown error!" : errorMessage;
		Logger.error("failed to create display!");
		al_show_native_message_box(NULL, "Ops!", "Error", errorMessage, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	} else {
		Logger.info("Allegro 5 is now loaded!");
	}

	timer = al_create_timer( 1.0 / (float) game->screenSetup.fps);
	al_set_target_backbuffer(window);

	al_set_window_title(window, "Senac PI II // Betelgeuse");
	al_flip_display();

	al_resize_display(window, width, height);

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	Logger.info("new game created! screen info:");
    Logger.complement("%dx%dpx (%dx scale)",
    	game->screenSetup.width, game->screenSetup.height,
    	game->screenSetup.scaleFactor);

    al_start_timer(timer);

	return setupIsOK;
}

static void shutdownAllegro(){

	al_stop_timer(timer);

	al_unregister_event_source(queue, al_get_keyboard_event_source());
    al_unregister_event_source(queue, al_get_display_event_source(window));
    al_unregister_event_source(queue, al_get_timer_event_source(timer));

    al_destroy_timer(timer);
    al_destroy_display(window);
    al_destroy_event_queue(queue);

    // al_uninstall & al_shutdown functions is auto called
    // by allegro, as stated in v5.0 manual
}
