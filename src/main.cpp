// Preprocessor variable created when running CMAKE process. This variable 
// indicates the location where non-compilabe or non c/c++ support files are located.
#ifndef RES_PATH_XYQ
#   define RES_PATH_XYQ ""
#else
#endif


/*
TODO: Create a base checkers game engine.
*/

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <algorithm>
#include <random>



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

#include "TTT_wt_but_XYQ.h"
#include "CHK_SFML_eng.h"
#include "CRG_SFML_eng.h"

#include "numUtils.h"

using namespace std;
using namespace gameEngine;

void play_cardReactGame();

// Global string variable holding the full path of the extra resource directory.
string RES_PATH_XYQ_str = string( RES_PATH_XYQ );


int main(int, char**){


    // tests::window_test_5();

    // tests::doButtonObjTest_4();

    // tests::doTxtBoxTest_1();

    // tests::doHPBarTest_1();

    // tests::doInfoBoxTest_1();

    // tests::doPageObjTest_2();

    // tests::TikTakTok_test1();
    
    // game::play_TikTakTok();



    // tests::checkers_test1();

    // tests::checkers_test2();

    // tests::checkers_test3();

    // tests::checkers_test4();

    // tests::CRG_test1();

    // game::play_Checkers();

    play_cardReactGame();
    
    return 0;

}


void play_cardReactGame(){

    // Define the number of cards at play.
    int possCardCnt = 9;

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string funny_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";

    vector<string> CRG_img_FFN_vec;
    int CRG_img_cnt = 9;
    for( int i = 0; i < CRG_img_cnt; i++ ){
        CRG_img_FFN_vec.push_back( RES_PATH_XYQ_str + "/CRG_img_" + to_string(i+1) + ".jpg" );
    }

    shared_ptr<sf::Texture> button_img_np_texture = SFMLUtilsXYQ::genTexture( button_img_np_FFN );
    shared_ptr<sf::Texture> button_img_p_texture = SFMLUtilsXYQ::genTexture( button_img_p_FFN );
    shared_ptr<sf::Texture> funny_img_texture = SFMLUtilsXYQ::genTexture( funny_img_FFN );

    vector< shared_ptr< sf::Texture > > CRG_img_texture_vec;
    for( int i = 0; i < CRG_img_cnt; i++ ){
        shared_ptr<sf::Texture> tmp = SFMLUtilsXYQ::genTexture( CRG_img_FFN_vec.at(i) );
        CRG_img_texture_vec.push_back( tmp );
    }

    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );


    /*
    Create second thread.
    */

