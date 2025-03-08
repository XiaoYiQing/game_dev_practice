#include "window_test.h"



/*
Perform a SFML window test. Really just testing out various functionalities 
of the SFML toolbox. Each index points to a test that focus on a few
SFML features.
*/
void tests::do_wind_test( int test_idx ){

    switch( test_idx ){
    case 1:
        window_test_1();
        break;
    case 2:
        window_test_2();
        break;
    case 3:
        window_test_3();
        break;
    case 4:
        window_test_4();
        break;
    case 5:
        window_test_5();
        break;
    case 6:
        window_test_6();
        break;
    default:
        cout << "Invalid test index." << endl;
        break;
    };

}







void tests::window_test_6(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image Example");

// ---------------------------------------------------------------------- >>>>>
//      External Resource Loading
// ---------------------------------------------------------------------- >>>>>

    // The arial ttf full file name.
    string arial_ttf_ffname = RES_PATH_XYQ_str + "/Arial.ttf";
    // Load a font.
    sf::Font font;
    if (!font.loadFromFile( arial_ttf_ffname )) { 
        std::cerr << "Error loading font\n";
        return;
    }

    // Create a texture to hold the image
    string tar_img1_ffname = RES_PATH_XYQ_str + "/funny_img_1.jpg";
    sf::Texture texture;
    if (!texture.loadFromFile( tar_img1_ffname )) { 
        std::cerr << "Error loading image file!\n";
        return;
    }

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Sprite Initialization
// ---------------------------------------------------------------------- >>>>>
    
    // Create a sprite to display the texture
    sf::Sprite sprite;
    float fig1_pos[2] = { 100, 100 };
    sprite.setTexture(texture);
    sprite.setPosition( fig1_pos[0], fig1_pos[1] ); // Position the sprite on the screen
    float fig1_sizes[2] = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height };

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Button Initialization
// ---------------------------------------------------------------------- >>>>>

    // Define the default color.
    sf::Color defaultColor = sf::Color::Green;
    // Define a depressed color.
    sf::Color depressedColor = sf::Color::Transparent;


    // Create a button (rectangle)
    sf::RectangleShape button1(sf::Vector2f( fig1_sizes[0], fig1_sizes[1] ));
    button1.setFillColor( defaultColor );
    button1.setPosition( fig1_pos[0], fig1_pos[1] ); // Centering the button in the window
    // Define boolean for keeping track whether button is pressed.
    bool pressed = false;
    bool button_flag = false;

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
                    // Check if the mouse is over the button
                    if ( SFMLUtilsXYQ::isMseOverRect(button1, window)) {
                        
                        pressed = true;

                        if( button_flag ){
                            button1.setFillColor( defaultColor );
                            button_flag = false;
                        }else{
                            button1.setFillColor( depressedColor );
                            button_flag = true;
                        }

                    }
                }
            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    if( pressed ){
                        pressed = false;
                    }
                }
            }
// ---------------------------------------------------------------------- <<<<<


        }

        // Clear the window.
        window.clear(sf::Color::Black); // Background color

        // Draw the sprite.
        window.draw(sprite);
        // Draw the button.
        window.draw(button1);

        // Display what has been rendered to the window
        window.display();

    }

}



