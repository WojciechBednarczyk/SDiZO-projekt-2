#pragma once
#include<vector>
#include<list>
using namespace std;
class Graf
{

public:
	struct Krawedz
	{
		int wierzcholek_poczatkowy, wierzcholek_koncowy, waga;
	};
	struct porownaj_krawedzie
	{
		bool operator () (Krawedz& krawedz1, Krawedz& krawedz2)
		{
			if (krawedz1.waga < krawedz2.waga) return true;
			if (krawedz1.waga > krawedz2.waga) return false;

			return false;
		}
	};

	Graf(int ilosc_wierzcholkow, int ilosc_krawedzi);
	Graf(int losowy, int ilosc_wierzcholkow, int ilosc_krawedzi);
	~Graf();
	int get_ilosc_wierzcholkow();
	int set_ilosc_wierzcholkow(int ilosc_wierzcholkow);
	int set_ilosc_krawedzi(int ilosc_krawedzi);
	void stworz_macierz(int ilosc_wierzcholkow, int ilosc_krawedzi);
	void usun_Graf();
	void wyswietl_macierz();
	void wyswietl_liste();
	void dodaj_krawedz(int krawedz, int wierzcholek_poczatkowy, int wierzcholek_koncowy,int waga);
	bool sprawdz_krawedz(int wierzcholek_poczatkowy, int wierzcholek_koncowy);
	void algorytm_Prima();
	void algorytm_Kruskala();
	void algorytm_Djikstry(int wierzcholek_poczatkowy,int wierzcholek_koncowy);
	void algorytm_Bellmana_Forda(int wierzcholek_poczatkowy, int wierzcholek_koncowy);
	
	
private:
	int ilosc_wierzcholkow, ilosc_krawedzi;
	int** macierz_incydencji;
	int** macierz_wynikowa;
	vector<int> wagi_krawedzi;
	vector<int> koszt_wierzcholka;
	vector<int> zbadane_wierzcholki;
	vector<vector<int>> lista_sasiedztwa;
	vector<vector<int>> lista_wynikowa;
	vector<vector<int>> zbiory;
	vector<vector<int>> trasa;
	list<Krawedz> lista_krawedzi;
	
};
