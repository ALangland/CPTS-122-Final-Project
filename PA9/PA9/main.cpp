#include <SFML/Graphics.hpp>
#include "Menu.h"

int main(void) {
	float screenX = 800, screenY = 600;
	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Minesweeper");

	Menu myMenu(screenX, screenY);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		myMenu.displayMenu(window);

		window.display();
	}

	

	return 0;
}