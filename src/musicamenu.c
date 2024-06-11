#include <stdlib.h>
#include "state.h"
#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void playMenuSong() {
	Mix_Music* music = Mix_LoadMUS("./assets/menu.mp3");
	Mix_PlayMusic(music, -1);

}