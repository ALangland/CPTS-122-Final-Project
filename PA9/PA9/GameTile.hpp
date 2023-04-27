#ifndef TILE
#define TILE

#include <SFML/Graphics.hpp>
#include "Button.hpp"

//Author: Alex Langland

/*
CLASS TILE

This class inherits the properties of a Button, fulfilling the Inheritance requirement

The Tile is a special kind of Button that represents one tile on the minefield. It is a button that, once pressed,
will be "revealed" and the Number or Mine concealed will be revealed. If the "contents" is equal to 9, this
represents a mine and the game will end.

This class also contains a position vector for easy reference of placing the Text within the tile, and a "revealed" tag representing
whether the tile has been clicked or not.

*/

class Tile : public Button {

public:

	Tile();
	Tile(float x, float y);
	~Tile();

	void setContents(int newContents);
	int getContents(void);
	void setPosVec(float x, float y);

	void revealContents(void);

	bool isRevealed(void);
	void hide(void);

private:

	int contents;
	sf::Vector2f posVec;
	bool revealed;

};

#endif
