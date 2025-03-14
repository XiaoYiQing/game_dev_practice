#include "CRG_SFML_eng.h"



using namespace gameEngine;



const sf::Color CRG_SFML_eng::noCardUPColor = sf::Color( 255, 255, 255, 255 );
const sf::Color CRG_SFML_eng::noCardPColor = sf::Color( 0, 0, 255, 255 );
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
    float x_start = 250;        float y_start = 100;
    float butWidth = 100;       float butHeight = 100;
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
            buttonX->setUPColor( noCardUPColor );
            buttonX->setPColor( noCardPColor );

            buttonX->setTxtFont( mainFont );
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
    this->mainCard = shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    mainCard->setPos( x_start - 150, y_start );

    mainCard->setWidth( butWidth );      
    mainCard->setHeight( butHeight );
    mainCard->setUPColor( noCardUPColor );
    mainCard->setPColor( noCardPColor );
    mainCard->setTxtStr( to_string( mainCardID ) );
    mainCard->setTxtColor( noCardTxtColor );
    mainCard->disableText();
    mainCard->disableSprite();

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
    float x_start = 250;        float y_start = 100;
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
            buttonX->setUPColor( noCardUPColor );
            buttonX->setPColor( noCardPColor );

            buttonX->setTxtFont( mainFont );
            buttonX->setTxtStr( to_string( z ) );
            buttonX->setTxtColor( noCardTxtColor );
            buttonX->enableText();

            buttonX->disableSprite();

            buttonX->update();

            z++;

        }

    }

    // Initialize the main card.
    this->mainCard = shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    mainCard->setPos( x_start - 150, y_start );

    mainCard->setWidth( butWidth );      
    mainCard->setHeight( butHeight );
    mainCard->setUPColor( noCardUPColor );
    mainCard->setPColor( noCardPColor );
    mainCard->setTxtStr( to_string( mainCardID ) );
    mainCard->setTxtColor( noCardTxtColor );
    mainCard->disableText();
    mainCard->disableSprite();

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (public)
// ====================================================================== >>>>>

shared_ptr<SFML_button_XYQ> CRG_SFML_eng::getMainCard(){
    return this->mainCard;    
}

void CRG_SFML_eng::setMainFont( sf::Font mainFont ){
    
    this->mainFont = mainFont;

    for( shared_ptr<SFML_button_XYQ> tmp_but : this->possCard_vect ){
        tmp_but->setTxtFont( this->mainFont );
    }
    this->mainCard->setTxtFont( this->mainFont );

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

void CRG_SFML_eng::update(){
    
    for( shared_ptr<SFML_button_XYQ> tmp_but : this->possCard_vect ){
        tmp_but->update();
    }

    this->mainCard->update();

}

void CRG_SFML_eng::reset(){
    
    cardReact::reset();

    mainCard->disableSprite();
    mainCard->disableText();

}

void CRG_SFML_eng::start(){

    cardReact::start();

    // Create a new thread that runs the runInThread function
    std::thread myThread( countDownThread, ref( *this ) );
    myThread.detach();

}

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

            bool selected = this->selectCard( z );

            if( selected ){
                cout << get_CRG_STATE_Str( this->state ) << endl;
            }else{
                cout << "Well." << endl;
            }

            break;

        }

    }

    return released;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions (Protected)
// ====================================================================== >>>>>

void CRG_SFML_eng::countDownThread( CRG_SFML_eng& tarObj ){

    std::this_thread::sleep_for( chrono::milliseconds( 2000 ) );
    cout << "Second thread run ends." << endl;
    // tarGame.mainCard->enableText();
    // tarGame.mainCard->enableSprite();

}

// ====================================================================== <<<<<