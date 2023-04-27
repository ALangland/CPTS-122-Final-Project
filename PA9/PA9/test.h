#pragma once

//Author: Alex Langland

/*
TEST CLASS

built to test out that certain functions and objects we have
programmed are working as intended.

Split into several unit functions and run by
a wrapper function at the beginning of the main() function

*/

class test {

public:
    test();
    ~test();

    void testButtonConstructor();

    void testButtonSetters();

    void testLeaderboardInsert();

    void testTileReveal();

    void testTileHide();

    void wrapTests();

};