#include "SFML_button_XYQ.h"


/* 
An offset value to shift the position of the sprite slightly in the upper-left 
direction. Rescaling of the sprite will also compensate for the use of this offset 
(To ensure the rescaled sprite covers the base button rectangle closely but completely).
*/
const float SFML_button_XYQ::sprt_pos_offset = 1.0f;


SFML_button_XYQ::SFML_button_XYQ():
    SFML_obj_XYQ()
{

    // Initialize button press count (only counts when pressed AND released).
    pressCnt = 0;

    // Flags initialization.
    this->drawSprite = true;
    this->drawText = true;

    this->size = sf::Vector2f( 200, 50 );

    // Initialize the button's rectangle.
    butRect = sf::RectangleShape( size );
    pressed = false;
    buttonFlag = false;
    locked = false;

    // Initialize the image handling objects.
    this->upSprite = std::shared_ptr<sf::Sprite>( new sf::Sprite() );
    this->pSprite = std::shared_ptr<sf::Sprite>( new sf::Sprite() );
    this->upTexture = std::shared_ptr<sf::Texture>( new sf::Texture() );
    this->pTexture = std::shared_ptr<sf::Texture>( new sf::Texture() );
    // Initialize the sprite scaling factors.
    this->upSprtScale = sf::Vector2f(1,1);
    this->pSprtScale = sf::Vector2f(1,1);

    // Text object variables initialization.
    txtX = 0;   txtY = 0;
    txtSize = 24;
    txtStr = "I am button.";
    txtColor = sf::Color::Blue;
    
    // Perform the button update for the first time.
    this->update();

}


// ====================================================================== >>>>>
//      Button Functionalities
// ====================================================================== >>>>>

bool SFML_button_XYQ::canBePressed( const sf::RenderWindow& window ) const{

    bool isValid = this->enabled && !this->locked;
    isValid = isValid && !pressed;
    if( !isValid )
        {return isValid;}

    isValid = isValid && SFMLUtilsXYQ::isMseOverRect( this->butRect, window );
    isValid = isValid && window.hasFocus();
    return isValid;

}

bool SFML_button_XYQ::canBeReleased(){

    bool isValid = this->enabled;
    isValid = isValid && pressed;
    return isValid;

}

bool SFML_button_XYQ::pressButton( const sf::RenderWindow& window ){

    // Abort if button is not in condition to be pressed..
    if( !canBePressed( window ) ){
        return false;
    }
    
    this->pressed = true;
    this->butRect.setFillColor( this->pColor );

    return true;

}

bool SFML_button_XYQ::releaseButton(){
    
    // Abort if button is not in condition to be released.
    if( !canBeReleased() ){
        return false;
    }

    this->buttonFlag = !( this->buttonFlag );
    this->pressed = false;
    this->butRect.setFillColor( this->upColor );
    this->pressCnt++;

    return true;

}



void SFML_button_XYQ::update(){

    // Button position update.
    butRect.setPosition( this->position );
    butRect.setSize( size );

    // Button text content update.
    this->bTxt.setString( txtStr );
    this->bTxt.setFillColor( txtColor );
    this->bTxt.setFont( *txtFont );
    this->bTxt.setCharacterSize( txtSize );

    // Button text position update.
    sf::FloatRect butRectBox = butRect.getLocalBounds();
    sf::Vector2f butRectBoxDim = butRectBox.getSize();
    float b_center_X = position.x + butRectBoxDim.x/2.0f;
    float b_center_Y = position.y + butRectBoxDim.y/2.0f;
    this->bTxt.setPosition( b_center_X + this->txtX, b_center_Y + this->txtY );
    // Reset the text box's coordinate point of reference at its center.
    sf::FloatRect textRect = this->bTxt.getLocalBounds();
    bTxt.setOrigin(textRect.left + textRect.width/2.0f, 
        textRect.top + textRect.height/2.0f);

    // Button sprites update.
    upd_PB_sprite();
    upd_UPB_sprite();

    // Additional button modifiers depending on button state.
    if( this->pressed ){
        butRect.setFillColor( this->pColor );
    }else{
        butRect.setFillColor( this->upColor );
    }

}



