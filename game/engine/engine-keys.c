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

static ALLEGRO_KEYBOARD_STATE keyboard_state;
static actionState updateForKey(int keyCode, actionState currentState);

void updateEnvironmentKeys(Game *game){
	al_get_keyboard_state(&keyboard_state);

	game->keyState.a = updateForKey(ALLEGRO_KEY_A, game->keyState.a);
	game->keyState.b = updateForKey(ALLEGRO_KEY_B, game->keyState.b);

	game->keyState.up      = updateForKey(ALLEGRO_KEY_UP, game->keyState.up);
    game->keyState.right   = updateForKey(ALLEGRO_KEY_RIGHT, game->keyState.right);
    game->keyState.down    = updateForKey(ALLEGRO_KEY_DOWN, game->keyState.down);
    game->keyState.left    = updateForKey(ALLEGRO_KEY_LEFT, game->keyState.left);

}

static actionState updateForKey(int keyCode, actionState currentState) {
	
	bool down = al_key_down(&keyboard_state, keyCode);

	if (down == true) {
		switch (currentState) {
			case KEY_IS_UP: return KEY_IS_DOWN;
			case KEY_IS_RELEASED: return KEY_IS_DOWN;
			case KEY_IS_DOWN: return KEY_IS_PRESSED;
			case KEY_IS_PRESSED: return KEY_IS_PRESSED;
		}
	} else if (down == false) {
		switch (currentState) {
			case KEY_IS_UP: return KEY_IS_UP;
			case KEY_IS_RELEASED: return KEY_IS_UP;
			case KEY_IS_DOWN: return KEY_IS_RELEASED;
			case KEY_IS_PRESSED: return KEY_IS_RELEASED;
		}
	}

	Logger.error("Key not handled: %d!", keyCode);
	return KEY_IS_UP;
}
