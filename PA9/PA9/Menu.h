#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include "Button.hpp"

//Author: Alex Langland

/*
CLASS MENU

Contains all the graphical elements of the Main Menu,
functions within to draw them and update the interactive components.

Drawn first after the window has been rendered, contains
the updateButtons function that allows the user to navigate
to other "Screens".

*/

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
