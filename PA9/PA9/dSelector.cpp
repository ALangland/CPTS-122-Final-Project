#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Difficulty.hpp"

//Author: Alex Langland

//Construct the Elements of the Difficulty Selector Menu
dSelector::dSelector(float width, float height) {

	font.loadFromFile("LSANS.ttf");

	float centerX = 0.0;
	top.setString("Choose your difficulty:");
	top.setStyle(sf::Text::Bold);
	top.setLetterSpacing(1.3);
	top.setFont(font);
	top.setCharacterSize(50);

	centerX = (width / 2 - (top.getLocalBounds().width / 2));
	top.setFillColor(sf::Color::Black);
	top.setPosition(sf::Vector2f(centerX, height / 8 + 15));

	box.setFillColor(sf::Color::White);
	box.setPosition(sf::Vector2f(centerX - 20, height / 8));
	box.setSize(sf::Vector2f(top.getLocalBounds().width + 35, top.getLocalBounds().height + 35));

	float bX = width / 2 - 200;
	options[0] = new Button(bX, (height / 8) + 115, 180, 70, "Demo: 20 Mines", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);
	options[1] = new Button(bX + 220, (height / 8) + 115, 180, 70, "Easy: 50 Mines", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);
	options[2] = new Button(bX, (height / 8) + 200, 180, 70, "Normal: 80 Mines", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);
	options[3] = new Button(bX + 220, (height / 8) + 200, 180, 70, "HARD: 100 Mines", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);

	instruction.setString("TO PLAY: Begin clicking on squares to reveal what they contain.\nThe Goal of the game is to reveal all Squares that do not contain\na mine. However, clicking on a mine will result in losing the game.\nEach number found beneath a square how many mines are in the\nsurrounding eight spaces.");
	instruction.setFont(font);
	instruction.setCharacterSize(23);
	instruction.setPosition(bX - 175, height / 8 + 340);

}

//Default Constructor
dSelector::~dSelector() {

}

//Draw the Menu
void dSelector::drawSelector(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(top);
	for (int i = 0; i < 4; i++) {
		options[i]->drawbutton(window);
	}
	window.draw(instruction);
}

//Update the menu based on mouse position and click
//Returns how many mines have been selected, if none have been pressed returns 0.
int dSelector::updateSelector(sf::RenderWindow& window) {
	sf::Vector2i mPos = sf::Mouse::getPosition(window);
	int clicked = 0, mines = 0;
	for (int i = 0; i < 4; i++) {
		options[i]->updateButton((sf::Vector2f)mPos);
		if (options[i]->isPressed() == true) {
			clicked = i + 1;
		}
	}
	switch (clicked) {
	case 1:
		mines = 20;
		break;
	case 2:
		mines = 50;
		break;
	case 3:
		mines = 80;
		break;
	case 4:
		mines = 100;
		break;
	}
	return mines;
}