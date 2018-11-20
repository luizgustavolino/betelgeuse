//
// SENAC BCC PI 2
// Projeto Betelgeuse
#include <stddef.h>
#include <stdio.h>
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

typedef struct AssetNode {
	IMAGE_ASSET id;
    ALLEGRO_BITMAP *image;
    struct AssetNode *next;
} AssetNode;

static IMAGE_ASSET insertImageAsset(ALLEGRO_BITMAP *image);
static void removeAssetNode(IMAGE_ASSET id);
static ALLEGRO_BITMAP* findAssetNode(IMAGE_ASSET id);

IMAGE_ASSET loadImageAsset(char* name) {

	Logger.info("loading asset (ALLEGRO_BITMAP)");
	Logger.complement("%s", name);

	// 1) find image path
	char *path = allocStringJoining("assets/", name);
	ALLEGRO_PATH *dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(dir, path);

	const char *fullpath = al_path_cstr(dir, ALLEGRO_NATIVE_PATH_SEP);
	Logger.complement("path: %s", fullpath);

	// 2) load bitmap & cleanup tmps
	ALLEGRO_BITMAP *image = al_load_bitmap(fullpath);
	al_destroy_path(dir);
	free(path);

	// 3) validate and insert into assets list
	if(!image) {
		Logger.error("Failed to load image");
		Logger.complement("%s", fullpath);
		return 0;
	} else {
		IMAGE_ASSET id = insertImageAsset(image);
		Logger.complement("loaded with asset ID: %d", id);
		return id;
	}
}

void drawImageAsset(IMAGE_ASSET tag, double x, double y){
	ALLEGRO_BITMAP *asset = findAssetNode(tag);
	if (asset != NULL) al_draw_bitmap(asset, x, y, 0);
	else Logger.error("can't draw asset with id: %d", tag);
}

void unloadImageAsset(IMAGE_ASSET tag){
	removeAssetNode(tag);
}

// AssetNode handling
// based on code by: learn-c.org
// at: https://www.learn-c.org/en/Linked_lists (oct 6, 2018)
static AssetNode *head;
static IMAGE_ASSET currentID;

void setupImageAssetPool(){
	currentID = 0;
	head = malloc(sizeof(AssetNode));
	head->id = currentID;
	head->image = NULL;
	head->next  = NULL;
}

static IMAGE_ASSET insertImageAsset(ALLEGRO_BITMAP *image){

	// find last node
	AssetNode *current = head;
    while (current->next != NULL) current = current->next;

	// create new node and configure
    current->next = malloc(sizeof(AssetNode));
    current->next->id = ++currentID;
    current->next->image = image;
    current->next->next = NULL;

	// return node ID
	return currentID;
}

static void removeAssetNode(IMAGE_ASSET tag){
	ALLEGRO_BITMAP *asset = findAssetNode(tag);
	if (asset != NULL) al_destroy_bitmap(asset);
	else Logger.warning("can't unload image asset with id: %d", tag);
}

static ALLEGRO_BITMAP* findAssetNode(IMAGE_ASSET id){

	// find node that matches id
	// or, if reaches end of list, return NULL
	AssetNode *current = head;

    do {
    	if (current->id == id) return current->image;
    	else current = current->next;
    } while (current != NULL);

	return NULL;
}

// Fill entire screen with solid RGB color
// each channel goes from 0 to 255
void fillRGB(Game *game, unsigned char r, unsigned char g, unsigned char b){
	int width  = game->screenSetup.width;
	int height = game->screenSetup.height;
	ALLEGRO_COLOR tint = al_map_rgb(r,g,b);
	al_draw_filled_rectangle(0, 0, width, height, tint);
}

// Geometric drawing
void drawRect(Rect frame, Color rgb){
	ALLEGRO_COLOR tint = al_map_rgb(rgb.r, rgb.g, rgb.b);
	al_draw_filled_rectangle(frame.x, frame.y, frame.x + frame.width, frame.y + frame.height, tint);
}

// Text drawing
static ALLEGRO_FONT *font = NULL;
static ALLEGRO_COLOR color;

void setTextRGBColor(unsigned char r, unsigned char g, unsigned char b){
	color = al_map_rgb(r,g,b);
}


static void drawAlignedText(const char *text,  double x, double y, bool centralized){

	// load font, if needed
	if (font == NULL) {

		// find font path
		char *path = "assets/game-font.ttf";
		ALLEGRO_PATH *dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
		al_set_path_filename(dir, path);

		// and load
		const char *fullpath = al_path_cstr(dir, ALLEGRO_NATIVE_PATH_SEP);
		font = al_load_ttf_font(fullpath, 8, ALLEGRO_TTF_MONOCHROME);
		al_destroy_path(dir);
	}

	int len = strlen(text);
	char str[len];

	strcpy(str, text);
	char *token = strtok(str, ";");
	int line = 0;

	while (token != NULL) {
		int align = centralized ? ALLEGRO_ALIGN_CENTRE : ALLEGRO_ALIGN_LEFT;
		al_draw_text(font, color, x, y + line * 12, align, token);
		token = strtok(NULL, ";");
		line ++;
	}

}


void drawText(const char *text,  double x, double y){
	drawAlignedText(text, x, y, false);
}

void drawCentralizedText(const char *text,  double x, double y){
	drawAlignedText(text, x, y, true);
}

void drawLine(Point a, Point b, Color rgb){
	ALLEGRO_COLOR color = al_map_rgb(rgb.r, rgb.g, rgb.b);
	al_draw_line(a.x, a.y, b.x, b.y, color, 1.0);
}

#endif
