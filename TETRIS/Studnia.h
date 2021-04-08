#pragma once
#ifndef STUDNIA_H
#define STUDNIA_H
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "ObiektGraficzny.h"
#include "Colors.h"
#include "Szablony.h"
#include <vector>
#include <iostream>

class Studnia:public ObiektGraficzny {
public:
	int x, y;
	int szerokosc, wysokosc;
	int wiersze, kolumny;
	SDL_Color** colors;
	int animacja;

	Studnia();
	Studnia(int x, int y, int w, int h, int wiersze, int kolumny);
	void rysujKsztalt(int kol, int wie, SDL_Color color, SDL_Renderer* renderer);
	void rysujObramowanie(int kol, int wie, SDL_Renderer* renderer);
	bool Zajete(int x, int y);
	void rysuj(SDL_Renderer* renderer);
	void wyczyscwiersze();
	
	std::vector<int> wierszedousuniecia;

};

#endif // !STUDNIA_H

