#include "Button.hpp"
#include "GameTile.hpp"

//Author: Alex Langland
using std::to_string;

//Default Constructor for a Minefield Tile
Tile::Tile() {

	posVec.x = 0, posVec.y = 0;
	this->initializeButton(0, 0, 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
	this->formatText(7, 10, 20, sf::Color::Black);
	this->activateOutline();
	contents = 0;
	revealed = false;

}

//Constructor for Minefield, accepts float values for the position of the Tile
//EXAMPLE OF POLYMORPHY: AN OVERLOAD TO THE CONSTRUCTOR
Tile::Tile(float x, float y) {

	posVec.x = x, posVec.y = y;
	this->initializeButton(x, y, 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
	this->formatText(x+7, y-1, 20, sf::Color::Black);
	this->activateOutline();
	contents = 0;
	revealed = false;

}

//Set the Position Vector for outside reference
void Tile::setPosVec(float x, float y) {
	posVec.x = x;
	posVec.y = y;
}

//Default Destructor
Tile::~Tile(){

}

//Setter/Getter for the Contents (The number representing how many adjacent mines there are or if there is a mine under this tile).
void Tile::setContents(int newContents) {
	contents = newContents;
}
int Tile::getContents(void) {
	return contents;
}

//Revearl The Contents of the tile:
//This function deactivates the Button as pressable, and reveals the number present, no number is there are no adjacent mines (or, in the case of a mine, the M).
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
		//Different Text Colors are used for some of the more common number possibilities for ease of reading
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

//Checks if the tile has been "Revealed"
bool Tile::isRevealed(void) {
	return revealed;
}

//Sets the "revealed" tag to false
void Tile::hide(void) {
	revealed = false;
}