#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "GameTile.hpp"

//Author: Alex Langland

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



