#ifndef CRG_SFML_ENG_H
#define CRG_SFML_ENG_H



#include <chrono>
#include <SFML/Graphics.hpp>
#include <thread>

#include "cardReact.h"
#include "SFML_button_XYQ.h"
#include "SFML_infoBox_XYQ.h"
#include "SFML_page_XYQ.h"


using namespace std;

extern string RES_PATH_XYQ_str;


namespace gameEngine{


class CRG_SFML_eng : public cardReact{


public:

    // The color of the unpressed button before game over when no sprite is present.
    static const sf::Color upColorBef;
    // The color of the pressed button before game over when no sprite is present.
    static const sf::Color pColorBef;
    // The color of the unpressed button after game over when no sprite is present.
    static const sf::Color upColorAft;
    // The color of the pressed button after game over when no sprite is present.
    static const sf::Color pColorAft;
    // The color of the button's text when no sprite is present.
    static const sf::Color noCardTxtColor;

    

    
// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

    CRG_SFML_eng( int possCardCnt = 9, long long cntDownT = 3000 );

    CRG_SFML_eng( vector<shared_ptr<SFML_button_XYQ>> possCard_vect, long long cntDownT );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (public)
// ====================================================================== >>>>>
    
    // Obtain a shared pointer to the main card.
    shared_ptr<SFML_button_XYQ> getMainCard();

    // Set the main font utilized by objects the display texts in this class.
    // Also applies the font to all valid targets in the class.
    void setMainFont( sf::Font );

    //possCardTex_vect
    void setPossCardTex_vect( vector<shared_ptr<sf::Texture>> possCardTex_vect );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

    // Update the objects related to SFML.
    void update();
    
    /*
    Reset the state of the game.
    */
    void reset();
    
    /*
    Update the main card.
    */
    void upd_mainCard();

    /*
    Update the field cards.
    Positions are shuffled if specified.
    NOTE: only the card placement is shuffled, not the card indices.
    */
    void upd_fieldCards( bool shuffle );

    /*
    Start the game.
    */
    void start();

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
//      Gameplay Functions (Protected)
// ====================================================================== >>>>>

    /*
    Perform a countdown, following which the hidden card is revealed.
    NOTE: this function is meant to be used on a separate thread.
    */
    static void countDownThread( CRG_SFML_eng& tarObj );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (protected)
// ====================================================================== >>>>>

// ====================================================================== <<<<<
    

    // The color of the button when not pressed.
    sf::Color upColor;
    // The color of the button when pressed
    sf::Color pColor;
    // The color of the main card background.
    sf::Color mainCardColor;

    /*
    The font adopted by text in this class.
    */
    sf::Font mainFont;

    /*
    Vector holding the number of rows (x) and columns (y).
    */
    sf::Vector2u rowColCnt;
    
    // Position (Upper-left corner) of the field of possible cards.
    sf::Vector2f field_pos;
    // Size of the cards from the field of cards (x = width, y = height).
    sf::Vector2f field_card_dim;
    // Separation between cards from the field.
    float field_card_sep;
    // The cards ordering.
    vector<unsigned int> rdOrdIdx_Vect;

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


};


namespace game{
    
    /*
    Initialize a game of checkers.
    */
    void play_cardReact();

};

#endif  // CRG_SFML_ENG_H