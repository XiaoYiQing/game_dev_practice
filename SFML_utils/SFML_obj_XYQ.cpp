#include "SFML_obj_XYQ.h"



SFML_obj_XYQ::SFML_obj_XYQ( float x, float y ){

    this->position = sf::Vector2f( x, y );
    enabled = true;

}


SFML_obj_XYQ::SFML_obj_XYQ(  sf::Vector2f position ){

    this->position = position;
    enabled = true;

}


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

bool SFML_obj_XYQ::isEnabled() const
    {return this->enabled;}
void SFML_obj_XYQ::enable()
    {this->enabled = true;}
void SFML_obj_XYQ::disable()
    {this->enabled = false;}
void SFML_obj_XYQ::enableToggle()
    {this->enabled = !enabled;}

float SFML_obj_XYQ::getX() const
    {return this->position.x;}
void SFML_obj_XYQ::setX( float bX )
    {this->position.x = bX;}
float SFML_obj_XYQ::getY() const
    {return this->position.y;}
void SFML_obj_XYQ::setY( float bY )
    {this->position.y = bY;}
sf::Vector2f SFML_obj_XYQ::getPos() const
    {return this->position;}
void SFML_obj_XYQ::setPos( sf::Vector2f position )
    {this->position = position;}
void SFML_obj_XYQ::setPos( float bX, float bY )
    {this->position = sf::Vector2f( bX, bY );}

// ====================================================================== <<<<<
