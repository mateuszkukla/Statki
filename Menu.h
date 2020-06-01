#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Okno.h"

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(void);
	~Menu(void);
	RenderWindow window;
	Texture tekstura;
	Sprite menuTxt;
	void UruchomGre();
	enum StanGry { MENU, GRA, KONIEC, INSTRUKCJA };
	StanGry stan;

private:
	Font czcionka;
	void Opcje();
	void Rozgrywka();
	void Instrukcja();

};


