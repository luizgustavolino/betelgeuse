//
// SENAC BCC PI 2
// Projeto Betelgeuse
//
// engine-audio.c

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

ALLEGRO_AUDIO_STREAM *currentOST = NULL;


void stopSoundtrack(Game *game){
	if (currentOST != NULL) {
		al_set_audio_stream_playing(currentOST, false);
		al_detach_audio_stream(currentOST);
		al_destroy_audio_stream(currentOST);
		currentOST = NULL;
	}
}

static ALLEGRO_SAMPLE *sample;
void playSfx(Game *game, char* name){

	// file path
	Logger.info("loading asset (ALLEGRO_SAMPLE)");
	char *path = allocStringJoining("assets/sfx/", name);
	ALLEGRO_PATH *dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(dir, path);

	const char *fullpath = al_path_cstr(dir, ALLEGRO_NATIVE_PATH_SEP);
	Logger.complement("path: %s", fullpath);

	sample = al_load_sample(fullpath);
	if (!sample) Logger.error("Can't load sample!");
	al_play_sample(sample, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	// cleanup
	al_destroy_path(dir);
	free(path);
}

void playSoundtrack(Game *game, char* name){

	// stop old, if any is loaded
	stopSoundtrack(game);

	// file path
	Logger.info("loading asset (ALLEGRO_AUDIO_STREAM)");
	char *path = allocStringJoining("assets/ost/", name);
	ALLEGRO_PATH *dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(dir, path);

	const char *fullpath = al_path_cstr(dir, ALLEGRO_NATIVE_PATH_SEP);
	Logger.complement("path: %s", fullpath);

	// filename, buffer_count, samples
	currentOST = al_load_audio_stream(fullpath, 4, 1024);
	al_set_audio_stream_gain(currentOST, 0.5);
	al_set_audio_stream_playmode(currentOST, ALLEGRO_PLAYMODE_LOOP);
	al_attach_audio_stream_to_mixer(currentOST, al_get_default_mixer());
	al_set_audio_stream_playing(currentOST, true);

	// cleanup
	al_destroy_path(dir);
	free(path);
}

#endif
