#pragma once
#include <string.h>
#include <iostream>
#include <string.h>

class Pole
{
public:
	Pole();
	~Pole();
	int punkty = 0, SIpunkty = 0;
private:

	int SiatkaA[100],SiatkaB[100];
	int statki4, statki3, statki2, statki1, trafA[20], trafB[20];
	

public:

std::wstring text;
int Ustaw(int Xp, int Yp, int Xk, int Yk);
int Losuj();
int Sprawdz(int ile, int poz, int kierunek,int gracz);
int Przekaz(int znak);
void Generuj();
int Rozgrywka(int x, int y);
int Przeciwnik();




};