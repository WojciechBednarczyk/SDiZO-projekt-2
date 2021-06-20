#include<iostream>
#include<fstream>
#include "Graf.h"
#include<queue>
using namespace std;

void menu_Start()
{
	int wybrany_problem;
	cout << "SDIZO - zadanie projektowe 2\n";
	cout << "Autor: Wojciech Bednarczyk\n\n";
	cout << "Wybierz problem do rozwiazania:\n";
	cout << "[1] Wyznaczanie minimalnego drzewa rozpinajacego\n";
	cout << "[2] Wyznaczanie najkrotszej sciezki w grafie\n";
	cin >> wybrany_problem;
	switch (wybrany_problem)
	{
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}
int main()
{
	int ilosc_wierzcholkow, ilosc_krawedzi;
	int wierzcholek_poczatkowy, wierzcholek_koncowy,waga;
	char wybrany_problem;
	
	
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
		graf.dodaj_krawedz(wybrany_problem, i, wierzcholek_poczatkowy, wierzcholek_koncowy, waga);
	}
	cout << endl;
	graf.wyswietl_macierz();
	cout << endl;
	graf.wyswietl_liste();
	/*cout << endl;
	graf.algorytm_Prima();*/
	/*cout << endl;
	graf.algorytm_Kruskala();
	*/
	graf.algorytm_Djikstry(0, 3);
	//graf.algorytm_Bellmana_Forda(1, 4);
}
