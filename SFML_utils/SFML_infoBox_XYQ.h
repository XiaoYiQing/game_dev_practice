#ifndef SFML_INFOBOX_XYQ_H
#define SFML_INFOBOX_XYQ_H



#include "SFML_obj_XYQ.h"
#include "SFML_button_XYQ.h"
#include "SFML_TxtBox_XYQ.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;



/*
SFML object which combines a button with a text description.
The object's goal is to make a visual display with text explanation easy to create.
The visual display may also be used as a real button for simple page traversal.
*/
class SFML_infoBox_XYQ: public SFML_obj_XYQ{

public:

    SFML_infoBox_XYQ();

    void update() override;

    void beDrawn( sf::RenderWindow& window ) const override;

    /*
    The image box.
    */
    SFML_button_XYQ imgBox;

    /*
    The text box.
    */
    SFML_TxtBox_XYQ txtBox;
    
protected:

    


private:


};


#endif  // SFML_INFOBOX_XYQ_H



/*
DONE: In the update of this class object, make sure the height of the textbox is automatically
matched to that of the button.
*/