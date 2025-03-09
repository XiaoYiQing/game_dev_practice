
#include "cardReact.h"


using namespace gameEngine;




// ====================================================================== >>>>>
//      Constructor
// ====================================================================== >>>>>

cardReact::cardReact( int possCardCnt ){

    this->possCardCnt = possCardCnt;

    // Use straightforward incremental ID assignement.
    for( unsigned int i = 0; i < possCardCnt; i++ ){
        possCardID_vect.push_back( i );
    }

    

}

// ====================================================================== <<<<<