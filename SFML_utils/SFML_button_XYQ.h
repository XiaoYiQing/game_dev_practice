#ifndef SFML_BUTTON_XYQ_H
#define SFML_BUTTON_XYQ_H

#include "SFML_utils_XYQ.h"
#include "SFML_obj_XYQ.h"

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;


class SFML_button_XYQ: public SFML_obj_XYQ
{
public:

// ====================================================================== >>>>>
//      Static Support Functions
// ====================================================================== >>>>>
    
// ====================================================================== <<<<<

// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>
    SFML_button_XYQ();
// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Button Functionalities
// ====================================================================== >>>>>

    /*
    The function checks the conditions necessary for the button to be available to
    press. The conditions are as follow:
        > If the button is enabled.
        > If the button is in an unpressed state.
        > If the mouse is over the area the button occupies on a window.
        > If the window has focus.
    */
    bool canBePressed( const sf::RenderWindow& window ) const;

    /*
    The function checks the conditions necessary for the button to be able to
    be released. The conditions are as follow:
        > If the button is enabled.
        > If the button is pressed.
    */
    bool canBeReleased();

    /* 
    Perform a press button action. 
    Return bool indicates the press button action is succesful.
    NOTE: The function only verifies if the button CAN be pressed, and performs the 
    press action if it can, but it does NOT check if there was actually a mouse click or
    which mouse button was clicked.
    */
    bool pressButton( const sf::RenderWindow& window );
    /*
    Perform a release button action. 
    Return bool indicates the release button is succesful.
    NOTE: the function does nothing if the button was not in a pressed state.
    */
    bool releaseButton();

    /*
    Update the state of the button.
    This function is necessary for individual changes to the button to take effect.
    */
    void update() override;

    // Specific update of the sprite of the unpressed button.
    void upd_UPB_sprite();
    // Specific update of the sprite of the pressed button.
    void upd_PB_sprite();

    /*
    Use the target window object to draw the elements representing the button.
    */
    void beDrawn( sf::RenderWindow& window ) const override;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Support Functions
// ====================================================================== >>>>>
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    const sf::RectangleShape getRect() const;

    float getWidth() const;
    void setWidth( float bWidth );
    float getHeight() const;
    void setHeight( float bHeight );


    // Obtain the button color when unpressed.
    sf::Color getUPColor() const;
    // Obtain the unpressed button color.
    void setUPColor( sf::Color upColor );
    // Set the unpressed button color using RGB code (0 to 255) and alpha = opacity (0 to 255).
    void setUPColor( unsigned int red, unsigned int green, unsigned int blue, 
        unsigned int alpha = 255 );

    // Obtain the button color when pressed.
    sf::Color getPColor() const;
    // Set the pressed button color.
    void setPColor( sf::Color pColor );
    // Set the pressed button color using RGB code (0 to 255) and alpha=opacity (0 to 255).
    void setPColor( unsigned int red, unsigned int green, unsigned int blue, 
        unsigned int alpha = 255 );

    /* 
    Set the sprite to illustrate the button when unpressed. 
    Input: target image file full file name.
    */
    bool setUPTexture( string imgFFName );
    /* 
    Set the sprite to illustrate the button when unpressed. 
    Input: target image texture.
    */
    bool setUPTexture( shared_ptr<sf::Texture> upTexture );
    // Delete the texture used for unpressed state.
    void delUPTexture();
    /* 
    Determine if the button has a texture for illustrating its unpressed state.
    A texture having 0 width or 0 height results in false.
    */
    bool hasUPTexture() const;

    // Set the sprite to illustrate the button when pressed. 
    // Input: target image file full file name.
    bool setPTexture( string imgFFName );
    /* 
    Set the sprite to illustrate the button when pressed. 
    Input: target image texture.
    */
    bool setPTexture( shared_ptr<sf::Texture> pTexture );
    // Delete the texture used for pressed state.
    void delPTexture();
    /* 
    Determine if the button has a texture for illustrating its pressed state.
    A texture having 0 width or 0 height results in false.
    */
    bool hasPTexture() const;

    void setUpSprtScale( float x, float y );
    void setUpSprtScale( sf::Vector2f upSprtScale );
    
    void setPSprtScale( float x, float y );
    void setPSprtScale( sf::Vector2f upSprtScale );

    // Enable drawing of sprite, if any.
    void enableSprite();    
    // Disable drawing of sprite.
    void disableSprite();
    // Enable drawing of text, if any.
    void enableText();
    // Disable drawing of text.
    void disableText();

