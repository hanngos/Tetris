#include "Ramka.h"

void Ramka::rysuj(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, &rect);
}
