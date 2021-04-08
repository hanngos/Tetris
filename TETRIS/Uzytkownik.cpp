#include "Uzytkownik.h"

Uzytkownik::Uzytkownik() :r_nazwa("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)[A-Za-z\\d]{5,12}$") {
	this->pobierz_nazwe(this->r_nazwa);
}

void Uzytkownik::pobierz_nazwe(regex r) {
	cout << "PODAJ NAZWE" << endl;
	string s;
	cin >> s;
	while (!regex_match(s, r)) {
		cout << s << " nie jest poprawny! Podaj jeszcze raz!" << endl;
		cout << "Nazwa musi zawierac conajmniej jedna mala litere, jedna duza, cyfre i miec 5-12 znakow!" << endl;
		cin >> s;
	}
	this->nazwa = s;
}
