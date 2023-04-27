#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include "Button.hpp"

//Author: Alex Langland

class Menu {

public:

	Menu(float width, float height);
	~Menu();

	void displayMenu(sf::RenderWindow &window);

	int updateButtons(sf::RenderWindow& window);

private:

	sf::RectangleShape titleBox;
	sf::Text title;
	Button* options[3];
	sf::Font font;

};

#endif
