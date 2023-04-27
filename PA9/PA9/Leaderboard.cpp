#include <SFML/Graphics.hpp>
#include "Leaderboard.hpp"
using namespace std;
#include <string>
#include <fstream>
#include <sstream>

//Constructor for the Leaderboard
Leaderboard::Leaderboard(fstream& fileStream) {
	count = 0;
	fileStream.clear();
	fileStream.seekp(0, std::ios_base::beg);
	string initbuffer;
	char getfline[20];
	string delimiter1 = ",";
	while (count < 10 && fileStream.is_open() == true) {
		//Automatically Load the Data from the Save File
		fileStream.getline(getfline, 20);
		string test(getfline);
		this->lbTimes[this->count] = stoi(test.substr(0, test.find(delimiter1)));
		test.erase(0, test.find(delimiter1) + delimiter1.length());
		this->lbInitials[count] = test;
		this->count++;
	}
}

//Default Destructor
Leaderboard::~Leaderboard() {

}

//Draw the Leaderboard's times to the render window
void Leaderboard::drawLeaderboard(sf::RenderWindow& window, float x, float y, fstream& fileStream) {
	sf::Font font;
	font.loadFromFile("LSANS.ttf");
	sf::Text myText;
	myText.setFont(font);
	myText.setFillColor(sf::Color::White);
	myText.setCharacterSize(16);
	char getfline[20];
	//size of each leaderboard rectangle
	//ideal text would be time: xx.xx | [initials]
	sf::Vector2f rectangleSize;
	rectangleSize.x = 190;
	rectangleSize.y = 40;
	string nString;
	myText.setString("LEADERBOARD");
	myText.setStyle(sf::Text::Bold);
	myText.setPosition(100, 50);
	window.draw(myText);
	myText.setStyle(sf::Text::Regular);
	for (int i = 0; i < 10; i++) {
		//draw rectangle using x and y
		//calculate center for the text
		//draw the text
		//update y for next rectangle
		//yes this is a mess :(

		//creating string to display
		fileStream.getline(getfline, 20);
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
		mRect.setOutlineColor(sf::Color::White);
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

//Check if a new time is faster than any time on the top 10 leaderboard
//If it is, place it in the leaderboard where it belongs
void Leaderboard::insertRecord(int time, string initials) {
	//order by time
	for (int i = 0; i < count; i++) {
		if (time <= this->lbTimes[i]) {
			removeLastRecord(i);
			this->lbTimes[i] = time;
			this->lbInitials[i] = initials;
			break;
		}
	}
}

//Push out the slowest time upon the arrival of a new faster time
void Leaderboard::removeLastRecord(int position) {
	position--;
	for (int j = 8; j > position; j--) {
		this->lbTimes[j + 1] = this->lbTimes[j];
		this->lbInitials[j + 1] = this->lbInitials[j];
	}
}

//Save the current Leaderboard to the File
//format: [time(in milliseconds)],[initials]
void Leaderboard::writeToFile(fstream& fileStream) {
	for (int i = 0; i < 10; i++) {
		if (i == 9) {
			fileStream << this->lbTimes[i] << "," << this->lbInitials[i];
			break;
		}
		fileStream << this->lbTimes[i] << "," << this->lbInitials[i] << endl;
	}
}