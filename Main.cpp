#include<iostream>
#include<fstream>
#include "Graf.h"
#include<queue>
using namespace std;



struct krawedz
{
	int wierzcholek_poczatkowy, wierzcholek_koncowy, waga;
};
struct porownaj_krawedzie
{
	bool operator () (krawedz &krawedz1, krawedz &krawedz2)
	{
		if (krawedz1.waga > krawedz2.waga) return true;
		if (krawedz1.waga < krawedz2.waga) return false;
		
		return false;
	}
};
priority_queue < krawedz, std::vector < krawedz >, porownaj_krawedzie> kolejkaPriorytetowa;
int main()
{
	int ilosc_wierzcholkow, ilosc_krawedzi;
	int wierzcholek_poczatkowy, wierzcholek_koncowy,waga;
	char wybrany_problem;
	cout << "SDIZO - zadanie projektowe 2\n";
	cout << "Autor: Wojciech Bednarczyk\n\n";
	cout << "Wybierz problem do rozwiazania:\n";
	cout << "[1] Wyznaczanie minimalnego drzewa rozpinajacego\n";
	cout << "[2] Wyznaczanie najkrotszej sciezki w grafie\n";
	cin >> wybrany_problem;
	ifstream plik;;
	plik.open("dane.txt");
	plik >> ilosc_wierzcholkow;
	plik >> ilosc_krawedzi;
	Graf graf(ilosc_wierzcholkow, ilosc_krawedzi);
	for (int i = 0; i < ilosc_krawedzi; i++)
	{
		plik >> wierzcholek_poczatkowy;
		plik >> wierzcholek_koncowy;
		plik >> waga;
		graf.dodaj_krawedz(wybrany_problem,i, wierzcholek_poczatkowy, wierzcholek_koncowy,waga);
		graf.wyswietl_macierz();
		cout << endl;
		
		//krawedz nowa_krawedz;
		//nowa_krawedz.waga = waga;
		//nowa_krawedz.wierzcholek_poczatkowy = wierzcholek_poczatkowy;
		//nowa_krawedz.wierzcholek_koncowy = wierzcholek_koncowy;
		//kolejkaPriorytetowa.push(nowa_krawedz);
	}
	/*for (int i = 0; i < ilosc_krawedzi; i++)
	{
		cout << kolejkaPriorytetowa.top().waga;
		kolejkaPriorytetowa.pop();
	}*/
	cout << endl;
	graf.wyswietl_macierz();
	cout << "\n\n";
	graf.algorytm_Prima();
	
}
