#include "Pole.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Okno.h"


int ile = 0, trafiony = 0;

Pole::Pole()
{
	for (int i = 0; i < 100; i++)
	{
		SiatkaA[i] = 0;
		SiatkaB[i] = 0;
	}
	statki1 = 4;	statki2 = 3;	statki3 = 2;	statki4 = 1;
	Generuj();
	statki1 = 4;	statki2 = 3;	statki3 = 2;	statki4 = 1;
	text = L"Rozmieść statki  4X:1  3X:2  2X:3  1X:4";


}

Pole::~Pole()
{
	
}

int Pole::Ustaw(int Xp, int Yp, int Xk, int Yk)
{
	//uklad 0= pionowo uklad 1= poziomo
	int pom, gra;
	std::string spom;
	if (statki4 == 0 && statki3 == 0 && statki2 == 0 && statki1 == 0)
	{
		gra = Rozgrywka(Xp, Yp);
		return 2;
	}
	Xp = (Xp - 76) / 32;
	Yp = (Yp - 147) / 32;
	Xk = (Xk - 76) / 32;
	Yk = (Yk - 147) / 32;

	if (Xp >= 0 && Xk >= 0 && Yp >= 0 && Yk >= 0 && Xp < 10 && Xk < 10 && Yp < 10 && Yk < 10)
	{

		//	JEDNOMASZTOWIEC
		if (Xp == Xk && Yp == Yk && statki1 > 0)
		{
			pom = Xp * 10 + Yk;
			if (Sprawdz(1, pom, 0, 0) == 1)
			{

				statki1--;
				trafA[statki1] = pom;
			}
		}
		//	DWUMASZTOWIEC
		if (((Xp == Xk + 1 || Xp == Xk - 1) && Yp == Yk) || (Xp == Xk && (Yp == Yk + 1 || Yp == Yk - 1)))
		{
			if (statki2 > 0)
			{
				if (Xp == Xk)
				{
					if (Yp < Yk)pom = Xp * 10 + Yp;
					else pom = Xp * 10 + Yk;
					if (Sprawdz(2, pom, 1, 0) == 1)
					{
						trafA[(statki2 * 2 + 3)] = pom;
						trafA[(statki2 * 2 + 2)] = pom + 1;
						statki2--;

					}
				}
				else
				{
					if (Xp < Xk)pom = Xp * 10 + Yp;
					else pom = Xk * 10 + Yp;
					if (Sprawdz(2, pom, 0, 0) == 1)
					{
						trafA[(statki2 * 2 + 3)] = pom;
						trafA[(statki2 * 2 + 2)] = pom + 10;
						statki2--;

					}
				}
			}
		}
		//TRZYMASZTOWIEC
		if (((Xp == Xk + 2 || Xp == Xk - 2) && Yp == Yk) || (Xp == Xk && (Yp == Yk + 2 || Yp == Yk - 2)))
		{
			if (statki3 > 0)
			{
				if (Xp == Xk)
				{
					if (Yp < Yk)pom = Xp * 10 + Yp;
					else pom = Xp * 10 + Yk;
					if (Sprawdz(3, pom, 1, 0) == 1)
					{
						statki3--;
						trafA[(statki3 * 3 + 12)] = pom;
						trafA[(statki3 * 3 + 11)] = pom + 1;
						trafA[(statki3 * 3 + 10)] = pom + 2;


					}
				}
				else
				{
					if (Xp < Xk)pom = Xp * 10 + Yp;
					else pom = Xk * 10 + Yp;
					if (Sprawdz(3, pom, 0, 0) == 1)
					{
						statki3--;
						trafA[(statki3 * 3 + 12)] = pom;
						trafA[(statki3 * 3 + 11)] = pom + 10;
						trafA[(statki3 * 3 + 10)] = pom + 20;


					}
				}
			}
		}
		//CZTEROMASZTOWIEC
		if (((Xp == Xk + 13 || Xp == Xk - 3) && Yp == Yk) || (Xp == Xk && (Yp == Yk + 3 || Yp == Yk - 3)))
		{
			if (statki4 > 0)
			{
				if (Xp == Xk)
				{
					if (Yp < Yk)pom = Xp * 10 + Yp;
					else pom = Xp * 10 + Yk;
					if (Sprawdz(4, pom, 1, 0) == 1)
					{
						statki4--;
						trafA[19] = pom;
						trafA[18] = pom + 1;
						trafA[17] = pom + 2;
						trafA[16] = pom + 3;
					}
				}
				else
				{
					if (Xp < Xk)pom = Xp * 10 + Yp;
					else pom = Xk * 10 + Yp;
					if (Sprawdz(4, pom, 0, 0) == 1)
					{
						statki4--;
						trafA[19] = pom;
						trafA[18] = pom + 10;
						trafA[17] = pom + 20;
						trafA[16] = pom + 30;
					}
				}
			}
		}
		if (statki4 == 0 && statki3 == 0 && statki2 == 0 && statki1 == 0)
		{
			return 1;
		}
	}

	text = L"Rozmieść statki  4X:" + std::to_string(statki4) + "  3X:" + std::to_string(statki3) + "  2X:" + std::to_string(statki2) + "  1X:" + std::to_string(statki1);

	return 1;


}

