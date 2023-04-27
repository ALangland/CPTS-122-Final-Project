#pragma once
using namespace std;
#include "SFML\Graphics.hpp"
#include <string>
//Author: Ethan Burzynski

class Button : public sf::RectangleShape{
public:

	Button(float x, float y, float width, float height, string nText, sf::Color nNormalColor, sf::Color nHoverColor, sf::Color nPressedColor, bool nChangeable) {
		this->buttonShape.setSize(sf::Vector2f(width, height));
		this->buttonShape.setPosition(sf::Vector2f(x, y)); 
		this->text.setString(nText);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(16);
		this->text.setPosition(0, 0);
		this->font.loadFromFile("LSANS.ttf");
		this->text.setFont(font);
		this->text.setPosition(this->buttonShape.getPosition().x + this->buttonShape.getLocalBounds().width / 2.0 - this->text.getLocalBounds().width / 2.0, 
							   this->buttonShape.getPosition().y + this->buttonShape.getLocalBounds().height / 2.0 - this->text.getLocalBounds().height / 2.0);
		this->normalColor = nNormalColor;
		this->buttonShape.setFillColor(nNormalColor);
		this->hoverColor = nHoverColor;
		this->pressedColor = nPressedColor;
		this->pressed = false;
		this->hovered = false;
		this->changeable = nChangeable;
	}
	Button() {
		buttonShape.setSize(sf::Vector2f(0, 0));
		text.setString("");

		this->normalColor = sf::Color::White;
		this->buttonShape.setFillColor(sf::Color::White);
		this->hoverColor = sf::Color::White;
		this->pressedColor = sf::Color::White;
		this->pressed = false;
		this->hovered = false;
		this->changeable = false;
	}
	void initializeButton(float x, float y, float width, float height, string nText, sf::Color nNormalColor, sf::Color nHoverColor, sf::Color nPressedColor, bool nChangeable) {
		this->buttonShape.setSize(sf::Vector2f(width, height));
		this->buttonShape.setPosition(sf::Vector2f(x, y));
		this->text.setString(nText);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(16);
		this->text.setPosition(0, 0);
		this->font.loadFromFile("LSANS.ttf");
		this->text.setFont(font);
		this->text.setPosition(this->buttonShape.getPosition().x + this->buttonShape.getLocalBounds().width / 2.0 - this->text.getLocalBounds().width / 2.0,
			this->buttonShape.getPosition().y + this->buttonShape.getLocalBounds().height / 2.0 - this->text.getLocalBounds().height / 2.0);
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
		if (this->buttonShape.getGlobalBounds().contains(mousePos) && changeable == true) {
			this->hovered = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->pressed = true;
			}
		}
		if (this->pressed == true) {
			this->buttonShape.setFillColor(this->pressedColor);
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
	void formatText(float x, float y, int charSize, sf::Color color) {
		text.setPosition(sf::Vector2f(x, y));
		text.setCharacterSize(charSize);
		text.setFillColor(color);
	}
	void setText(sf::String& newText) {
		text.setString(newText);
	}
	void setText(std::string& newText) {
		text.setString(newText);
	}
	void setFillColor(sf::Color color) {
		pressedColor = color;
		normalColor = color;
	}
	void toggleOff(void) {
		changeable = false;
	}
	void activateOutline(void) {
		buttonShape.setOutlineColor(sf::Color::Black);
		buttonShape.setOutlineThickness(0.5);
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