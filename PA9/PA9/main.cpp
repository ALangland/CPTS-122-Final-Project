#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameTile.hpp"
#include "Game.hpp"
#include "Difficulty.hpp"
#include "Leaderboard.hpp"
#include <iostream>

//Author: Alex Langland

/*
MINESWEEPER

By:
Alex Langland
Ethan Burzynski

For CPTS 122 PA9
Using SFML for Graphics
*/

using std::cout;
using std::cin;
using std::endl;

int main(void) {
	float screenX = 800, screenY = 600;
	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Minesweeper");

	sf::Vector2i reset(0, 0);
	Menu myMenu(screenX, screenY);
	dSelector mySelector(screenX, screenY);
	Game myGame(screenX);
	Leaderboard myLeaders;

	bool inMenu = 1;
	bool inGame = 0;
	bool dSelect = 0;
	bool leaderBoard = 0;
	int gameOver = 0;
	bool enterScore = 0;

	sf::Clock gameTime;
	float time = 1.0;

	Button returnToMenu(screenX - 200, 5, 140, 35, "Return to Menu", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);
	returnToMenu.setTextSize(12);

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
				sf::Mouse::setPosition(reset, window);
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
			int diffSelect = mySelector.updateSelector(window);
			if (diffSelect != 0) {
				myGame.difficultySelect(diffSelect);
				dSelect = 0;
				inGame = 1;
				sf::Mouse::setPosition(reset, window);
				gameTime.restart();
				myGame.populateMines();
			}
			else {
				mySelector.drawSelector(window);
			}
		}

		if (inGame == 1) {
			myGame.drawGameBoard(window);
			myGame.updateGameBoard(window, gameTime.getElapsedTime().asSeconds());
			if (myGame.checkWin() == true) {
				inGame = 0;
				gameOver = 1;
				time = myGame.getTime();
				myGame.revealBoard();
			}
			if (myGame.checkLose() == true) {
				inGame = 0;
				gameOver = 2;
				myGame.revealBoard();
			}
		}

		if (gameOver != 0) {
			if (gameOver == 1) {
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				returnToMenu.updateButton((sf::Vector2f)mPos);
				bool exit = returnToMenu.isPressed();
				if (exit == true) {
					gameOver = 0;
					enterScore = 1;
				}
				else {
					returnToMenu.drawbutton(window);
					myGame.drawGameBoard(window);
				}
			}
			if (gameOver == 2) {
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				returnToMenu.updateButton((sf::Vector2f)mPos);
				bool exit = returnToMenu.isPressed();
				if (exit == true) {
					gameOver = 0;
					inMenu = 1;
				}
				else {
					returnToMenu.drawbutton(window);
					myGame.drawGameBoard(window);
				}
			}
		}

		if (enterScore == 1) {
			string initials = "";
			cout << "Enter 3 Initials:" << endl;
			cin >> initials;
			myLeaders.insertRecord(time, initials);
			enterScore = 0;
			inMenu = 1;
		}

		if (leaderBoard == 1) {
			sf::Vector2i mPos = sf::Mouse::getPosition(window);
			returnToMenu.updateButton((sf::Vector2f)mPos);
			bool exit = returnToMenu.isPressed();
			if (exit == true) {
				leaderBoard = 0;
				inMenu = 1;
			}
			else {
				returnToMenu.drawbutton(window);
				myLeaders.drawLeaderboard(window, 100, 100);
			}
		}

		window.display();
	}
	return 0;
}