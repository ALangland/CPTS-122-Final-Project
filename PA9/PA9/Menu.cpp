#include "Menu.h"
#include "Button.hpp"

//Author: Alex Langland

Menu::Menu(float width, float height) {

	font.loadFromFile("LSANS.ttf");

	float centerX = 0.0;
	title.setString("MINESWEEPER");
	title.setStyle(sf::Text::Underlined | sf::Text::Bold);
	title.setLetterSpacing(1.8);
	title.setFont(font);
	title.setCharacterSize(60);
	centerX = (width / 2 - (title.getLocalBounds().width / 2));
	title.setFillColor(sf::Color::Black);
	title.setPosition(sf::Vector2f(centerX, height / 8));
	
	titleBox.setFillColor(sf::Color::White);
	titleBox.setPosition(sf::Vector2f(centerX - 20, height / 8));
	titleBox.setSize(sf::Vector2f(title.getLocalBounds().width + 40, title.getLocalBounds().height + 40));

	float bX = width / 2 - 75;

	options[0] = new Button(bX, (height / 8) + 130, 150, 80, "Play Game", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);

	options[1] = new Button(bX, (height / 8) + 230, 150, 80, "Leaderboard", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);

	options[2] = new Button(bX, (height / 8) + 330, 150, 80, "Exit", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);

}

Menu::~Menu() {
}

int Menu::updateButtons(sf::RenderWindow& window) {
	sf::Vector2i mPos = sf::Mouse::getPosition(window);
	int clicked = 0;
	for (int i = 0; i < 3; i++) {
		options[i]->updateButton((sf::Vector2f)mPos);
		if (options[i]->isPressed() == true) {
			clicked = i + 1;
		}
	}
	return clicked;
}

void Menu::displayMenu(sf::RenderWindow& window) {
	window.draw(titleBox);
	window.draw(title);
	for (int i = 0; i < 3; i++) {
		options[i]->drawbutton(window);
	}
	
}