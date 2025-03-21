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
        mainCard->delUPTexture();
        mainCard->delPTexture();
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

            bool selected = this->selectCard( z );

            if( selected ){

                this->upColor = upColorAft;
                this->pColor = pColorAft;
                this->upd_fieldCards( false );
                this->update();

            }else{

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




void game::play_cardReact(){

    
// ---------------------------------------------------------------------- >>>>>
//      Variables Initialization
// ---------------------------------------------------------------------- >>>>>

    // Define the number of cards at play.
    int possCardCnt = 9;

    // Create full file names for accessing the textures for button images.
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string funny_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";
    vector<string> CRG_img_FFN_vec;
    int CRG_img_cnt = 9;
    for( int i = 0; i < CRG_img_cnt; i++ ){
        CRG_img_FFN_vec.push_back( RES_PATH_XYQ_str + "/CRG_img_" + to_string(i+1) + ".jpg" );
    }

    // Load the actual textures using their full file name addresses.
    shared_ptr<sf::Texture> button_img_np_texture = SFMLUtilsXYQ::genTexture( button_img_np_FFN );
    shared_ptr<sf::Texture> button_img_p_texture = SFMLUtilsXYQ::genTexture( button_img_p_FFN );
    shared_ptr<sf::Texture> funny_img_texture = SFMLUtilsXYQ::genTexture( funny_img_FFN );
    vector< shared_ptr< sf::Texture > > CRG_img_texture_vec;
    for( int i = 0; i < CRG_img_cnt; i++ ){
        shared_ptr<sf::Texture> tmp = SFMLUtilsXYQ::genTexture( CRG_img_FFN_vec.at(i) );
        CRG_img_texture_vec.push_back( tmp );
    }

    // Load the font for texts.
    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Main Menu Page Setup
// ---------------------------------------------------------------------- >>>>>

    // Page initialization.
    SFML_page_XYQ page1_mmenu = SFML_page_XYQ();

    // Object: start game button.
    shared_ptr<SFML_button_XYQ> but1A_startGame = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but1A_startGame->setPos( 300, 100 );
    but1A_startGame->setWidth( 200 );
    but1A_startGame->setHeight( 50 );      
    but1A_startGame->setTxtFont( font );
    but1A_startGame->setTxtStr( "Start Game" );
    but1A_startGame->setTxtColor( 50, 50, 50, 255 );
    but1A_startGame->setUPTexture( button_img_np_texture );
    but1A_startGame->setPTexture( button_img_p_texture );
    page1_mmenu.addObj( but1A_startGame );

    // Object: read me button.
    shared_ptr<SFML_button_XYQ> but1B_readMe = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but1B_readMe->setPos( 300, 200 );
    but1B_readMe->setWidth( 200 );      
    but1B_readMe->setHeight( 50 );      
    but1B_readMe->setTxtFont( font );
    but1B_readMe->setTxtStr( "READ ME" );
    but1B_readMe->setTxtColor( 50, 50, 50, 255 );
    but1B_readMe->setUPTexture( button_img_np_texture );
    but1B_readMe->setPTexture( button_img_p_texture );
    page1_mmenu.addObj( but1B_readMe );

    // Object: exit button.
    shared_ptr<SFML_button_XYQ> but1C_exit = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but1C_exit->setPos( 300, 300 );
    but1C_exit->setWidth( 200 );      
    but1C_exit->setHeight( 50 );      
    but1C_exit->setTxtFont( font );
    but1C_exit->setTxtStr( "Exit" );
    but1C_exit->setTxtColor( 50, 50, 50, 255 );
    but1C_exit->setUPTexture( button_img_np_texture );
    but1C_exit->setPTexture( button_img_p_texture );
    page1_mmenu.addObj( but1C_exit );

    page1_mmenu.update();
    page1_mmenu.enable();
    
// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Read Me Page Setup
// ---------------------------------------------------------------------- >>>>>

    // Page initialization.
    SFML_page_XYQ page2_readme = SFML_page_XYQ();


    // Object: button.
    shared_ptr<SFML_button_XYQ> but2A_back = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but2A_back->setPos( 300, 500 );
    but2A_back->setWidth( 200 );      
    but2A_back->setHeight( 50 );      
    but2A_back->setTxtFont( font );
    but2A_back->setTxtStr( "Back" );
    but2A_back->setTxtColor( 50, 50, 50, 255 );
    but2A_back->setUPTexture( button_img_np_texture );
    but2A_back->setPTexture( button_img_p_texture );
    // Add to page.
    page2_readme.addObj( but2A_back );

    
    shared_ptr<SFML_infoBox_XYQ> infoBox2A = 
        shared_ptr<SFML_infoBox_XYQ>( new SFML_infoBox_XYQ() );

    string infoBox2A_msg = "This is a card reaction game that I created for coding practice. ";
    infoBox2A_msg += "The goal is to select the matching card on the right field of possible cards as quickly as possible ";
    infoBox2A_msg += "once the hidden card is revealed.";


    infoBox2A->setPos( 150, 150 );
    infoBox2A->imgBox.setHeight( 200 );
    infoBox2A->imgBox.setWidth( 200 );
    infoBox2A->imgBox.setTxtStr( "No Image" );
    // infoBox2A->imgBox.setUPTexture( funny_img_texture );
    infoBox2A->imgBox.setUPTexture( funny_img_texture );
    

    infoBox2A->txtBox.setTxtLenLim( 250.0f );
    infoBox2A->txtBox.setTxtFont( font );
    infoBox2A->txtBox.txt.setCharacterSize( 20 );
    infoBox2A->txtBox.txt.setString( infoBox2A_msg );
    // Add to page.
    page2_readme.addObj( infoBox2A );

    page2_readme.update();
    page2_readme.disable();

// ---------------------------------------------------------------------- <<<<<


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
    but3A_start->setPos( 100, 500 );
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
    but3B_reset->setPos( 275, 500 );
    but3B_reset->setWidth( 150 );      
    but3B_reset->setHeight( 50 );      
    but3B_reset->setTxtFont( font );
    but3B_reset->setTxtStr( "Reset" );
    but3B_reset->setTxtColor( 50, 50, 50, 255 );
    but3B_reset->setUPTexture( button_img_np_texture );
    but3B_reset->setPTexture( button_img_p_texture );
    // Add to page.
    page3_game.addObj( but3B_reset );


    // Object: button for returning to the main page.
    shared_ptr<SFML_button_XYQ> but3A_mmenu = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3A_mmenu->setPos( 500, 500 );
    but3A_mmenu->setWidth( 150 );      
    but3A_mmenu->setHeight( 50 );      
    but3A_mmenu->setTxtFont( font );
    but3A_mmenu->setTxtStr( "Back" );
    but3A_mmenu->setTxtColor( 50, 50, 50, 255 );
    but3A_mmenu->setUPTexture( button_img_np_texture );
    but3A_mmenu->setPTexture( button_img_p_texture );
    // Add to page.
    page3_game.addObj( but3A_mmenu );


    // Object: button for displaying time elapsed as well as count down time.
    shared_ptr<SFML_button_XYQ> but3C_timeDisplay = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3C_timeDisplay->setPos( 50, 200 );
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


    // Object: button for displaying the current state of the game.
    shared_ptr<SFML_button_XYQ> but3D_stateDisplay = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3D_stateDisplay->setPos( 50, 275 );
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

    // Object: button for displaying the true card pick time.
    shared_ptr<SFML_button_XYQ> but3E_truePickTimeDisplay = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3E_truePickTimeDisplay->setPos( 50, 350 );
    but3E_truePickTimeDisplay->setWidth( 150 );      
    but3E_truePickTimeDisplay->setHeight( 50 );      
    but3E_truePickTimeDisplay->setTxtFont( font );
    but3E_truePickTimeDisplay->setTxtSize( 20 );
    but3E_truePickTimeDisplay->setTxtStr( "" );
    but3E_truePickTimeDisplay->setTxtColor( 255, 255, 255, 255 );
    but3E_truePickTimeDisplay->setUPColor( 0, 0, 255 );
    but3E_truePickTimeDisplay->setPColor( 0, 0, 255 );
    but3E_truePickTimeDisplay->disableSprite();
    // Add to page.
    page3_game.addObj( but3E_truePickTimeDisplay );


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
    page3_game.disable();

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
                
                if( but1A_startGame->pressButton( window ) ){}
                if( but1B_readMe->pressButton( window ) ){}
                if( but1C_exit->pressButton( window ) ){}

                if( but2A_back->pressButton( window ) ){}

                // Game start button press event.
                if( but3A_start->pressButton( window ) ){};
                // Game reset button press event.
                if( but3B_reset->pressButton( window ) ){};
                // Return to main menu button.
                if( but3A_mmenu->pressButton( window ) ){};
                // Game buttons press check.
                if( CRG_SFML_obj.pressButton( window ) ){};

            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){

                if( but1A_startGame->releaseButton() ){
                    page1_mmenu.disable();
                    page3_game.enable();
                    CRG_SFML_obj.reset();
                }
                if( but1B_readMe->releaseButton() ){
                    page1_mmenu.disable();
                    page2_readme.enable();
                }
                if( but1C_exit->releaseButton() ){
                    window.close();
                }

                if( but2A_back->releaseButton() ){
                    page2_readme.disable();
                    page1_mmenu.enable();
                }

                if( but3A_start->releaseButton() ){
                    CRG_SFML_obj.start();
                }
                if( but3B_reset->releaseButton() ){
                    CRG_SFML_obj.reset();
                }
                // Leave page and return to main menu.
                if( but3A_mmenu->releaseButton() ){

                    CRG_SFML_obj.reset();

                    page3_game.disable();
                    page1_mmenu.enable();
                    
                }
                bool gameButRel = CRG_SFML_obj.releaseButton();

            }
            
        }

        string trueCardPickTimeStr = "------";

        currCRGState = CRG_SFML_obj.getState();
        switch( currCRGState ){
        case cardReact::CRG_STATE::UNSTARTED:
            but3C_timeDisplay->setTxtColor( 255, 255, 255, 255 );
            but3C_timeDisplay->setTxtStr( to_string( -CRG_SFML_obj.getCountDownMS() ) + "ms" );
            break;
        case cardReact::CRG_STATE::COUNTDOWN:
        case cardReact::CRG_STATE::ONGOING:
            but3C_timeDisplay->setTxtStr( to_string( CRG_SFML_obj.getElapsedMS() - 
                CRG_SFML_obj.getCountDownMS() ) + "ms" );
            break;
        case cardReact::CRG_STATE::HIT:
            but3C_timeDisplay->setTxtColor( 0, 255, 0 );
            trueCardPickTimeStr = to_string( CRG_SFML_obj.getPickCardMS() ) + "ms" ;
            break;
        case cardReact::CRG_STATE::MISS:
            but3C_timeDisplay->setTxtColor( 255, 0, 0 );
            trueCardPickTimeStr = to_string( CRG_SFML_obj.getPickCardMS() ) + "ms" ;
            break;
        }
        but3C_timeDisplay->update();
        // Update the game state.
        but3D_stateDisplay->setTxtStr( cardReact::get_CRG_STATE_Str( currCRGState ) );
        but3D_stateDisplay->update();

        but3E_truePickTimeDisplay->setTxtStr( trueCardPickTimeStr );
        but3E_truePickTimeDisplay->update();


        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the pages.
        page1_mmenu.beDrawn( window );
        page2_readme.beDrawn( window );
        page3_game.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}

