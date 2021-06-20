#include<iostream>
#include<fstream>
#include "Graf.h"
#include<queue>
#include<string>
#include<conio.h>
using namespace std;

void menu_MST(Graf& graf)
{
	int wybor;
	cout << endl;
	cout << "[WYZNACZANIE MINIMALNEGO DRZEWA ROZPINAJACEGO]\n\n";
	cout << "[1] Algorytm Prima\n";
	cout << "[2] Algorytm Kruskala\n";
	cin >> wybor;
	switch (wybor)
	{
	case 1:
		graf.algorytm_Prima();
		break;
	case 2:
		graf.algorytm_Kruskala();
		break;
	default:
		cout << "Podano zla opcje!";
		break;
	}
}
void najkrotsza_sciezka_menu(Graf &graf)
{
	int wybor;
	int wierzcholek_poczatkowy, wierzcholek_koncowy;
	cout << endl;
	cout << "[WYZNACZANIE NAJKROTSZEJ SCIEZKI W GRAFIE]\n\n";
	cout << "[1] Algorytm Dijkstry\n";
	cout << "[2] Algorytm Forda-Bellmana\n";
	cin >> wybor;
	switch (wybor)
	{
	case 1:
		cout << "Podaj wierzcholek startowy:";
		cin >> wierzcholek_poczatkowy;
		if (wierzcholek_poczatkowy > graf.get_ilosc_wierzcholkow()-1 || wierzcholek_poczatkowy < 0)
		{
			cout << "Podano zly wierzcholek!\n";
			break;
		}
		cout << "Podaj wierzcholek koncowy:";
		cin >> wierzcholek_koncowy;
		if (wierzcholek_koncowy > graf.get_ilosc_wierzcholkow()-1 || wierzcholek_koncowy < 0)
		{
			cout << "Podano zly wierzcholek!\n\n";
			break;
		}
		graf.algorytm_Djikstry(wierzcholek_poczatkowy,wierzcholek_koncowy);
		break;
	case 2:
		cout << "Podaj wierzcholek startowy:";
		cin >> wierzcholek_poczatkowy;
		if (wierzcholek_poczatkowy > graf.get_ilosc_wierzcholkow() - 1 || wierzcholek_poczatkowy < 0)
		{
			cout << "Podano zly wierzcholek!\n";
			break;
		}
		cout << "Podaj wierzcholek koncowy:";
		cin >> wierzcholek_koncowy;
		if (wierzcholek_koncowy > graf.get_ilosc_wierzcholkow() - 1 || wierzcholek_koncowy < 0)
		{
			cout << "Podano zly wierzcholek!\n\n";
			break;
		}
		graf.algorytm_Bellmana_Forda(wierzcholek_poczatkowy, wierzcholek_koncowy);
		break;
	default:
		break;
	}
}
void menu_Start(Graf &graf)
{
	int wybrany_problem;
	int ilosc_wierzcholkow;
	int ilosc_krawedzi;
	cout << "Wybierz problem do rozwiazania:\n";
	cout << "[1] Wyznaczanie minimalnego drzewa rozpinajacego\n";
	cout << "[2] Wyznaczanie najkrotszej sciezki w grafie\n";
	cout << "[3] Wyswietl dane o grafie\n";
	cout << "[4] Losuj graf\n";
	cout << "[5] Wyjdz\n";
	cin >> wybrany_problem;
	switch (wybrany_problem)
	{
	case 1:
		menu_MST(graf);
		_getch();
		menu_Start(graf);
		break;
	case 2:
		najkrotsza_sciezka_menu(graf);
		_getch();
		menu_Start(graf);
		break;
	case 3:
		graf.wyswietl_macierz();
		graf.wyswietl_liste();
		_getch();
		menu_Start(graf);
		break;
	case 4:
		cout << "Podaj ilosc wierzcholkow:";
		cin >> ilosc_wierzcholkow;
		cout << "Podaj ilosc krawedzi:";
		cin >> ilosc_krawedzi;
		_getch();
		menu_Start(graf);
		break;
	case 5:
		exit(0);
	default:
		cout << "Wybrano zla opcje!\n\n";
		menu_Start(graf);
		break;
	}
}

int main()
{
	int ilosc_wierzcholkow, ilosc_krawedzi;
	int wierzcholek_poczatkowy, wierzcholek_koncowy,waga;
	char wybrany_problem;
	cout << "SDIZO - zadanie projektowe 2\n";
	cout << "Autor: Wojciech Bednarczyk\n\n";
	//Tworymy graf z pliku tekstowego
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
		graf.dodaj_krawedz(i, wierzcholek_poczatkowy, wierzcholek_koncowy, waga);
	}
	menu_Start(graf);

	//graf.algorytm_Prima();

	
	//graf.algorytm_Djikstry(0, 3);
	//graf.algorytm_Bellmana_Forda(1, 4);
}
