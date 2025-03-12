
#include "cardReact.h"


using namespace gameEngine;



// ====================================================================== >>>>>
//      Class Enum "CRG_STATE" Help Functions
// ====================================================================== >>>>>

string cardReact::get_CRG_STATE_Str( CRG_STATE tar_CRG_STATE ){
    return string( magic_enum::enum_name( tar_CRG_STATE ) );
}

cardReact::CRG_STATE get_CRG_STATE_AtIdx( int idx ){
    if( idx >= 0 && idx < cardReact::CRG_STATE_Count ){
        return static_cast<cardReact::CRG_STATE>(idx);
    }else{
        cout << "Invalid int index for accessing enum \"CRG_STATE\"." << endl;
        return static_cast<cardReact::CRG_STATE>(-1);
    }
}

// ====================================================================== <<<<<




// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

cardReact::cardReact( int possCardCnt, long long cntDownT ){

    this->state = CRG_STATE::UNSTARTED;
    this->possCardCnt = possCardCnt;
    this->cntDownT = cntDownT;

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

long long cardReact::getElapsedMS() const{

    if( this->state == CRG_STATE::UNSTARTED ){
        return 0;
    }

    auto tmp = chrono::high_resolution_clock::now();
    return duration_cast<chrono::milliseconds>( tmp - startTimePt ).count();

}

long long cardReact::getPickCardMS() const{
    if( this->state == CRG_STATE::WIN || this->state == CRG_STATE::LOSS ){
        return duration_cast<chrono::milliseconds>( cardPickTimePt - 
            startTimePt ).count() - cntDownT;
    }else{
        return -1;
    }
}

bool cardReact::isMainCardRevealed() const{

    if( this->state == CRG_STATE::UNSTARTED ){
        return false;
    }

    auto tmp = chrono::high_resolution_clock::now();
    long long elapsedTime = 
        duration_cast<chrono::milliseconds>( tmp - startTimePt ).count();

    return cntDownT < elapsedTime;

}

cardReact::CRG_STATE cardReact::getState() const{
    return this->state;
}

// ====================================================================== <<<<<




// ====================================================================== >>>>>
//      Game Functionality (Public)
// ====================================================================== >>>>>

void cardReact::reset(){

    this->state = CRG_STATE::UNSTARTED;

    // Select a new card.
    this->pickMainCard();

    // Reset the start time point.
    startTimePt = chrono::high_resolution_clock::now();
    cardPickTimePt = startTimePt;

}


void cardReact::start(){

    this->state = CRG_STATE::ONGOING;

    startTimePt = chrono::high_resolution_clock::now();
    cardPickTimePt = startTimePt;

}


bool cardReact::selectCard( int cardVect_idx ){

    bool success = false;

    if( ( this->state == CRG_STATE::ONGOING ) && ( this->isMainCardRevealed() ) ){

        // Record the card pick time.
        this->cardPickTimePt = chrono::high_resolution_clock::now();

        // Win/Loss verification.
        if( cardVect_idx == mainCardID ){
            this->state = CRG_STATE::WIN;
        }else{
            this->state = CRG_STATE::LOSS;
        }

        // Card is selected successfully.
        success = true;

    }

    return success;

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game Functionality (Protected)
// ====================================================================== >>>>>

void cardReact::pickMainCard(){
    
    // Select a random card vector index.
    this->mainCardID = randIntVectGen( 0, possCardCnt - 1, 1 ).at(0);

}

// ====================================================================== <<<<<



void tests::CRG_test1(){
    
    gameEngine::cardReact myGame(8);
    myGame.start();

    this_thread::sleep_for( chrono::milliseconds(2900) );

    cout << myGame.getElapsedMS() << ": ";
    if( myGame.isMainCardRevealed() ){
        cout << "true: " << myGame.get_CRG_STATE_Str( myGame.getState() ) << endl;
    }else{
        cout << "false: " << myGame.get_CRG_STATE_Str( myGame.getState() ) << endl;
    }
    cout << "Card pick time: " << myGame.getPickCardMS() << endl;

    this_thread::sleep_for( chrono::milliseconds(250) );

    cout << myGame.getElapsedMS() << ": ";
    if( myGame.isMainCardRevealed() ){
        cout << "true: " << myGame.get_CRG_STATE_Str( myGame.getState() ) << endl;
    }else{
        cout << "false: " << myGame.get_CRG_STATE_Str( myGame.getState() ) << endl;
    }

    int mainCardID = myGame.getMainCardID();
    myGame.selectCard( mainCardID );

    cout << myGame.getElapsedMS() << ": ";
    cout << myGame.get_CRG_STATE_Str( myGame.getState() ) << endl;
    cout << "Card pick time: " << myGame.getPickCardMS() << endl;

}
