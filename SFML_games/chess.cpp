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
//      Class Enum "CHS_STATE" Help Functions
// ====================================================================== >>>>>

string chess::get_CHS_STATE_Str( CHS_STATE tar_CHS_STATE ){
    return string( magic_enum::enum_name( tar_CHS_STATE ) );
}

chess::CHS_STATE chess::get_CHS_STATE_AtIdx( int idx ){
    if( idx >= 0 && idx < chess::CHS_STATE_Count ){
        return static_cast<chess::CHS_STATE>(idx);
    }else{
        throw invalid_argument( "Invalid int index for accessing enum \"CHS_STATE\"." );
    }
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Chess Piece Class
// ====================================================================== >>>>>

chess::chs_piece::chs_piece(){
    this->set_as_empty();
}

chess::chs_piece::chs_piece( CHS_PIECE_TYPE type, CHS_PIECE_COLOR color ){
    this->type = type;
    this->color = color;
}

void chess::chs_piece::set_as_empty(){
    this->type = chess::CHS_PIECE_TYPE::NO_P;
    this->color = chess::CHS_PIECE_COLOR::NO_C;
}

void chess::chs_piece::printPiece() const{

    char color_char = ' ';
    switch( this->color ){
    case CHS_PIECE_COLOR::WHITE:
        color_char = 'W';   break;
    case CHS_PIECE_COLOR::BLACK:
        color_char = 'B';   break;
    case CHS_PIECE_COLOR::NO_C:
        color_char = 'N';   break;
    default:
        throw runtime_error("Unrecognized chess piece color enum.");
    }

    char type_char = ' ';
    switch( this->type ){
    case CHS_PIECE_TYPE::NO_P:
        type_char = 'N';   break;
    case CHS_PIECE_TYPE::PAWN:
        type_char = 'P';   break;
    case CHS_PIECE_TYPE::KNIGHT:
        type_char = 'K';   break;
    case CHS_PIECE_TYPE::BISHOP:
        type_char = 'B';   break;
    case CHS_PIECE_TYPE::QUEEN:
        type_char = 'Q';   break;
    case CHS_PIECE_TYPE::KING:
        type_char = 'K';   break;
    default:
        throw runtime_error("Unrecognized chess piece type enum.");
    }

    // Print the piece symbol.
    cout << color_char << type_char;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Chess Move Class
// ====================================================================== >>>>>

chess::chs_move::chs_move(){
    this->pt_a = pair<int,int>( 0, 0 );
    this->pt_b = pair<int,int>( 0, 0 );
}

chess::chs_move::chs_move( int i_a, int j_a, int i_b, int j_b ){
    this->pt_a = pair<int,int>( i_a, j_a );
    this->pt_b = pair<int,int>( i_b, j_b );
}

chess::chs_move::chs_move( pair<int,int> pt_a, pair<int,int> pt_b ){
    this->pt_a = pt_a;
    this->pt_b = pt_b;
}

std::pair<int,int> chess::chs_move::get_vec(){
    return pair( pt_b.first - pt_a.first , pt_b.second - pt_a.second );
}


bool chess::chs_move::is_move_valid( chs_piece tar_piece ){
    return is_move_valid( tar_piece.type, tar_piece.color );
}

bool chess::chs_move::is_move_valid( CHS_PIECE_TYPE tar_type, 
    CHS_PIECE_COLOR tar_color ){

    // A piece with the "none" equivalent value in type and/or color is automatically
    // disqualified from having a valid move.
    if( tar_type == CHS_PIECE_TYPE::NO_P || tar_color == CHS_PIECE_COLOR::NO_C ){
        return false;
    }

    // A starting coordinate outside the bound of the chess board is automatically invalid.
    if( this->pt_a.first < 0 || this->pt_a.first >= BOARDHEIGHT ||
        this->pt_a.second < 0 || this->pt_a.second >= BOARDWIDTH ){
        return false;
    }
    // An ending coordinate outside the bound of the chess board is automatically invalid.
    if( this->pt_b.first < 0 || this->pt_b.first >= BOARDHEIGHT ||
        this->pt_b.second < 0 || this->pt_b.second >= BOARDWIDTH ){
        return false;
    }

    // Obtain the move vector.
    pair<int,int> myVec = this->get_vec();
    // A null move is invalid.
    if( myVec.first == 0 && myVec.second == 0 ){
        return false;
    }

    
    int tile_cnt = abs( myVec.first ) + abs( myVec.second );
    // Ruling under different piece types.
    switch( tar_type ){
    case CHS_PIECE_TYPE::PAWN:

        if( tar_color == CHS_PIECE_COLOR::WHITE ){
            return ( myVec.first == -1 && myVec.second == 0 );
        }else if(tar_color == CHS_PIECE_COLOR::BLACK){
            return ( myVec.first == 1 && myVec.second == 0 );
        }else{
            throw runtime_error( "is_move_valid: Unexpected chess piece color enum." );
        }
    
        break;

    case CHS_PIECE_TYPE::KNIGHT:

        return ( tile_cnt == 3 ) && ( abs( myVec.first ) == 1 || abs( myVec.second ) == 1 );
        break;

    case CHS_PIECE_TYPE::BISHOP:

        return ( abs( myVec.first ) == abs( myVec.second ) );
        break;

    case CHS_PIECE_TYPE::ROOK:

        return ( myVec.first == 0 || myVec.second == 0 );
        break;

    case CHS_PIECE_TYPE::QUEEN:

        return ( abs( myVec.first ) == abs( myVec.second ) ) ||
            ( myVec.first == 0 || myVec.second == 0 );
        break;

    case CHS_PIECE_TYPE::KING:

        return ( abs( myVec.first ) <= 1 && abs( myVec.second ) <= 1 );
        break;

    }

    return true;
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

chess::chess(){

    // Empty piece.
    chess::chs_piece curr_piece;
    curr_piece.set_as_empty();

    // Initialize the chessboard.
    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        this->CHS_board[i][j] = curr_piece;
    }
    }

    this->turn_cnt = 0;
    this->no_change_turn_cnt = 0;
    this->state = CHS_STATE::ONGOING;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

void chess::clearBoard(){

    // Empty piece.
    chess::chs_piece curr_piece;
    curr_piece.set_as_empty();

    // Initialize the chessboard.
    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        this->CHS_board[i][j] = curr_piece;
    }
    }

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

void chess::printBoard() const{

    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){
        for( unsigned int j = 0; j < BOARDWIDTH; j++ ){

            this->CHS_board[i][j].printPiece();

            if( j != BOARDWIDTH ){
                cout << ' ';
            }

        }

        if( i != BOARDHEIGHT ){
            cout << endl;
        }
    }

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Function
// ====================================================================== >>>>>

chess::chs_piece chess::get_piece_at( unsigned int i, unsigned int j ) const{
    if( i >= BOARDHEIGHT || j > BOARDWIDTH ){
        throw out_of_range( "get_piece_at: the specified coordinate is out of bound." );
    }
    return this->CHS_board[i][j];
}

void chess::set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce ){
    if( i >= BOARDHEIGHT || j > BOARDWIDTH ){
        throw out_of_range( "set_piece_at: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j] = inPce;
}

unsigned int chess::getTurn_cnt() const
    { return this->turn_cnt; }
void chess::setTurn_cnt( const unsigned int turn_cnt )
    { this->turn_cnt = turn_cnt; }

chess::CHS_STATE chess::get_state() const
    { return this->state; }
void chess::set_state( const CHS_STATE state )
    { this->state = state; }

// ====================================================================== <<<<<