void tests::window_test_5(){
    
    // The window object representation.
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Input");

// ---------------------------------------------------------------------- >>>>>
//      Text Font Selection
// ---------------------------------------------------------------------- >>>>>

    // The arial ttf full file name.
    string arial_ttf_ffname = RES_PATH_XYQ_str + "/Arial.ttf";
    // Load a font
    sf::Font font;
    if (!font.loadFromFile( arial_ttf_ffname )) { // replace with your font file path
        std::cerr << "Error loading font\n";
        return;
    }

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Text Object Initialization
// ---------------------------------------------------------------------- >>>>>

    // Text object position.
    float txt_pos[2] = { 0, 0 };
    unsigned int textCharSize = 30;

    // Configure the text.
    sf::Text text;
    sf::Color textColor = sf::Color::Red;
    text.setFont(font);
    text.setCharacterSize( textCharSize );
    text.setFillColor( textColor );
    text.setPosition( txt_pos[0], txt_pos[1] );
    // Determine the maximum vertical size of the text using dummy string.
    text.setString( "jqJM" );
    float text_max_height = text.getLocalBounds().height;
    // Delete the dummy string.
    text.setString( "" );

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Text Box Initialization
// ---------------------------------------------------------------------- >>>>>

    // Text box left indent amount (For the text).
    float tb_Lind = ( (float) textCharSize )/8;
    // Text box right indent amount (For the text).
    float tb_RInd = ( (float) 1.5 ) * tb_Lind;
    // Textbox lower bound compensating extension.
    float tb_lb_cp_ext = ( (float) textCharSize )/3;    
    // Text box position.
    float tb_pos[2] = { 100, 100 };
    // Text box dimensions.
    float tb_dim[2] = { 400, text_max_height + tb_lb_cp_ext };

    // Configure the text box.

    sf::Color textBoxColor = sf::Color::White;
    sf::Color textBoxBorderColor = sf::Color::Magenta;
    float textBoxThickness = 2;
    // The text box object.
    sf::RectangleShape textBox(sf::Vector2f( tb_dim[0], tb_dim[1] ));
    textBox.setFillColor( textBoxColor );
    textBox.setOutlineColor( textBoxBorderColor );
    textBox.setOutlineThickness( textBoxThickness );
    textBox.setPosition( tb_pos[0], tb_pos[1] ); 

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Text and Text Box Objects Interdependencies Adjustment
// ---------------------------------------------------------------------- >>>>>

    // Relative horizontal position of text with respect to box.
    txt_pos[0] = textBox.getPosition().x + tb_Lind;
    // Relative vertical position of text with respect to box.
    txt_pos[1] = textBox.getPosition().y;
    // Update the text position.
    text.setPosition( txt_pos[0], txt_pos[1] );

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Text Box Cursor Initialization
// ---------------------------------------------------------------------- >>>>>

    // Cursor object to indicate the text box is in focus and where the next 
    // user inputted character will appear.
    sf::RectangleShape cursor;
    // Configure the cursor
    cursor.setSize(sf::Vector2f( 1, (float) textCharSize ));
    cursor.setFillColor( textColor );
    // Text box in focus flag.
    bool hasFocus = false;
    // Cursor's horizontal indentation w.r.t. the text box.
    float cursorHorInd = 0.05f*textCharSize;
    // Cursor's vertical indentation w.r.t. the text box.
    float cursorVerInd = 0.15f*textCharSize;

    // Clock to assist in the cursor's blinking effect.
    sf::Clock cursorClock;
    // Cursor's blinking interval time.
    float cursorBlkInterv = 0.5;
    // Cursor's blinking flag.
    bool showCursor = true;

// ---------------------------------------------------------------------- <<<<<


    std::string inputString;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }

            // Mouse click event
            if( event.type == sf::Event::MouseButtonPressed ){
                // Check if the click is within the text box
                if (textBox.getGlobalBounds().contains(
                        window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    hasFocus = true;
                } else {
                    hasFocus = false;
                }
            }

            // Deal with text entered event.
            if (event.type == sf::Event::TextEntered && hasFocus) {
                if (event.text.unicode < 128) { // Ensure it's an ASCII character
                    if (event.text.unicode == '\b') {
                        // Handle backspace
                        if (!inputString.empty()) {
                            inputString.pop_back();
                        }
                    } else {
                        
                        // Create a temporary string with the characterappended at the end.
                        std::string testString = inputString + static_cast<char>(event.text.unicode);
                        // Put the test string in the text area.
                        text.setString(testString);
                        // Only update the true text string with the temporary string if the test
                        // string meets the text box boundary condition.
                        if( text.getLocalBounds().width < textBox.getSize().x - tb_RInd ){
                            inputString = testString;
                        }

                    }
                }
            }

        }

