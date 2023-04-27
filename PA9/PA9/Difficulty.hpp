#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

//Author: Alex Langland

/*
CLASS DSELECTOR

This class contains the Menu elements to select the "difficulty", or number of mines for the game.

There is not much logic here, the menu's point is to return the chosen number of mines
through the updateSelector() function.

This class also contains the Game Instructions

*/

class dSelector {

public:

	dSelector(float width, float height);
	~dSelector();

	void drawSelector(sf::RenderWindow& window);
	int updateSelector(sf::RenderWindow& window);

private:

	sf::Text top;
	sf::RectangleShape box;
	sf::Font font;
	Button* options[4];
	sf::Text instruction;

};