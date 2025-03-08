#include "infoBox_test.h"



/*
Do various tests on the SFML object which combines a button with a text description.
The object's goal is to make a combination of visual display with text explanation 
easy to create.
The visual display may also be used as a real button for simple page navigation.
*/
void tests::doInfoBoxTest_1(){
    
    string button_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";
    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );

    // Initialize the info box.
    SFML_infoBox_XYQ myInfoBox;
    myInfoBox.setPos( 100, 100 );
    myInfoBox.imgBox.setHeight( 200 );
    myInfoBox.imgBox.setWidth( 200 );
    myInfoBox.imgBox.setTxtStr( "" );
    myInfoBox.imgBox.setUPTexture( button_img_FFN );

    string txtBoxStr = "There were 12 train carts parked there. I parked at the end of the world.JAJAJA";
    myInfoBox.txtBox.setTxtFont( font );
    myInfoBox.txtBox.setTxtLenLim( 150 );
    myInfoBox.txtBox.txt.setCharacterSize( 30 );
    myInfoBox.txtBox.txt.setString( txtBoxStr );
    myInfoBox.txtBox.setUseBoxMargFact( false, false, true, true );
    myInfoBox.txtBox.setBoxMargAmt( 0, 30 );    // Upper margin.
    myInfoBox.txtBox.setBoxMargAmt( 1, 50 );    // Lower margin.
    myInfoBox.update();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image Example");
    
    // Main loop.
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        myInfoBox.beDrawn(window);

        // Display what has been rendered to the window
        window.display();

    }

}