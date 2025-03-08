#include "txtBox_test.h"


void tests::doTxtBoxTest_1(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Text Box Test.");

    float x_tar = 300;
    float y_tar = 150;

    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );

    // Define a vertical line using two vertices
    sf::VertexArray vert_line(sf::Lines, 2);
    // Set the starting and ending points of the line
    vert_line[0].position = sf::Vector2f( x_tar, 0.f); 
    vert_line[0].color = sf::Color::White;             
    vert_line[1].position = sf::Vector2f( x_tar, 600.f); 
    vert_line[1].color = sf::Color::White;  

    // Define an horizontal line using two vertices
    sf::VertexArray horz_line(sf::Lines, 2);
    // Set the starting and ending points of the line
    horz_line[0].position = sf::Vector2f( 0.f, y_tar ); 
    horz_line[0].color = sf::Color::White;             
    horz_line[1].position = sf::Vector2f( 800.f, y_tar ); 
    horz_line[1].color = sf::Color::White;               


    SFML_TxtBox_XYQ myTxtBox = SFML_TxtBox_XYQ( font, "Me not want this" );
    myTxtBox.txt.setCharacterSize( 60 );

    myTxtBox.setBoxFillColor( sf::Color( 0, 120, 0 ) );
    myTxtBox.setBoxOutlineColor( sf::Color( 255, 50, 0 ) );
    myTxtBox.setBoxOutlThick( 10.0f );
    
    myTxtBox.setPos( x_tar, y_tar );
    myTxtBox.update();

    


    // Main loop
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }



        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the text box.
        myTxtBox.beDrawn( window );

        // Draw two perpendicular crossing lines.
        window.draw( vert_line );
        window.draw( horz_line );

        // Display what has been rendered to the window
        window.display();

    }

}
