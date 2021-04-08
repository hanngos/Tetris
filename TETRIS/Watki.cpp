#include "Watki.h"

void odczytPliku(Lista<string, int>& Lista) {
    fstream infile;
    infile.open("Ranking.txt", ios::in);
    try {
        if (infile.good() == true) {
            while (!infile.eof()) {
                string nazwa;
                int punkty;
                infile >> nazwa >> punkty;
                if (nazwa != "")
                    Lista.DodajWOdpowiednimMiejscu(nazwa, punkty);
            }
            infile.close();
        }
        else throw WyjatekPlik();
    }
    catch (WyjatekPlik p) {
        p.komunikat();
    }
}

void zapisDoPliku(Lista<string, int> Lista) {
    fstream file;
    file.open("Ranking.txt", ios::out);
    try {
        if (file.good() == true) {
            string s = Lista.WypiszDoString();
            file << s;
            file.close();
        }
        else throw WyjatekPlik();
    }
    catch (WyjatekPlik p) {
        p.komunikat();
    }
}

void ladujobrazki(vector<Obrazek*>& obrazki, SDL_Renderer*& renderer)
{
    Obrazek* tetris = new Obrazek();
    tetris->setSrc(0, 0, 380, 110);
    tetris->setImage("tetris.png", renderer);
    obrazki.push_back(tetris);
    Obrazek* menuN = new Obrazek();
    menuN->setSrc(0, 0, 310, 90);
    menuN->setImage("menuN.png", renderer);
    obrazki.push_back(menuN);
    Obrazek* menup = new Obrazek();
    menup->setSrc(0, 0, 220, 70);
    menup->setImage("menup.png", renderer);
    obrazki.push_back(menup);
    Obrazek* nowagra = new Obrazek();
    nowagra->setSrc(0, 0, 220, 70);
    nowagra->setImage("nowagra.png", renderer);
    obrazki.push_back(nowagra);
    Obrazek* rankingN = new Obrazek();
    rankingN->setSrc(0, 0, 310, 90);
    rankingN->setImage("rankingN.png", renderer);
    obrazki.push_back(rankingN);
    Obrazek* rankingP = new Obrazek();
    rankingP->setSrc(0, 0, 220, 70);
    rankingP->setImage("rankingP.png", renderer);
    obrazki.push_back(rankingP);
    Obrazek* pauzaN = new Obrazek();
    pauzaN->setSrc(0, 0, 310, 90);
    pauzaN->setImage("pauzaN.png", renderer);
    obrazki.push_back(pauzaN);
    Obrazek* pauzaP = new Obrazek();
    pauzaP->setSrc(0, 0, 170, 60);
    pauzaP->setImage("pauzaP.png", renderer);
    obrazki.push_back(pauzaP);
    Obrazek* gameover = new Obrazek();
    gameover->setSrc(0, 0, 400, 90);
    gameover->setImage("gameover.png", renderer);
    obrazki.push_back(gameover);
    Obrazek* wznow = new Obrazek();
    wznow->setSrc(0, 0, 220, 70);
    wznow->setImage("wznow.png", renderer);
    obrazki.push_back(wznow);
    Obrazek* wyjdz = new Obrazek();
    wyjdz->setSrc(0, 0, 220, 70);
    wyjdz->setImage("wyjdz.png", renderer);
    obrazki.push_back(wyjdz);
    Obrazek* nast = new Obrazek();
    nast->setSrc(0, 0, 170, 55);
    nast->setImage("nast.png", renderer);
    obrazki.push_back(nast);
    Obrazek* tetrisS = new Obrazek();
    tetrisS->setSrc(0, 0, 300, 600);
    tetrisS->setImage("tetrisS.png", renderer);
    obrazki.push_back(tetrisS);
    Obrazek* start = new Obrazek();
    start->setSrc(0, 0, 220, 70);
    start->setImage("start.png", renderer);
    obrazki.push_back(start);
}

void RTTI(vector<Bloczek*>& bloczki, Bloczek* nast) {
    if (typeid(*nast) == typeid(I)) {
        I* b = dynamic_cast<I*>(nast);
        bloczki.push_back(b);
    }
    else if (typeid(*nast) == typeid(O)) {
        O* b = dynamic_cast<O*>(nast);
        bloczki.push_back(b);
    }
    else if (typeid(*nast) == typeid(T)) {
        T* b = dynamic_cast<T*>(nast);
        bloczki.push_back(b);
    }
    else if (typeid(*nast) == typeid(S)) {
        S* b = dynamic_cast<S*>(nast);
        bloczki.push_back(b);
    }
    else if (typeid(*nast) == typeid(Z)) {
        Z* b = dynamic_cast<Z*>(nast);
        bloczki.push_back(b);
    }
    else if (typeid(*nast) == typeid(J)) {
        J* b = dynamic_cast<J*>(nast);
        bloczki.push_back(b);
    }
    else if (typeid(*nast) == typeid(L)) {
        L* b = dynamic_cast<L*>(nast);
        bloczki.push_back(b);
    }
}
