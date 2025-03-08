#ifndef SFML_HPBAR_XYQ_H
#define SFML_HPBAR_XYQ_H

#include "SFML_TxtBox_XYQ.h"
#include "SFML_obj_XYQ.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>



class SFML_HPBar_XYQ: public SFML_obj_XYQ
{

public:

// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

    SFML_HPBar_XYQ();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>

    // Update the health bar.
    void update() override;

    // Draw the HP bar.
    void beDrawn( sf::RenderWindow& window ) const override;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    // Get the fullbar's width.
    float get_FB_width() const;
    // Set the fullbar's width.
    void set_FB_width( float width_in );

    // Get the fullbar's height.
    float get_FB_height() const;
    // Set the fullbar's height.
    void set_FB_height( float height_in );

    // Get the fullbar's x coordinate.
    float get_FB_x() const;
    // Set the fullbar's x coordinate.
    void set_FB_x( float x_in );

    // Get the fullbar's y coordinate.
    float get_FB_y() const;
    // Set the fullbar's y coordinate.
    void set_FB_y( float y_in );

    // Return the inner margin (distance between fullbar and dynamic bar).
    float get_in_marg() const;
    // Set the inner margin (distance between fullbar and dynamic bar).
    void set_in_marg( float in_marg );

    // Return the full bar's outline thickness.
    float get_FB_outl_thick() const;
    // Set the full bar's outline thickness.
    void set_FB_outl_thick( float fb_outl_thick );

    // Return the dynamic bar's outline thickness.
    float get_DB_outl_thick() const;
    // Set the dynamic bar's outline thickness.
    void set_DB_outl_thick( float db_outl_thick );

    // Return the full bar's color.
    sf::Color get_FB_color() const;
    // Set the full bar's color.
    void set_FB_color( sf::Color );

    // Return the dynamic bar's color.
    sf::Color get_DB_color() const;
    // Set the dynamic bar's color.
    void set_DB_color( sf::Color );

    // Return the full bar's outline color.
    sf::Color get_FB_outl_color() const;
    // Set the full bar's outline color.
    void set_FB_outl_color( sf::Color );

    // Return the dynamic bar's outline color.
    sf::Color get_DB_outl_color() const;
    // Set the dynamic bar's outline color.
    void set_DB_outl_color( sf::Color );

    // Return the current HP amount.
    float getHP() const;
    // Set the current HP amount.
    void setHP( float );
    
    // Return the maximum HP amount.
    float getMaxHP() const;
    // Set the maximum HP amount (Maintains HP percentage).
    void setMaxHP( float );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    // The text box attached to the HP bar to provide details.
    SFML_TxtBox_XYQ infoBox;

// ====================================================================== <<<<<


private:

    // The name of the bar.
    string contName = "HP";

    // The sub-block linked to the HP bar for placing the verbal explanation of
    // what the bar represent.

    // The full bar serving as backdrop illustrating the full HP extend.
    sf::RectangleShape fullBar;
    // The bar illustrating the actual HP that dynamically changes.
    sf::RectangleShape dynamBar;

    /* 
    The dimensions of the full HP bar:  
        [0-> x]  [1-> y]  [2-> width]  [3-> height].
    */
    float fb_p_d[4] = { 0, 0, 250, 40 };

    // The fullbar outline thickness.
    float fb_outl_thick = 4;

    // The fullbar color.
    sf::Color fb_color = sf::Color( 120, 120, 120 );
    // The fullbar bar outline color.
    sf::Color fb_outl_color = sf::Color( 255, 255, 255 );

    /* 
    The dimensions of the full HP bar:  
        [0-> x]  [1-> y]  [2-> width]  [3-> height].
    */
    float db_p_d[4] = { fb_p_d[0], fb_p_d[1], fb_p_d[2], fb_p_d[3] };

    // The dynamic to full bar margin (Distance from the inner bar to the outer bar).
    float in_marg = 5;
    // The dynamic bar outline thickness.
    float db_outl_thick = 2;

    
    // The dynamic bar color.
    sf::Color db_color = sf::Color( 0, 200, 0 );
    // The dynamic bar outline color.
    sf::Color db_outl_color = sf::Color( 0, 80, 0 );

    // The numerical amount of max HP and HP, in that order in the array.
    float HPnum[2] = { 100, 100 };


    

};


#endif // SFML_HPBAR_XYQ_H

