#include "CRG_SFML_eng.h"



using namespace gameEngine;


const sf::Color CRG_SFML_eng::upColorBef = sf::Color( 0, 150, 0, 255 );
const sf::Color CRG_SFML_eng::pColorBef = sf::Color( 0, 80, 0, 255 );
const sf::Color CRG_SFML_eng::upColorAft = sf::Color( 200, 0, 0, 255 );
const sf::Color CRG_SFML_eng::pColorAft = sf::Color( 120, 0, 0, 255 );

const sf::Color CRG_SFML_eng::noCardTxtColor = sf::Color( 255, 255, 255, 255 );



// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

CRG_SFML_eng::CRG_SFML_eng( int possCardCnt, long long cntDownT ) : 
    cardReact( possCardCnt, cntDownT )
{

    // Set the main card color.
    mainCardColor = sf::Color( 138, 43, 226, 255 );

    // Initialize the main card.
    this->mainCard = shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

    // Field of cards properties.
    this->field_pos.x = 250;
    this->field_pos.y = 50;
    this->field_card_dim.x = 140;
    this->field_card_dim.y = 120;
    this->field_card_sep = 5;
    // Initialize a set of cards and a vector holding index reordering of the field cards.
    for( int i = 0; i < possCardCnt; i++ ){
        shared_ptr<SFML_button_XYQ> buttonX = 
            shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

        possCard_vect.push_back( buttonX );
        rdOrdIdx_Vect.push_back(i);
    }
    
    // Insert a set of dummy textures.
    for( int i = 0; i < possCardCnt; i++ ){
        possCardTex_vect.push_back( shared_ptr<sf::Texture>( new sf::Texture() ) );
    }

    // Perform the first reset, which effectively acts as an initialization to variables
    // which participate in resets.
    this->reset();

}