int Pole::Sprawdz(int ile, int poz, int kierunek, int gracz)
{
	int licznik = 0, start = poz, petla, dziesiatki, jednosci;

	for (int i = 0; i < ile; i++)
	{
		if (kierunek == 1)
		{
			start = poz + i;
			for (int j = 0; j < 9; j++)
			{
				dziesiatki = start / 10 + j / 3 - 1;
				jednosci = start % 10 + j % 3 - 1;
				petla = dziesiatki * 10 + jednosci;
				if (gracz == 0 && petla >= 0 && petla < 100 && dziesiatki == petla / 10 && jednosci == petla % 10)
				{
					if (SiatkaA[petla] == 2)licznik++;

				}
				if (gracz == 1 && petla >= 0 && petla < 100 && dziesiatki == petla / 10 && jednosci == petla % 10)
				{
					if (SiatkaB[petla] == 2)licznik++;
				}
			}
		}
		else
		{
			start = poz + i * 10;
			for (int j = 0; j < 9; j++)
			{
				dziesiatki = start / 10 + j / 3 - 1;
				jednosci = start % 10 + j % 3 - 1;
				petla = dziesiatki * 10 + jednosci;
				if (gracz == 0 && petla >= 0 && petla < 100 && dziesiatki == petla / 10 && jednosci == petla % 10)
				{
					if (SiatkaA[petla] == 2)licznik++;

				}
				if (gracz == 1 && petla >= 0 && petla < 100 && dziesiatki == petla / 10 && jednosci == petla % 10)
				{
					if (SiatkaB[petla] == 2)licznik++;
				}
			}
		}
	}
	if (licznik == 0)
		for (int i = 0; i < ile; i++)
		{
			if (kierunek == 1)
			{
				start = poz + i;
				if (gracz == 0)SiatkaA[start] = 2;
				else SiatkaB[start] = 2;
			}
			else
			{
				start = poz + i * 10;
				if (gracz == 0)SiatkaA[start] = 2;
				else SiatkaB[start] = 2;
			}
		}

	if (licznik == 0)return 1;
	return 0;
}

int Pole::Przekaz(int znak)
{


	if (znak < 100)
	{
		if (SiatkaA[znak] == 1)return 1;//trafiony
		if (SiatkaA[znak] == 2)return 2;//statek
		if (SiatkaA[znak] == 3)return 3;//zatopiony
		if (SiatkaA[znak] == 5)return 5;//strzal
	}
	else
	{
		if (SiatkaB[znak - 100] == 1)return 1;
		if (SiatkaB[znak - 100] == 3)return 3;
		if (SiatkaB[znak - 100] == 5)return 5;
	}
	return 0;
}

void Pole::Generuj()
{
	int  poz, kierunek;
	srand(time(NULL));

	while (statki4 != 0)
	{
		poz = (std::rand() % 100);
		kierunek = (std::rand() % 2);
		if ((poz < 70 && kierunek == 0) || ((poz % 10) < 7 && kierunek == 1))
			if (Sprawdz(4, poz, kierunek, 1) == 1)
			{
				statki4--;
				if (kierunek == 0)
				{
					trafB[19] = poz;
					trafB[18] = poz + 10;
					trafB[17] = poz + 20;
					trafB[16] = poz + 30;

				}
				else
				{
					trafB[19] = poz;
					trafB[18] = poz + 1;
					trafB[17] = poz + 2;
					trafB[16] = poz + 3;

				}

			}
	}
	while (statki3 != 0)
	{
		poz = (std::rand() % 100);
		kierunek = (std::rand() % 2);
		if ((poz < 80 && kierunek == 0) || ((poz % 10) < 8 && kierunek == 1))
			if (Sprawdz(3, poz, kierunek, 1) == 1)
			{
				statki3--;
				if (kierunek == 0)
				{
					trafB[statki3 * 3 + 12] = poz;
					trafB[statki3 * 3 + 11] = poz + 10;
					trafB[statki3 * 3 + 10] = poz + 20;
				}
				else
				{
					trafB[statki3 * 3 + 12] = poz;
					trafB[statki3 * 3 + 11] = poz + 1;
					trafB[statki3 * 3 + 10] = poz + 2;
				}

			}
	}
	while (statki2 != 0)
	{
		poz = (std::rand() % 100);
		kierunek = (std::rand() % 2);
		if ((poz < 90 && kierunek == 0) || ((poz % 10) < 9 && kierunek == 1))
			if (Sprawdz(2, poz, kierunek, 1) == 1)
			{
				statki2--;
				if (kierunek == 0)
				{
					trafB[statki2 * 2 + 5] = poz;
					trafB[statki2 * 2 + 4] = poz + 10;
				}
				else
				{
					trafB[statki2 * 2 + 5] = poz;
					trafB[statki2 * 2 + 4] = poz + 1;
				}

			}

	}
	while (statki1 != 0)
	{
		poz = (std::rand() % 100);
		if (SiatkaB[poz] == 0)
			if (Sprawdz(1, poz, kierunek, 1) == 1)
			{
				statki1--;
				trafB[statki1] = poz;
			}
	}


}

