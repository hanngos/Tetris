#pragma once
#ifndef WATKI_H
#define WATKI_H
#include <fstream>
#include <vector>
#include "Szablony.h"
#include "Wyjatki.h"
#include "Obrazki.h"
#include "Bloczek.h"
#include "I.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "S.h"
#include "T.h"
#include "Z.h"


using namespace std;

void odczytPliku(Lista<string, int>& Lista);

void zapisDoPliku(Lista<string, int> Lista);

void ladujobrazki(vector<Obrazek*>& obrazki, SDL_Renderer*& renderer);

void RTTI(vector<Bloczek*>& bloczki, Bloczek* nast);

#endif // !WATKI_H

