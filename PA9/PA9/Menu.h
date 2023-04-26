#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>

class Menu {

public:

	Menu(float width, float height);
	~Menu();

	void displayMenu(sf::RenderWindow &window);

	void moveChoice(int dir);


private:

	int iChoice;
	sf::RectangleShape titleBox;
	sf::Text textBlocks[4];
	sf::Font font;

};

#endif
