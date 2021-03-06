//Szymon Lewandowski 22.12.2017
//Graficzne wyswietlanie drzewa BST na wzor zadania dodatkowego z laboratoriow
#include "stdafx.h"

#include<ctime>
#include<cstdlib>
#include<iostream>

using namespace std;

class Kulka {
public:
	Kulka() {
		wartosc_ = (rand() % 100) + 100;
		prawy_ = nullptr;
		lewy_ = nullptr;
		poziom_drzewa_ = 1;
	}

	void DodajKulkeDoDrzewa(Kulka* nowa) {
		if (wartosc_ <= nowa->wartosc_) {
			++(nowa->poziom_drzewa_);
			if (prawy_ == nullptr)
				prawy_ = nowa;
			else
				prawy_->DodajKulkeDoDrzewa(nowa);
		}
		else {
			++(nowa->poziom_drzewa_);
			if (lewy_ == nullptr)
				lewy_ = nowa;
			else
				lewy_->DodajKulkeDoDrzewa(nowa);
		}
	}

	void WyswietlDrzewo(int tab[]) {
		if (prawy_ != nullptr) Przejscie(prawy_, tab);
		RysowanieLinii(tab);
		if (lewy_ != nullptr)Przejscie(lewy_, tab);
	}

	void RysowanieLinii(int* tab){
		bool juz_wystapilo_w_drzewie = false;
		bool wyjatek = false;
		int poziom_wyjatku = 0;

		for (int i = 1; i < poziom_drzewa_; ++i)
			if (tab[i] == wartosc_)++juz_wystapilo_w_drzewie;
		if (juz_wystapilo_w_drzewie)++wartosc_;
		for (int i = 1; i < poziom_drzewa_; ++i) {
			if (tab[i] == wartosc_) {
				++wyjatek;
				poziom_wyjatku = i + 1;
			}
		}
		for (int i = 0; i < poziom_drzewa_; ++i) {
			if (i == 0)cout << ' ';
			else {
				if ((tab[i - 1] > wartosc_ &&
					tab[i] < wartosc_) || (tab[i - 1]<wartosc_ &&
						tab[i]>wartosc_)) cout << '|';
				else if (wyjatek &&
					(tab[poziom_wyjatku - 2]<tab[poziom_wyjatku - 1]) &&
					i == poziom_wyjatku - 1) cout << '|';
				else if (wyjatek && i == poziom_wyjatku) cout << '|';
				else cout << ' ';
			}
			cout << "      ";
		}
		if (juz_wystapilo_w_drzewie)--wartosc_;
		cout << "+--(" << wartosc_ << ')' << endl;
	}
	
	void Przejscie(Kulka* wskaznik, int* tab){
		tab[poziom_drzewa_] = wartosc_;
		wskaznik->WyswietlDrzewo(tab);
		tab[poziom_drzewa_] = 0;
	}

	int get_wartosc() const{ return wartosc_; }

private:
	int wartosc_;
	int poziom_drzewa_;
	Kulka* prawy_;
	Kulka* lewy_;
};

int main() {
	srand(time(nullptr));

	Kulka* korzen = new Kulka();
	Kulka* nowa;
	const int liczba_tworzonych_kulek = 40;
	for (int i = 1; i <liczba_tworzonych_kulek; ++i) {
		nowa = new Kulka();
		korzen->DodajKulkeDoDrzewa(nowa);
	}
	const int maksymalna_liczba_poziomow_drzewa = 20;
	// tab przechowuje wartosci kulek juz odwiedzonych (od korzenia do obecnej)
	int tab[maksymalna_liczba_poziomow_drzewa] = {};
	tab[0] = korzen->get_wartosc();
	korzen->WyswietlDrzewo(tab);

	return 0;
}