// ---------------------------------------------------------------------- >>>>>
//      Window's Variables Update
// ---------------------------------------------------------------------- >>>>>

        // Update the text to be displayed
        text.setString(inputString);

        // Update the cursor visibility
        if (cursorClock.getElapsedTime().asSeconds() >= cursorBlkInterv) {
            showCursor = !showCursor;
            cursorClock.restart();
        }
        // Position the cursor at the end of the text
        if (hasFocus) {
            cursor.setPosition(text.getGlobalBounds().left + 
                text.getGlobalBounds().width + cursorHorInd, 
                text.getPosition().y + cursorVerInd );
        }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Window's Graphic Update
// ---------------------------------------------------------------------- >>>>>

        // Clear the window
        window.clear( sf::Color::Blue );
        // Draw the text box.
        window.draw( textBox );
        // Draw the text.
        window.draw( text );

        // Draw the cursor if it should be visible.
        if ( hasFocus && showCursor ) {
            window.draw(cursor);
        }

        // Display the window contents
        window.display();

// ---------------------------------------------------------------------- <<<<<


    }

}


void tests::window_test_4(){

    // Create a window.
    unsigned int wind_dim[2] = { 800, 600 };
    auto window = sf::RenderWindow(sf::VideoMode(wind_dim[0], wind_dim[1]), 
        "Depressing Button Example");
    window.setFramerateLimit(60);

    // The arial ttf full file name.
    string arial_ttf_ffname = RES_PATH_XYQ_str + "/Arial.ttf";

    // Load a font
    sf::Font font;
    if (!font.loadFromFile( arial_ttf_ffname )) { // replace with your font file path
        std::cerr << "Error loading font\n";
        return;
    }

    // First text object.
    sf::Text text1;
    text1.setFont(font); // Set the font.
    text1.setString("Hello, SFML!"); // Set the text string
    text1.setCharacterSize(50); // Set character size
    text1.setFillColor(sf::Color::White); // Set text color
    text1.setStyle(sf::Text::Bold); // Optional: set text style
    text1.setPosition( 100, 100 );   // Indicate the location of the upper left corner of the text box.

    // Second text object.
    sf::Text text2;
    float txt2_pos_orig[2] = { 100, 110 };
    float txt2_pos_alt[2] = { 100, 200 };
    text2.setFont(font); // Set the font.
    text2.setString("Bad Placement!"); // Set the text string
    text2.setCharacterSize(50); // Set character size
    text2.setFillColor(sf::Color::White); // Set text color
    text2.setStyle(sf::Text::Bold); // Optional: set text style
    text2.setPosition( txt2_pos_orig[0], txt2_pos_orig[1] );   // Indicate the location of the upper left corner of the text box.


    // Define the default color.
    sf::Color defaultColor = sf::Color::Green;
    // Define a depressed color.
    sf::Color depressedColor = sf::Color::Blue;

    // Create a button (rectangle)
    sf::RectangleShape button1(sf::Vector2f(200, 50));
    button1.setFillColor( defaultColor );
    button1.setPosition(400, 300); // Centering the button in the window
    // Define boolean for keeping track whether button is pressed.
    bool pressed = false;
    bool button_flag = false;

    // Define the text that is to appear on the button.
    sf::Text button1_txt;
    button1_txt.setFont(font);
    button1_txt.setString("Click Me!");
    button1_txt.setCharacterSize(24);
    button1_txt.setFillColor(sf::Color::Red);
    // Center the text on the button
    sf::FloatRect textRect = button1_txt.getLocalBounds();
    // Reset the point of reference of the button text box at its center.
    button1_txt.setOrigin(textRect.left + textRect.width/2.0f, 
        textRect.top + textRect.height/2.0f);
    // Set the position of the button text box at the center of the target button.
    button1_txt.setPosition(button1.getPosition().x + button1.getSize().x/2.0f, 
                           button1.getPosition().y + button1.getSize().y/2.0f);

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Prevent the window from being resized
            if (event.type == sf::Event::Resized) {
                // Reset to fixed size
                window.setSize(sf::Vector2u(wind_dim[0], wind_dim[1]));
            }

            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse is over the button
                    if ( SFMLUtilsXYQ::isMseOverRect(button1, window) ) {
                        button1.setFillColor( depressedColor );
                        pressed = true;

                        // Perform placement switch of the target text box.
                        if( button_flag ){
                            text2.setPosition( txt2_pos_orig[0], txt2_pos_orig[1] );
                            text2.setString( "Bad Placement!" );
                            button_flag = false;
                        }else{
                            text2.setPosition( txt2_pos_alt[0], txt2_pos_alt[1] );
                            text2.setString( "Good Placement!" );
                            button_flag = true;
                        }
                    }
                }

            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    if( pressed ){
                        button1.setFillColor( defaultColor );
                        std::cout << "Button Clicked!" << std::endl;
                        pressed = false;
                    }
                }
            }
        }

        // Clear the window
        window.clear();
        
        // Draw text
        window.draw(text1);
        window.draw(text2);
        
        // Draw the button.
        window.draw( button1 );
        window.draw( button1_txt );

        // Display everything
        window.display();
    }


}



