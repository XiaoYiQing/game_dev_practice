#include "TTT_wt_but_XYQ.h"


using namespace gameEngine;



// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

TTT_wt_but_XYQ::TTT_wt_but_XYQ() : TikTakTok()
{

    this->vsAI = true;
    this->AI_first = false;

    this->TTT_O_img_texture = shared_ptr<sf::Texture>( new sf::Texture() );
    this->TTT_X_img_texture = shared_ptr<sf::Texture>( new sf::Texture() );

    // Define the default locations and sizes of the buttons.
    float x_start = 100;        float y_start = 100;
    float butWidth = 100;       float butHeight = 100;
    float butSep = 5;

    for( unsigned int i = 0; i < 3; i++ ){
        for( unsigned int j = 0; j < 3; j++ ){

            shared_ptr<SFML_button_XYQ> buttonX = 
                shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

            buttonX->setPos( x_start + ( butWidth + butSep )*j, 
                y_start + ( butHeight + butSep )*i );
            buttonX->setWidth( butWidth );      
            buttonX->setHeight( butHeight );    
            buttonX->setUPColor( 255, 255, 255, 255 );  
            buttonX->setPColor( 255, 255, 255, 255 );  
            buttonX->setTxtStr( "" );
            buttonX->setTxtColor( 255, 0, 0, 255 );
            buttonX->disableSprite();

            TTT_buttons.push_back( buttonX );

        }
    }

}



