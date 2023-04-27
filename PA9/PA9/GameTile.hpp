#ifndef TILE
#define TILE

#include <SFML/Graphics.hpp>
#include "Button.hpp"

//Author: Alex Langland

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

private:

	int contents;
	sf::Vector2f posVec;
	bool revealed;

};

#endif
