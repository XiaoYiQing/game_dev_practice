#ifndef SFML_TXTBOX_XYQ_H
#define SFML_TXTBOX_XYQ_H

#include "SFML_utils_XYQ.h"
#include "SFML_obj_XYQ.h"

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <stdexcept>
#include <string>



using namespace std;



/*
Simple textbox object. It is a box with a text centered (by default) in it, which
adjust its size with respect to the text inputted.
*/
class SFML_TxtBox_XYQ: public SFML_obj_XYQ
{

public:

    SFML_TxtBox_XYQ( sf::Font txtFont = sf::Font(), string txtStr = "NO TEXT" );
    SFML_TxtBox_XYQ( shared_ptr<sf::Font> txtFont, string txtStr = "NO TEXT" );
    
    /*
    The text that appears in the box. This variable is intended to be freely
    manipulated. It is the box surrounding the text which is updated upon changes
    made to the Text object. Make sure to use "update()" following any changes to
    the Text object to ensure the box follows the changes.
    */
    sf::Text txt;

// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>
    

    /* 
    Update the box serving as backdrop to the text object.
    Given how this class is designed, the "txt" object should be updated
    by the user beforehand as it is accessible publicly. This would ensure
    the box object updates with the intended "txt" settings.
    */
    void update() override;

    /*
    Update the text string to insert line breaks whenever a line length crosses a
    specified limit.
    NOTE: The line length limit is not respected in an absolute sense as the line 
        break is placed AFTER the word which crosses the limit.
    */
    void upd_lineBreak();

    // Draw the text box object.
    void beDrawn( sf::RenderWindow& window ) const override;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    float getTxtLenLim() const;
    void setTxtLenLim( float txtLenLim );

    const sf::Font getTxtFont() const;
    const shared_ptr<sf::Font> getTxtFontPtr() const;
    void setTxtFont( const sf::Font );
    void setTxtFont( const shared_ptr<sf::Font> );

    // Obtain a reference to the box.
    const sf::RectangleShape* getBox() const;

    const float* getBoxMargFact() const;
    // Set the margin factor of the target direction ( 0=up, 1=down, 2=left, 3=right )
    void setBoxMargFact( unsigned int directIdx, float value );

    const float* getBoxMargAmt() const;
    // Set the margin amount of the target direction ( 0=up, 1=down, 2=left, 3=right )
    void setBoxMargAmt( unsigned int directIdx, float value );

    // Return flag indicating whether box to text margin is factor based or a direct amount.
    const bool* getUseBoxMargFact() const;
    /* 
    Set flag indicating whether box to text margin is factor based or a direct amount for
    the target direction ( 0=up, 1=down, 2=left, 3=right ).
    */
    void setUseBoxMargFact( unsigned int directIdx, bool value );
    /* 
    Set flag indicating whether box to text margin is factor based or a direct amount for
    the all directions.
    */
    void setUseBoxMargFact( bool up, bool down, bool left, bool right );

    sf::Color getBoxFillColor() const;
    void setBoxFillColor( sf::Color boxColor );

    sf::Color getBoxOutlineColor() const;
    void setBoxOutlineColor( sf::Color boxOutlColor );

    // Obtain the thickness of the box outline.
    float getBoxOutlThick() const;
    // Set the thickness of the box outline.
    void setBoxOutlThick( float boxOutlThickness );

    /*
    Forcibly change the text box height to the target value.
    Utilizing this function will force the upper and bottom margins to use direct values.
    The height set cannot be smaller than the height of the text object itself.

    NOTE: This function cannot be updated at the same time as other changes made to the textbox.
    It is necessary to wait until all other updates are made before calling this function.
    An "update()" call is required for changes made by this function to take effect.
    */
    void setBoxHeight( float bHeight );

// ====================================================================== <<<<<

private:

    /*
    The length of the text object where line break will be applied before breaching.
    */
    float txtLenLim = 200;

    /*
    The font of the text.
    */
    //sf::Font txtFont;
    shared_ptr<sf::Font> txtFont;

    /*
    The rectangle shape representing the button's actual location and area occupied.
    */
    sf::RectangleShape box;

    /* 
    The margins of the rectangle around the text as a percentage of the text size. 
    These margin values form an alternative to "boxMargAmt".
    [ upper margin, lower margin, left margin, right margin ]
    */
    float boxMargFact[4] = { 0.2f, 0.2f, 0.2f, 0.2f };
    /*
    The margins of the rectangle around the text as a direct value.
    These margin values form an alternative to "boxMargFact".
    [ upper margin, lower margin, left margin, right margin ]
    */
    float boxMargAmt[4] = { 4.f, 4.f, 4.f, 4.f };
    // Flag controlling whether we use factors or direct amounts to define the margin.
    // If true, factors are used to calculate the margins, else direct amounts are applied.
    bool useBoxMargFact[4] = { true, true, true, true };

    // The color of the box.
    sf::Color boxColor = sf::Color::Green;
    // The color of the box outline.
    sf::Color boxOutlColor = sf::Color( 255, 155, 0 );
    // The thickness of the rectangle's outline.
    float boxOutlThickness = 4;

};

#endif  // SFML_TXTBOX_XYQ_H



// DONE: Create way to auto apply line break in order for the text to be kept within
// the boundary of the box.

// DONE: Arrange the update function individual tasks in an orderly fashion.
