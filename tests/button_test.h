#ifndef BUTTON_TEST_H
#define BUTTON_TEST_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "SFML_button_XYQ.h"
#include "SFML_utils_XYQ.h"

using namespace std;


extern string RES_PATH_XYQ_str;


namespace tests{

    /*
    Basic button object test, simply going through the access functions.
    No actual window is created.
    */
    void doButtonObjTest_1();

    /*
    Button object test aimed at its update functionality making sure individual
    changes to its properties are updated in batch by a specific function.
    Function also checks the beDrawn( sf::RenderWindow window ) function which makes
    drawing of the necessary parts of a button easier to manage.
    */
    void doButtonObjTest_2();

    /*
    Test aimed at using an image to illustrate the button.
    Both the button's pressed and unpressed states have their own image, allowing
    visual differentiation of the states.
    */
    void doButtonObjTest_3();

    /*
    Test button functionality to react to the state of being pressed and released.
    The number of presses is counted and displayed when the button is released 
    after being pressed.
    Another button appears only during the first button's pressed state, which 
    means the other button cannot be pressed.
    Also tests the enable and disable functionalities of the buttons.
    */
    void doButtonObjTest_4();

    /*
    Test of a pair buttons with only one appearing at a time.
    Pressing the visible button will disable the button while revealing and
    enabling the other button.
    */
    void doButtonObjTest_5();

}


#endif // BUTTON_TEST_H


