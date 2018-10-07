//
// SENAC BCC PI 2 
// Projeto Betelgeuse

#include <stdio.h>
#include <stdlib.h>

#ifdef ENGINE_ALLEGRO

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

#include "engine.h"

ALLEGRO_DISPLAY *window;
ALLEGRO_EVENT_QUEUE *queue;

// forward declaration, will be implemented
// on engine-drawing by allegro
void setupImageAssetPool();

static void shutdownAllegro();
static bool loadAllegro(Game *game);

bool setupEnvironment(Game *game){
	return loadAllegro(game);
}

void quitEnvironment(Game *game) {
	shutdownAllegro();
	Logger.info("environment is quit!");
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
	
	setupIsOK = setupIsOK ? al_init_font_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro font addon!";

	setupIsOK = setupIsOK ? al_init_image_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro image addon!";

	setupIsOK = setupIsOK ? al_install_audio() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro install audio!";

	setupIsOK = setupIsOK ? al_init_acodec_addon() : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro acodec addon!";

	setupIsOK = setupIsOK ? al_reserve_samples(1) : false;
	if(!setupIsOK && errorMessage == NULL)
		errorMessage = "Failed to initialize allegro acodec addon!";

	setupImageAssetPool();

	int width  = game->screenSetup.width;
	int height = game->screenSetup.height;
	window = al_create_display(width, height);

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

	al_set_window_title(window, "Senac PI II // Betelgeuse");
	al_flip_display();

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_keyboard_event_source());

	Logger.info("new game created! screen info:");
    Logger.complement("%dx%dpx (%dx scale)",
    	game->screenSetup.width, game->screenSetup.height,
    	game->screenSetup.scaleFactor);

	return setupIsOK;
}

static void shutdownAllegro(){

	al_destroy_display(window);

	al_unregister_event_source(queue, al_get_keyboard_event_source());
    al_unregister_event_source(queue, al_get_display_event_source(window));
    al_destroy_event_queue(queue);

	al_uninstall_keyboard();
    al_uninstall_audio();
    al_shutdown_image_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
}

#endif
