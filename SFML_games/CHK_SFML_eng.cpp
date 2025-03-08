#include "CHK_SFML_eng.h"


using namespace gameEngine;


const sf::Color CHK_SFML_eng::LTILECOLOR = sf::Color( 255, 255, 255, 255 );
const sf::Color CHK_SFML_eng::DTILECOLOR = sf::Color( 155, 155, 155, 255 );
const sf::Color CHK_SFML_eng::PTILECOLOR = sf::Color( 0, 255, 255, 255 );
const sf::Color CHK_SFML_eng::LOCKTILECOLOR = sf::Color( 255, 255, 0, 255 );



CHK_SFML_eng::CHK_SFML_eng() : checkers()
{

    act_set_lock = false;


    CHKText_red = shared_ptr<sf::Texture>( new sf::Texture() );
    CHKText_blk = shared_ptr<sf::Texture>( new sf::Texture() );
    CHKText_cred = shared_ptr<sf::Texture>( new sf::Texture() );
    CHKText_cblk = shared_ptr<sf::Texture>( new sf::Texture() );

    // Define the default locations and sizes of the buttons.
    float x_start = 100;        float y_start = 100;
    float butWidth = 50;       float butHeight = 50;
    float butSep = 5;

    for( unsigned int i = 0; i < BOARDWIDTH; i++ ){
        for( unsigned int j = 0; j < BOARDHEIGHT; j++ ){

            shared_ptr<SFML_button_XYQ> buttonX = 
                shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

            buttonX->setPos( x_start + ( butWidth + butSep )*i, 
                y_start + ( butHeight + butSep )*j );
            buttonX->setWidth( butWidth );      
            buttonX->setHeight( butHeight );    
            if( remainder(i+j,2) ){
                buttonX->setUPColor( LTILECOLOR );  
                buttonX->setPColor( PTILECOLOR );  
            }else{
                buttonX->setUPColor( DTILECOLOR );  
                buttonX->setPColor( PTILECOLOR );  
            } 
            buttonX->setTxtStr( "" );
            buttonX->setTxtColor( 255, 0, 0, 255 );
            buttonX->disableSprite();

            CHK_buttons.push_back( buttonX );

        }
    }

}



CHK_SFML_eng::CHK_SFML_eng( vector<shared_ptr<SFML_button_XYQ>> CHK_buttons ) : checkers()
{
    act_set_lock = false;
    this->CHK_buttons = CHK_buttons;
}



bool CHK_SFML_eng::pressButton( const sf::RenderWindow& window ){

    bool success = false;

    for( unsigned int i = 0; i < BOARDWIDTH; i++ ){
        for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
            shared_ptr<SFML_button_XYQ> buttonX = this->get_button_at_ij( i, j );

            success = buttonX->pressButton( window );

            if( success ){

                if( act_set_lock ){
                    
                }else{
                    act_set_lock_coords = sf::Vector2i( i, j );
                }

                break;
            }

        }

        if( success ){
            break;
        }
    }



    return success;

}


