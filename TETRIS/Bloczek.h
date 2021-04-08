//#pragma once
#ifndef BLOCZEK_H
#define BLOCZEK_H
#include "ObiektGraficzny.h"
#include "Colors.h"
#include "Studnia.h"
#include "Szablony.h"

class Bloczek :public ObiektGraficzny {
public:
	bool **matrix;
	int rozmiar_matrixa;
	SDL_Color color;
	int waga;

	Bloczek() {};
	Bloczek(int n, int numery[], SDL_Color color);
	Bloczek(const Bloczek &kopia);
	void rysuj(SDL_Renderer* renderer);
	void rysuj(SDL_Renderer* renderer, Studnia* studnia, int x, int y);
	void rysuj(SDL_Renderer* renderer, Studnia* studnia, int x, int y, int ostatni_wiersz);
	int zwrocwage() { return waga; }

};

#endif // !BLOCZEK_H