CRG_SFML_eng::CRG_SFML_eng( vector<shared_ptr<SFML_button_XYQ>> possCard_vect, 
    long long cntDownT ) : cardReact( possCard_vect.size(), cntDownT )
{

    // Set the main card color.
    mainCardColor = sf::Color( 138, 43, 226, 255 );

    // Use the given card pointer vector.
    this->possCard_vect = possCard_vect;

    // Initialize the main card.
    this->mainCard = shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    
    // Field of cards properties.
    this->field_pos.x = 250;
    this->field_pos.y = 50;
    this->field_card_dim.x = 140;
    this->field_card_dim.y = 120;
    this->field_card_sep = 5;
    // Initialize vector holding index reordering of the field cards.
    for( unsigned int i = 0; i < this->possCardCnt; i++ ){
        rdOrdIdx_Vect.push_back(i);
    }

    // Insert a set of dummy textures.
    for( unsigned int i = 0; i < possCardCnt; i++ ){
        possCardTex_vect.push_back( shared_ptr<sf::Texture>( new sf::Texture() ) );
    }

    // Perform the first reset, which effectively acts as an initialization to variables
    // which participate in resets.
    this->reset();

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

void CRG_SFML_eng::setPossCardTex_vect( vector<shared_ptr<sf::Texture>> possCardTex_vect ){
    this->possCardTex_vect = possCardTex_vect;
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

void CRG_SFML_eng::update(){
    
    for( shared_ptr<SFML_button_XYQ> buttonX : this->possCard_vect ){
        buttonX->update();
    }

    this->mainCard->update();

}

void CRG_SFML_eng::reset(){
    
    this->cardReact::reset();    

    // Reset the card colors to before being pressed.
    this->upColor = upColorBef;
    this->pColor = pColorBef;
    
    // Update the main card.
    this->upd_mainCard();
    // Disable text and spirte to hide the card's new identity.
    mainCard->disableText();
    mainCard->disableSprite();

    // Update the field cards.
    this->upd_fieldCards(true);

    // Update all SFML elements.
    this->update();

}

void CRG_SFML_eng::upd_mainCard(){

    // Initialize the main card.
    // mainCard->setPos( field_pos.x - 150, field_pos.y );
    mainCard->setPos( 50, field_pos.y );

    mainCard->setWidth( field_card_dim.x );      
    mainCard->setHeight( field_card_dim.y );
    mainCard->setUPColor( mainCardColor );
    mainCard->setPColor( mainCardColor );
    mainCard->setTxtStr( to_string( mainCardID ) );
    mainCard->setTxtColor( noCardTxtColor );

    if( mainCardID < possCardTex_vect.size() && 
        mainCard->setUPTexture( possCardTex_vect.at( mainCardID ) ) ){

        mainCard->setPTexture( possCardTex_vect.at( mainCardID ) );
        mainCard->enableSprite();
        mainCard->disableText();

    }else{
        mainCard->disableSprite();
        mainCard->enableText();
    }

}

void CRG_SFML_eng::upd_fieldCards( bool shuffle = false ){

    
    // Shuffle the vector is required.
    if( shuffle ){
        // Shuffle this index vector.
        shuffleVector( rdOrdIdx_Vect );
    }

    // Determine the number of rows and columns of cards depending on how many cards there
    // are in total.
    float tmp = std::sqrt( (float) possCardCnt );
    rowColCnt.x = (int) std::ceil( ( (float) possCardCnt )/tmp );
    rowColCnt.y = (int) std::ceil( tmp );

    // Card index variable.
    unsigned int z = 0;

    // Standard distribution of buttons into a rectangular formation (as close to square as possible).
    for( unsigned int i = 0; ( i < rowColCnt.x && z < possCardCnt ); i++ ){
        for( unsigned int j = 0; ( j < rowColCnt.y && z < possCardCnt ); j++ ){

            unsigned int orig_idx = rdOrdIdx_Vect.at(z);
            shared_ptr<SFML_button_XYQ> buttonX = this->possCard_vect.at( orig_idx );

            buttonX->setPos( field_pos.x + ( field_card_dim.x + field_card_sep )*j, 
                field_pos.y + ( field_card_dim.y + field_card_sep )*i );
            
            buttonX->setWidth( field_card_dim.x );      
            buttonX->setHeight( field_card_dim.y );
            buttonX->setUPColor( upColor );
            buttonX->setPColor( pColor );

            buttonX->setTxtFont( mainFont );
            buttonX->setTxtStr( to_string( orig_idx ) );
            buttonX->setTxtColor( noCardTxtColor );

            if( orig_idx < possCardCnt ){
                if( orig_idx < possCardTex_vect.size() && 
                    buttonX->setUPTexture( possCardTex_vect.at(orig_idx) ) ){
                    buttonX->setPTexture( possCardTex_vect.at(orig_idx) );

                    buttonX->enableSprite();
                    buttonX->disableText();
                }else{
                    buttonX->disableSprite();
                    buttonX->enableText();
                }
            }else{
                buttonX->disableSprite();
                buttonX->enableText();
            }

            z++;

        }
    }

}


void CRG_SFML_eng::start(){
    
    // Prevent the game from starting if it is not ready.
    if( this->state != CRG_STATE::UNSTARTED ){
        return;
    }

    // Set the game state to
    // cardReact::start();
    this->state = CRG_STATE::COUNTDOWN;

    startTimePt = chrono::high_resolution_clock::now();
    cardPickTimePt = startTimePt;

    // Create a new thread that runs the runInThread function
    std::thread myThread( countDownThread, ref( *this ) );
    myThread.detach();

}

bool CRG_SFML_eng::pressButton( const sf::RenderWindow& window ){

    bool success = false;

    for( unsigned int z = 0; z < possCardCnt; z++ ){

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

    for( unsigned int z = 0; z < possCardCnt; z++ ){

        // Get the current button.
        shared_ptr<SFML_button_XYQ> buttonX = this->possCard_vect.at(z);

        released = buttonX->releaseButton();

        // If current button is the one being released.
        if( released ){

            cout << "Button released: " << to_string(z) << endl;

            bool selected = this->selectCard( z );

            if( selected ){

                this->upColor = upColorAft;
                this->pColor = pColorAft;
                this->upd_fieldCards( false );
                this->update();
                cout << "Reaction time (ms): " << this->getPickCardMS() << endl;

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

    std::this_thread::sleep_for( chrono::milliseconds( tarObj.cntDownT ) );
    tarObj.cntDownEndTimePt = chrono::high_resolution_clock::now();
    tarObj.state = CRG_STATE::ONGOING;

    if( tarObj.mainCard->hasUPTexture() && tarObj.mainCard->hasPTexture() ){
        tarObj.mainCard->enableSprite();
    }else{
        tarObj.mainCard->enableText();
    }

}

// ====================================================================== <<<<<