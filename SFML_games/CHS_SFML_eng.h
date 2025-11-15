#ifndef CHS_SFML_ENG_H
#define CHS_SFML_ENG_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>

#include "chess.h"
#include "SFML_button_XYQ.h"
#include "SFML_page_XYQ.h"
#include "SFML_utils_XYQ.h"
#include "SFML_infoBox_XYQ.h"


using namespace std;



namespace gameEngine{


class CHS_SFML_eng : public chess{

    // The color of light tiles.
    static const sf::Color LTILECOLOR;
    // The color of dark tiles.
    static const sf::Color DTILECOLOR;
    // The color of pressed (by mouse) tiles.
    static const sf::Color PTILECOLOR;
    // The color of locked tile.
    static const sf::Color LOCKTILECOLOR;

    CHS_SFML_eng();

    CHS_SFML_eng( vector< shared_ptr< SFML_button_XYQ > > CHS_buttons );

// ====================================================================== >>>>>
//      Gameplay Control Functions
// ====================================================================== >>>>>

    /*
    Try to perform a press button action on all buttons.
    If any button is pressed, return true, else false.
    NOTE: This function does not check if a mouse click is performed or which mouse
    click is performed.
    */
    bool pressButton( const sf::RenderWindow& window );

    /*
    Try to perform a button release on all buttons.
    If any button is released, return true, else false.
    A button being released triggers a series of checks.
    */
    bool releaseButton();

    // Lock all buttons.
    void lock_buttons();
    // Unlock all buttons.
    void unlock_buttons();

    /*
    Let the AI perform the next play.
    NOTE: this function is meant to be used on a separate thread.
    */
    static bool AI_play( CHS_SFML_eng& tarGame );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

    /*
    Update the board buttons to reflect the state of the game.
    */
    void updateCHSBoard();

    /*
    Reset the board to the state of a fresh new game.
    */
    void resetBoard();
    
// ====================================================================== <<<<<

// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

/*
Set the texture for the target piece. 
TODO: There is no direct translation from checkers to chess.
*/
bool setCHS_pieceText( chess::CHS_PIECE_TYPE tarPiece, shared_ptr<sf::Texture> inText );

// ====================================================================== <<<<<

protected:


// ====================================================================== >>>>>
//      Access Functions (Protected)
// ====================================================================== >>>>>

    /*
    Return the button at board coordinate (i,j) = (row index, column index).
    */
    shared_ptr<SFML_button_XYQ> get_button_at_ij(unsigned int i, unsigned int j) const;

    /*
    Set the chess piece button at the target board coordinate directly.
    */
    void set_button_at_ij( unsigned int i, unsigned int j, shared_ptr<SFML_button_XYQ> inBut );

    

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Variables
// ====================================================================== >>>>>

    /*
    The vector of buttons representing the CHS board squares.
    */
    vector< shared_ptr< SFML_button_XYQ > > CHS_buttons;

    // Textures for the white pieces.
    map< CHS_PIECE_TYPE, shared_ptr<sf::Texture> > CHS_PCE_W_tex_map;
    
    // Textures for the black pieces.
    map< CHS_PIECE_TYPE, shared_ptr<sf::Texture> > CHS_PCE_B_tex_map;

    /*
    Boolean indicating the first click for an action is set.
    This occurs when a piece that can move has been clicked, so that the lock indicates
    that the subsequent click is meant as an action pointer for this specific piece.
    */
    bool act_set_lock;
    shared_ptr<SFML_button_XYQ> act_set_lock_but;
    sf::Vector2i act_set_lock_coords;

// ====================================================================== <<<<<


};


}


namespace game{
    
    /*
    Initialize a game of chess.
    */
    void play_chess();


}



#endif // CHS_SFML_ENG_H