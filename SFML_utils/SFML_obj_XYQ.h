#ifndef SFML_OBJ_XYQ_H
#define SFML_OBJ_XYQ_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;

/*
Polymorphic parent function to objects that can be drawn on a SFML window.
*/
class SFML_obj_XYQ
{

public:

    SFML_obj_XYQ( float x = 0, float y = 0 );
    SFML_obj_XYQ( sf::Vector2f position );


// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>

    /*
    Update the object.
    */
    virtual void update() = 0;

    /*
    Draw the object on the target window.
    */
    virtual void beDrawn( sf::RenderWindow& window ) const = 0;

    // Virtual destructor.
    virtual ~SFML_obj_XYQ() = default;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    bool isEnabled() const;
    void enable();
    void disable();
    // Switch enabled state from false to true or vice versa.
    void enableToggle();

    float getX() const;
    void setX( float bX );
    float getY() const;
    void setY( float bY );
    sf::Vector2f getPos() const;
    void setPos( sf::Vector2f position );
    void setPos( float bX, float bY );

// ====================================================================== <<<<<

protected:

    /*
    The object's position.
    */
    sf::Vector2f position;

    /*
    The flag indicating if this object is enabled. 
    Expected functionality is to prevent this object from being rendered  
    as well as to prevent interactions with this object if enabled = false.
    */
    bool enabled;

private:

};

#endif  // SFML_OBJ_XYQ_H
