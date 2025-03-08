#include "SFML_utils_XYQ.h"


bool SFMLUtilsXYQ::isMseOverRect(const sf::RectangleShape& button, const sf::RenderWindow& tarWind ) {
    return button.getGlobalBounds().contains(
        static_cast<sf::Vector2f>( sf::Mouse::getPosition(tarWind) ));
}



void SFMLUtilsXYQ::replAllStrPattern(std::string& str, const std::string& pattern, const std::string& repl) {
    size_t startPos = 0;
    while ( (startPos = str.find( pattern, startPos ) ) != std::string::npos) {
        str.replace(startPos, pattern.length(), repl);
        startPos += repl.length(); // Move past the replaced content to avoid infinite loop
    }
}

sf::Font SFMLUtilsXYQ::getArialFont( std::string filePath ){
    // The arial ttf full file name.
    std::string arial_ttf_ffname = filePath + "/Arial.ttf";
    // Load a font.
    sf::Font font;
    if (!font.loadFromFile( arial_ttf_ffname )) { 
        std::cerr << "Error loading font\n";
        return font;
    }
    return font;
}


std::shared_ptr<sf::Font> SFMLUtilsXYQ::getArialFontPtr( std::string filePath ){

    // The arial ttf full file name.
    std::string arial_ttf_ffname = filePath + "/Arial.ttf";
    // Load a font.
    std::shared_ptr<sf::Font> font = std::shared_ptr<sf::Font>( new sf::Font() );
    if (!font->loadFromFile( arial_ttf_ffname )) { 
        std::cerr << "Error loading font\n";
        return font;
    }
    return font;

}


std::shared_ptr<sf::Texture> SFMLUtilsXYQ::genTexture( std::string fullFileName ){

    std::shared_ptr<sf::Texture> newTexture = std::shared_ptr<sf::Texture>( new sf::Texture() );
    if ( !( newTexture->loadFromFile( fullFileName ) ) ) { 
        std::cerr << "Error loading image file!\n";
        return nullptr;
    }
    return newTexture;

}
