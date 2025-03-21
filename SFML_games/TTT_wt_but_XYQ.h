#ifndef TTT_WT_BUT_XYQ_H
#define TTT_WT_BUT_XYQ_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


#include "TikTakTok.h"
#include "SFML_button_XYQ.h"
#include "SFML_page_XYQ.h"
#include "SFML_utils_XYQ.h"
#include "SFML_infoBox_XYQ.h"


using namespace std;

extern string RES_PATH_XYQ_str;


namespace gameEngine{

/*
Game engine for the game of Tik-Tak-Toc (TTT) with additional integrated SFML
button functionalities.
The buttons used are based on the class SFML_button_XYQ, which are custom buttons
I created using SFML libraries.
*/
class TTT_wt_but_XYQ : public TikTakTok{

public:

    /*
    The default constructor provides a set of buttons set at a default location,
    but it is strongly advised you use the alternative constructor which takes 
    in the buttons you created yourself and customized to your need as well as
    image texture to represent O and X states.
    */
    TTT_wt_but_XYQ();

    /*
    Create a TTT game engine with assigned buttons and O and X image textures.
    */
    TTT_wt_but_XYQ( vector<shared_ptr<SFML_button_XYQ>> TTT_buttons,
        shared_ptr<sf::Texture> TTT_O_img_texture, shared_ptr<sf::Texture> TTT_X_img_texture );

    /*
    Try to perform a press button action on all nine buttons.
    If any one of the nine buttons is pressed, return true, else false.
    NOTE: This function does not check if a mouse click is performed or which mouse
    click is performed.
    */
    bool pressButton( const sf::RenderWindow& window );
    /*
    Try to perform a button release on all nine buttons.
    If any one of the nine buttons is released, return true, else false.
    A button being released triggers a series of checks which attempt to see if
    the associated square is to be assigned either O or X and if so, is the game
    to be continued or ended now.
    */
    bool releaseButton();

    /*
    Obtain the current state of the game.
    Possible states: [0 = unfinished], [1 = O won], [2 = X won], [3 = draw].
    */
    unsigned int getState() const;
    
    /*
    Reset the game to a fresh start including buttons reset.
    */
    void reset();

    /*
    Set the texture the square is assigned with when O is selected.
    */
    void set_O_Texture( shared_ptr<sf::Texture> TTT_O_img_texture );
    /*
    Set the texture the square is assigned with when X is selected.
    */
    void set_X_Texture( shared_ptr<sf::Texture> TTT_X_img_texture );

protected:

    /*
    The vector of buttons representing the TTT board squares.
    */
    vector<shared_ptr<SFML_button_XYQ>> TTT_buttons;

    // The square texture when the square has not being pressed yet.
    //shared_ptr<sf::Texture> TTT_n_img_texture;
    // The square texture when O is assigned to the square.
    shared_ptr<sf::Texture> TTT_O_img_texture;
    // The square texture when X is assigned to the square.
    shared_ptr<sf::Texture> TTT_X_img_texture;

};

}





namespace game{
    /*
    Initialize a game of Tik-Tak-Tok.
    */
    void play_TikTakTok();
}

#endif  // TTT_WT_BUT_XYQ_H