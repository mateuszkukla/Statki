#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;
class Okno : public sf::Drawable,
	sf::Transformable
{
private:
	RenderWindow *window;
	Text tekst;
	Text info;
	Text  punkt1;
	Text  punkt2;
	Font font;
	
public:
	Okno();
	~Okno();
	enum StanGry { GRA, KONIEC, MENU };
	int punkty, SIpunkty;
	StanGry stan;
	sf::RectangleShape ksztalt, strzal, statek, trafiony, zatopiony;
	void oknoStart(RenderWindow &okn);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void Powrot();
	
};

