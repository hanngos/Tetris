#pragma once
#ifndef SZABLONY_H
#define SZABLONY_H
#include <memory>
#include <iostream>
#include <string>

using namespace std;

template<typename T>
T** tablica2D(int kolumny, int wiersze) {
	T **tablica = new T * [kolumny];
	for (int n = 0; n < kolumny; n++)
		tablica[n] = new T[wiersze];
	return tablica;
}
template<typename T>
void tablicadelete(T**tablica, int kolumny) {
    for (int i = 0; i < kolumny; i++)
        delete [] tablica[i];
    delete [] tablica;
}

template <class T1, class T2>
struct Element {
    T1 t1;
    T2 t2;
    shared_ptr<Element> pNext;
    Element(T1 t1, T2 t2) : t1(t1), t2(t2), pNext(nullptr) {};
};

template <class T1, class T2>
class Lista {
    shared_ptr<Element<T1, T2>> pHead;
    int dlugosc = 0;

public:
    void DodajWOdpowiednimMiejscu(T1 t1, T2 t2);
    void UsunListe();
    string WypiszDoString();
    string WypiszElementoID(int ID);
};

template<class T1, class T2>
void Lista<T1, T2>::DodajWOdpowiednimMiejscu(T1 t1, T2 t2)
{
    auto TMP = make_shared<Element<T1, T2>>(t1, t2);
    auto curr = move(TMP);
    if (!pHead || pHead->t2 < t2) {
        curr->pNext = pHead;
        pHead = curr;
        this->dlugosc++;
        return;
    }
    else {
        auto temp = pHead;
        while (temp->pNext) {
            if (temp->pNext->t2 <= t2) {
                curr->pNext = temp->pNext;
                temp->pNext = curr;
                this->dlugosc++;
                return;
            }
            temp = temp->pNext;
        }
        temp->pNext = curr;
        this->dlugosc++;
        return;
    }
}

template<class T1, class T2>
void Lista<T1, T2>::UsunListe()
{
    auto temp = pHead;
    while (pHead) {
        temp = pHead;
        pHead = pHead->pNext;
        temp.reset();
    }
    this->dlugosc = 0;
}

template<class T1, class T2>
string Lista<T1, T2>::WypiszDoString()
{
    string s;
    if (!pHead) s = "";
    else {
        auto temp = pHead;
        while (temp) {
            s += temp->t1 + " " + to_string(temp->t2) + "\n";
            temp = temp->pNext;
        }
    }
    return s;
}

template<class T1, class T2>
string Lista<T1, T2>::WypiszElementoID(int ID)
{
    string s = "";
    if (dlugosc >= ID + 1) {
        auto temp = pHead;
        for (int i = 0; i < ID; i++) {
            temp = temp->pNext;
        }
        s = to_string(ID + 1) + ".  " + temp->t1 + "    " + to_string(temp->t2);
    }
    return s;
}

#endif // !SZABLONY_H

