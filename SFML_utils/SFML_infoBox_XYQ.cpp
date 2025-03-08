#include "SFML_infoBox_XYQ.h"



SFML_infoBox_XYQ::SFML_infoBox_XYQ(): 
    SFML_obj_XYQ()
{

    imgBox = SFML_button_XYQ();

    imgBox.setTxtStr( "Object" );
    imgBox.setPos( position );
    imgBox.setUPColor( sf::Color::Green );
    imgBox.setPColor( sf::Color::Green );

    txtBox = SFML_TxtBox_XYQ();
    txtBox.txt.setString( "Object description." );
    txtBox.setBoxFillColor( sf::Color::Yellow );
    
    this->update();

}



void SFML_infoBox_XYQ::update(){

    imgBox.setPos( this->position );
    imgBox.update();

    float imgBoxWidth = imgBox.getWidth();
    float imgBoxHeight = imgBox.getHeight();


    // The txt object position must be with respect to the image object's position.
    txtBox.setPos( this->position.x + imgBoxWidth, 
        this->position.y );
    txtBox.update();

    txtBox.setBoxHeight( imgBoxHeight );
    txtBox.update();

}

void SFML_infoBox_XYQ::beDrawn( sf::RenderWindow& window ) const{

    this->imgBox.beDrawn( window );

    this->txtBox.beDrawn( window );

}