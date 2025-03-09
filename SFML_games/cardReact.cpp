
#include "cardReact.h"


using namespace gameEngine;




// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

cardReact::cardReact( int possCardCnt ){

    this->possCardCnt = possCardCnt;

    // Use straightforward incremental ID assignement.
    for( int i = 0; i < possCardCnt; i++ ){
        possCardID_vect.push_back( i );
    }



}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

int cardReact::getMainCardID() const{
    return this->mainCardID;
}

void cardReact::setMainCardID( int mainCardID ){
    this->mainCardID = mainCardID;
}

int cardReact::getPossCardID( int vect_idx ) const{
    return this->possCardID_vect.at( vect_idx );
}

void cardReact::setPossCardID( int vect_idx, int newID ){
    this->possCardID_vect.at( vect_idx ) = newID;
}


// ====================================================================== <<<<<




// ====================================================================== >>>>>
//      Game Functionality (Public)
// ====================================================================== >>>>>



// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Functionality (Protected)
// ====================================================================== >>>>>

void pickMainCard(){
    
}

// ====================================================================== <<<<<


