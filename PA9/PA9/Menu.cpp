#include "Menu.h"

Menu::Menu(float width, float height) {

	iChoice = 1;
	font.loadFromFile("LSANS.ttf");

	float centerX = 0.0;
	textBlocks[0].setString("MINESWEEPER");
	textBlocks->setStyle(sf::Text::Underlined | sf::Text::Bold);
	textBlocks[0].setLetterSpacing(1.8);
	textBlocks[0].setFont(font);
	textBlocks[0].setCharacterSize(60);
	centerX = (width / 2 - (textBlocks[0].getLocalBounds().width / 2));
	textBlocks[0].setFillColor(sf::Color::Black);
	textBlocks[0].setPosition(sf::Vector2f(centerX, height / 8));
	
	titleBox.setFillColor(sf::Color::White);
	titleBox.setPosition(sf::Vector2f(centerX - 20, height / 8));
	titleBox.setSize(sf::Vector2f(textBlocks[0].getLocalBounds().width + 40, textBlocks[0].getLocalBounds().height + 40));

	textBlocks[1].setString("> Play Game");
	textBlocks[1].setFillColor(sf::Color::Red);
	textBlocks[1].setFont(font);
	textBlocks[1].setCharacterSize(45);
	textBlocks[1].setPosition(centerX + 10, height / 8 + 130);

	textBlocks[2].setString("Leaderboard");
	textBlocks[2].setFont(font);
	textBlocks[2].setCharacterSize(45);
	textBlocks[2].setPosition(centerX + 40, height / 8 + 200);

	textBlocks[3].setString("Exit");
	textBlocks[3].setFont(font);
	textBlocks[3].setCharacterSize(45);
	textBlocks[3].setPosition(centerX + 40, height / 8 + 270);

}

Menu::~Menu() {
}


void Menu::displayMenu(sf::RenderWindow& window) {
	window.draw(titleBox);
	for (int i = 0; i < 4; i++) {
		window.draw(textBlocks[i]);
	}
}