#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "GameTile.hpp"

class Game {

public:

	Game(float screenW = 800);
	~Game(void);

	void populateMines(void);

	void drawGameBoard(sf::RenderWindow& window);
	void updateGameBoard(sf::RenderWindow& window);

	int checkSurroundings(int tCol, int tRow);
	void revealEmpties(int tCol, int tRow);

private:

	Tile board[20][20];
	int tWidth;
	int tHeight;
	bool hasWon;
	bool hasLost;
	int mines;

};

