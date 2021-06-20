#include "Graf.h"
#include<iostream>
#include<vector>
#include<list>
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
		vector<int> sasiedzi ;
		vector<int> wierzcholek;
		lista_sasiedztwa.push_back(sasiedzi);
		lista_wynikowa.push_back(sasiedzi);
		zbiory.push_back(sasiedzi);
		zbiory[i].push_back(i);
		trasa.push_back(wierzcholek);
		trasa[i].push_back(i);
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

int Graf::get_ilosc_wierzcholkow()
{
	return ilosc_wierzcholkow;
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
	cout << endl;
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
	cout << endl;
}


void Graf::dodaj_krawedz(int krawedz,int wierzcholek_poczatkowy, int wierzcholek_koncowy,int waga)
{
	Krawedz nowa_krawedz;

		macierz_incydencji[wierzcholek_koncowy][krawedz] = 1;
		macierz_incydencji[wierzcholek_poczatkowy][krawedz] = 1;
		wagi_krawedzi.push_back(waga);
		nowa_krawedz.wierzcholek_poczatkowy = wierzcholek_poczatkowy;
		nowa_krawedz.wierzcholek_koncowy = wierzcholek_koncowy;
		nowa_krawedz.waga = waga;
		lista_krawedzi.push_back(nowa_krawedz);
		lista_sasiedztwa[wierzcholek_poczatkowy].push_back(wierzcholek_koncowy);
		lista_sasiedztwa[wierzcholek_koncowy].push_back(wierzcholek_poczatkowy);
}
void Graf::algorytm_Prima()
{
	
	int szukany_wierzcholek;
	int najmniejsza_waga;
	int najmniejszy_koszt_wierzcholek=0;
	int ilosc_wierzcholkow_do_zbadania=ilosc_wierzcholkow;
	bool czy_zbadany;
	int suma = 0;
	zbadane_wierzcholki.clear();
	//koszt_wierzcholka.clear();
	//for (int i = 0; i < ilosc_wierzcholkow; i++)
	//{
	//	koszt_wierzcholka.push_back(1000000);
	//}
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
				lista_wynikowa[iter->wierzcholek_poczatkowy].push_back(iter->wierzcholek_koncowy);
				lista_wynikowa[iter->wierzcholek_koncowy].push_back(iter->wierzcholek_poczatkowy);
				break;
			}
		}
	}
	
	//Wypisanie wynikow
	for (int i = 0; i < koszt_wierzcholka.size(); i++)
	{
		suma += koszt_wierzcholka[i];
	}
	cout << "Minimalne drzewo rozpinajace:"<<suma<<endl<<endl;
	cout << "Macierz wynikowa:\n";
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		
		for (int j = 0; j < ilosc_wierzcholkow - 1; j++)
		{
			cout << macierz_wynikowa[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Lista sasiedztwa wynikowa:\n";
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << "Wierzcholek " << i << ": ";
		for (int j = 0; j < lista_wynikowa[i].size(); j++)
		{
			cout << lista_wynikowa[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::algorytm_Kruskala()
{	
	bool wstaw;
	int  kolumna_macierzy = 0;
	zbadane_wierzcholki.clear();
	lista_krawedzi.sort(porownaj_krawedzie());
	for (list<Krawedz>::iterator iter = lista_krawedzi.begin(); iter != lista_krawedzi.end(); iter++)
	{
		if (zbiory[iter->wierzcholek_poczatkowy][0] != zbiory[iter->wierzcholek_koncowy][0])
		{
			for (int i = 0; i < zbiory.size(); i++)
			{

				if (zbiory[i][0] == zbiory[iter->wierzcholek_koncowy][0] && i!= iter->wierzcholek_koncowy)
				{
					zbiory[i][0] = zbiory[iter->wierzcholek_poczatkowy][0];
				}
			}
			zbiory[iter->wierzcholek_koncowy][0] = zbiory[iter->wierzcholek_poczatkowy][0];
			lista_wynikowa[iter->wierzcholek_poczatkowy].push_back(iter->wierzcholek_koncowy);
			lista_wynikowa[iter->wierzcholek_koncowy].push_back(iter->wierzcholek_poczatkowy);
			macierz_wynikowa[iter->wierzcholek_poczatkowy][kolumna_macierzy] = 1;
			macierz_wynikowa[iter->wierzcholek_koncowy][kolumna_macierzy] = 1;
			kolumna_macierzy++;
		}
	}

	//Wypisanie wynikow
	cout << "Macierz wynikowa:\n";
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{

		for (int j = 0; j < ilosc_wierzcholkow - 1; j++)
		{
			cout << macierz_wynikowa[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Lista sasiedztwa wynikowa:\n";
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << "Wierzcholek " << i << ": ";
		for (int j = 0; j < lista_wynikowa[i].size(); j++)
		{
			cout << lista_wynikowa[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graf::algorytm_Djikstry(int wierzcholek_poczatkowy, int wierzcholek_koncowy)
{
	koszt_wierzcholka.clear();
	zbadane_wierzcholki.clear();

	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		koszt_wierzcholka.push_back(1000000);
	}
	koszt_wierzcholka[wierzcholek_poczatkowy] = 0;
	int badany_wierzcholek=wierzcholek_poczatkowy;
	bool czy_zbadany_wierzcholek;
	int calkowity_koszt = 0;
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		calkowity_koszt = koszt_wierzcholka[badany_wierzcholek];
		for (list<Krawedz>::iterator iter = lista_krawedzi.begin(); iter != lista_krawedzi.end(); iter++)
		{
			if (iter->wierzcholek_poczatkowy == badany_wierzcholek)
			{
				if (iter->waga < koszt_wierzcholka[iter->wierzcholek_koncowy])
				{
					koszt_wierzcholka[iter->wierzcholek_koncowy] = iter->waga+calkowity_koszt;
					trasa[iter->wierzcholek_koncowy].clear();
					for (int j = 0; j < trasa[iter->wierzcholek_poczatkowy].size(); j++)
					{
						trasa[iter->wierzcholek_koncowy].push_back(trasa[iter->wierzcholek_poczatkowy][j]);
					}
					trasa[iter->wierzcholek_koncowy].push_back(iter->wierzcholek_koncowy);
				}
			}
		}
		zbadane_wierzcholki.push_back(badany_wierzcholek);
		int najmniejszy_koszt = 1000000;

		for (int j = 0; j < ilosc_wierzcholkow; j++)
		{
			czy_zbadany_wierzcholek = false;
			for (int k = 0; k < zbadane_wierzcholki.size(); k++)
			{
				if (zbadane_wierzcholki[k] == j)
				{
					czy_zbadany_wierzcholek = true;
					break;
				}
			}
			if (czy_zbadany_wierzcholek == false)
			{
				if (koszt_wierzcholka[j] < najmniejszy_koszt)
				{
					badany_wierzcholek = j;
					najmniejszy_koszt = koszt_wierzcholka[j];
					calkowity_koszt += koszt_wierzcholka[badany_wierzcholek];
				}
			}
		}
	

	}
	cout << "Najkrotsza sciezka od wierzcholka "<<wierzcholek_poczatkowy<<" do wierzcholka " << wierzcholek_koncowy << " wynosi " << koszt_wierzcholka[wierzcholek_koncowy];
	cout << "\n\nTrasa: ";
		for (int j = 0; j < trasa[wierzcholek_koncowy].size()-1; j++)
		{
			cout << trasa[wierzcholek_koncowy][j] << " -> ";
		}
		cout << trasa[wierzcholek_koncowy][trasa[wierzcholek_koncowy].size()-1];
		cout << endl;

}

void Graf::algorytm_Bellmana_Forda(int wierzcholek_poczatkowy, int wierzcholek_koncowy)
{
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		koszt_wierzcholka.push_back(1000000);
	}

	bool czy_zmiana;
	koszt_wierzcholka[wierzcholek_poczatkowy] = 0;
	int* poprzednicy = new int[ilosc_wierzcholkow];
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		poprzednicy[i] = i;;
	}
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		czy_zmiana = false;
		for (int j = 0; j < ilosc_wierzcholkow; j++)
		{
			if (koszt_wierzcholka[j] == 1000000)
			{
				continue;
			}
			else
			{
				for (list<Krawedz>::iterator iter = lista_krawedzi.begin(); iter != lista_krawedzi.end(); iter++)
				{
					if (iter->wierzcholek_poczatkowy == j)
					{
						if (iter->waga + koszt_wierzcholka[iter->wierzcholek_poczatkowy]< koszt_wierzcholka[iter->wierzcholek_koncowy])
						{
							czy_zmiana = true;
							koszt_wierzcholka[iter->wierzcholek_koncowy] = iter->waga + koszt_wierzcholka[iter->wierzcholek_poczatkowy];
							poprzednicy[iter->wierzcholek_koncowy] = iter->wierzcholek_poczatkowy;
						}
					}
				}
			}
			
		}
		if (czy_zmiana == false)
		{
			break;
		}
	}
	for (int  i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << poprzednicy[i] << endl;
	}
	cout << endl;
	int ostatni_wierzcholek = wierzcholek_koncowy;
	if (poprzednicy[ostatni_wierzcholek] == ostatni_wierzcholek)
	{
		cout << "Nie ma polaczenia miedzy wierzcholkiem " << wierzcholek_poczatkowy << " a wierzcholkiem " << wierzcholek_koncowy << endl;
	}
	else
	{
		cout << "Najkrotsza sciezka od wierzcholka " << wierzcholek_poczatkowy << " do wierzcholka " << wierzcholek_koncowy << " wynosi " << koszt_wierzcholka[wierzcholek_koncowy];
		cout << endl;
		cout << "Trasa: ";
		cout << ostatni_wierzcholek<<" <- ";
		while (poprzednicy[ostatni_wierzcholek] != wierzcholek_poczatkowy)
		{
			cout << poprzednicy[ostatni_wierzcholek] << " <- ";
			ostatni_wierzcholek = poprzednicy[ostatni_wierzcholek];
		}
		cout << wierzcholek_poczatkowy;
	}
	
}
