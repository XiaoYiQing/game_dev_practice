#ifndef CARDREACT_H
#define CARDREACT_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <string>
#include <thread>
#include <vector>


#include "numUtils.h"

using namespace std;



namespace gameEngine{

/**
 * This is the base functionality implementation of a card picking reaction game that
 * is called Card Reaction Game (CRG).
 * 
 * The game consists of:
 *  - One faced down card at the beginning of the game.
 *  - All possible cards this hidden card can be displayed by the side.
 * 
 * After a countdown, the faced down card is revealed, and the player must select
 * the matching card as fast as possible.
 */
class cardReact{

public:


// ====================================================================== >>>>>
//      Class Enum "CRG_STATE" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the states the CRG game can be in.
     */
    enum class CRG_STATE{ UNSTARTED, COUNTDOWN, ONGOING, HIT, MISS };

    // The number of enum entries in the enum "CRG_STATE" (Uses magic enum).
    const static int CRG_STATE_Count = (int) magic_enum::enum_count<CRG_STATE>();

    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CRG_STATE The target CRG_STATE enum.
     * @return The string representation of the target CRG_STATE enum.
     */
    static string get_CRG_STATE_Str( CRG_STATE tar_CRG_STATE );
    // Obtain the enum matching the enum integer index.

    /**
     * Obtain the CRG_STATE enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CRG_STATE enum.
     * @return The matching CRG_STATE enum to the target index, if it exists.
     */
    static CRG_STATE get_CRG_STATE_AtIdx( int idx );

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>
    
    /**
     * Constructor for the card react game.
     * 
     * @param possCardCnt Number of possible cards.
     * @param cntDownT Countdown duration time in ms (milli-seconds) before the hidden card
     *  is revealed following a game start.
     */
    cardReact( unsigned int possCardCnt = 8, long long cntDownT = 3000 );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

    /**
     * Obtain the main card's ID.
     * 
     * @return The ID of the hidden card, which is simply the index of the chosen
     *  card serving as the hidden card in the array of possible cards.
     */
    int getMainCardID() const;
    /**
     * Set the ID of the main card.
     * 
     * @param mainCardID The ID or the index of that chosen card.
     */
    void setMainCardID( int mainCardID );

    /**
     * Obtain the amount of time in milliseconds (ms) elapsed since the start 
     * of the game.
     * 
     * @return The amount of ms elapsed since the beginning of the game.
     */
    long long getElapsedMS() const;


    /**
     * Obtain the amount of time (ms) elapsed between the card reveal time and
     * the time a card has been picked.
     * 
     * @return The amount of ms elapsed between card reveal and card picked.
     * 
     * \note A real time is returned only when the game is finished (hit/miss),
     *  otherwise -1 is returned.
     */
    long long getPickCardMS() const;

    /**
     * Obtain the countdown time amount (Before a user card pick can be registered).
     * 
     * This is the fix starting amount, not the current amount left.
     * 
     * @return The fixed countdown time in ms that this CRG game instance uses.
     */
    long long getCountDownMS() const;

    /**
     * Obtain the current reveal flag of the main card.
     * 
     * @return The flag indicating whether the main card is revealed or not.
     */
    bool isMainCardRevealed() const;

    /**
     * Return the current game state enum.
     * 
     * @return The current game state enum.
     */
    CRG_STATE getState() const;

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Functionality (Public)
// ====================================================================== >>>>>

    /**
     * Reset the state of the game to that of a fresh unstarted game.
     */
    void reset();

    /**
     * Start the game, which triggers the countdown.
     */
    void start();

    /**
     * \brief Perform the select card action.
     * 
     * - Card selection will fail if the countdown has not yet finished yet.
     * 
     * - Card selection will fail if game is not ongoing.
     * 
     * \param cardVect_idx The index of the selected card.
     * \return Boolean indicating whether card selection is successful.
     */
    bool selectCard( int cardVect_idx );

// ====================================================================== <<<<<



protected:

// ====================================================================== >>>>>
//      Game Functionality (Protected)
// ====================================================================== >>>>>

    /**
     * Randomly select the main card.
     */
    void pickMainCard();

    /**
     * Perform a countdown, following which the hidden card is revealed.
     * 
     * \param tarObj The present CRG instance requiring the countdown triggering.
     * 
     * \note This function is meant to be used on a separate thread.
     */
    static void countDownThread( cardReact& tarObj );

// ====================================================================== <<<<<

    // The state of the game.
    CRG_STATE state;

    // The ID of the main card.
    unsigned int mainCardID;

    // Number of possible cards.
    unsigned int possCardCnt;

    // The amount of time in milliseconds for the countdown before the main 
    // card is revealed.
    long long cntDownT;

    // The time point when the game has officially stated (Going into "ONGOING" state).
    chrono::steady_clock::time_point startTimePt;
    // The time point when a possible card has been selected.
    chrono::steady_clock::time_point cardPickTimePt;
    // The time point when the countdown has finished.
    chrono::steady_clock::time_point cntDownEndTimePt;

private:


};

}



namespace tests{

    void CRG_test1();

}



#endif  
