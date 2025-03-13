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

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (public)
// ====================================================================== >>>>>

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>


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