bool CHK_SFML_eng::releaseButton(){

    bool released = false;
    for( unsigned int i = 0; i < BOARDWIDTH; i++ ){
        for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
            shared_ptr<SFML_button_XYQ> buttonX = this->get_button_at_ij( i, j );

            released = buttonX->releaseButton();
            if( released ){
                
                if( act_set_lock ){
                    
                    // Reset the tile color of the locked coordinate.
                    if( remainder( act_set_lock_coords.x + act_set_lock_coords.y, 2 ) ){
                        act_set_lock_but->setUPColor( LTILECOLOR );
                    }else{
                        act_set_lock_but->setUPColor( DTILECOLOR );
                    }
                    act_set_lock_but->update();

                    // Reset the lock.
                    act_set_lock = false;

                    // Obtain the coordinate of the current button pressed.
                    sf::Vector2i curr_ij = sf::Vector2i( i, j );
                    // Compute the vector from the initial lock position to the currently clicked position.
                    sf::Vector2i ij_diff = sf::Vector2i( curr_ij.x - act_set_lock_coords.x, 
                        curr_ij.y - act_set_lock_coords.y );
                    

                    checkers::CHK_DIREC vect_direct;
                    if( ij_diff.x == 1 && ij_diff.y == -1 ){
                        vect_direct = CHK_DIREC::DOWNLEFT;
                    }else if( ij_diff.x == 1 && ij_diff.y == 1 ){
                        vect_direct = CHK_DIREC::DOWNRIGHT;
                    }else if( ij_diff.x == -1 && ij_diff.y == -1 ){
                        vect_direct = CHK_DIREC::UPLEFT;
                    }else if( ij_diff.x == -1 && ij_diff.y == 1 ){
                        vect_direct = CHK_DIREC::UPRIGHT;
                    }else{
                        vect_direct = CHK_DIREC::NO_D;
                    }

                    // cout << this->get_CHK_DIREC_Str( vect_direct ) << endl;
                    this->play( act_set_lock_coords.x, act_set_lock_coords.y, vect_direct );
                    this->updateCHKBoard();

                }else{
                    act_set_lock_but = buttonX;
                    act_set_lock_but->setUPColor( LOCKTILECOLOR );
                    act_set_lock_but->update();

                    act_set_lock = true;
                }

                break;
            }
        }

        if(released){
            break;
        }
    }
    
    return released;

}


void CHK_SFML_eng::updateCHKBoard(){

    for( unsigned int i = 0; i < BOARDWIDTH; i++ ){
        for( unsigned int j = 0; j < BOARDHEIGHT; j++ ){

            shared_ptr<SFML_button_XYQ> but_ij = get_button_at_ij( i, j );

            switch( CHK_board[i][j] ){

                case CHK_PIECE::NO_P:
                    but_ij->disableSprite();
                    but_ij->setTxtStr( "" );
                    but_ij->disableText();
                    break;

                case CHK_PIECE::RED_P:
                    if( !CHKText_red ){
                        but_ij->setTxtStr( "X" );
                        but_ij->setTxtColor( sf::Color::Red );
                        but_ij->enableText();
                        but_ij->disableSprite();
                    }else{
                        but_ij->setUPTexture( CHKText_red );
                        but_ij->setPTexture( CHKText_red );
                        but_ij->disableText();
                        but_ij->enableSprite();
                    }
                    break;

                case CHK_PIECE::BLK_P:
                    if( !CHKText_blk ){
                        but_ij->setTxtStr( "X" );
                        but_ij->setTxtColor( sf::Color::Black );
                        but_ij->enableText();
                        but_ij->disableSprite();
                    }else{
                        but_ij->setUPTexture( CHKText_blk );
                        but_ij->setPTexture( CHKText_blk );
                        but_ij->disableText();
                        but_ij->enableSprite();
                    }
                    break;

                case CHK_PIECE::CRED_P:
                    if( !CHKText_cred ){
                        but_ij->setTxtStr( "C" );
                        but_ij->setTxtColor( sf::Color::Red );
                        but_ij->enableText();
                        but_ij->disableSprite();
                    }else{
                        but_ij->setUPTexture( CHKText_cred );
                        but_ij->setPTexture( CHKText_cred );
                        but_ij->disableText();
                        but_ij->enableSprite();
                    }
                    break;

                case CHK_PIECE::CBLK_P:
                    if( !CHKText_cred ){
                        but_ij->setTxtStr( "C" );
                        but_ij->setTxtColor( sf::Color::Black );
                        but_ij->enableText();
                        but_ij->disableSprite();
                    }else{
                        but_ij->setUPTexture( CHKText_cblk );
                        but_ij->setPTexture( CHKText_cblk );
                        but_ij->disableText();
                        but_ij->enableSprite();
                    }
                    break;

                default:
                    cerr << "Unrecognized CHK_PIECE enum. Abort" << endl;
                    return;

            }

            but_ij->update();

        }
    }

    return;

}



void CHK_SFML_eng::resetBoard(){

    checkers::resetBoard();

    this->updateCHKBoard();

}


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

