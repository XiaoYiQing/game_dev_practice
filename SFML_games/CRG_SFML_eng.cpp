#include "CRG_SFML_eng.h"



using namespace gameEngine;

CRG_SFML_eng::CRG_SFML_eng( int possCardCnt = 8, long long cntDownT = 3000 ) : 
    cardReact( possCardCnt, cntDownT )
{

    // Determine the number of rows and columns of cards depending on how many cards there
    // are in total.
    float tmp = std::sqrt( (float) possCardCnt );
    rowColCnt.x = std::ceil( ( (float) possCardCnt )/tmp );
    rowColCnt.y = std::ceil( tmp );
    

    // Define the default locations and sizes of the buttons.
    float x_start = 100;        float y_start = 100;
    float butWidth = 50;       float butHeight = 50;
    float butSep = 5;

    // Card index variable.
    int z = 0;
    for( int i = 0; ( i < rowColCnt.x && z < possCardCnt ); i++ ){
        for( int j = 0; ( j < rowColCnt.y && z < possCardCnt ); j++ ){

            possCardTex_vect.push_back( shared_ptr<sf::Texture>( new sf::Texture() ) );

            shared_ptr<SFML_button_XYQ> buttonX = 
                    shared_ptr<SFML_button_XYQ>( new SFML_button_XYQ() );

            buttonX->setPos( x_start + ( butWidth + butSep )*j, 
                y_start + ( butHeight + butSep )*i );
            buttonX->setWidth( butWidth );      
            buttonX->setHeight( butHeight );  
            buttonX->setTxtStr( "" + z );
            buttonX->disableSprite();

            possCard_vect.push_back( buttonX );

            z++;

        }

    }

}