    // Get boolean flag indicating whether the button is in pressed state or not.
    bool isPressed() const;

    bool getButtonFlag() const;
    void setButtonFlag( bool buttonFlag );

    // Determine whether the button is locked or not.
    bool isLocked() const;
    // Lock the button.
    void lock();
    // Unlock the button.
    void unlock();

    unsigned int getPressCnt() const;
    void setPressCnt( unsigned int );

    /* 
    Return flag indicating whether the button is enabled.
    If true (enabled), the button works as per usual without any changes.
    If false (disabled):
        > Cannot be pressed or released.
        > Cannot be drawn.
        > Can still be modified and updated.
    */
    //bool isEnabled();
    // Set the state of the button as enabled.
    //void enable();
    // Set the state of the button as not enabled.
    //void disable();
    // Switch the enabled state to opposite.
    //void enableToggle();

    const sf::Font getTxtFont() const;
    const shared_ptr<sf::Font> getTxtFontPtr() const;
    void setTxtFont( sf::Font );
    void setTxtFont( shared_ptr<sf::Font> );

    string getTxtStr() const;
    void setTxtStr( string txtStr );

    sf::Color getTxtColor() const;
    void setTxtColor( sf::Color );
    // Set the text color using RGB code (0 to 255) and alpha=opacity (0 to 255).
    void setTxtColor( unsigned int red, unsigned int green, unsigned int blue, 
        unsigned int alpha = 255 );
    
    void setTxtSize( unsigned int txtSize );

    float getTxtX() const;
    void setTxtX( float txtX );
    float getTxtY() const;
    void setTxtY( float txtY );
    void setTxtPos( float txtX, float txtY );

// ====================================================================== <<<<<


private:

    /* 
    An offset value to shift the position of the sprite slightly in the upper-left 
    direction. Rescaling of the sprite will also compensate the use of this offset 
    (To ensure sprite covers the base button rectangle)
    */
    static const float sprt_pos_offset;

    /*
    The rectangle shape representing the button's actual location and area occupied.
    */
    sf::RectangleShape butRect;
    
    // Vector holding the width and height of the button.
    sf::Vector2f size;

    // The position of the button.
    //sf::Vector2f position override = sf::Vector2f( 0.0f, 0.0f );

    /* 
    The color of the button when not pressed. 
    Only visible if no image associated to the button when not pressed.
    */
    sf::Color upColor = sf::Color::Green;
    /* 
    The color of the button when pressed. 
    Only visible if no image associated to the button when pressed.
    */
    sf::Color pColor = sf::Color::Blue;

    
    // The sprite (image) the button is illustrated by when unpressed.
    std::shared_ptr<sf::Sprite> upSprite;
    // The sprite (image) the button is illustrated by when pressed.
    std::shared_ptr<sf::Sprite> pSprite;
    // The actual texture/image of the button when unpressed.
    std::shared_ptr<sf::Texture> upTexture;
    // The actual texture/image of the button when pressed.
    std::shared_ptr<sf::Texture> pTexture;
    
    /* 
    The scale ( x = width scale, y = height scale ) of the unpressed state sprite with respect to the rectangle. 
    A scale of 1 for width and height means the sprite is going to match the width and height of the rectangle, respectively.
    */
    sf::Vector2f upSprtScale;
    /* 
    The scale ( x = width scale, y = height scale ) of the pressed state sprite with respect to the rectangle. 
    A scale of 1 for width and height means the sprite is going to match the width and height of the rectangle, respectively.
    */
    sf::Vector2f pSprtScale;

    // Flag indicating whether or not to draw the sprite.
    bool drawSprite;
    // Flag indicating whether or not to draw the text.
    bool drawText;

    // Flag indicating whether the button is being pressed.
    bool pressed;
    // Two-state flag indicator, for keeping track of which state the button is at.
    bool buttonFlag;
    // Flag indicating whether the button is locked or not. Locked button cannot be pressed.
    bool locked;

    // The number of times the button has been pressed AND released.
    unsigned int pressCnt;

    /*
    The text that appears on the button.
    */
    sf::Text bTxt;

    //The font adopted by the button.
    //sf::Font txtFont;
    shared_ptr<sf::Font> txtFont;


    // The size of the text object on the button.
    unsigned int txtSize;
    // The string of the text object.
    string txtStr;
    // The color of the text object.
    sf::Color txtColor;
    // X position of the text object relative to the center of button shape.
    float txtX;
    // Y position of the text object relative to the center of button shape.
    float txtY;


};


#endif // SFML_BUTTON_XYQ_H
