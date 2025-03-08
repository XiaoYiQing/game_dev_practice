#include "SFML_TxtBox_XYQ.h"




// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

SFML_TxtBox_XYQ::SFML_TxtBox_XYQ( sf::Font txtFont, string txtStr ): 
    SFML_obj_XYQ()
{

    this->txtFont = shared_ptr<sf::Font>( new sf::Font( txtFont ) );
  
    // Initialize text.
    //txt.setFont( txtFont );
    txt.setPosition( this->position.x, this->position.y );
    //txt.setFont( *txtFont );
    txt.setString( txtStr );
    txt.setFillColor( sf::Color::Blue );
    txt.setCharacterSize( 24 );

    // Initialize flags.

    // Update the text box.
    this->update();

}

SFML_TxtBox_XYQ::SFML_TxtBox_XYQ( shared_ptr<sf::Font> txtFont, 
        string txtStr )
{
    this->txtFont = txtFont;
  
    // Initialize text.
    //txt.setFont( txtFont );
    txt.setPosition( this->position.x, this->position.y );
    //txt.setFont( *txtFont );
    txt.setString( txtStr );
    txt.setFillColor( sf::Color::Blue );
    txt.setCharacterSize( 24 );

    // Initialize flags.

    // Update the text box.
    this->update();
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Functionalities
// ====================================================================== >>>>>


void SFML_TxtBox_XYQ::update(){

// ---------------------------------------------------------------------- >>>>>
//      Text Object Updates (Non-Positional)
// ---------------------------------------------------------------------- >>>>>
    // Update the font.
    txt.setFont( *this->txtFont );

    // Obtain the size of the text.
    float charSize = (float) txt.getCharacterSize();

    this->upd_lineBreak();
// ---------------------------------------------------------------------- <<<<<

    // Obtain the dimensions of the text object.
    sf::FloatRect txtGlobDim = txt.getGlobalBounds();
    sf::Vector2f txtGlobPos = txtGlobDim.getPosition();
    sf::Vector2f txtGlobSize = txtGlobDim.getSize();
    sf::Vector2f txtPos = txt.getPosition();
    // Compute the text object offset from the intended position to the global true position.
    sf::Vector2f txtPosOffset = txtGlobPos - txtPos;
    txtPosOffset.x = abs( txtPosOffset.x );
    txtPosOffset.y = abs( txtPosOffset.y );

    // Determine the margins.
    // ( 0=up, 1=down, 2=left, 3=right )
    std::unique_ptr<float[]> margArr( new float[4] );
    for (size_t i = 0; i < 4; i++){
        margArr[i] = (useBoxMargFact[i]) ? boxMargFact[i]*charSize : boxMargAmt[i];
    }

    // Compute the size of the rectangle.
    float rectWidth = txtGlobDim.width + margArr[2] + margArr[3];
    float rectHeight = txtGlobDim.height + margArr[0] + margArr[1];

    // Update the rectangle's properties except its position.
    box.setSize( sf::Vector2f( rectWidth, rectHeight ) );
    box.setFillColor( boxColor );
    box.setOutlineThickness( boxOutlThickness );
    box.setOutlineColor( boxOutlColor );

    // Update the text object position.
    txt.setPosition( position.x - txtPosOffset.x + margArr[2] + boxOutlThickness, 
        position.y - txtPosOffset.y + margArr[0] + boxOutlThickness );
    // Update the box object position.
    box.setPosition( position.x + boxOutlThickness, 
        position.y + boxOutlThickness );

}


void SFML_TxtBox_XYQ::upd_lineBreak(){

    string origStr = this->txt.getString();
    // The modified string with line breaks.
    string newStr;
    
    // Delete all existing line breaks and carriage returns within the text string.
    //origStr.erase( std::remove( origStr.begin(), origStr.end(), '\n' ), origStr.end() );
    //origStr.erase( std::remove( origStr.begin(), origStr.end(), '\r' ), origStr.end() );

    // Replace all instances of line break.
    SFMLUtilsXYQ::replAllStrPattern( origStr, "\n", " " );

    // Obtain an "iterator" which goes through each word in the string.
    std::istringstream words(origStr);
    // Define the variable to be assigned the current word being 'read'.
    string word;
    // Define the current line candidate.
    string currLine = "";

    // Create a dummy text object with the same font and character size to test 
    // line length.
    sf::Text testTxt;
    testTxt.setFont( *(this->txt.getFont()) );
    testTxt.setCharacterSize( this->txt.getCharacterSize() );

    // Create tracker of current line length.
    float currLineLen = 0.;

    // Parse through the string word by word.
    while( words >> word ){
        
        if( currLineLen > this->txtLenLim ){

            // Append the current line candidate to the new string along with a line break.
            newStr += currLine + "\n";
            // Clear the current line.
            currLine = "";

        }

        // Temporary line candidate appended with space and the next word.
        currLine = currLine + ( currLine.empty() ? "" : " " ) + word;
        // Set the temporary string into the test text object.
        testTxt.setString( currLine );

        // Obtain the width of the current line.
        currLineLen = testTxt.getLocalBounds().width;

    }
    // Append leftover line.
    newStr += currLine;

    // Update the official text object string with the newly generated string.
    this->txt.setString( newStr );

}

 
void SFML_TxtBox_XYQ::beDrawn( sf::RenderWindow& window ) const{

    window.draw( box );

    window.draw( txt );

}


// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

void SFML_TxtBox_XYQ::setTxtLenLim( float txtLenLim ){
    if( txtLenLim <= 0 ){
        throw std::invalid_argument( "Text length must be positive." );
    }else{
        this->txtLenLim = txtLenLim;
    }
}
float SFML_TxtBox_XYQ::getTxtLenLim() const
    {return this->txtLenLim;}

const sf::Font SFML_TxtBox_XYQ::getTxtFont() const{
    const sf::Font tmp = *this->txtFont;
    return tmp;
}
const shared_ptr<sf::Font> SFML_TxtBox_XYQ::getTxtFontPtr() const{
    const shared_ptr<sf::Font> tmp = this->txtFont;
    return tmp;
}
void SFML_TxtBox_XYQ::setTxtFont( const sf::Font font ){
    this->txtFont = shared_ptr<sf::Font>( new sf::Font(font) );
}
void SFML_TxtBox_XYQ::setTxtFont( const shared_ptr<sf::Font> txtFont ){
    this->txtFont = txtFont;
}

const sf::RectangleShape* SFML_TxtBox_XYQ::getBox() const{
    return &this->box;
}

const float* SFML_TxtBox_XYQ::getBoxMargFact() const{
    return this->boxMargFact;
}
void SFML_TxtBox_XYQ::setBoxMargFact( unsigned int directIdx, float value ){
    if( directIdx >= 4 ){
        throw std::range_error( "The direction index must be an integer in the range [0, 3]" );
        return;
    }
    this->boxMargFact[directIdx] = value;
}

const float* SFML_TxtBox_XYQ::getBoxMargAmt() const{
    return this->boxMargAmt;
}
void SFML_TxtBox_XYQ::setBoxMargAmt( unsigned int directIdx, float value ){
    if( directIdx >= 4 ){
        throw std::range_error( "The direction index must be an integer in the range [0, 3]" );
        return;
    }
    this->boxMargAmt[directIdx] = value;
}

const bool* SFML_TxtBox_XYQ::getUseBoxMargFact() const
    {return this->useBoxMargFact;}
void SFML_TxtBox_XYQ::setUseBoxMargFact( unsigned int directIdx, bool value )
    {this->useBoxMargFact[ directIdx ] = value;}
void SFML_TxtBox_XYQ::setUseBoxMargFact( bool up, bool down, bool left, bool right ){
    this->useBoxMargFact[0] = up;
    this->useBoxMargFact[1] = down;
    this->useBoxMargFact[2] = left;
    this->useBoxMargFact[3] = right;
}

sf::Color SFML_TxtBox_XYQ::getBoxFillColor() const
    {return this->boxColor;}
void SFML_TxtBox_XYQ::setBoxFillColor( sf::Color boxColor )
    {this->boxColor = boxColor;}

sf::Color SFML_TxtBox_XYQ::getBoxOutlineColor() const
    {return this->boxColor;}
void SFML_TxtBox_XYQ::setBoxOutlineColor( sf::Color boxOutlColor )
    {this->boxOutlColor = boxOutlColor;}

float SFML_TxtBox_XYQ::getBoxOutlThick() const
    {return this->boxOutlThickness;}
void SFML_TxtBox_XYQ::setBoxOutlThick( float boxOutlThickness )
    {this->boxOutlThickness = boxOutlThickness;}


void SFML_TxtBox_XYQ::setBoxHeight( float bHeight ){
    
    this->setUseBoxMargFact( 0, false ); // Upper margin using direct value.
    this->setUseBoxMargFact( 1, false ); // Lower margin using direct value.

    // Obtain the leftover height without the box outline.
    float leftOverHeight = bHeight - 2*( this->getBoxOutlThick() );

    // Deduct the height of the text object.
    sf::FloatRect txtGlobBnd = this->txt.getGlobalBounds();
    leftOverHeight -= txtGlobBnd.height;

    if( leftOverHeight <= 0 ){
        throw std::range_error( "Specified text box height is insufficient to accomodate the text itself. ABORT." );
        return;
    }else{
        // Put the text in the middle point of the text box.
        boxMargAmt[0] = leftOverHeight/2;
        boxMargAmt[1] = leftOverHeight/2;
    }

}

// ====================================================================== <<<<<




// DONE: When eliminating line breaks from the starting string, the resulting filtered string
// may have words merged together as no space is used to replace the line break.
// Use another way of eliminating the line breaks.