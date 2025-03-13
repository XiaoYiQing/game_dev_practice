#include "CRG_SFML_eng.h"



using namespace gameEngine;



const sf::Color CRG_SFML_eng::noCardColor = sf::Color( 255, 255, 255, 255 );
const sf::Color CRG_SFML_eng::noCardTxtColor = sf::Color( 255, 0, 0, 255 );


// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

CRG_SFML_eng::CRG_SFML_eng( int possCardCnt, long long cntDownT ) : 
    cardReact( possCardCnt, cntDownT )
{

    // Determine the number of rows and columns of cards depending on how many cards there
    // are in total.
    float tmp = std::sqrt( (float) possCardCnt );
    rowColCnt.x = (int) std::ceil( ( (float) possCardCnt )/tmp );
    rowColCnt.y = (int) std::ceil( tmp );
    

    // Define the default locations and sizes of the buttons.
    float x_start = 100;        float y_start = 100;
    float butWidth = 50;       float butHeight = 50;
    float butSep = 5;

    // Card index variable.
    int z = 0;

    // Standard distribution of buttons into a rectangular formation (as close to square as possible).
    for( int i = 0; ( i < rowColCnt.x && z < possCardCnt ); i++ ){
        for( int j = 0; ( j < rowColCnt.y && z < possCardCnt ); j++ ){

            possCardTex_vect.push_back( shared_ptr<sf::Texture>( new sf::Texture() ) );

            shared_ptr<SFML_button_XYQ> buttonX = 
                    shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

            buttonX->setPos( x_start + ( butWidth + butSep )*j, 
                y_start + ( butHeight + butSep )*i );
            buttonX->setWidth( butWidth );      
            buttonX->setHeight( butHeight );
            buttonX->setUPColor( noCardColor );
            buttonX->setPColor( noCardColor );
            buttonX->setTxtStr( to_string( z ) );
            buttonX->setTxtColor( noCardTxtColor );
            buttonX->enableText();
            buttonX->disableSprite();

            possCard_vect.push_back( buttonX );

            buttonX->update();

            z++;

        }

    }

    // Initialize the main card.
    int mainCardID = this->getMainCardID();
    this->mainCard = possCard_vect.at( mainCardID );

}


CRG_SFML_eng::CRG_SFML_eng( int possCardCnt, long long cntDownT, 
    vector<shared_ptr<SFML_button_XYQ>> possCard_vect )
{

    // Use the given card pointer vector.
    this->possCard_vect = possCard_vect;
    // Obtain the number of cards.
    this->possCardCnt = possCard_vect.size();

    // Determine the number of rows and columns of cards depending on how many cards there
    // are in total.
    float tmp = std::sqrt( (float) possCardCnt );
    rowColCnt.x = (int) std::ceil( ( (float) possCardCnt )/tmp );
    rowColCnt.y = (int) std::ceil( tmp );  
    
    

    // Define the default locations and sizes of the buttons.
    float x_start = 100;        float y_start = 100;
    float butWidth = 100;       float butHeight = 100;
    float butSep = 5;

    // Card index variable.
    int z = 0;

    // Standard distribution of buttons into a rectangular formation (as close to square as possible).
    for( int i = 0; ( i < rowColCnt.x && z < possCardCnt ); i++ ){
        for( int j = 0; ( j < rowColCnt.y && z < possCardCnt ); j++ ){

            possCardTex_vect.push_back( shared_ptr<sf::Texture>( new sf::Texture() ) );

            shared_ptr<SFML_button_XYQ> buttonX = this->possCard_vect.at(z);

            buttonX->setPos( x_start + ( butWidth + butSep )*j, 
                y_start + ( butHeight + butSep )*i );
            buttonX->setWidth( butWidth );      
            buttonX->setHeight( butHeight );
            buttonX->setUPColor( noCardColor );
            buttonX->setPColor( noCardColor );

            buttonX->setTxtStr( to_string( z ) );
            buttonX->setTxtColor( noCardTxtColor );
            buttonX->enableText();

            buttonX->disableSprite();

            buttonX->update();

            z++;

        }

    }

    // Initialize the main card.
    int mainCardID = this->getMainCardID();
    this->mainCard = possCard_vect.at( mainCardID );

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (public)
// ====================================================================== >>>>>

shared_ptr<SFML_button_XYQ> CRG_SFML_eng::getMainCard(){
    return this->mainCard;    
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

bool CRG_SFML_eng::pressButton( const sf::RenderWindow& window ){

    bool success = false;

    for( int z = 0; z < possCardCnt; z++ ){

        // Get the current button.
        shared_ptr<SFML_button_XYQ> buttonX = this->possCard_vect.at(z);

        // Attempt a button press on current button.
        success = buttonX->pressButton( window );

        if( success ){

            cout << "Button pressed: " << to_string(z) << endl;

            break;

        }

    }

    return false;

}


bool CRG_SFML_eng::releaseButton(){
    
    bool released = false;

    for( int z = 0; z < possCardCnt; z++ ){

        // Get the current button.
        shared_ptr<SFML_button_XYQ> buttonX = this->possCard_vect.at(z);

        released = buttonX->releaseButton();

        if( released ){

            cout << "Button released: " << to_string(z) << endl;

            if( z == mainCardID ){
                cout << "MATCH!" << endl;
            }

            break;

        }

    }

    return released;

}
