#include "button_test.h"



void tests::doButtonObjTest_5(){
    
    // Create the main window.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window A");

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";

    // The arial ttf full file name.
    string arial_ttf_ffname = RES_PATH_XYQ_str + "/Arial.ttf";
    // Load a font.
    sf::Font font = SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str );
    
// ---------------------------------------------------------------------- >>>>>
//      Window A Elements Initialization
// ---------------------------------------------------------------------- >>>>>

    SFML_button_XYQ myButtonA = SFML_button_XYQ();

    myButtonA.setWidth( 200 );      
    myButtonA.setHeight( 50 );      
    myButtonA.setX( 200 );          
    myButtonA.setY( 150 );          

    myButtonA.setTxtFont( font );
    myButtonA.setTxtStr( "Button A" );
    myButtonA.setTxtColor( 50, 50, 50, 255 );

    myButtonA.setUPTexture( button_img_np_FFN );
    myButtonA.setPTexture( button_img_p_FFN );
    myButtonA.update();

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Window B Elements Initialization
// ---------------------------------------------------------------------- >>>>>

    SFML_button_XYQ myButtonB = SFML_button_XYQ();
    myButtonB.disable();

    myButtonB.setWidth( 200 );
    myButtonB.setHeight( 50 );
    myButtonB.setX( 200 );
    myButtonB.setY( 300 );

    myButtonB.setTxtFont( font );
    myButtonB.setTxtStr( "Button B" );
    myButtonB.setTxtColor( 50, 50, 50, 255 );
    myButtonB.setUPTexture( button_img_np_FFN );
    myButtonB.setPTexture( button_img_p_FFN );
    myButtonB.update();

    // Window B elements are turned off at first.
    myButtonB.disable();

// ---------------------------------------------------------------------- <<<<<

    // Main loop
    while (window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

// ---------------------------------------------------------------------- >>>>>
//      Mouse (Left) Click Event
// ---------------------------------------------------------------------- >>>>>

            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if( myButtonA.pressButton( window ) ){
                    }
                    if( myButtonB.pressButton( window ) ){
                    }
                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    if( myButtonA.releaseButton() ){
                        myButtonA.disable();
                        myButtonB.enable();
                    }
                    if( myButtonB.releaseButton() ){
                        myButtonB.disable();
                        myButtonA.enable();
                    }
                }
            }
// ---------------------------------------------------------------------- <<<<<

        }


        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        myButtonA.beDrawn( window );
        myButtonB.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }


}

void tests::doButtonObjTest_4(){
    
    // Create the main window.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window A");

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    shared_ptr<sf::Font> font = SFMLUtilsXYQ::getArialFontPtr( RES_PATH_XYQ_str );

// ---------------------------------------------------------------------- >>>>>
//      Button Initialization
// ---------------------------------------------------------------------- >>>>>

    SFML_button_XYQ myButtonA = SFML_button_XYQ();
    SFML_button_XYQ myButtonB = SFML_button_XYQ();
    myButtonB.disable();

    myButtonA.setWidth( 200 );      myButtonB.setWidth( 200 );
    myButtonA.setHeight( 50 );      myButtonB.setHeight( 50 );
    myButtonA.setX( 200 );          myButtonB.setX( 200 );
    myButtonA.setY( 150 );          myButtonB.setY( 300 );

    myButtonA.setTxtFont( font );
    myButtonB.setTxtFont( font );
    myButtonA.setTxtStr( "Button A" );
    myButtonB.setTxtStr( "Button B" );
    myButtonA.setTxtColor( 50, 50, 50, 255 );
    myButtonB.setTxtColor( 50, 50, 50, 255 );

    myButtonA.setUPTexture( button_img_np_FFN );
    myButtonB.setUPTexture( button_img_np_FFN );
    myButtonA.setPTexture( button_img_p_FFN );
    myButtonB.setPTexture( button_img_p_FFN );

    myButtonA.update();
    myButtonB.update();

// ---------------------------------------------------------------------- <<<<<

    bool tmpBool = false;

    // Integer keeping count how many times a button is pressed.
    int pres_cnt = 0;

    // Main loop
    while (window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

// ---------------------------------------------------------------------- >>>>>
//      Mouse (Left) Click Event
// ---------------------------------------------------------------------- >>>>>
            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if( myButtonA.pressButton( window ) ){
                        myButtonB.enable();
                    }
                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    if( myButtonA.releaseButton() ){
                        pres_cnt++;
                        myButtonA.setTxtStr( "Press Count: " + std::to_string( pres_cnt ) );
                        myButtonB.disable();
                    }
                }
            }
// ---------------------------------------------------------------------- <<<<<

        }

        myButtonA.update();

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the button A.
        myButtonA.beDrawn( window );
        // Draw the button B.
        myButtonB.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}