int Pole::Rozgrywka(int x, int y)
{

	for (int k = 0; k < 17; k++)
	{
		int jakas = trafA[k], jakas2, jakas3, jakas4;
		jakas = trafB[k];
		if (SiatkaB[jakas] == 1)
		{
			if (k < 4)SiatkaB[jakas] = 3;
			if (k < 10 && k>3)
			{
				if (k % 2 == 0)
				{
					jakas2 = trafB[k + 1];
					if (SiatkaB[jakas2] == 1)
					{
						SiatkaB[jakas] = 3;
						SiatkaB[jakas2] = 3;
					}
				}
			}
			if (k > 9 && k < 16)
				if (k == 10 || k == 13)
				{
					jakas2 = trafB[k + 1];
					if (SiatkaB[jakas] == 1)
					{
						jakas3 = trafB[k + 2];
						if (SiatkaB[jakas3] == 1)
						{
							SiatkaB[jakas] = 3;
							SiatkaB[jakas2] = 3;
							SiatkaB[jakas3] = 3;
						}


					}
				}
			if (k == 16)
			{
				jakas2 = trafB[k + 1];
				if (SiatkaB[jakas2] == 1)
				{
					jakas3 = trafB[k + 2];
					jakas4 = trafB[k + 3];
					if (SiatkaB[jakas4] == 1 && SiatkaB[jakas3] == 1)
					{
						SiatkaB[jakas] = 3;
						SiatkaB[jakas2] = 3;
						SiatkaB[jakas3] = 3;
						SiatkaB[jakas4] = 3;
					}


				}
			}
		}
	}

	text = L" ";
	int pom, algo;
	if (x > 618 && x < 950)x = (x - 624) / 32;
	else return 0;
	if (y > 138 && y < 457) y = (y - 148) / 30.5;
	pom = x * 10 + y;
	if (SiatkaB[pom] == 2)
	{
		SiatkaB[pom] = 1;
		if(SIpunkty < 20 && punkty < 20)
		algo = Rozgrywka(x,y);
	
	}
	if (x < 10 && y < 10 && SiatkaB[pom] == 0)
	{
		SiatkaB[pom] = 5;
		if (SIpunkty < 20 && punkty < 20)
		algo = Przeciwnik();
	}

	return 0;
}

