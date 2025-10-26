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
    this->not_moved = true;
}

void chess::chs_piece::set_as_empty(){
    this->type = chess::CHS_PIECE_TYPE::NO_P;
    this->color = chess::CHS_PIECE_COLOR::NO_C;
    this->not_moved = true;
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


    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
        this->atk_list_by_B[z].reserve( BOARDHEIGHT*BOARDWIDTH );
        this->atk_list_by_W[z].reserve( BOARDHEIGHT*BOARDWIDTH );
    }

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

    // Set all squares as empty.
    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        this->CHS_board[i][j] = curr_piece;
    }
    }

    // Update all state related variables.
    this->upd_all();

}

void chess::set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce ){
    if( i >= BOARDHEIGHT || j >= BOARDWIDTH ){
        throw out_of_range( "set_piece_at: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j] = inPce;
    this->upd_all();
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

    // Update all remaining state related variables.
    upd_all();

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>


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
    if( max( i_bef, i_aft ) >= BOARDHEIGHT || max( j_bef, j_aft ) >= BOARDHEIGHT ){
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
    if( endPce.type != CHS_PIECE_TYPE::NO_P || endPce.color != CHS_PIECE_COLOR::NO_C ){
        return false;
    }

    // Obtain the color of the current piece.
    CHS_PIECE_COLOR tarColor = tarPce.color;
    // Turn check.
    if( this->turn_cnt % 2 == 0 && tarColor != CHS_PIECE_COLOR::WHITE ||
        this->turn_cnt % 2 == 1 && tarColor != CHS_PIECE_COLOR::BLACK ){
        return false;
    }

    // Obtain the type of the current piece.
    CHS_PIECE_TYPE tarType = tarPce.type;
    // Computed the movement vector.
    pair<int,int> moveVec( (int)i_aft - (int)i_bef, (int)j_aft - (int)j_bef );
    // Piece's capability match.
    switch( tarType ){
    case CHS_PIECE_TYPE::PAWN:

        // Pawn move must be restricted along a column.
        if( moveVec.second != 0 ){
            return false;
        }

        // A pawn can only move forward (white goes up, black goes down).
        if( ( moveVec.first < 0 && tarColor == CHS_PIECE_COLOR::WHITE ) || 
            ( moveVec.first > 0 && tarColor == CHS_PIECE_COLOR::BLACK ) ){
            return false;
        }

        // The pawn had never moved before and can move up 1 or 2 squares.
        if( ( i_bef == 1 && tarColor == CHS_PIECE_COLOR::WHITE ) || 
            ( i_bef == BOARDHEIGHT - 2 && tarColor == CHS_PIECE_COLOR::BLACK ) ){
            if( abs( moveVec.first ) > 2 ){
                return false;
            }
        // The pawn has moved before and can move up only 1 square.
        }else{
            if( abs( moveVec.first ) > 1 ){
                return false;
            }
        }
        
        break;

    case CHS_PIECE_TYPE::KNIGHT:

        // The knight can only jump in the smallest L shapes.
        if( ( abs( moveVec.first ) + abs( moveVec.second ) != 3 ) || 
            ( moveVec.first == 0 || moveVec.second == 0 ) ){
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

        // Rooks can only move in horizontals and verticals.
        if( moveVec.first != 0 && moveVec.second != 0 ){
            return false;
        }
        break;

    case CHS_PIECE_TYPE::QUEEN:
        if( abs( moveVec.first ) != abs( moveVec.second ) &&
            ( moveVec.first != 0 && moveVec.second != 0 ) ){
            return false;
        }
        break;

    case CHS_PIECE_TYPE::KING:

        // Standard king move.
        if( abs( moveVec.first ) <= 1 && abs( moveVec.second ) <= 1 ){
            
            // Check for threat at destination square.
            if( tarColor == CHS_PIECE_COLOR::WHITE && !atk_list_by_B[ sub2ind( i_aft, j_aft ) ].empty() ||
                tarColor == CHS_PIECE_COLOR::BLACK && !atk_list_by_W[ sub2ind( i_aft, j_aft ) ].empty() )
            {
                return false;
            }
            break;

        // Check for castling possibility.
        }else if( tarPce.not_moved && BOARDHEIGHT == 8 && BOARDWIDTH == 8 ){

            if( tarColor == CHS_PIECE_COLOR::WHITE ){
                
                bool cast_poss = true;

                // Right-side castling.
                if( i_bef == 0 && j_bef == 4 && i_aft == 0 && j_aft == 6 ){

                    // The right-side rook must have not moved yet.
                    cast_poss = cast_poss && ( this->CHS_board[0][7].type == CHS_PIECE_TYPE::ROOK );
                    cast_poss = cast_poss && ( this->CHS_board[0][7].color == CHS_PIECE_COLOR::WHITE );
                    cast_poss = cast_poss && ( this->CHS_board[0][7].not_moved );
                    if( !cast_poss ){ return false; }

                    // Make sure the entire path is clear from black threats.
                    cast_poss = cast_poss && ( atk_list_by_B[sub2ind(0,4)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_B[sub2ind(0,5)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_B[sub2ind(0,6)].empty() );
                    if( !cast_poss ){ return false; }

                // Left-side castling.
                }else if( i_bef == 0 && j_bef == 4 && i_aft == 0 && j_aft == 2 ){

                    // The left-side rook must have not moved yet.
                    cast_poss = cast_poss && ( this->CHS_board[0][0].type == CHS_PIECE_TYPE::ROOK );
                    cast_poss = cast_poss && ( this->CHS_board[0][0].color == CHS_PIECE_COLOR::WHITE );
                    cast_poss = cast_poss && ( this->CHS_board[0][0].not_moved );
                    // The left-side knight initial square must be cleared.
                    cast_poss = cast_poss && ( this->CHS_board[0][1].type == CHS_PIECE_TYPE::NO_P &&
                        this->CHS_board[0][1].color == CHS_PIECE_COLOR::NO_C );
                    if( !cast_poss ){ return false; }

                    // Make sure the entire path is clear from black threats.
                    cast_poss = cast_poss && ( atk_list_by_B[sub2ind(0,4)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_B[sub2ind(0,3)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_B[sub2ind(0,2)].empty() );
                    if( !cast_poss ){ return false; }

                // Not castling, and thus illegal
                }else{
                    return false;
                }

            }else if( tarColor == CHS_PIECE_COLOR::BLACK ){

                bool cast_poss = true;

                // Right-side castling.
                if( i_bef == 7 && j_bef == 4 && i_aft == 7 && j_aft == 6 ){

                    // The right-side rook must have not moved yet.
                    cast_poss = cast_poss && ( this->CHS_board[7][7].type == CHS_PIECE_TYPE::ROOK );
                    cast_poss = cast_poss && ( this->CHS_board[7][7].color == CHS_PIECE_COLOR::BLACK );
                    cast_poss = cast_poss && ( this->CHS_board[7][7].not_moved );
                    if( !cast_poss ){ return false; }

                    // Make sure the entire path is clear from white threats.
                    cast_poss = cast_poss && ( atk_list_by_W[sub2ind(7,4)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_W[sub2ind(7,5)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_W[sub2ind(7,6)].empty() );
                    if( !cast_poss ){ return false; }

                // Left-side castling.
                }else if( i_bef == 7 && j_bef == 4 && i_aft == 7 && j_aft == 2 ){

                    // The left-side rook must have not moved yet.
                    bool cast_poss = this->CHS_board[7][0].type == CHS_PIECE_TYPE::ROOK;
                    cast_poss = cast_poss && ( this->CHS_board[7][0].color == CHS_PIECE_COLOR::BLACK );
                    cast_poss = cast_poss && ( this->CHS_board[7][0].not_moved );
                    // The left-side knight initial square must be cleared.
                    cast_poss = cast_poss && ( this->CHS_board[7][1].type == CHS_PIECE_TYPE::NO_P &&
                        this->CHS_board[7][1].color == CHS_PIECE_COLOR::NO_C );
                    if( !cast_poss ){ return false; }

                    // Make sure the entire path is clear from white threats.
                    cast_poss = cast_poss && ( atk_list_by_W[sub2ind(7,4)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_W[sub2ind(7,3)].empty() );
                    cast_poss = cast_poss && ( atk_list_by_W[sub2ind(7,2)].empty() );
                    if( !cast_poss ){ return false; }

                // Not castling, and thus illegal
                }else{
                    return false;
                }

            }else{
                throw runtime_error( "Unrecognized chess piece color." );
            }

        // The king's move is against the rule.
        }else{
            return false;
        }

        break;

    default:

        throw runtime_error( "Unexpected chess piece type." );
        break;

    };

    // Obstruction check (Only the knight pieces do not need).
    if( tarType != CHS_PIECE_TYPE::KNIGHT ){

        // The segment lengths.
        pair<int,int>moveVecSeg(0,0);
        // The number of squares between start and end points.
        int sqr_cnt = 0;
        if( moveVec.first != 0 ){
            moveVecSeg.first = moveVec.first > 0 ? 1 : -1;
            sqr_cnt = abs( moveVec.first ) - 1;
        }
        if( moveVec.second != 0 ){
            moveVecSeg.second = moveVec.second > 0 ? 1 : -1;
            sqr_cnt = abs( moveVec.second ) - 1;
        }
        
        // Make sure every square between the start and end squares are empty.
        chs_piece pce_z;
        for( int z = 1; z <= sqr_cnt; z++ ){
            pce_z = this->get_piece_at( i_bef + z*moveVecSeg.first, j_bef + z*moveVecSeg.second );
            if( pce_z.type != CHS_PIECE_TYPE::NO_P || pce_z.color != CHS_PIECE_COLOR::NO_C ){
                return false;
            }
        }

    }

    return true;

}


bool chess::is_atk_valid( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft  )
{
    
    // Out of bound check.
    if( max( i_bef, i_aft ) >= BOARDHEIGHT || max( j_bef, j_aft ) >= BOARDHEIGHT ){
        return false;
    }

    // Trivial attack check.
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
    if( endPce.type == CHS_PIECE_TYPE::NO_P || endPce.color == CHS_PIECE_COLOR::NO_C ){
        return false;
    }

    // Make sure the attacker and the defender are of different colors.
    if( tarPce.color == endPce.color ){
        return false;
    }

    // Obtain the color of the current piece.
    CHS_PIECE_COLOR tarColor = tarPce.color;
    // Turn check.
    if( this->turn_cnt % 2 == 0 && tarColor != CHS_PIECE_COLOR::WHITE ||
        this->turn_cnt % 2 == 1 && tarColor != CHS_PIECE_COLOR::BLACK ){
        return false;
    }

    // Obtain the type of the current piece.
    CHS_PIECE_TYPE tarType = tarPce.type;
    // Computed the movement vector.
    pair<int,int> moveVec( (int)i_aft - (int)i_bef, (int)j_aft - (int)j_bef );
    
    // Piece's capability match.
    switch( tarType ){
    
    case CHS_PIECE_TYPE::PAWN:
        
        // A pawn can only move forward (white goes up, black goes down).
        if( ( moveVec.first < 0 && tarColor == CHS_PIECE_COLOR::WHITE ) || 
            ( moveVec.first > 0 && tarColor == CHS_PIECE_COLOR::BLACK ) ){
            return false;
        }

        // A pawn can only attack on its two immediate foward diagonal squares.
        if( abs( moveVec.first ) != 1 || abs( moveVec.second ) != 1 ){
            return false;
        }

        break;

    case CHS_PIECE_TYPE::KNIGHT:

        // The knight can only jump in the smallest L shapes.
        if( ( abs( moveVec.first ) + abs( moveVec.second ) != 3 ) || 
            ( moveVec.first == 0 || moveVec.second == 0 ) ){
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

        // Rooks can only move in horizontals and verticals.
        if( moveVec.first != 0 && moveVec.second != 0 ){
            return false;
        }
        break;
    
    case CHS_PIECE_TYPE::QUEEN:

        if( abs( moveVec.first ) != abs( moveVec.second ) &&
            ( moveVec.first != 0 && moveVec.second != 0 ) ){
            return false;
        }
        break;

    case CHS_PIECE_TYPE::KING:

        // Standard king move.
        if( abs( moveVec.first ) <= 1 && abs( moveVec.second ) <= 1 ){

            // Check for threat at destination square.
            if( tarColor == CHS_PIECE_COLOR::WHITE && !atk_list_by_B[ sub2ind( i_aft, j_aft ) ].empty() ||
                tarColor == CHS_PIECE_COLOR::BLACK && !atk_list_by_W[ sub2ind( i_aft, j_aft ) ].empty() )
            {
                return false;
            }

        }
        
        break;

    default:
        throw runtime_error( "Unexpected chess piece type." );
        break;

    };

    // Obstruction check (Only the knight pieces do not need).
    if( tarType != CHS_PIECE_TYPE::KNIGHT ){

        // The segment lengths.
        pair<int,int>moveVecSeg(0,0);
        // The number of squares between start and end points.
        int sqr_cnt = 0;
        if( moveVec.first != 0 ){
            moveVecSeg.first = moveVec.first > 0 ? 1 : -1;
            sqr_cnt = abs( moveVec.first ) - 1;
        }
        if( moveVec.second != 0 ){
            moveVecSeg.second = moveVec.second > 0 ? 1 : -1;
            sqr_cnt = abs( moveVec.second ) - 1;
        }
        
        // Make sure every square between the start and end squares are empty.
        chs_piece pce_z;
        for( int z = 1; z <= sqr_cnt; z++ ){
            pce_z = this->get_piece_at( i_bef + z*moveVecSeg.first, j_bef + z*moveVecSeg.second );
            if( pce_z.type != CHS_PIECE_TYPE::NO_P || pce_z.color != CHS_PIECE_COLOR::NO_C ){
                return false;
            }
        }

    }

    return true;
    
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

bool chess::is_sq_empty( int i, int j ){
    if( i < 0 || i >= BOARDHEIGHT || j < 0 || j >= BOARDWIDTH ){
        throw invalid_argument( "Invalid chess board coordinates." );
    }
    return ( this->CHS_board[i][j].type == CHS_PIECE_TYPE::NO_P && 
        this->CHS_board[i][j].color == CHS_PIECE_COLOR::NO_C );
}

vector< pair<int,int> > chess::get_all_atk_sq( int i, int j ){

    // Initialize the vector of attackers' positions.
    vector< pair<int,int> > retVal;
    // Return an empty vector if no piece.
    if( is_sq_empty( i, j ) ){
        return retVal;
    }

    // Obtain the attacking piece.
    chs_piece atk_piece = this->get_piece_at( i, j );
    // Initialize vector of all standard attack possilities completely disregarding
    // whether the attacked position is even on the board.
    vector<pair<int,int>> pos_atk_coords;


    /*
    Compute the distance (number of squares away) of the piece to each of the 
    board borders.
    */
    int top_dist = BOARDHEIGHT - 1 - i;
    int right_dist = BOARDWIDTH - 1 - j;
    int bottom_dist = i;
    int left_dist = j;

    switch( atk_piece.type ){
    case CHS_PIECE_TYPE::PAWN:

        if( atk_piece.color == CHS_PIECE_COLOR::WHITE ){

            pos_atk_coords.push_back( pair<int,int>( i + 1, j + 1 ) );
            pos_atk_coords.push_back( pair<int,int>( i + 1, j - 1 ) );

        }else if( atk_piece.color == CHS_PIECE_COLOR::BLACK ){

            pos_atk_coords.push_back( pair<int,int>( i - 1, j + 1 ) );
            pos_atk_coords.push_back( pair<int,int>( i - 1, j - 1 ) );

        }

        break;

    case CHS_PIECE_TYPE::KNIGHT:

        pos_atk_coords.push_back( pair<int,int>( i + 2, j + 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i + 2, j - 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 2, j + 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 2, j - 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i + 1, j + 2 ) );
        pos_atk_coords.push_back( pair<int,int>( i + 1, j - 2 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 1, j + 2 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 1, j - 2 ) );

        break;

    case CHS_PIECE_TYPE::BISHOP:

        // North-East diagonal sweep.
        for( int NE_z = 1; NE_z <= min( top_dist, right_dist ) ; NE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NE_z, j + NE_z ) );
            if( !this->is_sq_empty( i + NE_z, j + NE_z ) ){break;}
        }
        // North-West diagonal sweep.
        for( int NW_z = 1; NW_z <= min( top_dist, left_dist ) ; NW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NW_z, j - NW_z ) );
            if( !this->is_sq_empty( i + NW_z, j - NW_z ) ){break;}
        }
        // South-West diagonal sweep.
        for( int SW_z = 1; SW_z <= min( bottom_dist, left_dist ) ; SW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SW_z, j - SW_z ) );
            if( !this->is_sq_empty( i - SW_z, j - SW_z ) ){break;}
        }
        // South-East diagonal sweep.
        for( int SE_z = 1; SE_z <= min( bottom_dist, right_dist ) ; SE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SE_z, j + SE_z ) );
            if( !this->is_sq_empty( i - SE_z, j + SE_z ) ){break;}
        }

        break;

    case CHS_PIECE_TYPE::ROOK:

        // North sweep.
        for( int N_z = 1; N_z <= top_dist; N_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + N_z, j ) );
            if( !this->is_sq_empty( i + N_z, j ) ){break;}
        }
        // West sweep.
        for( int W_z = 1; W_z <= left_dist; W_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j - W_z ) );
            if( !this->is_sq_empty( i, j - W_z ) ){break;}
        }
        // South sweep.
        for( int S_z = 1; S_z <= bottom_dist; S_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - S_z, j ) );
            if( !this->is_sq_empty( i - S_z, j ) ){break;}
        }
        // East sweep.
        for( int E_z = 1; E_z <= right_dist; E_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j + E_z ) );
            if( !this->is_sq_empty( i, j + E_z ) ){break;}
        }

        break;

    case CHS_PIECE_TYPE::QUEEN:

        // North-East diagonal sweep.
        for( int NE_z = 1; NE_z <= min( top_dist, right_dist ) ; NE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NE_z, j + NE_z ) );
            if( !this->is_sq_empty( i + NE_z, j + NE_z ) ){break;}
        }
        // North-West diagonal sweep.
        for( int NW_z = 1; NW_z <= min( top_dist, left_dist ) ; NW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NW_z, j - NW_z ) );
            if( !this->is_sq_empty( i + NW_z, j - NW_z ) ){break;}
        }
        // South-West diagonal sweep.
        for( int SW_z = 1; SW_z <= min( bottom_dist, left_dist ) ; SW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SW_z, j - SW_z ) );
            if( !this->is_sq_empty( i - SW_z, j - SW_z ) ){break;}
        }
        // South-East diagonal sweep.
        for( int SE_z = 1; SE_z <= min( bottom_dist, right_dist ) ; SE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SE_z, j + SE_z ) );
            if( !this->is_sq_empty( i - SE_z, j + SE_z ) ){break;}
        }

        // North sweep.
        for( int N_z = 1; N_z <= top_dist; N_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + N_z, j ) );
            if( !this->is_sq_empty( i + N_z, j ) ){break;}
        }
        // West sweep.
        for( int W_z = 1; W_z <= left_dist; W_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j - W_z ) );
            if( !this->is_sq_empty( i, j - W_z ) ){break;}
        }
        // South sweep.
        for( int S_z = 1; S_z <= bottom_dist; S_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - S_z, j ) );
            if( !this->is_sq_empty( i - S_z, j ) ){break;}
        }
        // East sweep.
        for( int E_z = 1; E_z <= right_dist; E_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j + E_z ) );
            if( !this->is_sq_empty( i, j + E_z ) ){break;}
        }

        break;

    case CHS_PIECE_TYPE::KING:

        pos_atk_coords.push_back( pair<int,int>( i + 1, j + 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i + 1, j + 0 ) );
        pos_atk_coords.push_back( pair<int,int>( i + 1, j - 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 0, j - 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 1, j - 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 1, j - 0 ) );
        pos_atk_coords.push_back( pair<int,int>( i - 1, j + 1 ) );
        pos_atk_coords.push_back( pair<int,int>( i + 0, j + 1 ) );

        break; 

    default:
        throw runtime_error( "Unrecognized chess piece type." );
    }

    for( pair<int,int> coord_z : pos_atk_coords ){

        // Add to the main attack list if attack is possible.
        if( coord_z.first >= 0 && coord_z.first <= BOARDHEIGHT - 1 &&
            coord_z.second >= 0 && coord_z.second <= BOARDWIDTH - 1 ){
            retVal.push_back( coord_z );
        }

    }

    return retVal;

}


