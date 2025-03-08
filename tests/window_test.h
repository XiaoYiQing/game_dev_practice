#ifndef WINDOW_TEST_H
#define WINDOW_TEST_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "SFML_utils_XYQ.h"

using namespace std;


extern string RES_PATH_XYQ_str;


namespace tests{

    void do_wind_test( int test_idx );

    /* Most basic window creation ... no functionality except closing itself. */
    void window_test_1();

    /* 
    Window test where we create a button with a simple print functionality. 
    The console prints a message whenever the mouse left clicks while hovering over the button.
    */
    void window_test_2();

    /*
    Window test for a depressing button which prints something on the console only when clicked
    AND released. As well, when clicked, the button changes color to emulate a depressing button.
    Resizing the window has been disabled.
    */
    void window_test_3();
    
    /*
    Test of a window displaying some text using a chosen font.
    Two text boxes are placed on the window with overlapping positions.
    A button is on the window which allows you to displace the second text box to another location
    and back each time the button clicked.
    */
    void window_test_4();

    /*
    Test of a SFML window which allows user to input a string in an input box.
    Text length is restricted by the box area.
    Text can only be entered in the box when the text box is focused.
    */
    void window_test_5();

    /*
    Test of a SFML window which put an image on the window.
    A button of the exact same size covers the image, and switches between having 
    a flat color and being transparent at the user's left click.
    */
    void window_test_6();

}


#endif // WINDOW_TEST_H
