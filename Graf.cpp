#include "Graf.h"
#include<iostream>
#include<vector>
using namespace std;


Graf::Graf(int ilosc_wierzcholkow, int ilosc_krawedzi)
{
	this->ilosc_wierzcholkow = ilosc_wierzcholkow;
	this->ilosc_krawedzi = ilosc_krawedzi;
	
	//tworzymy macierz incydencji za pomoca tablic
	macierz_incydencji = new int*[ilosc_wierzcholkow];
	macierz_wynikowa = new int* [ilosc_wierzcholkow];
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		koszt_wierzcholka.push_back(1000000);
		macierz_incydencji[i] = new int[ilosc_krawedzi];
		macierz_wynikowa[i] = new int[ilosc_wierzcholkow-1];
		//wypelniamy macierz zerami
		for (int j = 0; j < ilosc_krawedzi; j++)
		{
			macierz_incydencji[i][j] = 0;
		}

		//wypelniamy macierz wynikowa zerami
		for (int k = 0; k < ilosc_wierzcholkow-1; k++)
		{
			macierz_wynikowa[i][k] = 0;
		}

	}
	
}

Graf::~Graf()
{
}

void Graf::wyswietl_macierz()
{
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		for (int j = 0; j < ilosc_krawedzi; j++)
		{
			cout << macierz_incydencji[i][j] << " ";
		}
		cout << endl;
	}
}

void Graf::dodaj_krawedz(char wybrany_problem,int krawedz,int wierzcholek_poczatkowy, int wierzcholek_koncowy,int waga)
{
	switch (wybrany_problem)
	{
	case '1':
		macierz_incydencji[wierzcholek_koncowy][krawedz] = 1;
		macierz_incydencji[wierzcholek_poczatkowy][krawedz] = 1;
		wagi_krawedzi.push_back(waga);
		break;
	case '2':
		macierz_incydencji[wierzcholek_koncowy][krawedz] = -1;
		macierz_incydencji[wierzcholek_poczatkowy][krawedz] = 1;
		wagi_krawedzi.push_back(waga);
		break;
	default:
		break;
	}

}
void Graf::algorytm_Prima()
{
	
	int szukany_wierzcholek;
	int najmniejsza_waga;
	int najmniejszy_koszt_wierzcholek=0;
	int ilosc_wierzcholkow_do_zbadania=ilosc_wierzcholkow;
	bool czy_zbadany;
	int suma = 0;
	koszt_wierzcholka[0] = 0;

	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		najmniejsza_waga = 100000;
		macierz_wynikowa[najmniejszy_koszt_wierzcholek][i]=1;
		cout << "Wybrany wierzcholek:" << najmniejszy_koszt_wierzcholek << endl;
		for (int j = 0; j < ilosc_krawedzi; j++)
		{
			szukany_wierzcholek = 0;
			czy_zbadany = false;
			if (macierz_incydencji[najmniejszy_koszt_wierzcholek][j] == 1)
			{	
				//szukamy wierzcholka koncowego
				while (true)
				{
					if(macierz_incydencji[szukany_wierzcholek][j]==1 && szukany_wierzcholek!=najmniejszy_koszt_wierzcholek)
					break;
					szukany_wierzcholek++;
				}
				//sprawdzamy czy zbadalismy juz wierzcholek
				for (int h = 0; h < zbadane_wierzcholki.size(); h++)
				{
					if (szukany_wierzcholek == zbadane_wierzcholki[h])
					{
						czy_zbadany = true;
						break;
					}
				}
				//zmniejszamy koszt wierzcholka jesli znalezlismy "lepsza" krawedz i wierzcholek nie byl badany
				if (wagi_krawedzi[j] < koszt_wierzcholka[szukany_wierzcholek] && czy_zbadany==false)
				{
					koszt_wierzcholka[szukany_wierzcholek] = wagi_krawedzi[j];
				}
			}


		}
		//dodajemy wierzcholek do zbadanych
		zbadane_wierzcholki.push_back(najmniejszy_koszt_wierzcholek);

		//ustawianie kolejnego badanego wierzcholka
		for (int k = 0; k < ilosc_wierzcholkow; k++)
		{
			czy_zbadany = false;
			cout << koszt_wierzcholka[k] << endl;
			if (koszt_wierzcholka[k] < najmniejsza_waga)
			{
				//sprawdzamy czy wierzcholek byl juz badany
				for (int h = 0; h < zbadane_wierzcholki.size(); h++)
				{
					if (k == zbadane_wierzcholki[h])
					{
						czy_zbadany = true;
						break;
					}
				}
				if (czy_zbadany == false)
				{
					najmniejsza_waga = koszt_wierzcholka[k];
					najmniejszy_koszt_wierzcholek = k;
				}
				
			}
				
		}
		macierz_wynikowa[najmniejszy_koszt_wierzcholek][i] = 1;
		cout << "\n\n";
	}
	for (int i = 0; i < koszt_wierzcholka.size(); i++)
	{
		suma += koszt_wierzcholka[i];
	}
	cout << "Minimalne drzewo rozpinajace:"<<suma<<endl;
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		for (int j = 0; j < ilosc_wierzcholkow - 1; j++)
		{
			cout << macierz_wynikowa[i][j] << " ";
		}
		cout << endl;
	}

}
