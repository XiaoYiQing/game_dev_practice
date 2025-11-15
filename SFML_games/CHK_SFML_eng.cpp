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


// ====================================================================== >>>>>
//      Gameplay Control Functions
// ====================================================================== >>>>>

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

    bool played = false;
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
                    
                    // Determine direction of action.
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

                    // Attempts a play on the target button along the target direction.
                    played = this->play( act_set_lock_coords.x, act_set_lock_coords.y, vect_direct );
                    // Update the visual components representing the game.
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
    
    return played;

}

// Lock all buttons.
void CHK_SFML_eng::lock_buttons(){
    for( shared_ptr<SFML_button_XYQ> button_z : CHK_buttons ){
        button_z->lock();
    }
}

// Unlock all buttons.
void CHK_SFML_eng::unlock_buttons(){
    for( shared_ptr<SFML_button_XYQ> button_z : CHK_buttons ){
        button_z->unlock();
    }
}


bool CHK_SFML_eng::AI_play( CHK_SFML_eng& tarGame ){
    
    // Only allow AI play if AI is enabled.
    if( !( tarGame.vsAI ) ){
        return false;
    }

    if( tarGame.state == CHK_STATE::LOCKED ){
        cerr << "The game cannot perform an AI play while in the locked state." << endl;
        return false;
    }
    // Lock all buttons when the AI is performing a play.
    tarGame.lock_buttons();

    // Let the AI perform the next play.
    checkers::CHK_move AI_move = checkers::AI_play( tarGame );
    // If the play failed.
    if( AI_move.k == CHK_DIREC::NO_D ){
        tarGame.unlock_buttons();
        return false;
    }

    // Continue making the AI play if the first AI move initiated a locked state.
    while( tarGame.state == CHK_STATE::LOCKED ){

        AI_move = checkers::AI_play( tarGame );
        if( AI_move.k == CHK_DIREC::NO_D ){
            tarGame.unlock_buttons();
            return false;
        }

    }
    
    // Unlock the buttons.
    tarGame.unlock_buttons();

    // Update the visual components representing the game.
    tarGame.updateCHKBoard();

    // Reaching this point means the AI play is successful.
    return true;

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>


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

            but_ij->unlock();
            but_ij->update();

        }
    }

    return;

}



void CHK_SFML_eng::resetBoard(){

    checkers::resetBoard();

    this->updateCHKBoard();

    // Let the AI make the first move if AI is enabled and AI goes first.
    if( this->vsAI && this->AI_first ){
        // CHK_SFML_eng::AI_play( *this );
        // Create a new thread that runs the AI play function.
        std::thread myThread( CHK_SFML_eng::AI_play, ref( *this ) );
        myThread.detach();
    }

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








