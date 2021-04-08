#include <iostream>
#include "Game.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>

using namespace std;

int main() {

	srand((int)time(NULL));

	Game* game = new Game();

	game->initSDL("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 610);
	game->initTetris();
	game->run();
	game->clean();
	cout << "Bye!" << endl;
	return 0;
}