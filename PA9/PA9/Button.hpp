#pragma once
using namespace std;
#include "SFML\Graphics.hpp"
#include <string>
//testing if github is working
//this is a test comment
class Button : public sf::RectangleShape{
public:
	Button() {

	}
	Button(float x, float y, float width, float height, string nText, sf::Color nNormalColor, sf::Color nHoverColor, sf::Color nPressedColor, bool nChangeable) {
		this->buttonShape.setSize(sf::Vector2f(width, height));
		this->buttonShape.setPosition(sf::Vector2f(x, y)); 
		this->text.setString(nText);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(16);
		this->text.setPosition(0, 0);
		this->font.loadFromFile("isocpeur.ttf");
		this->text.setFont(font);
		this->text.setPosition(this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2.0, 
							   this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.0);
		this->normalColor = nNormalColor;
		this->buttonShape.setFillColor(nNormalColor);
		this->hoverColor = nHoverColor;
		this->pressedColor = nPressedColor;
		this->pressed = false;
		this->hovered = false;
		this->changeable = nChangeable;
	}
	~Button() {

	}
	void updateButton(sf::Vector2f mousePos) {
		//update function for pressing the button and changing color when hovering
		this->hovered = false;
		if (changeable == true) {
			this->pressed = false;
		}
		if (this->buttonShape.getGlobalBounds().contains(mousePos)) {
			this->hovered = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->pressed = true;
			}
		}
		if (this->pressed == true) {
			this->buttonShape.setFillColor(this->pressedColor);
			//this->text.setRotation(this->text.getRotation() + 0.05);
			//funny rotation thing
		}
		else if (this->hovered == true) {
			this->buttonShape.setFillColor(this->hoverColor);
		}
		else if (this->hovered == false) {
			this->buttonShape.setFillColor(this->normalColor);
		}
	}
	void drawbutton(sf::RenderWindow& window) {
		window.draw(this->buttonShape);
		window.draw(this->text);
	}

	bool isPressed() {
		return this->pressed;
	}

	bool isHovered() {
		return this->hovered;
	}
	
private:
	sf::RectangleShape buttonShape;
	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
	sf::Text text;
	sf::Font font;
	bool pressed;
	bool hovered;
	bool changeable;
};