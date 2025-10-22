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

bool chess::chs_piece::operator==(const chs_piece& tar) const{
    bool comp_res = true;
    comp_res = comp_res && ( this->type == tar.type );
    comp_res = comp_res && ( this->color == tar.color );
    return comp_res;
}

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
    case CHS_PIECE_TYPE::ROOK:
        type_char = 'R';   break;
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



// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

chess::chess(){

    this->resetBoard();

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

void chess::set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce ){
    if( i >= BOARDHEIGHT || j >= BOARDWIDTH ){
        throw out_of_range( "set_piece_at: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j] = inPce;
}

void chess::resetBoard(){

    if( BOARDHEIGHT != 8 || BOARDWIDTH != 8 ){
        throw runtime_error( "Chess board reset cannot be done with a non-standard chess board dimensions." );
    }

    // Insert the last row pieces on both sides.
    unsigned int col_idx = 0;
    unsigned int row_idx = 0;
    this->set_piece_at( row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    col_idx = 1;
    this->set_piece_at( row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    col_idx = 2;
    this->set_piece_at( row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    col_idx = 3;
    this->set_piece_at( row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::BLACK ) );
    this->set_piece_at( BOARDHEIGHT - 1 - row_idx, BOARDWIDTH - 1 - col_idx, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );

    // Insert the pawns.
    row_idx = 1;
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        this->set_piece_at( row_idx, j, 
            chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
        this->set_piece_at( BOARDHEIGHT - 1 - row_idx, j, 
            chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    }

    // Set all remaining space as empty.
    chess::chs_piece NONE_PIECE( chess::CHS_PIECE_TYPE::NO_P, chess::CHS_PIECE_COLOR::NO_C );
    for( unsigned int i = 2; i < BOARDHEIGHT - 2; i++ ){
        for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
            this->set_piece_at( i, j, NONE_PIECE );
        }
    }

    // Reset all support variables descripbing the state of the game.
    this->turn_cnt = 0;
    this->no_change_turn_cnt = 0;
    this->state = CHS_STATE::ONGOING;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

/*
- Check if the coordinates are within board limits.
- Check if the move is trivial (0 move).
- Check if there is a piece at the starting coordinate.
- Check if there is free space at the ending coordinate.
- Check if the piece is white or black and if is its turn.
- Check if the specified movement matches the capability of the piece.
    To extend the above point, also deal with special moves such as 
    > Castling of king and rook
    > Pawn double square forward as first move.
- Check if there is any obstable between the starting and ending point (Except knight).
*/

bool chess::move( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft )
{

    return false;




}

/*
- Check if the coordinates are within board limits.
- Check if the move is trivial (0 move).
- Check if there is a piece at the starting coordinate.
- Check if there is free space at the ending coordinate.
- Check if the piece is white or black and if is its turn.
- Check if the specified movement matches the capability of the piece.
    To extend the above point, also deal with special moves such as 
    > Castling of king and rook
    > Pawn double square forward as first move.
- Check if there is any obstable between the starting and ending point (Except knight).
*/
bool chess::is_move_valid( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft )
{

    // Out of bound check.
    if( max( i_bef, i_aft ) >= BOARDHEIGHT && max( j_bef, j_aft ) >= BOARDHEIGHT ){
        return false;
    }

    // Trivial move check.
    if( i_bef == i_aft && j_bef == j_aft ){
        return false;
    }

    // Obtain the target piece to play.
    chs_piece tarPce = this->get_piece_at( i_bef, j_bef );
    // Empty starting square check.
    if( tarPce.type == CHS_PIECE_TYPE::NO_P || tarPce.color == CHS_PIECE_COLOR::NO_C ){
        return false;
    }    

    // Obtain piece at destination.
    chs_piece endPce = this->get_piece_at( i_aft, j_aft );
    // Check empty space at destination.
    if( tarPce.type != CHS_PIECE_TYPE::NO_P || tarPce.color != CHS_PIECE_COLOR::NO_C ){
        return false;
    }

    // Obtain the color of the current piece.
    CHS_PIECE_COLOR tarColor = tarPce.color;
    // Turn check.
    if( this->turn_cnt % 2 == 0 && tarColor != CHS_PIECE_COLOR::WHITE ){
        throw runtime_error( "Game is currently not at the target piece's turn to play." );
    }


    // Obtain the type of the current piece.
    CHS_PIECE_TYPE tarType = tarPce.type;
   

    // Computed the movement vector.
    pair<int,int> moveVec( (int)i_aft - (int)i_bef, (int)j_aft - (int)j_bef );



    bool valid_move = true;

    // Piece's capability match.
    switch( tarType ){
    case CHS_PIECE_TYPE::PAWN:

        // Pawn move must be a non-trivial move along a column.
        if( moveVec.first == 0 || moveVec.second != 0 ){
            return false;
        }

        // A pawn can only move forward (white goes up, black goes down).
        if( ( moveVec.first < 0 && tarColor == CHS_PIECE_COLOR::WHITE ) || 
            ( moveVec.first > 0 && tarColor == CHS_PIECE_COLOR::BLACK ) ){
            return false;
        }

        // The pawn had never moved before.
        if( ( i_bef == 1 && tarColor == CHS_PIECE_COLOR::WHITE ) || 
            ( i_bef == BOARDHEIGHT - 2 && tarColor == CHS_PIECE_COLOR::BLACK ) ){
            if( abs( moveVec.first ) > 2 ){
                return false;
            }
        // The pawn has moved before.
        }else{
            if( abs( moveVec.first ) > 1 ){
                return false;
            }
        }
        
        break;

    case CHS_PIECE_TYPE::KNIGHT:

        // The knight can only jump in the smallest L shapes.
        if( abs( moveVec.first ) + abs( moveVec.second ) != 3 ){
            return false;
        }

        break;

    case CHS_PIECE_TYPE::BISHOP:

        // Bishops can only move in diagonals.
        if( abs( moveVec.first ) != abs( moveVec.second ) ){
            return false;
        }
        break;

    case CHS_PIECE_TYPE::ROOK:

        // Bishops can only move in diagonals.
        if( abs( moveVec.first ) != abs( moveVec.second ) ){
            return false;
        }
        break;

    case CHS_PIECE_TYPE::QUEEN:

        break;

    case CHS_PIECE_TYPE::KING:

        break;

    default:

        break;
    };

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

void chess::printBoard() const{

    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){
        for( unsigned int j = 0; j < BOARDWIDTH; j++ ){

            this->CHS_board[ BOARDHEIGHT - 1 - i ][j].printPiece();

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

unsigned int chess::getTurn_cnt() const
    { return this->turn_cnt; }
void chess::setTurn_cnt( const unsigned int turn_cnt )
    { this->turn_cnt = turn_cnt; }

chess::CHS_STATE chess::getState() const
    { return this->state; }
void chess::setState( const CHS_STATE state )
    { this->state = state; }

unsigned int chess::getNo_change_turn_cnt() const
    { return this->no_change_turn_cnt; }
void chess::setNo_change_turn_cnt( const unsigned int no_change_turn_cnt )
    { this->no_change_turn_cnt = no_change_turn_cnt; }

// ====================================================================== <<<<<