void tests::doButtonObjTest_3(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Button with Image Test.");

// ---------------------------------------------------------------------- >>>>>
//      Button Initialization
// ---------------------------------------------------------------------- >>>>>

    SFML_button_XYQ myButton = SFML_button_XYQ();

    myButton.setPColor( 25, 200, 50, 255 );
    myButton.setUPColor( 200, 20, 200, 255 );
    myButton.setWidth( 200 );
    myButton.setHeight( 50 );
    myButton.setX( 200 );
    myButton.setY( 150 );

    myButton.setTxtFont( SFMLUtilsXYQ::getArialFontPtr( RES_PATH_XYQ_str ) );
    myButton.setTxtStr( "Button 1" );
    myButton.setTxtColor( 200, 200, 200, 255 );

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string tar_img3_ffname = RES_PATH_XYQ_str + "/button1.png";


    myButton.setUPTexture( button_img_np_FFN );
    myButton.setPTexture( button_img_p_FFN );


    myButton.update();

// ---------------------------------------------------------------------- <<<<<

    // Main loop
    while (window.isOpen()) {
        
        sf::Event event;
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

// ---------------------------------------------------------------------- >>>>>
//      Mouse (Left) Click Event
// ---------------------------------------------------------------------- >>>>>
            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    myButton.pressButton( window );
                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    myButton.releaseButton();
                }
            }
// ---------------------------------------------------------------------- <<<<<

        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the button.
        myButton.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}



void tests::doButtonObjTest_2(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image Example");

// ---------------------------------------------------------------------- >>>>>
//      Button Initialization
// ---------------------------------------------------------------------- >>>>>

    SFML_button_XYQ myButton = SFML_button_XYQ();

    myButton.setPColor( 25, 200, 50, 255 );
    myButton.setUPColor( 200, 20, 200, 255 );
    myButton.setX( 200 );
    myButton.setY( 150 );

    myButton.setTxtFont( SFMLUtilsXYQ::getArialFontPtr( RES_PATH_XYQ_str ) );
    myButton.setTxtStr( "Start Game" );
    myButton.setTxtColor( 255, 255, 255, 255 );

    myButton.update();

// ---------------------------------------------------------------------- <<<<<

    

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

// ---------------------------------------------------------------------- >>>>>
//      Mouse (Left) Click Event
// ---------------------------------------------------------------------- >>>>>
            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    myButton.pressButton( window );
                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    myButton.releaseButton();
                }
            }
// ---------------------------------------------------------------------- <<<<<


        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the button.
        myButton.beDrawn( window );

        // Display what has been rendered to the window
        window.display();

    }

}



void tests::doButtonObjTest_1(){
    
    SFML_button_XYQ myBut = SFML_button_XYQ();

    myBut.setTxtFont( SFMLUtilsXYQ::getArialFont( RES_PATH_XYQ_str ) );
    const sf::Font tmp = myBut.getTxtFont();
    cout << "[Text Font: " << tmp.getInfo().family << "]" << endl;

    myBut.setWidth( 210 );
    cout << "[Width: " << myBut.getWidth() << "], ";
    myBut.setHeight( 60 );
    cout << "[Height: " << myBut.getHeight() << "]" << endl;
    
    myBut.setX( 10 );
    cout << "[X pos: " << myBut.getX() << "], ";
    myBut.setY( 12 );
    cout << "[Y pos: " << myBut.getY() << "]" << endl;

    myBut.setTxtStr( "Name An Item." );
    cout << "[Button text: \"" << myBut.getTxtStr() << "\"]" << endl;

    sf::Color upColor = myBut.getUPColor();
    cout << "[Button unpressed state color: red=" << (unsigned int) upColor.r << 
        ", green=" << (unsigned int) upColor.g << 
        ", blue=" << (unsigned int) upColor.b <<  
        ", opacity=" << (unsigned int) upColor.a << "]" << endl;


    //myBut.setUPColor( sf::Color::Blue );
    myBut.setUPColor( 10, 80, 200, 254 );
    upColor = myBut.getUPColor();
    cout << "[Button unpressed state color: red=" << (unsigned int) upColor.r << 
        ", green=" << (unsigned int) upColor.g << 
        ", blue=" << (unsigned int) upColor.b <<  
        ", opacity=" << (unsigned int) upColor.a << "]" << endl;

    myBut.setPColor( 11, 12, 13, 14 );
    sf::Color pColor = myBut.getPColor();
    cout << "[Button pressed state color: red=" << (unsigned int) pColor.r << 
        ", green=" << (unsigned int) pColor.g << 
        ", blue=" << (unsigned int) pColor.b <<  
        ", opacity=" << (unsigned int) pColor.a << "]" << endl;

}
