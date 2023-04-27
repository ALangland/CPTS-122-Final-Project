#pragma once
#include "SFML\Graphics.hpp"
using namespace std;
#include <string>
#include <fstream>
#include <sstream>


//Author: Ethan Burzynski

class Leaderboard {
public:
	Leaderboard() {
		this->fileStream.open("leaderboard.txt");
		string initbuffer;
		char getfline[20];
		string delimiter1 = ",";
		while (!fileStream.eof()) {
			fileStream.getline(getfline, 20);
			string test(getfline);
			this->lbTimes[this->count] = stoi(test.substr(0, test.find(delimiter1)));
			test.erase(0, test.find(delimiter1) + delimiter1.length());
			this->lbInitials[count] = test;
			this->count++;
		}
	}
	~Leaderboard() {
		this->fileStream.close();
	}
	void drawLeaderboard(sf::RenderWindow& window, float x, float y) {
		sf::Font font;
		font.loadFromFile("isocpeur.ttf");
		sf::Text myText;
		myText.setFont(font);
		myText.setFillColor(sf::Color::Black);
		myText.setCharacterSize(16);
		this->fileStream.close();
		this->fileStream.open("leaderboard.txt");
		char getfline[20];
		//size of each leaderboard rectangle
		//ideal text would be time: xx.xx | [initials]
		sf::Vector2f rectangleSize;
		rectangleSize.x = 140;
		rectangleSize.y = 40;
		string nString;
		myText.setString("Leaderboard");
		myText.setPosition(x + (rectangleSize.x - myText.getGlobalBounds().width) / 2.0,
			y - 40 + (rectangleSize.y -myText.getGlobalBounds().height) / 2.0);
		window.draw(myText);
		for (int i = 0; i < 10; i++) {
			//draw rectangle using x and y
			//calculate center for the text
			//draw the text
			//update y for next rectangle
			//yes this is a mess :(

			//creating string to display
			this->fileStream.getline(getfline, 20);
			string mString(getfline);
			mString.insert(0, "time: ");
			nString = mString.substr(0, mString.find(","));
			mString.erase(0, mString.find(",") + 1);
			nString.insert(nString.length() - 2, ".");
			nString.append("s | ");
			nString.append(mString);
			myText.setString(nString);
			//creating rectangle
			sf::RectangleShape mRect;
			mRect.setOutlineColor(sf::Color::Black);
			mRect.setOutlineThickness(1);
			mRect.setFillColor(sf::Color(70, 70, 70, 200));
			mRect.setSize(rectangleSize);
			mRect.setPosition(x, y);
			myText.setPosition(mRect.getPosition().x + (mRect.getGlobalBounds().width - myText.getGlobalBounds().width) / 2.0,
				mRect.getPosition().y + (mRect.getGlobalBounds().height - myText.getGlobalBounds().height) / 2.0);
			window.draw(mRect);
			window.draw(myText);
			y += rectangleSize.y;
		}
	}
	void insertRecord(int time, string initials) {
		//order by time
		for (int i = 0; i < count; i++) {
			if (time <= this->lbTimes[i]) {
				removeLastRecord(i);
				this->lbTimes[i] = time;
				this->lbInitials[i] = initials;
				break;
			}
		}
		writeToFile();
	}
	void removeLastRecord(int position) {
		position--;
		for (int j = 8; j > position; j--) {
			this->lbTimes[j + 1] = this->lbTimes[j];
			this->lbInitials[j + 1] = this->lbInitials[j];
		}
	}
	//format: [time(in milliseconds)],[initials]
	void writeToFile() {
		this->fileStream.close();
		this->fileStream.open("leaderboard.txt");
		for (int i = 0; i < 10; i++) {
			if (i == 9) {
				this->fileStream << this->lbTimes[i] << "," << this->lbInitials[i];
				break;
			}
			this->fileStream << this->lbTimes[i] << "," << this->lbInitials[i] << endl;
		}
	}
private:
	fstream fileStream;
	int lbTimes[10];
	string lbInitials[10];
	int count = 0;
	//bool isloaded;
};