void chess::upd_atk_lists(){

    // Emtpy the existing attack list vectors.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
        this->atk_list_by_W[z].clear();
        this->atk_list_by_B[z].clear();
    }
    
    // Current sub index.
    pair<int,int> coord_z;
    // Current piece being scanned for attacked squares.
    chs_piece pce_z;
    // List of sub coordinates of squares being attacked by the current piece.
    vector< pair<int,int> > atk_list_z;
    // List of linear coordinates of squares being attacked by the current piece.
    vector<int> atk_sub_list_z;

    for( unsigned int z = 0; z < BOARDWIDTH*BOARDHEIGHT; z++ ){

        coord_z = ind2sub(z);
        // Skip if empty.
        if( this->is_sq_empty( coord_z.first, coord_z.second ) ){
            continue;
        }
        // Obtain the target piece.
        pce_z = get_piece_at( coord_z.first, coord_z.second );

        // Obtain the list of all squares attacked by the current piece.
        atk_list_z = get_all_atk_sq( coord_z.first, coord_z.second );
        // Translate into linear indexing.
        atk_sub_list_z = sub2ind( atk_list_z );

        if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

            for( int sq_lin_idx : atk_sub_list_z ){
                this->atk_list_by_W[sq_lin_idx].push_back(z);
            }

        }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){

            for( int sq_lin_idx : atk_sub_list_z ){
                this->atk_list_by_B[sq_lin_idx].push_back(z);
            }

        }else{
            throw runtime_error( "Unrecognized chess piece color." );
        }

    }

}


