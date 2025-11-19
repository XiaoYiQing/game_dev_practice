#include "CHS_SFML_eng.h"

using namespace gameEngine;



void game::play_chess(){

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string funny_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";

    // Textures file full name for the white pieces.
    map< chess::CHS_PIECE_TYPE, string > CHS_PCE_W_tex_FFN_map;
    // Textures file full name for the black pieces.
    map< chess::CHS_PIECE_TYPE, string > CHS_PCE_B_tex_FFN_map;

    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::PAWN ] = 
        RES_PATH_XYQ_str + "/CHS_w_pawn.png";
    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::KNIGHT ] = 
        RES_PATH_XYQ_str + "/CHS_w_knight.png";
    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::BISHOP ] = 
        RES_PATH_XYQ_str + "/CHS_w_bishop.png";
    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::ROOK ] = 
        RES_PATH_XYQ_str + "/CHS_w_rook.png";
    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::QUEEN ] = 
        RES_PATH_XYQ_str + "/CHS_w_queen.png";
    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::KING ] = 
        RES_PATH_XYQ_str + "/CHS_w_king.png";

    CHS_PCE_B_tex_FFN_map[ chess::CHS_PIECE_TYPE::PAWN ] = 
        RES_PATH_XYQ_str + "/CHS_b_pawn.png";
    CHS_PCE_B_tex_FFN_map[ chess::CHS_PIECE_TYPE::KNIGHT ] = 
        RES_PATH_XYQ_str + "/CHS_b_knight.png";
    CHS_PCE_B_tex_FFN_map[ chess::CHS_PIECE_TYPE::BISHOP ] = 
        RES_PATH_XYQ_str + "/CHS_b_bishop.png";
    CHS_PCE_B_tex_FFN_map[ chess::CHS_PIECE_TYPE::ROOK ] = 
        RES_PATH_XYQ_str + "/CHS_b_rook.png";
    CHS_PCE_B_tex_FFN_map[ chess::CHS_PIECE_TYPE::QUEEN ] = 
        RES_PATH_XYQ_str + "/CHS_b_queen.png";
    CHS_PCE_B_tex_FFN_map[ chess::CHS_PIECE_TYPE::KING ] = 
        RES_PATH_XYQ_str + "/CHS_b_king.png";
    

    shared_ptr<sf::Texture> button_img_np_texture = SFMLUtilsXYQ::genTexture( button_img_np_FFN );
    shared_ptr<sf::Texture> button_img_p_texture = SFMLUtilsXYQ::genTexture( button_img_p_FFN );
    shared_ptr<sf::Texture> funny_img_texture = SFMLUtilsXYQ::genTexture( funny_img_FFN );

    // shared_ptr<sf::Texture> CHK_red_img_texture = SFMLUtilsXYQ::genTexture( CHK_red_img_FFN );
    
    // White piece textures.
    map< chess::CHS_PIECE_TYPE, shared_ptr<sf::Texture> > CHS_PCE_W_tex_map;
    // Black piece textures.
    map< chess::CHS_PIECE_TYPE, shared_ptr<sf::Texture> > CHS_PCE_B_tex_map;
    // Obtain the white piece textures from specific file locations.
    for (const pair< chess::CHS_PIECE_TYPE, string >& pair_z : CHS_PCE_W_tex_FFN_map) 
        { CHS_PCE_W_tex_map[ pair_z.first ] = SFMLUtilsXYQ::genTexture( pair_z.second ); }
    // Obtain the black piece textures from specific file locations.
    for (const pair< chess::CHS_PIECE_TYPE, string >& pair_z : CHS_PCE_B_tex_FFN_map) 
        { CHS_PCE_B_tex_map[ pair_z.first ] = SFMLUtilsXYQ::genTexture( pair_z.second ); }

    // Obtain the font used for the game's texts.
    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );


