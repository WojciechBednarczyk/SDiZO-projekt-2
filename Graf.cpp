#include "Graf.h"
#include<iostream>
#include<vector>
#include<list>
using namespace std;



//struct porownaj_krawedzie
//{
//	bool operator () (Krawedz& krawedz1, Krawedz& krawedz2)
//	{
//		if (krawedz1.waga > krawedz2.waga) return true;
//		if (krawedz1.waga < krawedz2.waga) return false;
//
//		return false;
//	}
//};


Graf::Graf(int ilosc_wierzcholkow, int ilosc_krawedzi)
{
	this->ilosc_wierzcholkow = ilosc_wierzcholkow;
	this->ilosc_krawedzi = ilosc_krawedzi;
	
	//tworzymy macierz incydencji za pomoca tablic
	macierz_incydencji = new int*[ilosc_wierzcholkow];
	macierz_wynikowa = new int* [ilosc_wierzcholkow];
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		vector<int> sasiedzi ;
		lista_sasiedztwa.push_back(sasiedzi);
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
	cout << "Macierz incydencji:\n\n";
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		for (int j = 0; j < ilosc_krawedzi; j++)
		{
			cout << macierz_incydencji[i][j] << " ";
		}
		cout << endl;
	}
}

void Graf::wyswietl_liste()
{
	cout << "Lista sasiedztwa:\n\n";
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << "Wierzcholek " << i << ": ";
		for (int j = 0; j < lista_sasiedztwa[i].size(); j++)
		{
			cout << lista_sasiedztwa[i][j]<<" ";
		}
		cout << endl;
	}
}


void Graf::dodaj_krawedz(char wybrany_problem,int krawedz,int wierzcholek_poczatkowy, int wierzcholek_koncowy,int waga)
{
	Krawedz nowa_krawedz;

	switch (wybrany_problem)
	{

	//grafy nieskierowane
	case '1':
		macierz_incydencji[wierzcholek_koncowy][krawedz] = 1;
		macierz_incydencji[wierzcholek_poczatkowy][krawedz] = 1;
		wagi_krawedzi.push_back(waga);
		nowa_krawedz.wierzcholek_poczatkowy = wierzcholek_poczatkowy;
		nowa_krawedz.wierzcholek_koncowy = wierzcholek_koncowy;
		nowa_krawedz.waga = waga;
		lista_krawedzi.push_back(nowa_krawedz);
		lista_sasiedztwa[wierzcholek_poczatkowy].push_back(wierzcholek_koncowy);
		lista_sasiedztwa[wierzcholek_koncowy].push_back(wierzcholek_poczatkowy);
		break;

	//grafy skierowane
	case '2':
		macierz_incydencji[wierzcholek_koncowy][krawedz] = -1;
		macierz_incydencji[wierzcholek_poczatkowy][krawedz] = 1;
		wagi_krawedzi.push_back(waga);
		nowa_krawedz.wierzcholek_poczatkowy = wierzcholek_poczatkowy;
		nowa_krawedz.wierzcholek_koncowy = wierzcholek_koncowy;
		nowa_krawedz.waga = waga;
		lista_krawedzi.push_back(nowa_krawedz);
		lista_sasiedztwa[wierzcholek_poczatkowy].push_back(wierzcholek_koncowy);
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
		//ustawiamy w macierzy wierzcholek koncowy i poczatkowy na 1
		for (list<Krawedz>::iterator iter = lista_krawedzi.begin(); iter != lista_krawedzi.end(); iter++)
		{
			if ((iter->wierzcholek_koncowy == najmniejszy_koszt_wierzcholek || iter->wierzcholek_poczatkowy) && iter->waga == najmniejsza_waga)
			{
				macierz_wynikowa[iter->wierzcholek_poczatkowy][i] = 1;
				macierz_wynikowa[iter->wierzcholek_koncowy][i] = 1;
				break;
			}
		}
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

void Graf::algorytm_Kruskala()
{
}