TTT_wt_but_XYQ::TTT_wt_but_XYQ( vector<shared_ptr<SFML_button_XYQ>> TTT_buttons, 
    shared_ptr<sf::Texture> TTT_O_img_texture, 
    shared_ptr<sf::Texture> TTT_X_img_texture ) : TikTakTok()
{

    this->vsAI = true;
    this->AI_first = false;

    this->TTT_O_img_texture = TTT_O_img_texture;
    this->TTT_X_img_texture = TTT_X_img_texture;
    this->TTT_buttons = TTT_buttons;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Functionalities
// ====================================================================== >>>>>

bool TTT_wt_but_XYQ::pressButton( const sf::RenderWindow& window ){

    bool success = false;
    for( shared_ptr<SFML_button_XYQ> buttonX : TTT_buttons ){
        success = success || buttonX->pressButton( window );
    }
    return success;

}


bool TTT_wt_but_XYQ::releaseButton(){

    bool released = false;
    for( unsigned int i = 0; i < 3; i++ ){
        for( unsigned int j = 0; j < 3; j++ ){

            shared_ptr<SFML_button_XYQ> buttonX = TTT_buttons.at( (i)*3 + j );

            // Case when the present button is the one being released.
            released = buttonX->releaseButton();
            if( released ){
                if( buttonX->getPressCnt() < 2 ){
                    
                    // Set the button to show correct sprite.
                    unsigned int playRes = this->play( i, j );
                    if( playRes == 2 ){
                        buttonX->setUPTexture( TTT_X_img_texture );
                        buttonX->setPTexture( TTT_X_img_texture );
                    }else if( playRes == 1 ){
                        buttonX->setUPTexture( TTT_O_img_texture );
                        buttonX->setPTexture( TTT_O_img_texture );
                    }
                    buttonX->enableSprite();
                    buttonX->update();

                    // Update the state of the game.
                    this->updState();

                    /*
                    Check for game end scenario.
                    */
                    if( this->state != 0 ){
                        // When game is over, prevent the buttons from being pressed.
                        for( shared_ptr<SFML_button_XYQ> button_y : TTT_buttons ){
                            button_y->lock();
                        }
                    }else if( vsAI ){

                        AI_play();

                    }

                }

                // Immediately stop once first released button is found.
                return true;
            }

        }
    }
    
    return false;

}

sf::Vector2u TTT_wt_but_XYQ::AI_play(){

    // Return empty vector if no AI play enabled.
    if( !( this->vsAI ) ){
        return sf::Vector2u();
    }

    // Let AI perform the next move.
    sf::Vector2u AI_move = this->bestMove();
    unsigned int AIPlayRes = play( AI_move.x, AI_move.y );

    shared_ptr<SFML_button_XYQ> buttonY = TTT_buttons.at( AI_move.x*3 + AI_move.y );
    if( AIPlayRes == 2 ){
        buttonY->setUPTexture( TTT_X_img_texture );
        buttonY->setPTexture( TTT_X_img_texture );
    }else if( AIPlayRes == 1 ){
        buttonY->setUPTexture( TTT_O_img_texture );
        buttonY->setPTexture( TTT_O_img_texture );
    }
    buttonY->enableSprite();
    buttonY->update();

    // Update the state of the game.
    this->updState();

    // Check for game end scenario.
    if( this->state != 0 ){
        // When game is over, prevent the buttons from being pressed.
        for( shared_ptr<SFML_button_XYQ> button_y : TTT_buttons ){
            button_y->lock();
        }
    }

    return AI_move;

}

unsigned int TTT_wt_but_XYQ::getState() const{
    return this->TikTakTok::getState();
}

void TTT_wt_but_XYQ::reset() {

    this->TikTakTok::reset();

    for( shared_ptr<SFML_button_XYQ> buttonX : TTT_buttons ){
        // Reset the number of time a button is pressed.
        buttonX->setPressCnt(0);
        // Disable the sprite drawing.
        buttonX->disableSprite();
        buttonX->setTxtStr( "" );
        buttonX->unlock();
        buttonX->update();
    }

    if( this->vsAI && this->AI_first ){
        this->AI_play();
    }

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

void TTT_wt_but_XYQ::set_O_Texture( shared_ptr<sf::Texture> TTT_O_img_texture ){
    this->TTT_O_img_texture = TTT_O_img_texture;
}
void TTT_wt_but_XYQ::set_X_Texture( shared_ptr<sf::Texture> TTT_X_img_texture ){
    this->TTT_X_img_texture = TTT_X_img_texture;
}

// Return status of whether AI is enabled.
bool TTT_wt_but_XYQ::is_AI_enabled() const{
    return this->vsAI;
}
// Enable AI.
void TTT_wt_but_XYQ::enable_AI(){
    this->vsAI = true;
}
// Disable AI.
void TTT_wt_but_XYQ::disable_AI(){
    this->vsAI = false;
}
// Toggle AI usage flag.
void TTT_wt_but_XYQ::toggle_AI(){
    this->vsAI = !vsAI;
}

bool TTT_wt_but_XYQ::is_AI_first() const{
    return this->AI_first;
}
void TTT_wt_but_XYQ::set_AI_first(){
    this->AI_first = true;
}
void TTT_wt_but_XYQ::set_AI_not_first(){
    this->AI_first = false;
}
void TTT_wt_but_XYQ::toggle_AI_first(){
    this->AI_first = !AI_first;
}

// ====================================================================== <<<<<




void game::play_TikTakTok(){

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string funny_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";
    string TTT_X_img_FFN = RES_PATH_XYQ_str + "/TTT_X.png";
    string TTT_O_img_FFN = RES_PATH_XYQ_str + "/TTT_O.png";

    shared_ptr<sf::Texture> button_img_np_texture = SFMLUtilsXYQ::genTexture( button_img_np_FFN );
    shared_ptr<sf::Texture> button_img_p_texture = SFMLUtilsXYQ::genTexture( button_img_p_FFN );
    shared_ptr<sf::Texture> funny_img_texture = SFMLUtilsXYQ::genTexture( funny_img_FFN );
    shared_ptr<sf::Texture> TTT_X_img_texture = SFMLUtilsXYQ::genTexture( TTT_X_img_FFN );
    shared_ptr<sf::Texture> TTT_O_img_texture = SFMLUtilsXYQ::genTexture( TTT_O_img_FFN );

    

    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );

// ---------------------------------------------------------------------- >>>>>
//      Page 1 Main Menu
// ---------------------------------------------------------------------- >>>>>

    float p1_x_start = 300;
    float p1_y_start = 100;
    float p1_but_y_leap = 100;

    // Page initialization.
    SFML_page_XYQ myPage1 = SFML_page_XYQ();

    // Object: start game button.
    shared_ptr<SFML_button_XYQ> button1A = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button1A->setPos( p1_x_start, p1_y_start + 0*p1_but_y_leap );
    button1A->setWidth( 200 );
    button1A->setHeight( 50 );      
    button1A->setTxtFont( font );
    button1A->setTxtStr( "Start Game" );
    button1A->setTxtColor( 50, 50, 50, 255 );
    button1A->setUPTexture( button_img_np_texture );
    button1A->setPTexture( button_img_p_texture );
    myPage1.addObj( button1A );

    // Object: read me button.
    shared_ptr<SFML_button_XYQ> button1B = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button1B->setPos( p1_x_start, p1_y_start + 1*p1_but_y_leap );
    button1B->setWidth( 200 );      
    button1B->setHeight( 50 );      
    button1B->setTxtFont( font );
    button1B->setTxtStr( "READ ME" );
    button1B->setTxtColor( 50, 50, 50, 255 );
    button1B->setUPTexture( button_img_np_texture );
    button1B->setPTexture( button_img_p_texture );
    myPage1.addObj( button1B );


    // Object: Options button.
    shared_ptr<SFML_button_XYQ> button1D = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button1D->setPos( p1_x_start, p1_y_start + 2*p1_but_y_leap );
    button1D->setWidth( 200 );      
    button1D->setHeight( 50 );      
    button1D->setTxtFont( font );
    button1D->setTxtStr( "Options" );
    button1D->setTxtColor( 50, 50, 50, 255 );
    button1D->setUPTexture( button_img_np_texture );
    button1D->setPTexture( button_img_p_texture );
    myPage1.addObj( button1D );


    // Object: exit button.
    shared_ptr<SFML_button_XYQ> button1C = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button1C->setPos( p1_x_start, p1_y_start + 3*p1_but_y_leap );
    button1C->setWidth( 200 );      
    button1C->setHeight( 50 );      
    button1C->setTxtFont( font );
    button1C->setTxtStr( "Exit" );
    button1C->setTxtColor( 50, 50, 50, 255 );
    button1C->setUPTexture( button_img_np_texture );
    button1C->setPTexture( button_img_p_texture );
    myPage1.addObj( button1C );

    

    myPage1.update();
    myPage1.enable();
    
// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Page 2 Read Me
// ---------------------------------------------------------------------- >>>>>

    // Page initialization.
    SFML_page_XYQ myPage2 = SFML_page_XYQ();


    // Object: button.
    shared_ptr<SFML_button_XYQ> button2A = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button2A->setPos( 300, 500 );
    button2A->setWidth( 200 );      
    button2A->setHeight( 50 );      
    button2A->setTxtFont( font );
    button2A->setTxtStr( "Back" );
    button2A->setTxtColor( 50, 50, 50, 255 );
    button2A->setUPTexture( button_img_np_texture );
    button2A->setPTexture( button_img_p_texture );
    // Add to page.
    myPage2.addObj( button2A );

    
    shared_ptr<SFML_infoBox_XYQ> infoBox2A = 
        shared_ptr<SFML_infoBox_XYQ>( new SFML_infoBox_XYQ() );

    string infoBox2A_msg = "This is a practice tik-tac-toc game. ";
    infoBox2A_msg += "You can do versus AI or versus player mode. ";
    infoBox2A_msg += "In versus player mode, control is shared.";


    infoBox2A->setPos( 200, 100 );
    infoBox2A->imgBox.setHeight(170);
    infoBox2A->imgBox.setWidth(200);
    infoBox2A->imgBox.setTxtStr( "No Image" );
    // infoBox2A->imgBox.setUPTexture( funny_img_texture );
    infoBox2A->imgBox.setUPTexture( funny_img_texture );
    

    infoBox2A->txtBox.setTxtFont( font );
    infoBox2A->txtBox.txt.setCharacterSize( 20 );
    infoBox2A->txtBox.txt.setString( infoBox2A_msg );
    // Add to page.
    myPage2.addObj( infoBox2A );

    myPage2.update();
    myPage2.disable();

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Page 3 Game
// ---------------------------------------------------------------------- >>>>>
    
    // Page initialization.
    SFML_page_XYQ myPage3 = SFML_page_XYQ();

    // Object: button for returning to the main page.
    shared_ptr<SFML_button_XYQ> button3A = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button3A->setPos( 150, 500 );
    button3A->setWidth( 200 );      
    button3A->setHeight( 50 );      
    button3A->setTxtFont( font );
    button3A->setTxtStr( "Back" );
    button3A->setTxtColor( 50, 50, 50, 255 );
    button3A->setUPTexture( button_img_np_texture );
    button3A->setPTexture( button_img_p_texture );
    // Add to page.
    myPage3.addObj( button3A );

    // Object: button for resetting the game board.
    shared_ptr<SFML_button_XYQ> button3B = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button3B->setPos( 400, 500 );
    button3B->setWidth( 200 );      
    button3B->setHeight( 50 );      
    button3B->setTxtFont( font );
    button3B->setTxtStr( "Reset" );
    button3B->setTxtColor( 50, 50, 50, 255 );
    button3B->setUPTexture( button_img_np_texture );
    button3B->setPTexture( button_img_p_texture );
    // Add to page.
    myPage3.addObj( button3B );


    // Vector of all buttons participating in Tik-Tak-Tok.
    vector<shared_ptr<SFML_button_XYQ>> TTT_buttons;
    
    float x_start = 100;        float y_start = 100;
    float butWidth = 100;       float butHeight = 100;
    float butSep = 5;

    for( unsigned int i = 0; i < 3; i++ ){
        for( unsigned int j = 0; j < 3; j++ ){

            shared_ptr<SFML_button_XYQ> button3X = 
                shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
            
            button3X->setPos( x_start + ( butWidth + butSep )*j, 
                y_start + ( butHeight + butSep )*i );
            button3X->setWidth( butWidth );      
            button3X->setHeight( butHeight );    
            button3X->setUPColor( 255, 255, 255, 255 );  
            button3X->setPColor( 255, 255, 255, 255 );  
            button3X->setTxtFont( font );
            button3X->setTxtStr( "" );
            button3X->setTxtColor( 255, 0, 0, 255 );
            button3X->disableSprite();

            TTT_buttons.push_back( button3X );
            myPage3.addObj( button3X );

        }
    }
    // Create TTT game object.
    gameEngine::TTT_wt_but_XYQ TTT_game_obj(TTT_buttons,TTT_O_img_texture,TTT_X_img_texture);
    
    TTT_game_obj.enable_AI();

    // Game state display object.
    shared_ptr<SFML_TxtBox_XYQ> txtBox3A = 
        shared_ptr<SFML_TxtBox_XYQ>( new SFML_TxtBox_XYQ( font ) );
    txtBox3A->txt.setString( "Game: Ongoing." );
    txtBox3A->txt.setFillColor( sf::Color( 255, 255, 255 ) );
    txtBox3A->txt.setCharacterSize( 30 );
    txtBox3A->setBoxFillColor( sf::Color( 255, 127, 80 ) );
    txtBox3A->setBoxOutlineColor( sf::Color( 0, 255, 0 ) );
    txtBox3A->setPos( 500, 200 );
    myPage3.addObj( txtBox3A );

    myPage3.update();
    myPage3.disable();

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Page 4 Options
// ---------------------------------------------------------------------- >>>>>
    
    float p4_x_start = 300;
    float p4_y_start = 150;
    float p4_but_y_leap = 100;
    unsigned int but_cnt = 0;
    string enabledAI_str = "VS AI: enabled";
    string disabledAI_str = "VS AI: disabled";

    bool AI_first = false;
    string AI_first_str = "AI first";
    string AI_not_first_str = "Player first";

    // Page initialization.
    SFML_page_XYQ myPage4 = SFML_page_XYQ();

    // Object: button for enabling/disabling AI.
    shared_ptr<SFML_button_XYQ> button4B = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button4B->setPos( p4_x_start, p4_y_start + but_cnt*p4_but_y_leap );
    button4B->setWidth( 200 );      
    button4B->setHeight( 50 );      
    button4B->setTxtFont( font );
    if( TTT_game_obj.is_AI_enabled() ){
        button4B->setTxtStr( enabledAI_str );
    }else{
        button4B->setTxtStr( disabledAI_str );
    }
    button4B->setTxtColor( 50, 50, 50, 255 );
    button4B->setUPTexture( button_img_np_texture );
    button4B->setPTexture( button_img_p_texture );
    // Add to page.
    myPage4.addObj( button4B );
    // Button count increment.
    but_cnt++;

    // Object: button for enabling/disabling AI.
    shared_ptr<SFML_button_XYQ> button4C = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button4C->setPos( p4_x_start, p4_y_start + but_cnt*p4_but_y_leap );
    button4C->setWidth( 200 );      
    button4C->setHeight( 50 );      
    button4C->setTxtFont( font );
    if( AI_first ){
        button4C->setTxtStr( AI_first_str );
    }else{
        button4C->setTxtStr( AI_not_first_str );
    }
    button4C->setTxtColor( 50, 50, 50, 255 );
    button4C->setUPTexture( button_img_np_texture );
    button4C->setPTexture( button_img_p_texture );
    // Add to page.
    myPage4.addObj( button4C );
    // Button count increment.
    but_cnt++;

    // Object: button for returning to the main page.
    shared_ptr<SFML_button_XYQ> button4A = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    button4A->setPos( p4_x_start, p4_y_start + but_cnt*p4_but_y_leap );
    button4A->setWidth( 200 );      
    button4A->setHeight( 50 );      
    button4A->setTxtFont( font );
    button4A->setTxtStr( "Back" );
    button4A->setTxtColor( 50, 50, 50, 255 );
    button4A->setUPTexture( button_img_np_texture );
    button4A->setPTexture( button_img_p_texture );
    // Add to page.
    myPage4.addObj( button4A );
    // Button count increment.
    but_cnt++;
    
    

    myPage4.update();
    myPage4.disable();

// ---------------------------------------------------------------------- <<<<<


    // Create the main window.
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image Example");

    // Main loop.
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

// ---------------------------------------------------------------------- >>>>>
//      Mouse (Left) Click Event
// ---------------------------------------------------------------------- >>>>>

            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if( button1A->pressButton( window ) ){}
                    if( button1B->pressButton( window ) ){}
                    if( button1C->pressButton( window ) ){}
                    if( button1D->pressButton( window ) ){}

                    if( button2A->pressButton( window ) ){}

                    if( button3A->pressButton( window ) ){}
                    if( button3B->pressButton( window ) ){}
                    TTT_game_obj.pressButton( window );

                    if( button4A->pressButton( window ) ){}
                    if( button4B->pressButton( window ) ){}
                    if( button4C->pressButton( window ) ){};

                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    if( button1A->releaseButton() ){
                        myPage1.disable();
                        myPage3.enable();
                        TTT_game_obj.reset();
                    }
                    if( button1B->releaseButton() ){
                        myPage1.disable();
                        myPage2.enable();
                    }
                    if( button1C->releaseButton() ){
                        window.close();
                    }
                    if( button1D->releaseButton() ){
                        myPage1.disable();
                        myPage4.enable();
                    }

                    if( button2A->releaseButton() ){
                        myPage2.disable();
                        myPage1.enable();
                    }

                    // Leave page and return to main menu.
                    if( button3A->releaseButton() ){

                        txtBox3A->txt.setString( "Game: Ongoing." );
                        txtBox3A->update();
                        TTT_game_obj.reset();

                        myPage3.disable();
                        myPage1.enable();
                        
                    }
                    // Reset TTT game.
                    if( button3B->releaseButton() ){
                        
                        txtBox3A->txt.setString( "Game: Ongoing." );
                        txtBox3A->update();
                        TTT_game_obj.reset();

                    }

                    // TTT button release scenario.
                    bool released = TTT_game_obj.releaseButton();
                    if( released ){

                        // Change the infobox message depending on the state of the game.
                        switch( TTT_game_obj.getState() ){
                            case 0:
                                break;
                            case 1:
                                txtBox3A->txt.setString( "Game: O Won!" );
                                break;
                            case 2:
                                txtBox3A->txt.setString( "Game: X Won!" );
                                break;
                            case 3:
                                txtBox3A->txt.setString( "Game: Draw." );
                                break;
                        }
                    }

                    if( button4A->releaseButton() ){
                        myPage4.disable();
                        myPage1.enable();
                    }
                    if( button4B->releaseButton() ){
                        TTT_game_obj.toggle_AI();
                        if( TTT_game_obj.is_AI_enabled() ){
                            button4B->setTxtStr( enabledAI_str );
                        }else{
                            button4B->setTxtStr( disabledAI_str );
                        }
                        button4B->update();
                    }
                    if( button4C->releaseButton() ){
                        AI_first = !AI_first;
                        if( AI_first ){
                            button4C->setTxtStr( AI_first_str );
                            TTT_game_obj.set_AI_first();
                        }else{
                            button4C->setTxtStr( AI_not_first_str );
                            TTT_game_obj.set_AI_not_first();
                        }
                        button4C->update();
                    }

                }
            }
// ---------------------------------------------------------------------- <<<<<

        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the page.
        myPage1.beDrawn( window );
        // Draw the page.
        myPage2.beDrawn( window );
        // Draw the page.
        myPage3.beDrawn( window );
        // Draw the page.
        myPage4.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }
    
}