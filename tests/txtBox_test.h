#ifndef TXTBOX_TEST_H
#define TXTBOX_TEST_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "SFML_utils_XYQ.h"
#include "SFML_TxtBox_XYQ.h"

using namespace std;


extern string RES_PATH_XYQ_str;


namespace tests{
    
    /*
    Test the text box object.
    Make sure its position is set with respect to the upper left corner of the box.
    */
    void doTxtBoxTest_1();

}



#endif  // TXTBOX_TEST_H

