#include "Bloczek.h"

Bloczek::Bloczek(int n, int numery[], SDL_Color color)
{
	this->rozmiar_matrixa = n;
	matrix = tablica2D<bool>(n, n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
			matrix[i][j] = false;
	for (int i = 0; i < (sizeof(numery)); i++) {
		matrix[numery[i] % n][numery[i] / n] = true;
	}
	this->color = color;
}

Bloczek::Bloczek(const Bloczek& kopia)
{
	matrix= tablica2D<bool>(kopia.rozmiar_matrixa, kopia.rozmiar_matrixa);

	for (int i = 0; i < kopia.rozmiar_matrixa; i++)
		for (int j = 0; j < kopia.rozmiar_matrixa; j++)
			matrix[i][j] = kopia.matrix[i][j];

	this->color = kopia.color;
	this->rozmiar_matrixa = kopia.rozmiar_matrixa;
	}

void Bloczek::rysuj(SDL_Renderer* renderer)
{
}

void Bloczek::rysuj(SDL_Renderer* renderer, Studnia*studnia, int x, int y)
{
	for (int i = 0; i < this->rozmiar_matrixa; i++) {
		for (int j = 0; j < this->rozmiar_matrixa; j++) {
			if (this->matrix[i][j]) {
				studnia->rysujKsztalt(x + i, y + j, this->color, renderer);
			}
		}
	}
}

void Bloczek::rysuj(SDL_Renderer* renderer, Studnia* studnia, int x, int y, int ostatni_wiersz)
{
		for (int i = 0; i < this->rozmiar_matrixa; i++) {
			for (int j = 0; j < this->rozmiar_matrixa; j++) {
				if (this->matrix[i][j]) {
					studnia->rysujKsztalt(x + i, y + j, this->color, renderer);
					studnia->rysujObramowanie(x + i, ostatni_wiersz + j, renderer);
				}
			}
		}
}