void SFML_button_XYQ::upd_UPB_sprite(){

        
    // Reset the scaling factors to norm.
    upSprite->setScale(1,1);

    // Obtain the position and size info of the sprite.
    sf::FloatRect sprtFRect = upSprite->getGlobalBounds();
    // Obtain the position and size info of the button rectangle.
    sf::FloatRect buttFRect = this->butRect.getGlobalBounds();
    
    // Compute the scaling conversion factors necessary for the sprite to fit the rectangle.
    float x_conv_fact = ( buttFRect.width + 2*sprt_pos_offset )/sprtFRect.width;
    float y_conv_fact = ( buttFRect.height + 2*sprt_pos_offset )/sprtFRect.height;
    
    // Rescale the sprite.
    upSprite->setScale( x_conv_fact*upSprtScale.x, y_conv_fact*upSprtScale.y );

    // // Update the position.
    // upSprite->setPosition( this->getX() - sprt_pos_offset, 
    //     this->getY() - sprt_pos_offset );

    // Set the origin of the sprite at its center.
    upSprite->setOrigin( sprtFRect.width/2, sprtFRect.height/2 );
    // Put the sprite at the center of the rectangle.
    upSprite->setPosition( this->getX() + buttFRect.width/2, 
        this->getY() + buttFRect.height/2 );

}


void SFML_button_XYQ::upd_PB_sprite(){

    

    // Reset the scaling factors to norm.
    pSprite->setScale(1,1);

    // Obtain the position and size info of the sprite.
    sf::FloatRect sprtFRect = pSprite->getGlobalBounds();
    // Obtain the position and size info of the button rectangle.
    sf::FloatRect buttFRect = this->butRect.getGlobalBounds();

    // Compute the scaling conversion factors necessary for the sprite to fit the rectangle.
    float x_conv_fact = (buttFRect.width + 2*sprt_pos_offset)/sprtFRect.width;
    float y_conv_fact = (buttFRect.height + 2*sprt_pos_offset)/sprtFRect.height;
    
    // Rescale the sprite.
    pSprite->setScale( x_conv_fact*pSprtScale.x, y_conv_fact*pSprtScale.y );

    // Update the position.
    pSprite->setPosition( this->getX() - sprt_pos_offset, 
        this->getY() - sprt_pos_offset );

    // Set the origin of the sprite at its center.
    pSprite->setOrigin( sprtFRect.width/2, sprtFRect.height/2 );
    // Put the sprite at the center of the rectangle.
    pSprite->setPosition( this->getX() + buttFRect.width/2, 
        this->getY() + buttFRect.height/2 );


}

