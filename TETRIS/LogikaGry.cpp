#include "LogikaGry.h"

LogikaGry::LogikaGry()
{
	studnia = new Studnia(5, 5, 300, 600, 20, 10);
    nastepny = new Studnia(355, 80, 100, 50, 2, 4);
    bloczki[0] = new I();
    bloczki[1] = new J();
    bloczki[2] = new L();
    bloczki[3] = new O();
    bloczki[4] = new S();
    bloczki[5] = new T();
    bloczki[6] = new Z();
    nast = bloczki[rand() % 7];
    ladujNast();

}

LogikaGry::~LogikaGry()
{
    tablicadelete(bloczki, 7);
    tablicadelete(studnia->colors, studnia->kolumny);
    tablicadelete(nastepny->colors, nastepny->kolumny);
    tablicadelete(nast->matrix, nast->rozmiar_matrixa);
    delete nast;
    delete curr;
    delete studnia;
    delete nastepny;
}

void LogikaGry::ladujNast()
{
    curr = new CurrBloczek(*nast, studnia);
    nast = bloczki[rand() % 7];
    currTime = 0;
    thread RTTI(RTTI, ref(bloczkiwgrze), nast);
    RTTI.join();
    game_over = !curr->Kolizja(curr->bloczek->rozmiar_matrixa, curr->bloczek->matrix, 3, -1);
    sprawdzenie();
}

void LogikaGry::sprawdzenie()
{
    if (linie - (poziom - 1) * 10 >= 10) {
        poziom++;
        if (poziom == 6)
            game_over = true;
        timer -= 200;
    }
}

void LogikaGry::update()
{
    currTime++;
    if (curr)
        curr->update();
    if (currTime >= timer && studnia->animacja == -1) {
        krokWDol();
        currTime = 0;
    }
}

void LogikaGry::koniecTury()
{
    for (int i = 0; i < curr->bloczek->rozmiar_matrixa; i++)
        for (int j = 0; j < curr->bloczek->rozmiar_matrixa; j++)
            if (curr->bloczek->matrix[i][j] && j + curr->y >= 0) {
                studnia->colors[i + curr->x][j + curr->y] = curr->bloczek->color;
            }
    if (sprawdzwiersze()) {
        curr = nullptr;
        studnia->animacja = 0;
    }
    else
        curr = nullptr;

    ladujNast();
}

void LogikaGry::hardDrop()
{
    curr->y = curr->ostatni_wiersz;
    wynik += (studnia->wiersze - curr->y);
}

void LogikaGry::krokWDol()
{
    if (curr->y >= curr->ostatni_wiersz) {
        koniecTury();
    }
    else {
        curr->y++;
        currTime = 0;
    }
}

void LogikaGry::wDol()
{
    if (curr->y >= curr->ostatni_wiersz) {
        koniecTury();
    }
    else {
        krokWDol();
        wynik += 1;
    }
}

void LogikaGry::wPrawo()
{
    if (curr->Kolizja(curr->bloczek->rozmiar_matrixa, curr->bloczek->matrix, curr->x + 1, curr->y))
        curr->x++;
    curr->update();
}

void LogikaGry::wLewo()
{
    if (curr->Kolizja(curr->bloczek->rozmiar_matrixa, curr->bloczek->matrix, curr->x - 1, curr->y))
        curr->x--;
    curr->update();
}

void LogikaGry::obrot()
{
    bool** obr;
    obr = tablica2D<bool>(curr->bloczek->rozmiar_matrixa, curr->bloczek->rozmiar_matrixa);
    
    for (int x = 0; x < curr->bloczek->rozmiar_matrixa; ++x)
        for (int y = 0; y < curr->bloczek->rozmiar_matrixa; ++y)
            obr[x][y] = curr->bloczek->matrix[y][curr->bloczek->rozmiar_matrixa - 1 - x];
    if (curr->Kolizja(curr->bloczek->rozmiar_matrixa, obr, curr->x, curr->y)) {
        curr->bloczek->matrix = obr;
        curr->update();
    }
    else if (curr->Kolizja(curr->bloczek->rozmiar_matrixa, obr, curr->x + 1, curr->y)) {
        curr->bloczek->matrix = obr;
        wPrawo();
    }
    else if (curr->Kolizja(curr->bloczek->rozmiar_matrixa, obr, curr->x - 1, curr->y)) {
        curr->bloczek->matrix = obr;
        wLewo();
    }
}

bool LogikaGry::sprawdzwiersze() {
    studnia->wierszedousuniecia.clear();
    for (int j = 0; j < studnia->wiersze; ++j) {
        int count = 0;
        for (int i = 0; i < studnia->kolumny; ++i)
            if (studnia->Zajete(i, j))
                count++;
        if (count >= studnia->kolumny)
            studnia->wierszedousuniecia.push_back(j);
    }
    if (studnia->wierszedousuniecia.empty())
        return false;

    linie += studnia->wierszedousuniecia.size();
    return true;
}

template<class T>
bool is(Bloczek* i) { return (typeid(T) == typeid(*i)); };

void LogikaGry::punktacja()
{
    punkty.push_back((bloczki[0]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<I>));//I
    punkty.push_back((bloczki[1]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<O>));//O
    punkty.push_back((bloczki[2]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<T>));//T
    punkty.push_back((bloczki[3]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<S>));//S
    punkty.push_back((bloczki[4]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<Z>));//Z
    punkty.push_back((bloczki[5]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<J>));//J
    punkty.push_back((bloczki[6]->zwrocwage()) * count_if(bloczkiwgrze.begin(), bloczkiwgrze.end(), is<L>));//L
}

