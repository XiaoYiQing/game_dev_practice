#include "HPBar_test.h"



void tests::doHPBarTest_1(){

    float x_tar = 100;
    float y_tar = 100;

    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );

    SFML_HPBar_XYQ myHPBar = SFML_HPBar_XYQ();

    myHPBar.set_FB_x(x_tar);
    myHPBar.set_FB_y(y_tar);
    myHPBar.set_in_marg( 10 );
    myHPBar.set_DB_outl_thick( 3 );
    myHPBar.setHP( 61.3f );
    myHPBar.setMaxHP( 150 );
    myHPBar.set_FB_width(400);
    myHPBar.set_FB_height(60);
    myHPBar.set_FB_color( sf::Color( 255, 0, 0 ) );
    myHPBar.set_DB_color( sf::Color( 0, 255, 255 ) );
    myHPBar.set_FB_outl_color( sf::Color( 200, 200, 0 ) );
    myHPBar.set_DB_outl_color( sf::Color( 0, 140, 140 ) );
    
    myHPBar.infoBox.setTxtFont( font );
    myHPBar.infoBox.txt.setString( "HP:" );
    myHPBar.infoBox.txt.setCharacterSize( 30 );
    myHPBar.infoBox.txt.setFillColor( sf::Color( 0, 100, 255 ) );
    myHPBar.infoBox.setBoxFillColor( sf::Color( 0, 200, 0 ) );
    myHPBar.update();



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


    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image Example");
    
    

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

        // Draw reference coordinate lines.
        window.draw( horz_line );
        window.draw( vert_line );

        // Draw the text box.
        myHPBar.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}