#pragma once
#ifndef LOGIKAGRY_H
#define LOGIKAGRY_H
#include <vector>
#include <thread>
#include <numeric>
#include <algorithm>
#include "Bloczek.h"
#include "Studnia.h"
#include "CurrBloczek.h"
#include "Watki.h"
#include "I.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "S.h"
#include "T.h"
#include "Z.h"

using namespace std;

class LogikaGry{
public:
	LogikaGry();
	~LogikaGry();
	vector<int> punkty;
	vector<Bloczek*> bloczkiwgrze;
	Bloczek* bloczki[7];
	Bloczek* nast;
	Studnia* studnia;
	Studnia* nastepny;
	CurrBloczek* curr;

	bool game_over = false;
	int timer = 1000;
	int currTime = 0;
	int wynik = 0;
	int linie = 0;
	int poziom = 1;

	void ladujNast();
	void koniecTury();
	void hardDrop();
	void krokWDol();
	void wDol();
	void wPrawo();
	void wLewo();
	void obrot();
	bool sprawdzwiersze();
	void punktacja();
	void sprawdzenie();
	void update();
};

#endif // !LOGIKAGRY_H

