#pragma once
#include "SFML\Graphics.hpp"
using namespace std;
#include <string>
#include <fstream>
#include <sstream>

//Author: Ethan Burzynski

/*
CLASS LEADERBOARD

This class holds the records of the top 10 times recorded playing Minesweeper.
It also contains functions to load and save top times to a file, every win in Minesweeper
has its time checked against the top 10 times and is saved where it belongs.

This class represents another "Screen" accessible from the main menu.

*/

class Leaderboard {
public:
	Leaderboard(fstream& fileStream);

	~Leaderboard();

	void drawLeaderboard(sf::RenderWindow& window, float x, float y, fstream& fileStream);

	void insertRecord(int time, string initials);

	void removeLastRecord(int position);

	void writeToFile(fstream& fileStream);

private:

	int lbTimes[10];
	string lbInitials[10];
	int count;

};