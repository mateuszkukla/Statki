#include "Okno.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Pole.h"
#include "Menu.h"
#include <string.h>
#include <sstream>

using namespace std;
using namespace sf;

Okno::Okno()
{
	
}


Okno::~Okno()
{
}

void Okno::oknoStart(RenderWindow &okn)
{
	
	window= &okn;
	stan = GRA;
	int start=0;
	int xp, yp, xk, yk;
	sf::Texture tekstura;
	sf::Sprite menuTxt;
	Pole pole;
	std::wstring s1, message;
	message = pole.text;
	if (!font.loadFromFile("BlackOpsOne-Regular.ttf"));
	sf::Text komunikat, strzal;

	komunikat.setFont(font);
	komunikat.setString(message);
	komunikat.setPosition(100, 42);
	komunikat.setCharacterSize(40);
	komunikat.setFillColor(sf::Color::Black);

	trafiony.setSize(Vector2f(32 / 2, 32 / 2));
	trafiony.setOutlineThickness(32 / 8);
	trafiony.setOrigin(0, -8);
	trafiony.setOutlineColor(Color(65, 65, 65));
	trafiony.setFillColor(Color::Red);

	statek.setSize(Vector2f(32 / 2, 32 / 2));
	statek.setOutlineThickness(32 / 8);
	statek.setOrigin(0, -8);
	statek.setOutlineColor(Color(65, 65, 65));
	statek.setFillColor(Color(65, 65, 65));

	s1 = L"X";
	strzal.setFont(font);
	strzal.setString(s1);
	strzal.setCharacterSize(30);
	strzal.setFillColor(sf::Color::Black);


	tekst.setFont(font);
	tekst.setCharacterSize(180);
	tekst.setFillColor(Color::Black);

	zatopiony.setSize(Vector2f(32 / 2, 32 / 2));
	zatopiony.setOutlineThickness(32 / 8);
	zatopiony.setOrigin(0, -8);
	zatopiony.setOutlineColor(Color(150, 0, 0));
	zatopiony.setFillColor(Color(150, 0, 0));

	ksztalt.setSize(Vector2f(30, 30));
	ksztalt.setOrigin(7, -2);
	ksztalt.setFillColor(Color(127, 255, 212));
	ksztalt.setOutlineThickness(0.5);
	ksztalt.setOutlineColor(Color::Black);
	
	
	
	while (window->isOpen())
	{
		window->clear(sf::Color(220, 220, 220));
		sf::Event event;
		while (window->pollEvent(event))
		{
			
			switch (event.type)
			{
			
		case sf::Event::Closed:
			{	
			window->close();
			break; 
			}
		case sf::Event::KeyPressed:
				{
				if (event.key.code == sf::Keyboard::L)
				{
					if (stan != KONIEC)start=pole.Losuj();
					komunikat.setString(message);
					break;
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					stan = MENU;
					window->close();
					Powrot();

					break;
				}
				else continue;
				}

			case sf::Event::KeyReleased:
			{
				if (event.key.code == sf::Keyboard::L)
				{
					if (stan != KONIEC)
						message = pole.text;
					komunikat.setString(message);
					break;
				}
				else continue;

			}
			case sf::Event::MouseButtonPressed:
			{		xp = event.mouseButton.x;
					yp = event.mouseButton.y;
				
					break;
			}
			case sf::Event::MouseButtonReleased:
			{
				xk = event.mouseButton.x;
				yk = event.mouseButton.y;
				
				if(stan != KONIEC)start=pole.Ustaw(xp, yp, xk, yk);
				if(stan != KONIEC)message = pole.text;
				komunikat.setString(message);
			}
				
			}
		}

		if (stan != KONIEC)
		{
			ostringstream p;
			p << "Punkty Przeciwnika: " << punkty;
			punkt1.setFont(font);
			punkt1.setCharacterSize(30);
			punkt1.setString(p.str());
			punkt1.setPosition(70, 610);
			punkt1.setFillColor(sf::Color::Black);
			window->draw(punkt1);
			std::ostringstream SIp;
			punkt2.setFont(font);
			punkt2.setCharacterSize(30);
			SIp << "Punkty Gracza: " << SIpunkty;
			punkt2.setString(SIp.str());
			punkt2.setPosition(605, 610);
			punkt2.setFillColor(sf::Color::Black);
			window->draw(punkt2);
		}
		
		window->draw(menuTxt);
		window->draw(komunikat);
		int xpom, ypom;
		punkty = 0, SIpunkty = 0;
		for (int i = 0; i < 200; i++)
		{
			if (i < 100)
			{
				xpom = 82 + ((i - (i % 10)) / 10) * 32;
				ypom = 142 + (i % 10) * 31;

					ksztalt.setPosition(xpom, ypom);
					window->draw(ksztalt);
				
			}
			else
			{
				xpom = 312+ ((i - (i % 10)) / 10) * 32;
				ypom = 145 + (i % 10) * 31;
		
		
				
					ksztalt.setPosition(xpom, ypom);
					window->draw(ksztalt);
				
				
			}
			if (pole.Przekaz(i) == 2 )
			{
				statek.setPosition(xpom, ypom);
				window->draw(statek);
				
			}
			if (pole.Przekaz(i) == 5 )
			{
					strzal.setPosition(xpom, ypom);
					window->draw(strzal);
				
			}
			if (pole.Przekaz(i) == 3)
			{
				zatopiony.setPosition(xpom, ypom);
				window->draw(zatopiony);
				if (i < 100)punkty++;
				else SIpunkty++;
			}
			if (pole.Przekaz(i) == 1)
			{
					trafiony.setPosition(xpom, ypom);
					window->draw(trafiony);

				if (i < 100)punkty++;
				else SIpunkty++;
			}
		

		}
		if (stan == KONIEC)
		{
			tekst.setPosition(1024 / 2 - tekst.getGlobalBounds().width / 2, 700 / 2 - tekst.getGlobalBounds().height / 2 - 100);
			window->draw(tekst);
			window->draw(info);
		}
		if (punkty == 20 && start == 2)
		{

			
			tekst.setString(L"PORA¯KA");
			stan = KONIEC;
		}
		if (SIpunkty == 20 && start == 2)
		{
			
			tekst.setString("WYGRANA");
			stan = KONIEC;

		}
		window->display();
		
		

	}

}

void Okno::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(ksztalt);
	target.draw(trafiony);
	target.draw(statek);
	target.draw(zatopiony);
}

void Okno::Powrot()
{
	Menu okienko;
	okienko.UruchomGre();
	stan = MENU;

}