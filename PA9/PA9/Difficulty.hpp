#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

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

};