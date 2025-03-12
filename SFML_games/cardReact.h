#ifndef CARDREACT_H
#define CARDREACT_H


#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <string>
#include <vector>

#include <chrono>

#include "numUtils.h"

using namespace std;



namespace gameEngine{

/*
This is a reaction game through picking cards.
One card is faced down at the beginning of the game.
All possible cards this hidden card can be are displayed by its side.
After a countdown, the faced down card is revealed, and the player must select
the nearby matching card to the revealed card as fast as possible.
*/
class cardReact{

public:

// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>
    
    cardReact( int possCardCnt = 8 );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    int getMainCardID() const;
    void setMainCardID( int mainCardID );

    int getPossCardID( int vect_idx ) const;
    void setPossCardID( int vect_idx, int newID );

    // Obtain the amount of time elapsed since the start of the game in milliseconds.
    long long getElapsedMS();

    /*
    Determines if the main card is revealed.
    */
    bool isMainCardRevealed();

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Functionality (Public)
// ====================================================================== >>>>>

    /*
    Reset the state of the game.
    */
    void reset();

    /*
    Start the game.
    Triggers the countdown.
    */
    void start();

    /*
    Select the card which matches the hidden card.
    Card selection will fail (false) if countdown has not yet finished yet.
    Card selection will fail (false) if wrong card is picked.
    */
    bool selectCard( int cardVect_idx );

// ====================================================================== <<<<<



protected:

// ====================================================================== >>>>>
//      Game Functionality (Protected)
// ====================================================================== >>>>>

    /*
    Randomly assign the main card.
    */
    void pickMainCard();

// ====================================================================== <<<<<


    

    /*
    The ID of the main card.
    */
    int mainCardID;

    
    // Number of possible cards.
    int possCardCnt;
    /*
    The integers representing the IDs of the possible cards.
    */
    vector<int> possCardID_vect;

    /*
    The amount of time in milliseconds for the count down before the main card is
    revealed.
    */
    long long cntDownStartT;

    chrono::steady_clock::time_point startTimePt;
    chrono::steady_clock::time_point lastTimePt;

private:


};

}

#endif  