// ---------------------------------------------------------------------- >>>>>
//      Game Page Setup
// ---------------------------------------------------------------------- >>>>>

    // Page initialization.
    SFML_page_XYQ page3_game = SFML_page_XYQ();

    // Initialize variable keeping track of the state of the game.
    cardReact::CRG_STATE currCRGState = cardReact::CRG_STATE::UNSTARTED;

    // Object: button for resetting the game board.
    shared_ptr<SFML_button_XYQ> but3A_start = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3A_start->setPos( 200, 500 );
    but3A_start->setWidth( 150 );      
    but3A_start->setHeight( 50 );      
    but3A_start->setTxtFont( font );
    but3A_start->setTxtStr( "Start" );
    but3A_start->setTxtColor( 50, 50, 50, 255 );
    but3A_start->setUPTexture( button_img_np_texture );
    but3A_start->setPTexture( button_img_p_texture );
    // Add to page.
    page3_game.addObj( but3A_start );


    // Object: button for resetting the game board.
    shared_ptr<SFML_button_XYQ> but3B_reset = 
    shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3B_reset->setPos( 400, 500 );
    but3B_reset->setWidth( 150 );      
    but3B_reset->setHeight( 50 );      
    but3B_reset->setTxtFont( font );
    but3B_reset->setTxtStr( "Reset" );
    but3B_reset->setTxtColor( 50, 50, 50, 255 );
    but3B_reset->setUPTexture( button_img_np_texture );
    but3B_reset->setPTexture( button_img_p_texture );
    // Add to page.
    page3_game.addObj( but3B_reset );


    // Object: button for resetting the game board.
    shared_ptr<SFML_button_XYQ> but3C_timeDisplay = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3C_timeDisplay->setPos( 70, 200 );
    but3C_timeDisplay->setWidth( 120 );      
    but3C_timeDisplay->setHeight( 50 );      
    but3C_timeDisplay->setTxtFont( font );
    but3C_timeDisplay->setTxtStr( "" );
    but3C_timeDisplay->setTxtColor( 255, 255, 255, 255 );
    but3C_timeDisplay->setUPColor( 0, 0, 255 );
    but3C_timeDisplay->setPColor( 0, 0, 255 );
    but3C_timeDisplay->disableSprite();
    // Add to page.
    page3_game.addObj( but3C_timeDisplay );


    // Object: button for resetting the game board.
    shared_ptr<SFML_button_XYQ> but3D_stateDisplay = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3D_stateDisplay->setPos( 50, 300 );
    but3D_stateDisplay->setWidth( 150 );      
    but3D_stateDisplay->setHeight( 50 );      
    but3D_stateDisplay->setTxtFont( font );
    but3D_stateDisplay->setTxtSize( 20 );
    but3D_stateDisplay->setTxtStr( "" );
    but3D_stateDisplay->setTxtColor( 255, 255, 255, 255 );
    but3D_stateDisplay->setUPColor( 0, 0, 255 );
    but3D_stateDisplay->setPColor( 0, 0, 255 );
    but3D_stateDisplay->disableSprite();
    // Add to page.
    page3_game.addObj( but3D_stateDisplay );


    // Vector of all possible card buttons.
    vector<shared_ptr<SFML_button_XYQ>> CGR_possCard_buttons;
    // Fill the vector with initial set of buttons.
    for( int z = 0; z < possCardCnt; z++ ){
        shared_ptr<SFML_button_XYQ> buttonX = 
            shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

        CGR_possCard_buttons.push_back( buttonX );
        page3_game.addObj( buttonX );
    }

    // Initialize the game object with button vector.
    gameEngine::CRG_SFML_eng CRG_SFML_obj( CGR_possCard_buttons, 3000 );
    CRG_SFML_obj.setMainFont( font );
    CRG_SFML_obj.setPossCardTex_vect( CRG_img_texture_vec );
    CRG_SFML_obj.reset();
    CRG_SFML_obj.update();

    shared_ptr<SFML_button_XYQ> mainCardBut = CRG_SFML_obj.getMainCard();
    page3_game.addObj( mainCardBut );


    page3_game.update();
    page3_game.enable();

// ---------------------------------------------------------------------- <<<<<


    // Create the main window.
    sf::RenderWindow window( sf::VideoMode(800, 600), "Card Reaction Game" );

    // Main loop.
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                
                but3A_start->pressButton( window );

                but3B_reset->pressButton( window );

                CRG_SFML_obj.pressButton( window );

            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){

                if( but3A_start->releaseButton() ){
                    CRG_SFML_obj.start();
                }

                if( but3B_reset->releaseButton() ){
                    CRG_SFML_obj.reset();
                }

                bool gameButRel = CRG_SFML_obj.releaseButton();

            }
            
        }


        currCRGState = CRG_SFML_obj.getState();
        switch( currCRGState ){
        case cardReact::CRG_STATE::ONGOING:
            but3C_timeDisplay->setTxtStr( to_string( CRG_SFML_obj.getElapsedMS() - 
                CRG_SFML_obj.getCountDownMS() ) + "ms" );
            break;
        case cardReact::CRG_STATE::UNSTARTED:
            but3C_timeDisplay->setTxtColor( 255, 255, 255, 255 );
            but3C_timeDisplay->setTxtStr( to_string( -CRG_SFML_obj.getCountDownMS() ) + "ms" );
            break;
        case cardReact::CRG_STATE::HIT:
            but3C_timeDisplay->setTxtColor( 0, 255, 0 );
            break;
        case cardReact::CRG_STATE::MISS:
            but3C_timeDisplay->setTxtColor( 255, 0, 0 );
            break;
        }
        but3C_timeDisplay->update();
        // Update the game state.
        but3D_stateDisplay->setTxtStr( cardReact::get_CRG_STATE_Str( currCRGState ) );
        but3D_stateDisplay->update();


        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the game page.
        page3_game.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}

// TODO: Make a more accurate time measurement for the game.

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