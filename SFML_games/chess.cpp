#include "chess.h"


using namespace gameEngine;


// ====================================================================== >>>>>
//      Class Enum "CHS_PIECE_TYPE" Help Functions
// ====================================================================== >>>>>

string chess::get_CHS_PIECE_TYPE_Str( chess::CHS_PIECE_TYPE tar_CHS_PIECE_TYPE ){
    return string( magic_enum::enum_name( tar_CHS_PIECE_TYPE ) );
}

chess::CHS_PIECE_TYPE chess::get_CHS_PIECE_TYPE_AtIdx( int idx ){
    if( idx >= 0 && idx < chess::CHS_PIECE_TYPE_Count ){
        return static_cast<chess::CHS_PIECE_TYPE>(idx);
    }else{
        throw invalid_argument( "Invalid int index for accessing enum \"CHS_PIECE_TYPE\"." );
    }
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHS_PIECE_COLOR" Help Functions
// ====================================================================== >>>>>

string chess::get_CHS_PIECE_COLOR_Str( chess::CHS_PIECE_COLOR tar_CHS_PIECE_COLOR ){
    return string( magic_enum::enum_name( tar_CHS_PIECE_COLOR ) );
}

chess::CHS_PIECE_COLOR chess::get_CHS_PIECE_COLOR_AtIdx( int idx ){
    if( idx >= 0 && idx < chess::CHS_PIECE_COLOR_Count ){
        return static_cast<chess::CHS_PIECE_COLOR>(idx);
    }else{
        throw invalid_argument( "Invalid int index for accessing enum \"CHS_PIECE_COLOR\"." );
    }
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Chess Piece Class
// ====================================================================== >>>>>

chess::chs_piece::chs_piece(){
    this->set_as_empty();
}

void chess::chs_piece::set_as_empty(){
    this->type = chess::CHS_PIECE_TYPE::NO_P;
    this->color = chess::CHS_PIECE_COLOR::NO_C;
}


// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

chess::chess(){

    // Initialize the chessboard.
    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        this->CHS_board[i][j] = chess::chs_piece();
    }
    }

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Function
// ====================================================================== >>>>>

chess::chs_piece chess::get_piece_at( unsigned int i, unsigned int j ){
    if( i >= BOARDHEIGHT || j > BOARDWIDTH ){
        throw out_of_range( "get_piece_at: the specified coordinate is out of bound." );
    }
    return this->CHS_board[i][j];
}

void chess::set_piece_at( unsigned int i, unsigned int j, chs_piece inPce ){
    if( i >= BOARDHEIGHT || j > BOARDWIDTH ){
        throw out_of_range( "set_piece_at: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j] = inPce;
}

// ====================================================================== <<<<<

