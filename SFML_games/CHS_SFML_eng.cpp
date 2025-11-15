#include "CHS_SFML_eng.h"

using namespace gameEngine;

const sf::Color CHS_SFML_eng::LTILECOLOR = sf::Color( 255, 255, 255, 255 );
const sf::Color CHS_SFML_eng::DTILECOLOR = sf::Color( 155, 155, 155, 255 );
const sf::Color CHS_SFML_eng::PTILECOLOR = sf::Color( 0, 255, 255, 255 );
const sf::Color CHS_SFML_eng::LOCKTILECOLOR = sf::Color( 255, 255, 0, 255 );


CHS_SFML_eng::CHS_SFML_eng() : chess(){

    act_set_lock = false;

    CHS_PCE_W_tex_arr = vector< shared_ptr<sf::Texture> >(6);
    CHS_PCE_B_tex_arr = vector< shared_ptr<sf::Texture> >(6);

    // Define the default locations and sizes of the buttons.
    float x_start = 100;        float y_start = 100;
    float butWidth = 50;       float butHeight = 50;
    float butSep = 5;

    // Fill the 
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

        this->CHS_buttons.push_back( buttonX );
        
    }
    }

}


CHS_SFML_eng::CHS_SFML_eng( vector<shared_ptr<SFML_button_XYQ>> CHS_buttons ) : chess()
{
    act_set_lock = false;
    this->CHS_buttons = CHS_buttons;
}


// ====================================================================== >>>>>
//      Gameplay Control Functions
// ====================================================================== >>>>>

bool CHS_SFML_eng::pressButton( const sf::RenderWindow& window ){

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


bool CHS_SFML_eng::releaseButton(){

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
                    
                    /*
                    TODO: This is where you need to update your game state using the play or ply
                    function. Once the internal game state is changed, update the visual state
                    as well.
                    */

                    // Update the visual components representing the game.
                    // this->updateCHKBoard();

                }else{

                    act_set_lock_but = buttonX;
                    act_set_lock_but->setUPColor( LOCKTILECOLOR );
                    act_set_lock_but->update();

                    act_set_lock = true;

                }

                break;
            }
        }

        if( released ){
            break;
        }
    }
    
    return played;

}


// Lock all buttons.
void CHS_SFML_eng::lock_buttons(){
    for( shared_ptr<SFML_button_XYQ> button_z : CHS_buttons ){
        button_z->lock();
    }
}

// Unlock all buttons.
void CHS_SFML_eng::unlock_buttons(){
    for( shared_ptr<SFML_button_XYQ> button_z : CHS_buttons ){
        button_z->unlock();
    }
}


bool CHS_SFML_eng::AI_play( CHS_SFML_eng& tarGame ){
    
    // Only allow AI play if AI is enabled.
    if( !( tarGame.vsAI ) ){
        return false;
    }

    // Lock all buttons when the AI is performing a play.
    tarGame.lock_buttons();

    /*
    TODO: 
    This is where you implement the AI play tasks.
    */
    
    // Unlock the buttons.
    tarGame.unlock_buttons();

    // Update the visual components representing the game.
    // tarGame.updateCHKBoard();

    // Reaching this point means the AI play is successful.
    return true;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>


// ====================================================================== <<<<<