void SFML_button_XYQ::beDrawn( sf::RenderWindow& window ) const{

    if( !enabled )
        {return;}

    window.draw( this->butRect );

    
    if(drawSprite){
        if( this->pressed ){
            if( this->pSprite ){
                window.draw( *this->pSprite );
            }
        }else{
            if( this->upSprite ){
                window.draw( *this->upSprite );
            }
        }
    }

    if( drawText ){
        window.draw( this->bTxt );
    }

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Support Functions
// ====================================================================== >>>>>
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

const sf::RectangleShape SFML_button_XYQ::getRect() const{
    return this->butRect;
}

float SFML_button_XYQ::getWidth() const
    {return this->size.x ;}
void SFML_button_XYQ::setWidth( float bWidth )
    {this->size.x = bWidth;}

float SFML_button_XYQ::getHeight() const
    {return this->size.y;}
void SFML_button_XYQ::setHeight( float bHeight )
    {this->size.y = bHeight;}

/*
string SFML_button_XYQ::getStr() const
    {return this->bTxt.getString();}
void SFML_button_XYQ::setStr( string txtStr )
    { this->txtStr = txtStr; }
*/

sf::Color SFML_button_XYQ::getUPColor() const
    { return this->upColor; }
void SFML_button_XYQ::setUPColor( sf::Color upColor ){ 
    this->upColor = upColor; 
}
void SFML_button_XYQ::setUPColor( unsigned int red, unsigned int green, 
    unsigned int blue, unsigned int alpha ){ 
    this->upColor = sf::Color( sf::Uint8(red), sf::Uint8(green), 
        sf::Uint8(blue), sf::Uint8(alpha) ); 
}

sf::Color SFML_button_XYQ::getPColor() const
    { return this->pColor; }
void SFML_button_XYQ::setPColor( sf::Color pColor ){ 
    this->pColor = pColor; 
}
void SFML_button_XYQ::setPColor( unsigned int red, unsigned int green, 
    unsigned int blue, unsigned int alpha ){ 
    this->pColor = sf::Color( sf::Uint8(red), sf::Uint8(green), 
        sf::Uint8(blue), sf::Uint8(alpha) );
}


void SFML_button_XYQ::setUPTexture( string imgFFName ){

    if ( !( upTexture->loadFromFile( imgFFName ) ) ) { 
        std::cerr << "Error loading image file!\n";
        return;
    }

    // Sprite adjustment.
    upSprite->setTexture( *upTexture, true );
    // Update the sprite.
    this->upd_UPB_sprite();

}
void SFML_button_XYQ::setUPTexture( shared_ptr<sf::Texture> upTexture ){

    // Check for empty pointer.
    if( !upTexture ){
        return;
    }

    this->upTexture = upTexture;
    // Sprite adjustment.
    upSprite->setTexture( *upTexture, true );
    // Update the sprite.
    this->upd_UPB_sprite();
}

void SFML_button_XYQ::setPTexture( string imgFFName ){

    if ( !( pTexture->loadFromFile( imgFFName ) ) ) { 
        std::cerr << "Error loading image file!\n";
        return;
    }

    // Sprite adjustment.
    pSprite->setTexture( *pTexture, true );
    // Update the sprite.
    this->upd_PB_sprite();

}
void SFML_button_XYQ::setPTexture( shared_ptr<sf::Texture> pTexture ){

    // Check for empty pointer.
    if( !pTexture ){
        return;
    }

    this->pTexture = pTexture;
    pSprite->setTexture( *pTexture, true );
    // Update the sprite.
    this->upd_PB_sprite();

}


void SFML_button_XYQ::setUpSprtScale( float x, float y ){
    this->upSprtScale.x = x;
    this->upSprtScale.y = y;
}
void SFML_button_XYQ::setUpSprtScale( sf::Vector2f upSprtScale ){
    this->upSprtScale = upSprtScale;
}
void SFML_button_XYQ::setPSprtScale( float x, float y ){
    this->pSprtScale.x = x;
    this->pSprtScale.y = y;
}
void SFML_button_XYQ::setPSprtScale( sf::Vector2f pSprtScale ){
    this->pSprtScale = pSprtScale;
}


bool SFML_button_XYQ::isPressed() const
    {return this->pressed;}

void SFML_button_XYQ::enableSprite()
    {this->drawSprite = true;}
void SFML_button_XYQ::disableSprite()
    {this->drawSprite = false;}
void SFML_button_XYQ::enableText()
    {this->drawText = true;}
void SFML_button_XYQ::disableText()
    {this->drawText = false;}


bool SFML_button_XYQ::getButtonFlag() const
    {return this->buttonFlag;}
void SFML_button_XYQ::setButtonFlag( bool buttonFlag )
    {this->buttonFlag = buttonFlag;}

// Determine whether the button is locked or not.
bool SFML_button_XYQ::isLocked() const
    {return this->locked;}
// Lock the button.
void SFML_button_XYQ::lock()
    {this->locked = true;}
// Unlock the button.
void SFML_button_XYQ::unlock()
    {this->locked = false;}

unsigned int SFML_button_XYQ::getPressCnt() const
    {return this->pressCnt;}
void SFML_button_XYQ::setPressCnt( unsigned int pressCnt )
    {this->pressCnt = pressCnt;}

const sf::Font SFML_button_XYQ::getTxtFont() const{
    const sf::Font tmp = *this->txtFont;
    return tmp;
}
const shared_ptr<sf::Font> SFML_button_XYQ::getTxtFontPtr() const{
    const shared_ptr<sf::Font> tmp = this->txtFont;
    return tmp;
}
void SFML_button_XYQ::setTxtFont( sf::Font txtFont ){
    this->txtFont = shared_ptr<sf::Font>( new sf::Font(txtFont) );
}
void SFML_button_XYQ::setTxtFont( shared_ptr<sf::Font> txtFont ){
    this->txtFont = txtFont;
}

string SFML_button_XYQ::getTxtStr() const
    {return this->txtStr;}
void SFML_button_XYQ::setTxtStr( string txtStr ){
    this->txtStr = txtStr;
}

sf::Color SFML_button_XYQ::getTxtColor() const
    {return this->txtColor;}
void SFML_button_XYQ::setTxtColor( sf::Color txtColor )
    {this->txtColor = txtColor;}
void SFML_button_XYQ::setTxtColor( unsigned int red, unsigned int green, 
    unsigned int blue, unsigned int alpha ){
    this->txtColor = sf::Color( red, green, blue, alpha );
}

float SFML_button_XYQ::getTxtX() const
    {return this->txtX;}
void SFML_button_XYQ::setTxtX( float txtX )
    {this->txtX = txtX;}
float SFML_button_XYQ::getTxtY() const
    {return this->txtY;}
void SFML_button_XYQ::setTxtY( float txtY )
    {this->txtY = txtY;}
void SFML_button_XYQ::setTxtPos( float txtX, float txtY )
    {this->txtX = txtX; this->txtY = txtY;}

// ====================================================================== <<<<<



