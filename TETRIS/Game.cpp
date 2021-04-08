#include "Game.h"

using namespace std;

Game::Game() {
}

Game::~Game() {
}

void Game::initSDL(const char* title, int xpos, int ypos, int width, int height) {
    try {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            throw WyjatekSDL();
            isRunning = false;
        }
        else {
            if (TTF_Init() < 0) throw WyjatekTTF();
            window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);

            if (!window) {
                throw WyjatekSDL();
                isRunning = false;
            }

            renderer = SDL_CreateRenderer(window, -1, 0);

            if (renderer) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                throw WyjatekSDL();
                isRunning = false;
            }

            isRunning = true;
        }
    }
    catch (WyjatekTTF w) {
        w.komunikat();
    }
    catch (WyjatekSDL w) {
        w.komunikat();
    }
}

void Game::initTetris() {

    thread zaladujobrazki(ladujobrazki, ref(obrazki), ref(renderer));
    zaladujobrazki.join();

    thread odczytajPlik(odczytPliku, ref(Gracze));
    odczytajPlik.join();

    ekran = ekrany::START;
}

void Game::run()
{
    while (isRunning) {
    
        float delta = (curtick - lasttick) / 1000.0f;
        if (curtick - fpstick >= FPS_DELAY) {
            fps = (unsigned int)(framecount * (1000.0f / (curtick - fpstick)));
            fpstick = curtick;
            framecount = 0;
        }
        else {
            framecount++;
        }
        lasttick = curtick;

        render(delta);
        update(delta);
        handleEvents();
    }
}

void Game::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                gra->wLewo();
                break;
            case SDLK_RIGHT:
                gra->wPrawo();
                break;
            case SDLK_DOWN:
                gra->wDol();
                break;
            case SDLK_UP:
                gra->obrot();
                break;
            case SDLK_SPACE:
                gra->hardDrop();
                break;
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                switch (ekran) {
                case ekrany::START:
                    if (xMouse > obrazki[start]->dest.x && xMouse < obrazki[start]->dest.x + obrazki[start]->dest.w && yMouse > obrazki[start]->dest.y && yMouse < obrazki[start]->dest.y + obrazki[start]->dest.h) {
                        ekran = ekrany::MENU;
                    }
                    break;
                case ekrany::MENU:
                    if (xMouse > obrazki[nowagra]->dest.x && xMouse < obrazki[nowagra]->dest.x + obrazki[nowagra]->dest.w && yMouse > obrazki[nowagra]->dest.y && yMouse < obrazki[nowagra]->dest.y + obrazki[nowagra]->dest.h) {
                        ekran = ekrany::GRA;
                        gra = new LogikaGry();
                    }
                    else if (xMouse > obrazki[rankingP]->dest.x && xMouse < obrazki[rankingP]->dest.x + obrazki[rankingP]->dest.w && yMouse > obrazki[rankingP]->dest.y && yMouse < obrazki[rankingP]->dest.y + obrazki[rankingP]->dest.h) {
                        ekran = ekrany::RANKING;
                    }
                    else if (xMouse > obrazki[wyjdz]->dest.x && xMouse < obrazki[wyjdz]->dest.x + obrazki[wyjdz]->dest.w && yMouse > obrazki[wyjdz]->dest.y && yMouse < obrazki[wyjdz]->dest.y + obrazki[wyjdz]->dest.h) {
                        isRunning = false;
                    }
                    break;
                case ekrany::GRA:
                    if (xMouse > obrazki[pauzaP]->dest.x && xMouse < obrazki[pauzaP]->dest.x + obrazki[pauzaP]->dest.w && yMouse > obrazki[pauzaP]->dest.y && yMouse < obrazki[pauzaP]->dest.y + obrazki[pauzaP]->dest.h) {
                        ekran = ekrany::PAUZA;
                    }
                    break;
                case ekrany::PAUZA:
                    if (xMouse > obrazki[wznow]->dest.x && xMouse < obrazki[pauzaP]->dest.x + obrazki[wznow]->dest.w && yMouse > obrazki[wznow]->dest.y && yMouse < obrazki[wznow]->dest.y + obrazki[wznow]->dest.h) {
                        ekran = ekrany::GRA;
                    }
                    else if (xMouse > obrazki[menuP]->dest.x && xMouse < obrazki[menuP]->dest.x + obrazki[menuP]->dest.w && yMouse > obrazki[menuP]->dest.y && yMouse < obrazki[menuP]->dest.y + obrazki[menuP]->dest.h) {
                        ekran = ekrany::MENU;
                        gra = nullptr;
                    }
                    break;
                case ekrany::GAMEOVER:
                    if (xMouse > obrazki[nowagra]->dest.x && xMouse < obrazki[nowagra]->dest.x + obrazki[nowagra]->dest.w && yMouse > obrazki[nowagra]->dest.y && yMouse < obrazki[nowagra]->dest.y + obrazki[nowagra]->dest.h) {
                        ekran = ekrany::GRA;
                        gra = new LogikaGry();
                    }
                    else if (xMouse > obrazki[menuP]->dest.x && xMouse < obrazki[menuP]->dest.x + obrazki[menuP]->dest.w && yMouse > obrazki[menuP]->dest.y && yMouse < obrazki[menuP]->dest.y + obrazki[menuP]->dest.h) {
                        ekran = ekrany::MENU;
                    }
                    else if (xMouse > obrazki[rankingP]->dest.x && xMouse < obrazki[rankingP]->dest.x + obrazki[rankingP]->dest.w && yMouse > obrazki[rankingP]->dest.y && yMouse < obrazki[rankingP]->dest.y + obrazki[rankingP]->dest.h) {
                        ekran = ekrany::RANKING;
                    }
                    break;
                case ekrany::RANKING:
                    if (xMouse > obrazki[menuP]->dest.x && xMouse < obrazki[menuP]->dest.x + obrazki[menuP]->dest.w && yMouse > obrazki[menuP]->dest.y && yMouse < obrazki[menuP]->dest.y + obrazki[menuP]->dest.h) {
                        ekran = ekrany::MENU;
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        default:
            break;
        }
        SDL_GetMouseState(&xMouse, &yMouse);
    }
}

