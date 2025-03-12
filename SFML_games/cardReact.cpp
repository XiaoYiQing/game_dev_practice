
#include "cardReact.h"


using namespace gameEngine;




// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

cardReact::cardReact( int possCardCnt ){

    this->possCardCnt = possCardCnt;
    this->cntDownStartT = 3000;

    // Use straightforward incremental ID assignement.
    for( int i = 0; i < possCardCnt; i++ ){
        possCardID_vect.push_back( i );
    }

    this->reset();

    this->pickMainCard();

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

long long cardReact::getElapsedMS(){

    lastTimePt = chrono::high_resolution_clock::now();
    return duration_cast<chrono::milliseconds>( lastTimePt - startTimePt ).count();

}

bool cardReact::isMainCardRevealed(){

    lastTimePt = chrono::high_resolution_clock::now();
    long long elapsedTime = duration_cast<chrono::milliseconds>( lastTimePt - startTimePt ).count();

    return cntDownStartT < elapsedTime;

}

// ====================================================================== <<<<<




// ====================================================================== >>>>>
//      Game Functionality (Public)
// ====================================================================== >>>>>

void cardReact::reset(){

    // Select a new card.
    this->pickMainCard();

    // Reset the start time point.
    startTimePt = chrono::high_resolution_clock::now();
    lastTimePt = startTimePt;

}


void cardReact::start(){

    startTimePt = chrono::high_resolution_clock::now();

}


bool cardReact::selectCard( int cardVect_idx ){

    if( this->isMainCardRevealed() ){

        if( possCardID_vect.at( cardVect_idx ) == mainCardID ){
            return true;
        }else{
            return false;
        }

    }else{
        return false;
    }

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Functionality (Protected)
// ====================================================================== >>>>>

void cardReact::pickMainCard(){
    
    // Select a random card vector index.
    int rand_vect_idx = randIntVectGen( 0, possCardCnt - 1, 1 ).at(0);

    // Set the main card's ID to be the randomly selected card's ID.
    this->mainCardID = this->possCardID_vect.at( rand_vect_idx );

}

// ====================================================================== <<<<<


