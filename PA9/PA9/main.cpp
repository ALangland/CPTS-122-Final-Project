#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameTile.hpp"
#include "Game.hpp"

int main(void) {
	float screenX = 800, screenY = 600;
	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Minesweeper");

	Menu myMenu(screenX, screenY);
	Game myGame(screenX);
	myGame.populateMines();

	bool inMenu = 1;
	bool inGame = 0;
	bool dSelect = 0;
	bool leaderBoard = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		if (inMenu == 1) {
			int menuOption = myMenu.updateButtons(window);
			switch (menuOption) {
			case 0:
				break;
			case 1:
				inMenu = 0;
				dSelect = 1;
				break;
			case 2:
				inMenu = 0;
				leaderBoard = 1;
				break;
			case 3:
				inMenu = 0;
				window.close();
				break;
			}
			if (menuOption == 0) {
				myMenu.displayMenu(window);
			}
		}

		if (dSelect == 1) {
			myGame.drawGameBoard(window);
			myGame.updateGameBoard(window);
		}

		window.display();

	}

	

	return 0;
}