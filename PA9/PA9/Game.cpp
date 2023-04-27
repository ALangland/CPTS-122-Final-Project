#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "GameTile.hpp"
#include "Game.hpp"

//Author: Alex Langland

//Constructor for a Game board, as well as for the timer
Game::Game(float screenW) {

	//Minefield of 20 x 20 tiles
	tWidth = 20;
	tHeight = 20;

	//Place the tiles contiguously
	float originX = screenW / 2 - (int)(tWidth * 13);
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			board[c][r].initializeButton((originX + (c * 26)), 50 + (r * 26), 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
			board[c][r].setPosVec(originX + (c * 26), 50 + (r * 26));
		}
	}

	//Set Data Members
	hasWon = false;
	hasLost = false;
	mines = 80;
	nTimer = 0.0;

	//Initialize Timer Text
	timerFont.loadFromFile("LSANS.ttf");
	timer.setString("TIME: 0.00");
	timer.setLetterSpacing(1.1);
	timer.setFont(timerFont);
	timer.setCharacterSize(30);
	timer.setPosition(sf::Vector2f(15, 8));
}

//Default destructor
Game::~Game(void) {
}

//Set the Game's "difficulty", (number of mines)
void Game::difficultySelect(int cMines) {
	mines = cMines;
}

//Get the value of the timer;
float Game::getTime(void) {
	return nTimer;
}

//Check the Surrounding Tiles of a Tile, returns how many mines are adjacent to the tile.
int Game::checkSurroundings(int tCol, int tRow) {
	int mNear = 0;
	if (tCol != 0) {
		//Check Left Side
		if (board[tCol - 1][tRow].getContents() == 9) {
			mNear++;
		}
		if (tRow != 19) {
			//Check Bottom Left
			if (board[tCol - 1][tRow + 1].getContents() == 9) {
				mNear++;
			}
		}
		if (tRow != 0) {
			//Check Top Left
			if (board[tCol - 1][tRow - 1].getContents() == 9) {
				mNear++;
			}
		}
	}
	if (tCol != 19) {
		//Check Right Side
		if (board[tCol + 1][tRow].getContents() == 9) {
			mNear++;
		}
		if (tRow != 19) {
			//Check Bottom Right
			if (board[tCol + 1][tRow + 1].getContents() == 9) {
				mNear++;
			}
		}
		if (tRow != 0) {
			//Check Top Right
			if (board[tCol + 1][tRow - 1].getContents() == 9) {
				mNear++;
			}
		}
	}
	if (tRow != 19) {
		//Check Bottom
		if (board[tCol][tRow + 1].getContents() == 9) {
			mNear++;
		}
	}
	if (tRow != 0) {
		//Check Top
		if (board[tCol][tRow - 1].getContents() == 9) {
			mNear++;
		}
	}
	return mNear;
}

//randomly place the Pre-determined number of mines across the board,
//then fills each non-mine tile with the number of adjacent mines.
void Game::populateMines(void) {
	srand(time(0));
	while (mines > 0) {
		int xTile = rand() % 20, yTile = rand() % 20;
		if (board[xTile][yTile].getContents() == 0) {
			board[xTile][yTile].setContents(9);
			mines--;
		}
	}
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			if (board[c][r].getContents() != 9) {
				board[c][r].setContents(checkSurroundings(c, r));
			}
		}
	}
}

//Draw all elements of the Game Board
void Game::drawGameBoard(sf::RenderWindow& window) {
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			board[c][r].drawbutton(window);
		}
	}
	window.draw(timer);
}

//Update the Game Board based on the current elapsed Time and position of the Mouse
void Game::updateGameBoard(sf::RenderWindow& window, float elapsedTime) {
	sf::Vector2i mPos = sf::Mouse::getPosition(window);
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			board[c][r].updateButton((sf::Vector2f)mPos);
			if (board[c][r].isPressed() == true) {
				board[c][r].revealContents();
				if (board[c][r].getContents() == 0) {
					revealEmpties(c, r);
				}
				checkStatus();
			}
		}
	}
	if (hasWon != true && hasLost != true) {
		nTimer = elapsedTime;
		timer.setString("TIMER: " + to_string(nTimer) + " sec");
	}
}

