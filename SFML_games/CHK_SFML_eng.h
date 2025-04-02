#ifndef CHK_SFML_ENG_H
#define CHK_SFML_ENG_H



#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


#include "checkers.h"
#include "SFML_button_XYQ.h"
#include "SFML_page_XYQ.h"
#include "SFML_utils_XYQ.h"
#include "SFML_infoBox_XYQ.h"


using namespace std;

extern string RES_PATH_XYQ_str;



namespace gameEngine{


/*
Game engine for the game of checkers (CHK) with additional integrated SFML
button functionalities.
The buttons used are based on the class SFML_button_XYQ, which are custom buttons
I created using SFML libraries.
*/
class CHK_SFML_eng : public checkers{

public:

    // The color of light tiles.
    static const sf::Color LTILECOLOR;
    // The color of dark tiles.
    static const sf::Color DTILECOLOR;
    // The color of pressed (by mouse) tiles.
    static const sf::Color PTILECOLOR;
    // The color of locked tile.
    static const sf::Color LOCKTILECOLOR;

    /*
    The default constructor provides a set of buttons set at a default location,
    but it is strongly advised you use the alternative constructor which takes 
    in the buttons you created yourself and customized to your need.
    */
    CHK_SFML_eng();

    CHK_SFML_eng( vector<shared_ptr<SFML_button_XYQ>> CHK_buttons );




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

    /*
    TODO: Eventually delete this or integrate this as or into the main releaseButton.
    Temporary version of releaseButton, with additional AI play feature.
    */
    bool releaseButton_alt();

    /*
    Let the AI perform the next play.
    */
    static bool AI_play( CHK_SFML_eng& tarGame );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

    /*
    Update the board buttons to reflect the state of the game.
    */
    void updateCHKBoard();

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
*/
bool setCHK_pieceText( CHK_PIECE tarPiece, shared_ptr<sf::Texture> inText );


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
    Set the checker piece at the target board coordinate directly
    */
    void set_button_at_ij( unsigned int i, unsigned int j, shared_ptr<SFML_button_XYQ> inBut );

// ====================================================================== <<<<<



    /*
    The vector of buttons representing the CHK board squares.
    */
    vector<shared_ptr<SFML_button_XYQ>> CHK_buttons;

    // Textures for the red pieces.
    shared_ptr<sf::Texture> CHKText_red;
    // Textures for the black pieces.
    shared_ptr<sf::Texture> CHKText_blk;
    // Textures for the crowned red pieces.
    shared_ptr<sf::Texture> CHKText_cred;
    // Textures for the crowned black pieces.
    shared_ptr<sf::Texture> CHKText_cblk;

    /*
    Boolean indicating the first click for an action is set.
    This occurs when a piece that can move has been clicked, so that the lock indicates
    that the subsequent click is meant as an action pointer for this specific piece.
    */
    bool act_set_lock;
    shared_ptr<SFML_button_XYQ> act_set_lock_but;
    sf::Vector2i act_set_lock_coords;

};

}





namespace game{
    
    /*
    Initialize a game of checkers.
    */
    void play_Checkers();

    /*
    TODO: Please delete this after you are done with your testing.
    */
    void play_Checkers_alt();

}





#endif  // CHK_SFML_ENG_H