bool CHK_SFML_eng::setCHK_pieceText( CHK_PIECE tarPiece, shared_ptr<sf::Texture> inText ){

    switch( tarPiece ){
        case CHK_PIECE::RED_P:
            CHKText_red = inText;
            break;
        case CHK_PIECE::BLK_P:
            CHKText_blk = inText;
            break;
        case CHK_PIECE::CRED_P:
            CHKText_cred = inText;
            break;
        case CHK_PIECE::CBLK_P:
            CHKText_cblk = inText;
            break;
        case CHK_PIECE::NO_P:
            return false;
        default:
            cerr << "Unknown checker piece enum. Abort." << endl;
            return false;
    }

    this->updateCHKBoard();
    return true;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions (Protected)
// ====================================================================== >>>>>

shared_ptr<SFML_button_XYQ> CHK_SFML_eng::get_button_at_ij(unsigned int i, unsigned int j) const{

    return CHK_buttons.at( i + j*BOARDWIDTH );

}


void CHK_SFML_eng::set_button_at_ij( unsigned int i, unsigned int j, shared_ptr<SFML_button_XYQ> inBut ){

    CHK_buttons.at( i + j*BOARDWIDTH ) = inBut;

}

// ====================================================================== <<<<<







void game::play_Checkers(){

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string funny_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";
    string CHK_red_img_FFN = RES_PATH_XYQ_str + "/CHK_piece_red.png";
    string CHK_cred_img_FFN = RES_PATH_XYQ_str + "/CHK_piece_red_crown.png";
    string CHK_blk_img_FFN = RES_PATH_XYQ_str + "/CHK_piece_blk.png";
    string CHK_cblk_img_FFN = RES_PATH_XYQ_str + "/CHK_piece_blk_crown.png";

    shared_ptr<sf::Texture> button_img_np_texture = SFMLUtilsXYQ::genTexture( button_img_np_FFN );
    shared_ptr<sf::Texture> button_img_p_texture = SFMLUtilsXYQ::genTexture( button_img_p_FFN );
    shared_ptr<sf::Texture> funny_img_texture = SFMLUtilsXYQ::genTexture( funny_img_FFN );

    shared_ptr<sf::Texture> CHK_red_img_texture = SFMLUtilsXYQ::genTexture( CHK_red_img_FFN );
    shared_ptr<sf::Texture> CHK_cred_img_texture = SFMLUtilsXYQ::genTexture( CHK_cred_img_FFN );
    shared_ptr<sf::Texture> CHK_blk_img_texture = SFMLUtilsXYQ::genTexture( CHK_blk_img_FFN );
    shared_ptr<sf::Texture> CHK_cblk_img_texture = SFMLUtilsXYQ::genTexture( CHK_cblk_img_FFN );

    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );


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

    string infoBox2A_msg = "This is a checkers game software developped as coding practice. ";
    infoBox2A_msg += "Control is shared between both players. ";
    infoBox2A_msg += "There is no A.I. yet.";


    infoBox2A->setPos( 200, 100 );
    infoBox2A->imgBox.setHeight( 200 );
    infoBox2A->imgBox.setWidth( 200 );
    infoBox2A->imgBox.setTxtStr( "No Image" );
    // infoBox2A->imgBox.setUPTexture( funny_img_texture );
    infoBox2A->imgBox.setUPTexture( funny_img_texture );
    

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

    // Object: button for returning to the main page.
    shared_ptr<SFML_button_XYQ> but3A_mmenu = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3A_mmenu->setPos( 200, 500 );
    but3A_mmenu->setWidth( 150 );      
    but3A_mmenu->setHeight( 50 );      
    but3A_mmenu->setTxtFont( font );
    but3A_mmenu->setTxtStr( "Back" );
    but3A_mmenu->setTxtColor( 50, 50, 50, 255 );
    but3A_mmenu->setUPTexture( button_img_np_texture );
    but3A_mmenu->setPTexture( button_img_p_texture );
    // Add to page.
    page3_game.addObj( but3A_mmenu );

    // Object: button for resetting the game board.
    shared_ptr<SFML_button_XYQ> but3B_reset = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but3B_reset->setPos( 400, 500 );
    but3B_reset->setWidth( 150 );      
    but3B_reset->setHeight( 50 );      
    but3B_reset->setTxtFont( font );
    but3B_reset->setTxtStr( "Reset" );
    but3B_reset->setTxtColor( 50, 50, 50, 255 );
    but3B_reset->setUPTexture( button_img_np_texture );
    but3B_reset->setPTexture( button_img_p_texture );
    // Add to page.
    page3_game.addObj( but3B_reset );


    // Vector of all buttons participating in Tik-Tak-Tok.
    vector<shared_ptr<SFML_button_XYQ>> CHK_buttons;
    
    float x_start = 210;        float y_start = 50;
    float butWidth = 44;       float butHeight = 44;
    float butSep = 4;

    for( unsigned int i = 0; i < 8; i++ ){
        for( unsigned int j = 0; j < 8; j++ ){

            shared_ptr<SFML_button_XYQ> button3X = 
                shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
            
            button3X->setPos( x_start + ( butWidth + butSep )*i, 
                y_start + ( butHeight + butSep )*j );
            button3X->setWidth( butWidth );      
            button3X->setHeight( butHeight );    

            if( remainder(i+j,2) ){
                button3X->setUPColor( gameEngine::CHK_SFML_eng::LTILECOLOR );  
                button3X->setPColor( gameEngine::CHK_SFML_eng::PTILECOLOR );  
            }else{
                button3X->setUPColor( gameEngine::CHK_SFML_eng::DTILECOLOR );  
                button3X->setPColor( gameEngine::CHK_SFML_eng::PTILECOLOR );  
            }

            button3X->setTxtFont( font );
            button3X->setTxtStr( "" );
            button3X->setTxtColor( 255, 0, 0, 255 );
            button3X->disableSprite();
            button3X->setUpSprtScale( 0.84f, 0.84f );
            button3X->setPSprtScale( 0.5f, 0.5f );

            CHK_buttons.push_back( button3X );
            page3_game.addObj( button3X );

        }
    }



    // Create TTT game object.
    gameEngine::CHK_SFML_eng CHK_game_obj( CHK_buttons );

    CHK_game_obj.setCHK_pieceText( gameEngine::checkers::CHK_PIECE::RED_P, CHK_red_img_texture );
    CHK_game_obj.setCHK_pieceText( gameEngine::checkers::CHK_PIECE::BLK_P, CHK_blk_img_texture );
    CHK_game_obj.setCHK_pieceText( gameEngine::checkers::CHK_PIECE::CRED_P, CHK_cred_img_texture );
    CHK_game_obj.setCHK_pieceText( gameEngine::checkers::CHK_PIECE::CBLK_P, CHK_cblk_img_texture );

    CHK_game_obj.updateCHKBoard();

    page3_game.update();
    page3_game.disable();

    
// ---------------------------------------------------------------------- <<<<<

    // Create the main window.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Checkers");

    // Main loop.
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }


            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    if( but1A_startGame->pressButton( window ) ){}
                    if( but1B_readMe->pressButton( window ) ){}
                    if( but1C_exit->pressButton( window ) ){}

                    if( but2A_back->pressButton( window ) ){}

                    if( but3A_mmenu->pressButton( window ) ){}
                    if( but3B_reset->pressButton( window ) ){}

                    CHK_game_obj.pressButton( window );

                }
            }

             // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){

                    if( but1A_startGame->releaseButton() ){
                        page1_mmenu.disable();
                        page3_game.enable();
                        CHK_game_obj.resetBoard();
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


                    // Leave page and return to main menu.
                    if( but3A_mmenu->releaseButton() ){

                        CHK_game_obj.resetBoard();

                        page3_game.disable();
                        page1_mmenu.enable();
                        
                    }

                    // Reset TTT game.
                    if( but3B_reset->releaseButton() ){

                        CHK_game_obj.resetBoard();

                    }

                    bool gameButRel = CHK_game_obj.releaseButton();

                }
            }

        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the main menu page.
        page1_mmenu.beDrawn( window );
        // Draw the read me page.
        page2_readme.beDrawn( window );
        // Draw the game page.
        page3_game.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}