// ---------------------------------------------------------------------- >>>>>
//      Page 1 Main Menu
// ---------------------------------------------------------------------- >>>>>

    float p1_x_start = 300;
    float p1_y_start = 100;
    float p1_but_y_leap = 100;
    int but_cnt = 0;

    // Page initialization.
    SFML_page_XYQ page1_mmenu = SFML_page_XYQ();

    // Object: start game button.
    shared_ptr<SFML_button_XYQ> but1A_startGame = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but1A_startGame->setPos( p1_x_start, p1_y_start + but_cnt*p1_but_y_leap );
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
    but_cnt++;
    but1B_readMe->setPos( p1_x_start, p1_y_start + but_cnt*p1_but_y_leap );
    but1B_readMe->setWidth( 200 );      
    but1B_readMe->setHeight( 50 );      
    but1B_readMe->setTxtFont( font );
    but1B_readMe->setTxtStr( "READ ME" );
    but1B_readMe->setTxtColor( 50, 50, 50, 255 );
    but1B_readMe->setUPTexture( button_img_np_texture );
    but1B_readMe->setPTexture( button_img_p_texture );
    page1_mmenu.addObj( but1B_readMe );

    // Object: Options button.
    but_cnt++;
    shared_ptr<SFML_button_XYQ> but1D_opt = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but1D_opt->setPos( p1_x_start, p1_y_start + 2*p1_but_y_leap );
    but1D_opt->setWidth( 200 );      
    but1D_opt->setHeight( 50 );      
    but1D_opt->setTxtFont( font );
    but1D_opt->setTxtStr( "Options" );
    but1D_opt->setTxtColor( 50, 50, 50, 255 );
    but1D_opt->setUPTexture( button_img_np_texture );
    but1D_opt->setPTexture( button_img_p_texture );
    page1_mmenu.addObj( but1D_opt );

    // Object: exit button.
    shared_ptr<SFML_button_XYQ> but1C_exit = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but_cnt++;
    but1C_exit->setPos( p1_x_start, p1_y_start + but_cnt*p1_but_y_leap );
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
//      Page 2 Read Me
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

    string infoBox2A_msg = "This is a chess game software developped as coding practice. ";
    infoBox2A_msg += "Control is shared between both players. ";
    infoBox2A_msg += "Play versus A.I. can be enabled/disabled in the option menu.";


    infoBox2A->setPos( 200, 100 );
    infoBox2A->imgBox.setHeight( 200 );
    infoBox2A->imgBox.setWidth( 200 );
    infoBox2A->imgBox.setTxtStr( "No Image" );
    infoBox2A->imgBox.setUPTexture( funny_img_texture );
    

    infoBox2A->txtBox.setTxtFont( font );
    infoBox2A->txtBox.txt.setCharacterSize( 20 );
    infoBox2A->txtBox.txt.setString( infoBox2A_msg );
    page2_readme.addObj( infoBox2A );

    page2_readme.update();
    page2_readme.disable();

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Page 3 Game
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

    // Vector of all buttons participating in the chess game.
    vector<shared_ptr<SFML_button_XYQ>> CHS_buttons;

    float x_start = 210;        float y_start = 50;
    float butWidth = 44;       float butHeight = 44;
    float butSep = 4;

    for( int i = 7; i >= 0; i-- ){
    for( int j = 0; j < 8; j++ ){

        shared_ptr<SFML_button_XYQ> button3X = 
            shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

        button3X->setPos( x_start + ( butWidth + butSep )*j,
            y_start + ( butHeight + butSep )*i );
        button3X->setWidth( butHeight );
        button3X->setHeight( butWidth );

        if( remainder(i+j,2) ){
            button3X->setUPColor( CHS_SFML_eng::DTILECOLOR );  
            button3X->setPColor( CHS_SFML_eng::PTILECOLOR );  
        }else{
            button3X->setUPColor( CHS_SFML_eng::LTILECOLOR );  
            button3X->setPColor( CHS_SFML_eng::PTILECOLOR );  
        }

        button3X->setTxtFont( font );
        button3X->setTxtStr( "" );
        button3X->setTxtColor( 255, 0, 0, 255 );
        button3X->disableSprite();
        button3X->setUpSprtScale( 0.6f, 0.9f );
        button3X->setPSprtScale( 0.5f, 0.5f );

        CHS_buttons.push_back( button3X );
        page3_game.addObj( button3X );

    }}

    // Create chess game object.
    CHS_SFML_eng CHS_game_obj( CHS_buttons );

    for( const pair< chess::CHS_PIECE_TYPE, shared_ptr<sf::Texture> >& pair_z : 
        CHS_PCE_W_tex_map )
        { CHS_game_obj.setCHS_pieceTex( pair_z.first, chess::CHS_PIECE_COLOR::WHITE, pair_z.second ); }
    for( const pair< chess::CHS_PIECE_TYPE, shared_ptr<sf::Texture> >& pair_z : 
        CHS_PCE_B_tex_map )
        { CHS_game_obj.setCHS_pieceTex( pair_z.first, chess::CHS_PIECE_COLOR::BLACK, pair_z.second ); }
    
    CHS_game_obj.updateCHSBoard();

    page3_game.update();
    page3_game.disable();

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Page 4 Options
// ---------------------------------------------------------------------- >>>>>

    float p4_x_start = 300;
    float p4_y_start = 150;
    float p4_but_y_leap = 100;
    but_cnt = 0;
    string enabledAI_str = "VS AI: enabled";
    string disabledAI_str = "VS AI: disabled";

    bool AI_first = false;
    string AI_first_str = "AI first";
    string AI_not_first_str = "Player first";

    // Page initialization.
    SFML_page_XYQ page4_opt = SFML_page_XYQ();

    // Object: button for enabling/disabling AI.
    shared_ptr<SFML_button_XYQ> but4B_AI_enable = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but4B_AI_enable->setPos( p4_x_start, p4_y_start + but_cnt*p4_but_y_leap );
    but4B_AI_enable->setWidth( 200 );      
    but4B_AI_enable->setHeight( 50 );      
    but4B_AI_enable->setTxtFont( font );
    // if( CHK_game_obj.is_AI_enabled() ){
    //     but4B_AI_enable->setTxtStr( enabledAI_str );
    // }else{
        but4B_AI_enable->setTxtStr( disabledAI_str );
    // }
    but4B_AI_enable->setTxtColor( 50, 50, 50, 255 );
    but4B_AI_enable->setUPTexture( button_img_np_texture );
    but4B_AI_enable->setPTexture( button_img_p_texture );
    // Add to page.
    page4_opt.addObj( but4B_AI_enable );
    // Button count increment.
    but_cnt++;

    // Object: button for deciding if AI plays first or not.
    shared_ptr<SFML_button_XYQ> but4C_AI_playOrd = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but4C_AI_playOrd->setPos( p4_x_start, p4_y_start + but_cnt*p4_but_y_leap );
    but4C_AI_playOrd->setWidth( 200 );      
    but4C_AI_playOrd->setHeight( 50 );      
    but4C_AI_playOrd->setTxtFont( font );
    if( AI_first ){
        but4C_AI_playOrd->setTxtStr( AI_first_str );
    }else{
        but4C_AI_playOrd->setTxtStr( AI_not_first_str );
    }
    but4C_AI_playOrd->setTxtColor( 50, 50, 50, 255 );
    but4C_AI_playOrd->setUPTexture( button_img_np_texture );
    but4C_AI_playOrd->setPTexture( button_img_p_texture );
    // Add to page.
    page4_opt.addObj( but4C_AI_playOrd );
    // Button count increment.
    but_cnt++;

    // Object: button for returning to the main page.
    shared_ptr<SFML_button_XYQ> but4A_mmenu = 
        shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );
    but4A_mmenu->setPos( p4_x_start, p4_y_start + but_cnt*p4_but_y_leap );
    but4A_mmenu->setWidth( 200 );      
    but4A_mmenu->setHeight( 50 );      
    but4A_mmenu->setTxtFont( font );
    but4A_mmenu->setTxtStr( "Back" );
    but4A_mmenu->setTxtColor( 50, 50, 50, 255 );
    but4A_mmenu->setUPTexture( button_img_np_texture );
    but4A_mmenu->setPTexture( button_img_p_texture );
    // Add to page.
    page4_opt.addObj( but4A_mmenu );
    // Button count increment.
    but_cnt++;


    page4_opt.update();
    page4_opt.disable();

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
                    if( but1D_opt->pressButton( window ) ){}

                    if( but2A_back->pressButton( window ) ){}

                    if( but3A_mmenu->pressButton( window ) ){}
                    if( but3B_reset->pressButton( window ) ){}

                    CHS_game_obj.pressButton( window );

                    if( but4A_mmenu->pressButton( window ) ){}
                    // if( but4B_AI_enable->pressButton( window ) ){}
                    // if( but4C_AI_playOrd->pressButton( window ) ){}

                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){

                    if( but1A_startGame->releaseButton() ){
                        page1_mmenu.disable();
                        page3_game.enable();
                        // CHS_game_obj.resetBoard();
                    }
                    if( but1B_readMe->releaseButton() ){
                        page1_mmenu.disable();
                        page2_readme.enable();
                    }
                    if( but1C_exit->releaseButton() ){
                        window.close();
                    }
                    if( but1D_opt->releaseButton() ){
                        page1_mmenu.disable();
                        page4_opt.enable();
                    }

                    if( but2A_back->releaseButton() ){
                        page2_readme.disable();
                        page1_mmenu.enable();
                    }


                    // Leave page and return to main menu.
                    if( but3A_mmenu->releaseButton() ){

                        CHS_game_obj.resetBoard();
                        
                        page3_game.disable();
                        page1_mmenu.enable();
                        
                    }

                    // Reset TTT game.
                    if( but3B_reset->releaseButton() ){

                        CHS_game_obj.resetBoard();

                    }

                    // // bool gameButRel = CHS_game_obj.releaseButton();
                    bool playMade = CHS_game_obj.releaseButton();
                    // if( playMade ){

                    //     // Create a new thread that runs the runInThread function
                    //     std::thread myThread( CHK_SFML_eng::AI_play, ref( CHS_game_obj ) );
                    //     myThread.detach();

                    // }

                    if( but4A_mmenu->releaseButton() ){
                        page4_opt.disable();
                        page1_mmenu.enable();
                    }

                    // if( but4B_AI_enable->releaseButton() ){
                    //     CHS_game_obj.toggle_AI();
                    //     if( CHS_game_obj.is_AI_enabled() ){
                    //         but4B_AI_enable->setTxtStr( enabledAI_str );
                    //     }else{
                    //         but4B_AI_enable->setTxtStr( disabledAI_str );
                    //     }
                    //     but4B_AI_enable->update();
                    // }

                    // if( but4C_AI_playOrd->releaseButton() ){
                    //     CHS_game_obj.toggle_AI_first();
                    //     if( CHS_game_obj.is_AI_first() ){
                    //         but4C_AI_playOrd->setTxtStr( AI_first_str );
                    //         CHS_game_obj.set_AI_first();
                    //     }else{
                    //         but4C_AI_playOrd->setTxtStr( AI_not_first_str );
                    //         CHS_game_obj.set_AI_not_first();
                    //     }
                    //     but4C_AI_playOrd->update();
                    // }

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
        // Draw the option page.
        page4_opt.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}