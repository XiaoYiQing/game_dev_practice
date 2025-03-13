#ifndef CRG_SFML_ENG_H
#define CRG_SFML_ENG_H

#include "cardReact.h"


#include <SFML/Graphics.hpp>

#include "SFML_button_XYQ.h"

using namespace std;



namespace gameEngine{


class CRG_SFML_eng : cardReact{


public:

    // The color of the button when no sprite is present.
    static const sf::Color noCardColor;
    // The color of the button's text when no sprite is present.
    static const sf::Color noCardTxtColor;

// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

    CRG_SFML_eng( int possCardCnt = 8, long long cntDownT = 3000 );

    CRG_SFML_eng( int possCardCnt, long long cntDownT, 
        vector<shared_ptr<SFML_button_XYQ>> possCard_vect );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (public)
// ====================================================================== >>>>>
    
    // Obtain a shared pointer to the main card.
    shared_ptr<SFML_button_XYQ> getMainCard();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
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
    If any one of the buttons is released, return true, else false.
    A button being released triggers a series of checks.
    */
    bool releaseButton();

// ====================================================================== <<<<<

protected:

// ====================================================================== >>>>>
//      Access Functions (protected)
// ====================================================================== >>>>>

// ====================================================================== <<<<<

    /*
    Vector holding the number of rows (x) and columns (y).
    */
    sf::Vector2i rowColCnt;

    /*
    The main card which is hidden at first when the game starts and is then
    revealed when the count down is finished.
    */
    shared_ptr<SFML_button_XYQ> mainCard;

    /*
    The vector of buttons representing the possible cards the hidden card can 
    share the same sprite with.
    */
    vector<shared_ptr<SFML_button_XYQ>> possCard_vect;

    /*
    Textures of the possible cards.
    */
    vector<shared_ptr<sf::Texture>> possCardTex_vect;


};


}


#endif  // CRG_SFML_ENG_H