#include "CurrBloczek.h"

CurrBloczek::CurrBloczek(Studnia* studnia){
    x = 3;
    y = -2;
    bloczek = nullptr;
    this->studnia = studnia;
    ostatni_wiersz = OstatniWiersz();
}

CurrBloczek::CurrBloczek(const Bloczek& bloczek, Studnia* studnia)
{
    this->bloczek = new Bloczek(bloczek);
    x = 3;
    y = -2;
    this->studnia = studnia;
    ostatni_wiersz = OstatniWiersz();
}

int CurrBloczek::OstatniWiersz()
{
    int start = (0 > y) ? 0 : y;
    for (int wie = start; wie <= studnia->wiersze; wie++) {
        if (!Kolizja(bloczek->rozmiar_matrixa, bloczek->matrix, x, wie))
            return wie - 1;
    }
	return -1;
}

bool CurrBloczek::Kolizja(int rozmiar_matrixa, bool** matrix, int kol, int wie)
{
    for (int i = 0; i < rozmiar_matrixa; i++) {
        for (int j = 0; j < rozmiar_matrixa; j++) {
            if (matrix[i][j] && studnia->Zajete(kol + i, wie + j))
                return false;
        }
    }
    return true;
}

void CurrBloczek::update()
{
    ostatni_wiersz = OstatniWiersz();
}

