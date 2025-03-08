#ifndef SFML_utils_XYQ_H
#define SFML_utils_XYQ_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


namespace SFMLUtilsXYQ{

    /* 
    Function to check if a point is inside a rectangle
    */
    bool isMseOverRect(const sf::RectangleShape& button, const sf::RenderWindow& tarWind);


    /*
    Replace all instances of the string <pattern> located in the string <str> by the string <repl>.
    */
    void replAllStrPattern(std::string& str, const std::string& pattern, const std::string& repl);


    /*
    Obtain the Arial text font, given the correct directory location.
    */
    sf::Font getArialFont( std::string filePath );

    /*
    Obtain the Arial text font, given the correct directory location.
    */
    std::shared_ptr<sf::Font> getArialFontPtr( std::string filePath );

    /*
    Generate a texture object from the specified image full file name (FullPath/name.ext).
    Failure to load image file result in nullptr being returned.
    */
    std::shared_ptr<sf::Texture> genTexture( std::string fullFileName );

}

#endif // SFML_utils_XYQ_H