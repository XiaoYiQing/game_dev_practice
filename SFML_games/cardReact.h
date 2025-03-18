#ifndef CARDREACT_H
#define CARDREACT_H


#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <string>
#include <thread>
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
//      Class Enum "CRG_STATE" Help Functions
// ====================================================================== >>>>>

    /*
    Enum representing the states the game can be in.
    */
    enum class CRG_STATE{ UNSTARTED, ONGOING, WIN, LOSS };

    // The number of enum entries in the enum "CRG_STATE" (Uses magic enum).
    const static int CRG_STATE_Count = (int) magic_enum::enum_count<CRG_STATE>();
    // Obtain the string of the target enum case (Uses magic enum).
    static string get_CRG_STATE_Str( CRG_STATE tar_CRG_STATE );
    // Obtain the enum matching the enum integer index.
    static CRG_STATE get_CRG_STATE_AtIdx( int idx );

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>
    
    /*
    Constructor for the card react game.
    > possCardCnt = number of possible cards.
    > cntDownT = countdown duration time (ms) before card is revealed following a game start.
    */
    cardReact( int possCardCnt = 8, long long cntDownT = 3000 );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    int getMainCardID() const;
    void setMainCardID( int mainCardID );

    // Obtain the amount of time (ms) elapsed since the start of the game.
    long long getElapsedMS() const;

    /* 
    Obtain the amount of time (ms) elapsed between the card reveal time and 
    the time a card has been picked.
    A real time is returned only when the game is finished (win/loss), otherwise
    -1 is returned.
    */
    long long getPickCardMS() const;

    /*
    Obtain the countdown time amount (Before a user card pick can be registered).
    */
    long long getCountDownMS() const;

    // Determines if the main card is revealed.
    bool isMainCardRevealed() const;

    // Obtain the state of the game.
    CRG_STATE getState() const;

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
    Card selection will fail (false) if game is not ongoing.
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
    The state of the game.
    */
    CRG_STATE state;

    /*
    The ID of the main card.
    */
    int mainCardID;

    
    // Number of possible cards.
    int possCardCnt;

    /*
    The amount of time in milliseconds for the count down before the main card is
    revealed.
    */
    long long cntDownT;

    chrono::steady_clock::time_point startTimePt;
    chrono::steady_clock::time_point cardPickTimePt;

private:


};

}



namespace tests{

    void CRG_test1();

}



#endif  
