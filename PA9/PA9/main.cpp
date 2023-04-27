#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameTile.hpp"
#include "Game.hpp"
#include "Difficulty.hpp"
#include "Leaderboard.hpp"
#include "test.h"
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

	//Run Test Cases
	test myTests;
	myTests.wrapTests();

	//Initialize Render Window
	float screenX = 800, screenY = 600;
	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Minesweeper");

	//Declare Objects Necessary to the Program
	sf::Font sysFont;
	sysFont.loadFromFile("LSANS.ttf");
	sf::Vector2i reset(0, 0);
	Menu myMenu(screenX, screenY);
	dSelector mySelector(screenX, screenY);
	Game myGame(screenX);
	fstream timesFile("leaderboard.txt");
	Leaderboard myLeaders(timesFile);
	timesFile.close();
	
	//Declare integer checks to determine which screen to draw
	bool inMenu = 1;
	bool inGame = 0;
	bool dSelect = 0;
	bool leaderBoard = 0;
	int gameOver = 0;
	bool enterScore = 0;

	//Initialize Timer Clock
	sf::Clock gameTime;
	float time = 1.0;

	//Create Standard Button to return to the Main Menu
	Button returnToMenu(screenX - 200, 5, 140, 35, "Return to Menu", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);
	returnToMenu.setTextSize(12);

	//Begin Drawing the window
	while (window.isOpen()) {
		//Event check so window can close properly
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		//Draw Main Menu
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

		//Draw Difficulty selection screen
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

		//Draw Game Board
		if (inGame == 1) {
			//Check Game Status
			myGame.drawGameBoard(window);
			myGame.updateGameBoard(window, gameTime.getElapsedTime().asSeconds());
			if (myGame.checkWin() == true) {
				//Winning Case
				inGame = 0;
				gameOver = 1;
				time = myGame.getTime();
				myGame.revealBoard();
				myGame.stopTimer(true);
				string temp("Enter Your Time");
				returnToMenu.setText(temp);
			}
			if (myGame.checkLose() == true) {
				//Losing Case
				inGame = 0;
				gameOver = 2;
				myGame.revealBoard();
				myGame.stopTimer(false);
			}
		}

		//End Game, based on whether the player won or lost
		if (gameOver != 0) {
			//Winning Case
			if (gameOver == 1) {
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				returnToMenu.updateButton((sf::Vector2f)mPos);
				bool exit = returnToMenu.isPressed();
				if (exit == true) {
					gameOver = 0;
					enterScore = 1;
					string temp("Return to Menu");
					returnToMenu.setText(temp);
				}
				else {
					returnToMenu.drawbutton(window);
					myGame.updateGameBoard(window, time);
					myGame.drawGameBoard(window);
				}
			}
			//Losing Case
			if (gameOver == 2) {
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				returnToMenu.updateButton((sf::Vector2f)mPos);
				bool exit = returnToMenu.isPressed();
				if (exit == true) {
					gameOver = 0;
					inMenu = 1;
					myGame.resetBoard(screenX);
				}
				else {
					myGame.updateGameBoard(window, time);
					returnToMenu.drawbutton(window);
					myGame.drawGameBoard(window);
				}
			}
		}

		//Screen to enter score (Time elapsed since beginning the puzzle) into the Leaderboard
		if (enterScore == 1) {
			sf::Text instructTime("Open The console\nto enter your score!", sysFont, 50);
			instructTime.setPosition(screenX / 2 - instructTime.getLocalBounds().width / 2, screenY / 2 - instructTime.getLocalBounds().height / 2);
			window.clear();
			window.draw(instructTime);
			window.display();
			string initials = "";
			//Pull up Console to enter Initials
			cout << "Enter 3 Initials:" << endl;
			cin >> initials;
			myLeaders.insertRecord(time * 100, initials);
			fstream outStream("leaderboard.txt");
			myLeaders.writeToFile(outStream);
			outStream.close();
			enterScore = 0;
			inMenu = 1;
			myGame.resetBoard(screenX);
			
		}

		//Draw Leaderboard Screen
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
				fstream readStream("leaderboard.txt");
				myLeaders.drawLeaderboard(window, 100, 100, readStream);
				readStream.close();
			}
		}

		window.display();
	}
	return 0;
}