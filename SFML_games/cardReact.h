#ifndef CARDREACT_H
#define CARDREACT_H


#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <string>
#include <vector>



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

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Functionality (Public)
// ====================================================================== >>>>>


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


    // Number of possible cards.
    int possCardCnt;

    /*
    The ID of the main card.
    */
    int mainCardID;
    /*
    The integers representing the IDs of the possible cards.
    */
    vector<int> possCardID_vect;



private:



};

}

#endif  // CARDREACT_H
