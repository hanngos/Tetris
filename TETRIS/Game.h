#ifndef GAME_H_
#define GAME_H_

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include <thread>
#include <iostream>
#include "Colors.h"
#include "Obrazki.h"
#include "Watki.h"
#include "LogikaGry.h"
#include "Wyjatki.h"
#include "Tekst.h"
#include "Ramka.h"
#include "Uzytkownik.h"
#define FPS_DELAY 100

class Game {
public:
    Game();
    ~Game();
    void initSDL(const char* title, int xpos, int ypos, int width, int hight);
    void initTetris();
    void run();
    void update(float delta);
    void render(float delta);
    void clean();
    void handleEvents();
    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int xMouse, yMouse;
    unsigned int lasttick, curtick, fpstick, framecount, fps;

    enum class ekrany {MENU, GRA, PAUZA, GAMEOVER, RANKING, START };
    ekrany ekran;
    enum obrazek { tetris, menuN, menuP, nowagra, rankingN, rankingP, pauzaN, pauzaP, gameover, wznow, wyjdz, nast, tetrisS, start };

    vector<Obrazek*> obrazki;
    Lista<string, int> Gracze;
    LogikaGry* gra;
    Tekst* tekst;
    Ramka* ramka;

};

#endif /// GAME_H_