#include "test.h" 
#include "Button.hpp"
#include "Leaderboard.hpp"
#include "GameTile.hpp"
#include "Game.hpp"
#include <iostream>

test::test() {
}

test::~test() {
}

//Test the Constructor for the Button Class
//Author: Ethan Burzynski
void test::testButtonConstructor() {
    Button testButton(100.5, 97.4, 45, 1, "this is a test button text", sf::Color::White, sf::Color::Red, sf::Color::Blue, true);
    cout << "button constructor succeeded, button is currently pressable multiple times" << endl;
    testButton.toggleOff();
    cout << "button public member function for toggling off multiple presses succeeded" << endl;
}

//Test the Setters to configure an instance of a Button Object
//Author: Ethan Burzynski
void test::testButtonSetters() {
    Button testButton(100.5, 97.4, 45, 1, "this is a test button text", sf::Color::White, sf::Color::Red, sf::Color::Blue, true);
    testButton.setSize(sf::Vector2f(200, 50));
    cout << "button inherited function for changing size succeeded" << endl;
    testButton.setTextSize(25);
    cout << "button member setter function for changing text size succeeded" << endl;
    testButton.setFillColor(sf::Color::Cyan);
    cout << "button member setter function for changing button pressed color and normal color succeeded" << endl;
}

//Test the function to insert a Time into the Leaderboard
//Author: Ethan Burzynski
void test::testLeaderboardInsert() {
    fstream test("testLeaderboard.txt");
    Leaderboard testLeaderboard(test);
    cout << "leaderboard constructor succeeded" << endl;
    testLeaderboard.insertRecord(2, "TES");
    cout << "leaderboard insert function succeeded" << endl;
    test.close();
}

//Test the function to reveal a tile's contents
//Author: Alex Langland
void test::testTileReveal() {
    Tile testTile(200, 200);
    cout << "Created Tile Object" << endl;
    testTile.revealContents();
    cout << "Successfully revealed Tile Contents" << endl;
}

//Test the function to reset a tile after a game has ended
//Author: Alex Langland
void test::testTileHide() {
    Tile testTile(200, 200);
    cout << "Created Tile Object" << endl;
    testTile.revealContents();
    testTile.initializeButton(200, 200, 26, 26, "", sf::Color(160, 160, 160, 204), sf::Color(120, 120, 120, 204), sf::Color(120, 120, 120, 204), true);
    testTile.hide();
    cout << "Tile Successfully Re-Concealed" << endl;

}

//The encapsulating function to run all test Cases at once
//Author: Alex Langland
void test::wrapTests() {
    testButtonConstructor();
    testButtonSetters();
    testLeaderboardInsert();
    testTileReveal();
    testTileHide();
    cout << "SUCCESSFULLY FINISHED ALL TEST CASES\n" << endl;
}
