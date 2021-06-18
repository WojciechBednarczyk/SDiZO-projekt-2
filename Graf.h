#pragma once
#include<vector>
using namespace std;
class Graf
{

public:
	Graf(int ilosc_wierzcholkow, int ilosc_krawedzi);
	~Graf();
	void wyswietl_macierz();
	void dodaj_krawedz(char wybrany_problem,int krawedz, int wierzcholek_poczatkowy, int wierzcholek_koncowy,int waga);
	void algorytm_Prima();
	
private:
	int ilosc_wierzcholkow, ilosc_krawedzi;
	int** macierz_incydencji;
	int** macierz_wynikowa;
	vector<int> wagi_krawedzi;
	vector<int> koszt_wierzcholka;
	vector<int> zbadane_wierzcholki;
};
