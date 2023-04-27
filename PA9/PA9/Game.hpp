#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "GameTile.hpp"

//Author: Alex Langland

/*
CLASS GAME

This Class encapsulates the Minefield of Tiles, as well as the Timer, and runs most of the Game Logic.

The functions within are capable of completely managing the Game Board and Timer,
This class communicates with main through the "hasWon" and "hasLost" tags, representing the status of the game.

This class also contains tWidth and tHeight, representing how many Tiles the game board is made up of, and mines, the total amount of mines
to be placed into the Minefield by the populateMines() function.

The timer is managed by this class and displayed alongside the Tile Array.

*/

class Game {

public:

	Game(float screenW = 800);
	~Game(void);

	void difficultySelect(int mines);
	float getTime(void);

	void populateMines(void);

	void drawGameBoard(sf::RenderWindow& window);
	void updateGameBoard(sf::RenderWindow& window, float elapsedTime);


	int checkSurroundings(int tCol, int tRow);
	void revealEmpties(int tCol, int tRow);

	void checkStatus(void);
	bool checkWin(void);
	bool checkLose(void);

	void stopTimer(bool won);
	void revealBoard(void);

	void resetBoard(float screenW);

private:

	Tile board[20][20];
	int tWidth;
	int tHeight;
	bool hasWon;
	bool hasLost;
	int mines;

	float nTimer;
	sf::Text timer;
	sf::Font timerFont;
};