void tests::window_test_3(){
    
    // Create a window.
    unsigned int wind_dim[2] = { 800, 600 };
    auto window = sf::RenderWindow(sf::VideoMode(wind_dim[0], wind_dim[1]), "Depressing Button Example");
    window.setFramerateLimit(60);

    // Define the default color.
    sf::Color defaultColor = sf::Color::Green;
    // Define a depressed color.
    sf::Color depressedColor = sf::Color::Blue;

    // Create a button (rectangle)
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor( defaultColor );
    button.setPosition(400, 300); // Centering the button in the window

    

    // Define boolean for keeping track whether button is pressed.
    bool pressed = false;

    // Window drawing.
    while (window.isOpen())
    {
        // Events functionality definition.
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            // Standard close event.
            if (event.type == sf::Event::Closed){
                window.close();
            }
            
            // Prevent the window from being resized
            if (event.type == sf::Event::Resized) {
                // Reset to fixed size
                window.setSize(sf::Vector2u(wind_dim[0], wind_dim[1]));
            }

            // Mouse pressed event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse is over the button
                    if ( SFMLUtilsXYQ::isMseOverRect(button, window) ) {
                        button.setFillColor( depressedColor );
                        pressed = true;
                    }
                }

            }

            // Mouse released event.
            if (event.type == sf::Event::MouseButtonReleased){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    if( pressed ){
                        button.setFillColor( defaultColor );
                        std::cout << "Button Clicked!" << std::endl;
                        pressed = false;
                    }
                }
            }

        }

        // Clear the window.
        window.clear( sf::Color::Black );

        // Draw the button.
        window.draw( button );

        // Display window contents
        window.display();

    }

}


void tests::window_test_2(){

    // Create a window with title "Button Example"
    auto window = sf::RenderWindow({800, 600}, "Button Example");
    window.setFramerateLimit(60);

    // Create a button (rectangle)
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Green);
    button.setPosition(400, 300); // Centering the button in the window

    // Window drawing.
    while (window.isOpen())
    {
        // Events functionality definition.
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            // Standard close event.
            if (event.type == sf::Event::Closed){
                window.close();
            }
            
            // Mouse click event.
            if (event.type == sf::Event::MouseButtonPressed) {
                // Specific left click event.
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse is over the button
                    if ( SFMLUtilsXYQ::isMseOverRect(button, window) ) {
                        std::cout << "Button Clicked!" << std::endl; // Simulate button action
                    }
                }

            }
        }

        // Clear the window.
        window.clear( sf::Color::Black );

        // Draw the button.
        window.draw( button );

        // Display window contents
        window.display();

    }

}

void tests::window_test_1(){

    auto window = sf::RenderWindow({800u, 600u}, "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    
        window.clear();
        window.display();
    }

}