void chess::upd_all(){
    this->upd_atk_lists();
}


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

int chess::sub2ind( int i, int j ){
    return ( i*BOARDWIDTH + j );
}
int chess::sub2ind( pair<int,int> subIdx ){
    return sub2ind( subIdx.first, subIdx.second );
}
vector<int> chess::sub2ind( vector<pair<int,int>> sub_arr ){
    vector<int> ind_arr = vector<int>( sub_arr.size() );
    for( unsigned int z = 0; z < sub_arr.size(); z++ ){
        ind_arr.at(z) = sub_arr[z].first*BOARDWIDTH + sub_arr[z].second;
    }
    return ind_arr;
}

pair<int,int> chess::ind2sub( int linIdx ){
    int rem_val = linIdx % BOARDWIDTH;
    return pair<int,int>( (linIdx - rem_val)/BOARDWIDTH, rem_val );
}
vector< pair<int,int> > chess::ind2sub( vector<int> linIdxVec ){
    vector< pair<int,int> > subIdxVec;
    subIdxVec.reserve( linIdxVec.size() );
    for( int idx_z : linIdxVec ){
        subIdxVec.push_back( chess::ind2sub( idx_z ) );
    }
    return subIdxVec;
}


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

array<vector<int>,chess::BOARDHEIGHT*chess::BOARDWIDTH> chess::getAtk_list_by_W()
    {return this->atk_list_by_W;}
array<vector<int>,chess::BOARDHEIGHT*chess::BOARDWIDTH> chess::getAtk_list_by_B()
    {return this->atk_list_by_B;}

// ====================================================================== <<<<<

