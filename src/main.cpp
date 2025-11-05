// Preprocessor variable created when running CMAKE process. This variable 
// indicates the location where non-compilabe or non c/c++ support files are located.
#ifndef RES_PATH_XYQ
#   define RES_PATH_XYQ ""
#else
#endif



#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <thread>




#include <SFML/Graphics.hpp>


#include "SFML_button_XYQ.h"
#include "SFML_TxtBox_XYQ.h"
#include "SFML_HPBar_XYQ.h"
#include "SFML_infoBox_XYQ.h"
#include "SFML_page_XYQ.h"

#include "window_test.h"
#include "button_test.h"
#include "txtBox_test.h"
#include "HPBar_test.h"
#include "infoBox_test.h"
#include "pageObj_test.h"
#include "chess_test.h"

#include "TTT_wt_but_XYQ.h"
#include "CHK_SFML_eng.h"
#include "CRG_SFML_eng.h"

#include "chess.h"

#include "numUtils.h"

using namespace std;
using namespace gameEngine;

// TODO: Organized your tests. For instance, the checkers_tests.cpp file should be
//  in the tests directory.

// TODO: Review your comments.

// TODO: Make a more official form of comments. Use this opportunity to review your code.

// TODO: Create a print state function for your game engines.

void do_tests( unsigned int test_id );

// Global string variable holding the full path of the extra resource directory.
string RES_PATH_XYQ_str = string( RES_PATH_XYQ );


int main(int, char**){


// ====================================================================== >>>>>
//      Global Resource Path Setup
// ====================================================================== >>>>>

    // Get the path to the executable
    std::filesystem::path exePath = std::filesystem::current_path();
    // Set resource directory relative to the executable
    std::filesystem::path resourceDir = exePath / ".." / "res";
    // Obtain the string representation and set it as the global resource path.
    RES_PATH_XYQ_str = resourceDir.string();
    // Replace backslashes with forward slashes
    std::replace(RES_PATH_XYQ_str.begin(), RES_PATH_XYQ_str.end(), '\\', '/');

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Run Game
// ====================================================================== >>>>>

    // game::play_TikTakTok();

    // game::play_Checkers();

    // game::play_cardReact();

// ====================================================================== <<<<<

    do_tests(0);

    return 0;

}



void do_tests( unsigned int test_id ){

    
    // tests::window_test_5();

    // tests::doButtonObjTest_4();

    // tests::doTxtBoxTest_1();

    // tests::doHPBarTest_1();

    // tests::doInfoBoxTest_1();

    // tests::doPageObjTest_2();

    // tests::TikTakTok_test1();

    // tests::TikTakTok_test4();

    // tests::TikTakTok_test6();

    // tests::checkers_test1();

    // tests::checkers_test2();

    // tests::checkers_test3();

    // tests::checkers_test4();

    // tests::checkers_test5();

    // tests::checkers_test8( 2 );

    // tests::checkers_test9(2);

    // tests::checkers_test10(10);

    // tests::CRG_test1();

    // tests::chess_base_tests();
    // tests::chess_chs_move_tests();
    // tests::chess_game_manip_tests();
    // tests::chess_move_tests();
    // tests::chess_atk_check_tests();
    // tests::chess_play_tests();
    // tests::chess_promo_tests();
    // tests::chess_en_pass_tests();

    // tests::chess_game_state_tests();
    // tests::chess_psbl_plays_tests();
    tests::chess_checkmate_tests();
    
    // tests::chess_full_game_tests();

}


/*
DONE: Create a base checkers game engine.
*/

/* 
DONE: Make a more accurate time measurement for the game.
*/

/*
DONE: Button's sprite now can have their size adjusted through modying its scaling 
value with respect to the rectangle's size.
*/

/*
DONE: rename your work directories to reflect the purpose of these directories.
    Also create a separate directory for your game engines.
*/

/*
DONE: Modify where you can the passing of texture rather than file name.
*/

/*
DONE: Buttons should have an alternative way to be given a sprite rather than a FFN.
Find a way to provide sprite shared pointer allowing direct transfer of sprites
without heavy usage of memory.
*/

/*
DONE: See if you can assign the TTT buttons to the TTT game engine. (Yes you can)
*/

/*
DONE: Create a Tik-Tac-Tok game engine so as to put the pieces of code related to 
TTT in a more structured manner rather than being spread out within the
SFML windown control codes.
*/

/*
DONE: Create a skeleton version of the game of Tik-Tak-Toc.
*/

/*
DONE: Use your test setup to create a navigatable set of menu pages.
*/

/* 
DONE: you need to create an exercise where you have two windows. Only one window is
drawn at a time, and they can switch to each other when a button on their respective 
area is pressed.
Note: I didn't create two windows; I make the window draw two sets of objects to mimic
the effect of having two windows.
*/

/*
DONE: Create polymorphic parent class to your SFML objects such that they can be grouped 
in a more structured way and be used in a more uniform manner.
*/

/*
DONE: Create an object which pairs up an image box with a text box.
The image box can be a button which doesn't necessarily have to do anything when clicked.
*/

/*
DONE: Create an object which represents a SFML page with all objects intended to be drawn
within that object as a sort of list or array.
This object has to be able to manage the SFML objects intended to be rendered on the target page.
*/


/*
DONE: Put all non-class functions into a utility file.
*/

/*
DONE: Don't use output printing for error messages. Replace them with exception throwing.
*/

/*
DONE: Eliminate all global variable dependencies of your tools in "testUtils" 
sub-directory.
*/

/*
DONE: Anything that uses sf::Font should use it as a shared_ptr.
*/

/*
DONE: Create a library out of the directory where you stored your SFML files.
*/

/*
DONE: Encapsulate non-class functions you created for your SFML custom objects
in a namespace.
*/