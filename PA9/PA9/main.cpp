#include <SFML/Graphics.hpp>
#include "Button.hpp"

int main(void) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
	Button mButton(50, 50, 100, 40, "EPIC BUTTON", sf::Color(70,70,70,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), true);
	sf::Event event;
	sf::Vector2i mousePos;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		mousePos = sf::Mouse::getPosition(window);
		mButton.updateButton((sf::Vector2f)mousePos);
		mButton.drawbutton(window);
		window.display();
	}

	return 0;
}