void Game::update(float delta) {
    if (gra) {
        gra->update();
    }
}

void Game::render(float delta) {
    SDL_SetRenderDrawColor(renderer, 24, 24, 24, 255);
    SDL_RenderClear(renderer);

    switch (ekran){ 
    case ekrany::START:
        obrazki[tetrisS]->setDest(105, 10);
        obrazki[tetrisS]->rysuj(renderer);
        obrazki[tetris]->setDest(60, 0);
        obrazki[tetris]->rysuj(renderer);
        obrazki[start]->setDest(140, 120);
        obrazki[start]->rysuj(renderer);
        break;
    case ekrany::MENU:
        obrazki[menuN]->setDest(95, 0);
        obrazki[menuN]->rysuj(renderer);
        obrazki[nowagra]->setDest(140, 150);
        obrazki[nowagra]->rysuj(renderer);
        obrazki[rankingP]->setDest(140, 250);
        obrazki[rankingP]->rysuj(renderer);
        obrazki[wyjdz]->setDest(140, 350);
        obrazki[wyjdz]->rysuj(renderer);
        break;
    case ekrany::GRA:
        ramka->rysuj(renderer,4, 4, 302, 602, 255, 255, 255);

        obrazki[pauzaP]->setDest(312, 546);
        obrazki[pauzaP]->rysuj(renderer);
        obrazki[nast]->setDest(316, 0);
        obrazki[nast]->rysuj(renderer);
        ///////////////////////////////////////////////////////
        if (gra->game_over) {
            Uzytkownik* gracz = new Uzytkownik();
            gra->punktacja();
            gra->wynik += (accumulate(gra->punkty.begin(), gra->punkty.end(), 0) + gra->linie * 10 + gra->poziom * 10);
            gracz->punkty = gra->wynik;
            Gracze.DodajWOdpowiednimMiejscu(gracz->nazwa, gracz->punkty);
            ekran = ekrany::GAMEOVER;
        }
        //////////////////////////////////////////////////////
        gra->studnia->rysuj(renderer);
        gra->nastepny->rysuj(renderer);
        if (gra->curr)
            gra->curr->bloczek->rysuj(renderer, gra->studnia, gra->curr->x, gra->curr->y, gra->curr->ostatni_wiersz);
        gra->nast->rysuj(renderer, gra->nastepny, 0, 0);

        break;
    case ekrany::PAUZA:
        obrazki[pauzaN]->setDest(95, 0);
        obrazki[pauzaN]->rysuj(renderer);
        obrazki[wznow]->setDest(140, 150);
        obrazki[wznow]->rysuj(renderer);
        obrazki[menuP]->setDest(140, 250);
        obrazki[menuP]->rysuj(renderer);
        break;
    case ekrany::GAMEOVER:
        obrazki[gameover]->setDest(50, 0);
        obrazki[gameover]->rysuj(renderer);
        tekst->rysuj(renderer, ("TWÓJ WYNIK: " + to_string(gra->wynik)).c_str(), 140, 100, 255, 255, 255);
        tekst->rysuj(renderer, ("POZIOM: " + to_string(gra->poziom)).c_str(), 140, 150, 255, 255, 255);
        tekst->rysuj(renderer, ("LINIE: " + to_string(gra->linie)).c_str(), 140, 200, 255, 255, 255);
        obrazki[nowagra]->setDest(140, 250);
        obrazki[nowagra]->rysuj(renderer);
        obrazki[menuP]->setDest(140, 350);
        obrazki[menuP]->rysuj(renderer);
        obrazki[rankingP]->setDest(140, 450);
        obrazki[rankingP]->rysuj(renderer);
        break;
    case ekrany::RANKING:
        obrazki[rankingN]->setDest(95, 0);
        obrazki[rankingN]->rysuj(renderer);
        for (int i = 0; i < 5; i++)
            tekst->rysuj(renderer, (Gracze.WypiszElementoID(i)).c_str(), 100, 100 + i*50, 255, 255, 255);
        obrazki[menuP]->setDest(140, 350);
        obrazki[menuP]->rysuj(renderer);
        break;
    default:
        break;
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    thread zapiszDoPliku(zapisDoPliku, Gracze);
    zapiszDoPliku.join();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}
