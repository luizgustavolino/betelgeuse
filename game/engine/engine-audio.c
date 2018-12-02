//
// SENAC BCC PI 2
// Projeto Betelgeuse
//
// engine-audio.c

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

ALLEGRO_AUDIO_STREAM *currentOST = NULL;

typedef struct AudioNode {
	AUDIO_ASSET id;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;
    struct AudioNode *next;
} AudioNode;

static AUDIO_ASSET insertAudioAsset(ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE_INSTANCE *instance);
static void removeAudioNode(AUDIO_ASSET id);

void playSfx(Game *game, char* name){

	// file path
	Logger.info("loading asset (ALLEGRO_SAMPLE)");
	char *path = allocStringJoining("assets/sfx/", name);
	ALLEGRO_PATH *dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(dir, path);

	const char *fullpath = al_path_cstr(dir, ALLEGRO_NATIVE_PATH_SEP);
	Logger.complement("path: %s", fullpath);

	ALLEGRO_SAMPLE *sample = al_load_sample(fullpath);
	if (!sample) Logger.error("Can't load sample!");

	ALLEGRO_SAMPLE_INSTANCE *instance = al_create_sample_instance(sample);
	al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
	al_set_sample_instance_gain(instance, 0.8);
	al_play_sample_instance(instance);
	insertAudioAsset(sample, instance);

	// cleanup
	al_destroy_path(dir);
	free(path);
}

void stopSoundtrack(Game *game){
	if (currentOST != NULL) {
		al_set_audio_stream_playing(currentOST, false);
		al_detach_audio_stream(currentOST);
		al_destroy_audio_stream(currentOST);
		currentOST = NULL;
	}
}

void playSoundtrack(Game *game, char* name){

	// stop old, if any is loaded
	stopSoundtrack(game);

	// file path
	char *path = allocStringJoining("assets/ost/", name);
	ALLEGRO_PATH *dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(dir, path);
	const char *fullpath = al_path_cstr(dir, ALLEGRO_NATIVE_PATH_SEP);

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

static AudioNode *head;
static AUDIO_ASSET currentID;


void setupAudioSfxPool(){
	currentID = 0;
	head = malloc(sizeof(AudioNode));
	head->id = currentID;
	head->sample 	= NULL;
	head->instance 	= NULL;
	head->next  	= NULL;
}

void garbageCollectAudioSfxPool(){

	// find last node
	AudioNode *current = head;
    while (current->next != NULL) {

    	if(current->instance != NULL && !al_get_sample_instance_playing(current->instance)) {
    		AUDIO_ASSET id = current->id;
    		current = current->next;
    		removeAudioNode(id);
    	} else {
    		current = current->next;
    	}

    }

}

static AUDIO_ASSET insertAudioAsset(ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE_INSTANCE *instance){

	// find last node
	AudioNode *current = head;
    while (current->next != NULL) current = current->next;

	// create new node and configure
    current->next = malloc(sizeof(AudioNode));
    current->next->id = ++currentID;
    current->next->sample = sample;
    current->next->instance = instance;
    current->next->next = NULL;

	// return node ID
	return currentID;
}

static void removeAudioNode(AUDIO_ASSET id){

	AudioNode *current  = head->next;
	AudioNode *previous = head;

    do {
    	if (current->id == id) {
    		previous->next = current->next;
    		ALLEGRO_SAMPLE *sample = current->sample;
			if (sample != NULL) {
				al_destroy_sample(current->sample);
				al_destroy_sample_instance(current->instance);
				free(current);
			}
			return;
    	} else {
    		previous = current;
    		current = current->next;
    	}
    } while (current != NULL);

	return;
}
