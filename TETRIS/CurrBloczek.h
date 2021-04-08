#pragma once
#ifndef CURRBLOCZEK_H
#define CURRBLOCZEK_H
#include "Bloczek.h"
#include "Studnia.h"

class CurrBloczek
{
public:
	Bloczek* bloczek;
	int x, y;
	int ostatni_wiersz;
	Studnia* studnia;
	
	CurrBloczek(Studnia* studnia);
	CurrBloczek(const Bloczek& bloczek, Studnia* studnia);
	int OstatniWiersz();
	bool Kolizja(int rozmiar_matrixa, bool **matrix, int kol, int wie);
	void update();
};

#endif //CURRBLOCZEK_H

