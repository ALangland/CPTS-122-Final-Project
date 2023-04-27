#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "GameTile.hpp"
#include "Game.hpp"

Game::Game(float screenW) {

	tWidth = 20;
	tHeight = 20;

	float originX = screenW / 2 - (int)(tWidth * 13);
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			board[c][r].initializeButton((originX + (c * 26)), 50 + (r * 26), 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
			board[c][r].setPosVec(originX + (c * 26), 50 + (r * 26));
		}
	}

	hasWon = false;
	hasLost = false;
	mines = 80;
	nTimer = 0.0;

	timerFont.loadFromFile("LSANS.ttf");
	timer.setString("TIME: 0.00");
	timer.setLetterSpacing(1.1);
	timer.setFont(timerFont);
	timer.setCharacterSize(30);
	timer.setPosition(sf::Vector2f(15, 8));
}

Game::~Game(void) {
}

void Game::difficultySelect(int cMines) {
	mines = cMines;
}

int Game::checkSurroundings(int tCol, int tRow) {
	int mNear = 0;
	if (tCol != 0) {
		if (board[tCol - 1][tRow].getContents() == 9) {
			mNear++;
		}
		if (tRow != 19) {
			if (board[tCol - 1][tRow + 1].getContents() == 9) {
				mNear++;
			}
		}
		if (tRow != 0) {
			if (board[tCol - 1][tRow - 1].getContents() == 9) {
				mNear++;
			}
		}
	}
	if (tCol != 19) {
		if (board[tCol + 1][tRow].getContents() == 9) {
			mNear++;
		}
		if (tRow != 19) {
			if (board[tCol + 1][tRow + 1].getContents() == 9) {
				mNear++;
			}
		}
		if (tRow != 0) {
			if (board[tCol + 1][tRow - 1].getContents() == 9) {
				mNear++;
			}
		}
	}
	if (tRow != 19) {
		if (board[tCol][tRow + 1].getContents() == 9) {
			mNear++;
		}
	}
	if (tRow != 0) {
		if (board[tCol][tRow - 1].getContents() == 9) {
			mNear++;
		}
	}
	return mNear;
}

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

void Game::drawGameBoard(sf::RenderWindow& window) {
	for (int r = 0; r < tHeight; r++) {
		for (int c = 0; c < tWidth; c++) {
			board[c][r].drawbutton(window);
		}
	}
	window.draw(timer);
}

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
			}
		}
	}
	if (hasWon != true && hasLost != true) {
		nTimer = elapsedTime;
		timer.setString("TIMER: " + to_string(nTimer) + " sec");
	}
}

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

bool Game::checkWin(void) {
	return hasWon;
}

bool Game::checkLose(void) {
	return hasLost;
}

void Game::stopTimer(bool won) {
	if (won == true) {
		timer.setString("You Won! Final Time: " + to_string(nTimer) + " seconds");
	}
	if (won == false) {
		timer.setString("You Lose!");
	}
}

void Game::revealBoard(void) {

}