//When an Empty square is revealed, Reveal all contiguous empty spaces and all numbered spaces bordering the empty Block.
//If an adjacent Empty space is found, use recursion to reveal all adjacent spaces to it until all adjacent empty spaces have been revealed
void Game::revealEmpties(int tCol, int tRow) {
	if (tCol != 0) {
		if (board[tCol - 1][tRow].isRevealed() == false) {
			board[tCol - 1][tRow].revealContents();
			if (board[tCol - 1][tRow].getContents() == 0) {
				revealEmpties(tCol - 1, tRow);
			}
		}
		if (tRow != 19 && board[tCol - 1][tRow + 1].isRevealed() == false) {
			board[tCol - 1][tRow + 1].revealContents();
			if (board[tCol - 1][tRow + 1].getContents() == 0) {
				revealEmpties(tCol - 1, tRow + 1);
			}
		}
		if (tRow != 0 && board[tCol - 1][tRow - 1].isRevealed() == false) {
			board[tCol - 1][tRow - 1].revealContents();
			if (board[tCol - 1][tRow - 1].getContents() == 0) {
				revealEmpties(tCol - 1, tRow - 1);
			}
		}
	}
	if (tCol != 19) {
		if (board[tCol + 1][tRow].isRevealed() == false) {
			board[tCol + 1][tRow].revealContents();
			if (board[tCol + 1][tRow].getContents() == 0) {
				revealEmpties(tCol + 1, tRow);
			}
		}
		if (tRow != 19 && board[tCol + 1][tRow + 1].isRevealed() == false) {
			board[tCol + 1][tRow + 1].revealContents();
			if (board[tCol + 1][tRow + 1].getContents() == 0) {
				revealEmpties(tCol + 1, tRow + 1);
			}
		}
		if (tRow != 0 && board[tCol + 1][tRow - 1].isRevealed() == false) {
			board[tCol + 1][tRow - 1].revealContents();
			if (board[tCol + 1][tRow - 1].getContents() == 0) {
				revealEmpties(tCol + 1, tRow - 1);
			}
		}
	}
	if (tRow != 19 && board[tCol][tRow + 1].isRevealed() == false) {
		board[tCol][tRow + 1].revealContents();
		if (board[tCol][tRow + 1].getContents() == 0) {
			revealEmpties(tCol, tRow + 1);
		}
	}
	if (tRow != 0 && board[tCol][tRow - 1].isRevealed() == false) {
		board[tCol][tRow - 1].revealContents();
		if (board[tCol][tRow - 1].getContents() == 0) {
			revealEmpties(tCol, tRow - 1);
		}
	}
}

//Run once a Tile has been revealed, checks to see if conditions have been met for a win or loss
void Game::checkStatus(void) {
	int status = 0;
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			if (board[c][r].getContents() == 9 && board[c][r].isRevealed() == true) {
				status = 1;
				hasLost = true;
			}
		}
	}
	if (status == 0) {
		bool incomplete = true;
		for (int r = 0; r < tHeight; r++) {
			for (int c = 0; c < tWidth; c++) {
				if (board[c][r].getContents() != 9 && board[c][r].isRevealed() == false) {
					status = 1;
				}
			}
		}
		if (status == 0) {
			hasWon = true;
		}
	}
}

//Checkers for each Game Over Condition tag, either a Win or Loss
bool Game::checkWin(void) {
	return hasWon;
}
bool Game::checkLose(void) {
	return hasLost;
}

//Stop the timer text and change its Content based on Game Result
void Game::stopTimer(bool won) {
	if (won == true) {
		//Win Case
		timer.setString("You Won! Final Time: " + to_string(nTimer) + " sec");
	}
	if (won == false) {
		//Lose Case
		timer.setString("You Lose!");
	}
}

//Reveal all unrevealed spaces on the Minefield; run when game is over
void Game::revealBoard(void) {
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			if (board[c][r].isRevealed() == false) {
				board[c][r].revealContents();
			}
		}
	}
}

//Reset the Contents of the Minefield and reconceal all Tiles, to play another Round without restarting the application.
void Game::resetBoard(float screenW) {
	float originX = screenW / 2 - (int)(tWidth * 13);
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			board[c][r].initializeButton((originX + (c * 26)), 50 + (r * 26), 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
			board[c][r].setPosVec(originX + (c * 26), 50 + (r * 26));
			board[c][r].setContents(0);
			board[c][r].hide();
		}
	}

	hasWon = false;
	hasLost = false;
	mines = 80;
	nTimer = 0.0;

}