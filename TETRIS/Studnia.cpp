#include "Studnia.h"

bool operator!=(const SDL_Color& a, const SDL_Color& b)
{
	if (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a)
		return false;
	return true;
}

Studnia::Studnia()
{
	wysokosc = 600;
	szerokosc = 300;
	kolumny = 10;
	wiersze = 20;
	x = 1;
	y = 1;
	colors = tablica2D<SDL_Color>(kolumny, wiersze);

	for (int i = 0; i < kolumny; i++) {
		for (int j = 0; j < wiersze; j++) {
			colors[i][j] = COLOR.grey;
		}
	}

	animacja = -1;
}

Studnia::Studnia(int x, int y, int w, int h, int wiersze, int kolumny)
{
	this->x = x;
	this->y = y;
	szerokosc = w;
	wysokosc = h;
	this->wiersze = wiersze;
	this->kolumny = kolumny;
	colors = tablica2D<SDL_Color>(kolumny, wiersze);

	for (int i = 0; i < kolumny; i++) {
		for (int j = 0; j < wiersze; j++) {
			colors[i][j] = COLOR.grey;
		}
	}
	animacja = -1;
}

void Studnia::rysujKsztalt(int kol, int wie, SDL_Color color, SDL_Renderer* renderer)
{
	if (kol < 0 || kol >= kolumny || wie < 0 || wie >= wiersze)
		return;
	SDL_Rect rect;
	rect.x = x + kol * (szerokosc / kolumny);
	rect.y = y + wie * (wysokosc / wiersze);
	rect.h = wysokosc / wiersze;
	rect.w = szerokosc / kolumny;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Studnia::rysujObramowanie(int kol, int wie, SDL_Renderer* renderer)
{
	if (kol < 0 || kol >= kolumny || wie < 0 || wie >= wiersze)
		return;
	SDL_Rect rect;
	rect.x = x + kol * (szerokosc / kolumny);
	rect.y = y + wie * (wysokosc / wiersze);
	rect.h = wysokosc / wiersze;
	rect.w = szerokosc / kolumny;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

bool Studnia::Zajete(int x, int y)
{
	if (y < 0 && x < kolumny && x >= 0) return false;
	return (x >= kolumny || x < 0 || y >= wiersze || this->colors[x][y] != COLOR.grey);
}

void Studnia::rysuj(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = wysokosc;
	rect.w = szerokosc;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);
	for (int i = 0; i < kolumny; i++)
		for (int j = 0; j < wiersze; j++)
			rysujKsztalt(i, j, colors[i][j], renderer);
	
	if (animacja >= 0) {
		for (int wiersz : wierszedousuniecia)
			for (int i = 0; i < kolumny; ++i)
				rysujKsztalt(i, wiersz, COLOR.white, renderer);
		animacja += 10;
		if (animacja > 5 * 255) {
			animacja = -1;
			wyczyscwiersze();
		}
	}
}

void Studnia::wyczyscwiersze() {
	for (int wiersz : wierszedousuniecia) {
		for (int j = wiersz - 1; j > 0; j--) {
			SDL_Color* Kopia = new SDL_Color[kolumny];
			for (int i = 0; i < kolumny; i++)
				Kopia[i] = colors[i][j];
			for (int i = 0; i < kolumny; i++)
				colors[i][j + 1] = Kopia[i];
		}
	}
}
