#include "Menu.h"

Menu::Menu(void)
{
	ContextSettings ustawienia;

	window.create(VideoMode(1024, 700), "Statki", Style::Default, ustawienia);
	
	stan = KONIEC;



	if (!czcionka.loadFromFile("BlackOpsOne-Regular.ttf"))
	{
		MessageBox(NULL, (LPCSTR)L"Czcionka nie znaleziona", NULL, MB_OK);
		return;
	}

	stan = MENU;

}

Menu::~Menu(void)
{
	
}

void Menu::UruchomGre()
{
	while (stan != KONIEC)
	{
		switch (stan)
		{
		case MENU:
			Opcje();
			break;
		case GRA:
			Rozgrywka();
			break;
		case INSTRUKCJA:
			Instrukcja();
			continue;

		}
	}
}

void Menu::Opcje()
{
	
	Text nazwa("STATKI", czcionka, 200);
	nazwa.setStyle(Text::Bold);
	nazwa.setFillColor(Color::Black);
	
	nazwa.setPosition(1024 / 2 - nazwa.getGlobalBounds().width / 2, 20);

	const int ile = 3;

	Text tekst[ile];

	wstring str[] = { L"Nowa Gra",L"Instrukcja", L"Wyjdü" };
	for (int i = 0; i < ile; i++)
	{
		tekst[i].setFont(czcionka);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1024 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (stan == MENU)
	{
		tekstura.loadFromFile("image.jpg");
		Sprite background(tekstura);
		background.setTexture(tekstura);
		window.draw(background);
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				stan = KONIEC;


			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				stan = GRA;
			}




			else if (tekst[2].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				stan = KONIEC;
			}


			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				stan = INSTRUKCJA;
			}
		}
		for (int i = 0; i < ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(Color::Red);
			else tekst[i].setFillColor(Color::Black);


		window.draw(nazwa);
		for (int i = 0; i < ile; i++)
			window.draw(tekst[i]);

		window.display();
	}
}

void Menu::Rozgrywka()
{
	Okno okienko;
	okienko.oknoStart(window);
	stan = MENU;

}


void Menu::Instrukcja()
{
	Event event;
	while (window.pollEvent(event))
	{

		tekstura.loadFromFile("Instrukcja.jpg");
		Sprite background(tekstura);
		background.setTexture(tekstura);
		window.draw(background);
		window.display();
		if (event.type == Event::Closed || event.type == Event::KeyPressed &&
			event.key.code == Keyboard::Escape)
	{
		
		stan = MENU;
		Opcje();
	}

	}
	
}