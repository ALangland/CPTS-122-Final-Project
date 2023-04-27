#include "Button.hpp"
#include "GameTile.hpp"

//Author: Alex Langland
using std::to_string;

Tile::Tile() {

	posVec.x = 0, posVec.y = 0;
	this->initializeButton(0, 0, 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
	this->formatText(7, 10, 20, sf::Color::Black);
	this->activateOutline();
	contents = 0;
	revealed = false;

}

Tile::Tile(float x, float y) {

	posVec.x = x, posVec.y = y;
	this->initializeButton(x, y, 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
	this->formatText(x+7, y-1, 20, sf::Color::Black);
	this->activateOutline();
	contents = 0;
	revealed = false;

}

void Tile::setPosVec(float x, float y) {
	posVec.x = x;
	posVec.y = y;
}

Tile::~Tile(){

}

void Tile::setContents(int newContents) {
	contents = newContents;
}
int Tile::getContents(void) {
	return contents;
}

void Tile::revealContents(void) {
	this->setFillColor(sf::Color::White);
	this->toggleOff();
	if (contents == 9) {
		string mine = "M";
		this->setText(mine);
		this->formatText(posVec.x+4, posVec.y-1, 20, sf::Color::Red);
	}
	if (contents > 0 && contents < 9) {
		std::string num = std::to_string(contents);
		if (contents == 1) {
			this->formatText(posVec.x + 7, posVec.y - 1, 20, sf::Color::Blue);
		}
		else if (contents == 2) {
			this->formatText(posVec.x + 7, posVec.y - 1, 20, sf::Color(11, 155, 0, 255));
		}
		else if (contents == 3){
			this->formatText(posVec.x + 7, posVec.y - 1, 20, sf::Color(214, 139, 10, 255));
		}
		else {
			this->formatText(posVec.x + 7, posVec.y - 1, 20, sf::Color(201, 19, 199, 255));
		}
		this->setText(num);
	}
	revealed = true;
}

bool Tile::isRevealed(void) {
	return revealed;
}