int Pole::Przeciwnik()
{

	for (int k = 0; k < 17; k++)
	{
		int jakas = trafA[k], jakas2, jakas3, jakas4;
		if (SiatkaA[jakas] == 1)
		{
			if (k < 4)SiatkaA[jakas] = 3;
			if (k < 10 && k>3)
			{
				if (k % 2 == 0)
				{
					jakas2 = trafA[k + 1];
					if (SiatkaA[jakas2] == 1)
					{
						SiatkaA[jakas] = 3;
						SiatkaA[jakas2] = 3;
					}
				}
			}
			if (k > 9 && k < 16)
				if (k == 10 || k == 13)
				{
					jakas2 = trafA[k + 1];
					if (SiatkaA[jakas2] == 1)
					{
						jakas3 = trafA[k + 2];
						if (SiatkaA[jakas3] == 1)
						{
							SiatkaA[jakas] = 3;
							SiatkaA[jakas2] = 3;
							SiatkaA[jakas3] = 3;
						}


					}
				}
			if (k == 16)
			{
				jakas2 = trafA[k + 1];
				if (SiatkaA[jakas2] == 1)
				{
					jakas3 = trafA[k + 2];
					jakas4 = trafA[k + 3];
					if (SiatkaA[jakas4] == 1 && SiatkaA[jakas3] == 1)
					{
						SiatkaA[jakas] = 3;
						SiatkaA[jakas2] = 3;
						SiatkaA[jakas3] = 3;
						SiatkaA[jakas4] = 3;
					}


				}
			}
		}
	}
	int pom, ready = 0;
	pom = (std::rand() % 100);
	for (int k = 0; k < 99; k++)
	{
		if (SiatkaA[k] == 1)
		{

			if (SiatkaA[k + 1] == 0 || SiatkaA[k + 1] == 2)
				if ((k + 1) % 10 != 0) { pom = k + 1;  break; }

			if (SiatkaA[k - 1] == 0 || SiatkaA[k - 1] == 2)
				if ((k - 1) % 10 != 9) { pom = k - 1; break; }
			
			if (SiatkaA[k + 10] == 0 || SiatkaA[k + 10] == 2)
				if ((k + 10) < 100) { pom = k + 10; break; }
			
			if (SiatkaA[k - 10] == 0 || SiatkaA[k - 10] == 2)
				if ((k - 10) >= 0) { pom = k - 10;   break; }

		}
	}

	while (SiatkaA[pom] == 1 || SiatkaA[pom] == 5 || pom > 99 || SiatkaA[pom] == 3 || pom < 0 || ready == 1)
	{

		pom = (std::rand() % 100);
		if (SiatkaA[pom + 1] == 3 || SiatkaA[pom - 1] == 3 || SiatkaA[pom + 10] == 3 || SiatkaA[pom - 10] == 3 || SiatkaA[pom + 11] == 3 || SiatkaA[pom - 11] == 3 || SiatkaA[pom + 9] == 3 || SiatkaA[pom - 10] == 3)  ready = 1;
		else ready = 0;
	}

	if (SiatkaA[pom] == 2)
	{
		SiatkaA[pom] = 1; 
		punkty++;
		if (punkty < 20 && SIpunkty <20)
		Przeciwnik();
		trafiony = pom;
		return pom;
	}
	if (SiatkaA[pom] == 0)SiatkaA[pom] = 5;

	return 0;

}

int Pole::Losuj()
{
	int  poz, kierunek;
	srand(time(NULL));
	text = L" ";
	while (statki4 != 0)
	{
		poz = (std::rand() % 100);
		kierunek = (std::rand() % 2);
		if ((poz < 70 && kierunek == 0) || ((poz % 10) < 7 && kierunek == 1))
			if (Sprawdz(4, poz, kierunek, 0) == 1)
			{
				statki4--;
				if (kierunek == 0)
				{
					trafA[19] = poz;
					trafA[18] = poz + 10;
					trafA[17] = poz + 20;
					trafA[16] = poz + 30;

				}
				else
				{
					trafA[19] = poz;
					trafA[18] = poz + 1;
					trafA[17] = poz + 2;
					trafA[16] = poz + 3;

				}

			}
	}
	while (statki3 != 0)
	{
		poz = (std::rand() % 100);
		kierunek = (std::rand() % 2);
		if ((poz < 80 && kierunek == 0) || ((poz % 10) < 8 && kierunek == 1))
			if (Sprawdz(3, poz, kierunek, 0) == 1)
			{
				statki3--;
				if (kierunek == 0)
				{
					trafA[statki3 * 3 + 12] = poz;
					trafA[statki3 * 3 + 11] = poz + 10;
					trafA[statki3 * 3 + 10] = poz + 20;
				}
				else
				{
					trafA[statki3 * 3 + 12] = poz;
					trafA[statki3 * 3 + 11] = poz + 1;
					trafA[statki3 * 3 + 10] = poz + 2;
				}

			}
	}
	while (statki2 != 0)
	{
		poz = (std::rand() % 100);
		kierunek = (std::rand() % 2);
		if ((poz < 90 && kierunek == 0) || ((poz % 10) < 9 && kierunek == 1))
			if (Sprawdz(2, poz, kierunek, 0) == 1)
			{
				statki2--;
				if (kierunek == 0)
				{
					trafA[statki2 * 2 + 5] = poz;
					trafA[statki2 * 2 + 4] = poz + 10;
				}
				else
				{
					trafA[statki2 * 2 + 5] = poz;
					trafA[statki2 * 2 + 4] = poz + 1;
				}

			}

	}
	while (statki1 != 0)
	{
		poz = (std::rand() % 100);
		if (SiatkaA[poz] == 0)
			if (Sprawdz(1, poz, kierunek, 0) == 1)
			{
				statki1--;
				trafA[statki1] = poz;
			}
	}

	if (statki4 == 0 && statki3 == 0 && statki2 == 0 && statki1 == 0)
	{
		return 1;
	}


	text = L"Rozmieść statki  4X:" + std::to_string(statki4) + "  3X:" + std::to_string(statki3) + "  2X:" + std::to_string(statki2) + "  1X:" + std::to_string(statki1);

	return 1;
}




