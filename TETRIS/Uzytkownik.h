#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H
#include <iostream>
#include <regex>
using namespace std;

class Uzytkownik {
	regex r_nazwa;
public:
	string nazwa;
	int punkty = 0;
	Uzytkownik();
	void pobierz_nazwe(regex r);
};

#endif // !UZYTKOWNIK_H
