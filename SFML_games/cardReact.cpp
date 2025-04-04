
#include "cardReact.h"


using namespace gameEngine;



// ====================================================================== >>>>>
//      Class Enum "CRG_STATE" Help Functions
// ====================================================================== >>>>>

string cardReact::get_CRG_STATE_Str( CRG_STATE tar_CRG_STATE ){
    return string( magic_enum::enum_name( tar_CRG_STATE ) );
}

cardReact::CRG_STATE cardReact::get_CRG_STATE_AtIdx( int idx ){
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

cardReact::cardReact( unsigned int possCardCnt, long long cntDownT ){

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
    if( this->state == CRG_STATE::HIT || this->state == CRG_STATE::MISS ){
        return duration_cast<chrono::milliseconds>( cardPickTimePt - 
            cntDownEndTimePt ).count();
        // return duration_cast<chrono::milliseconds>( cardPickTimePt - 
        //     startTimePt ).count() - cntDownT;
    }else{
        return -1;
    }
}

long long cardReact::getCountDownMS() const{
    return cntDownT;
}

bool cardReact::isMainCardRevealed() const{

    if( this->state == CRG_STATE::UNSTARTED || this->state == CRG_STATE::COUNTDOWN ){
        return false;
    }else{
        return true;
    }

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

    // Prevent the game from starting if it is not ready.
    if( this->state != CRG_STATE::UNSTARTED ){
        return;
    }

    // this->state = CRG_STATE::ONGOING;
    this->state = CRG_STATE::COUNTDOWN;

    startTimePt = chrono::high_resolution_clock::now();
    cardPickTimePt = startTimePt;

    // Create a new thread that runs the runInThread function
    std::thread myThread( countDownThread, ref( *this ) );
    myThread.detach();
    
}


bool cardReact::selectCard( int cardVect_idx ){

    bool success = false;

    if( ( this->state == CRG_STATE::ONGOING ) && ( this->isMainCardRevealed() ) ){

        // Record the card pick time.
        this->cardPickTimePt = chrono::high_resolution_clock::now();

        // Win/Loss verification.
        if( cardVect_idx == mainCardID ){
            this->state = CRG_STATE::HIT;
        }else{
            this->state = CRG_STATE::MISS;
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

void cardReact::countDownThread( cardReact& tarObj ){

    std::this_thread::sleep_for( chrono::milliseconds( tarObj.cntDownT ) );
    tarObj.cntDownEndTimePt = chrono::high_resolution_clock::now();
    tarObj.state = CRG_STATE::ONGOING;
    
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
