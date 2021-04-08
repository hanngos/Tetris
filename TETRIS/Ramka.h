#pragma once
#ifndef RAMKA_H
#define RAMKA_H
#include "ObiektGraficzny.h"

class Ramka : public ObiektGraficzny {
public:
    void rysuj(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b);
};

#endif // !RAMKA_H
