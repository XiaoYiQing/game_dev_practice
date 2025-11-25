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
//      Class Enum "CHS_AI_OPT" Help Functions
// ====================================================================== >>>>>

string chess::get_CHS_AI_OPT_Str( CHS_AI_OPT tar_CHS_AI_OPT ){
    return string( magic_enum::enum_name( tar_CHS_AI_OPT ) );
}

chess::CHS_AI_OPT chess::get_CHS_AI_OPT_AtIdx( int idx ){
    if( idx >= 0 && idx < chess::CHS_AI_OPT_Count ){
        return static_cast<chess::CHS_AI_OPT>(idx);
    }else{
        throw invalid_argument( "Invalid int index for accessing enum \"CHS_AI_OPT\"." );
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
        color_char = 'w';   break;
    case CHS_PIECE_COLOR::BLACK:
        color_char = 'b';   break;
    case CHS_PIECE_COLOR::NO_C:
        color_char = '-';   break;
    default:
        throw runtime_error("Unrecognized chess piece color enum.");
    }

    char type_char = ' ';
    switch( this->type ){
    case CHS_PIECE_TYPE::NO_P:
        type_char = '-';   break;
    case CHS_PIECE_TYPE::PAWN:
        type_char = 'p';   break;
    case CHS_PIECE_TYPE::KNIGHT:
        type_char = 'n';   break;
    case CHS_PIECE_TYPE::BISHOP:
        type_char = 'b';   break;
    case CHS_PIECE_TYPE::ROOK:
        type_char = 'r';   break;
    case CHS_PIECE_TYPE::QUEEN:
        type_char = 'q';   break;
    case CHS_PIECE_TYPE::KING:
        type_char = 'k';   break;
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

bool chess::chs_move::operator==(const chs_move& other) const{
    bool res = true;
    res = res && ( this->pt_a.first == other.pt_a.first );
    res = res && ( this->pt_a.second == other.pt_a.second );
    res = res && ( this->pt_b.first == other.pt_b.first );
    res = res && ( this->pt_b.second == other.pt_b.second );
    return res;
}

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

    this->verbose = false;

    // Default AI option is standard minmax with AB-pruning.
    AI_opt = CHS_AI_OPT::STD_AB_MM;
    vsAI = false;
    AI_first = false;
    // Define the numerical value to each of the chess piece type.
    this->chs_pce_val_map[ CHS_PIECE_TYPE::NO_P ] = 0;
    this->chs_pce_val_map[ CHS_PIECE_TYPE::PAWN ] = 1;
    this->chs_pce_val_map[ CHS_PIECE_TYPE::KNIGHT ] = 3;
    this->chs_pce_val_map[ CHS_PIECE_TYPE::BISHOP ] = 3;
    this->chs_pce_val_map[ CHS_PIECE_TYPE::ROOK ] = 5;
    this->chs_pce_val_map[ CHS_PIECE_TYPE::QUEEN ] = 9;
    this->chs_pce_val_map[ CHS_PIECE_TYPE::KING ] = 1000;

    AI_proc_flag = false;
    // Set the number of threads to utilize.
    this->thread_to_use = min( 2u, std::thread::hardware_concurrency() );

    this->resetBoard();

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>


void chess::resetStateVars(){

    // Reset all support variables describing the state of the game.
    this->turn_cnt = 0;
    this->no_change_turn_cnt = 0;
    this->en_pass_flag = false;
    this->en_pass_moves.clear();
    this->en_pass_moves.reserve(2);
    this->promo_lock = false;

    this->state = CHS_STATE::ONGOING;

}

void chess::clearBoard(){

    this->resetStateVars();

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
    this->upd_post_play();

}
void chess::resetBoard(){

    if( BOARDHEIGHT != 8 || BOARDWIDTH != 8 ){
        throw runtime_error( "Chess board reset cannot be done with a non-standard chess board dimensions." );
    }

    this->resetStateVars();

    // Insert the last row pieces on both sides.
    unsigned int col_idx = 0;
    unsigned int row_idx = 0;
    this->CHS_board[ row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK );    

    col_idx = 1;
    this->CHS_board[ row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ); 

    col_idx = 2;
    this->CHS_board[ row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ); 

    col_idx = 3;
    this->CHS_board[ row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::BLACK );
    this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ BOARDWIDTH - 1 - col_idx ] = 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK );

    // Insert the pawns.
    row_idx = 1;
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        this->CHS_board[ row_idx ][ j ] = 
            chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE );
        this->CHS_board[ BOARDHEIGHT - 1 - row_idx ][ j ] = 
            chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK );
    }

    // Set all remaining space as empty.
    chess::chs_piece NONE_PIECE( chess::CHS_PIECE_TYPE::NO_P, chess::CHS_PIECE_COLOR::NO_C );
    for( unsigned int i = 2; i < BOARDHEIGHT - 2; i++ ){
        for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
            this->CHS_board[ i ][ j ] = NONE_PIECE;
        }
    }

    // Update all remaining state related variables.
    upd_post_play();

}




void chess::clearSquare( unsigned int i, unsigned int j ){
    if( i >= BOARDHEIGHT || j >= BOARDWIDTH ){
        throw out_of_range( "clearSquare: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j].set_as_empty();
    this->upd_post_play();
}

void chess::set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce ){
    if( i >= BOARDHEIGHT || j >= BOARDWIDTH ){
        throw out_of_range( "set_piece_at: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j] = inPce;
    this->upd_post_play();
}
void chess::set_piece_at_ag_coord( const char c, const unsigned int n, const chs_piece inPce ){
    set_piece_at( n - 1, c - 'a', inPce );
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      AI Related Functions
// ====================================================================== >>>>>

    int chess::gameStateEval(){

        int stateValue = 0;

        // Update the game state before proceeding.
        this->upd_all();

    }

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>


bool chess::promote( unsigned int col_idx, CHS_PIECE_TYPE promo_type ){

    if( !this->promo_lock ){
        if( this->verbose )
            cout << "Pawn promotion is prohibited if the promotion lock is not set." << endl;
        return false;
    }

    chs_piece top_pce = this->get_piece_at( BOARDHEIGHT - 1, col_idx );
    chs_piece bot_pce = this->get_piece_at( 0, col_idx );
    
    // Missing pawn at end row of target column.
    if( top_pce.type != CHS_PIECE_TYPE::PAWN && bot_pce.type != CHS_PIECE_TYPE::PAWN ){
        return false;
    }

    // Both top and bottom of the same column have a pawn (impossible scenario).
    if( top_pce.type == bot_pce.type ){
        throw runtime_error( "Impossible scenario encountered while attempting to promote pawn: two pawns have reached the end row without promoting." );
    }

    // Illegal promotion.
    if( promo_type == CHS_PIECE_TYPE::NO_P || promo_type == CHS_PIECE_TYPE::PAWN || 
        promo_type == CHS_PIECE_TYPE::KING ){
        if( verbose )
            cout << "Illegal pawn promotion attempted." << endl;
        return false;
    }

    // Promote the pawn.
    if( top_pce.type == CHS_PIECE_TYPE::PAWN && top_pce.color == CHS_PIECE_COLOR::WHITE ){
        top_pce.type = promo_type;
        this->set_piece_at( BOARDHEIGHT - 1, col_idx, top_pce );
    }else if( bot_pce.type == CHS_PIECE_TYPE::PAWN && bot_pce.color == CHS_PIECE_COLOR::BLACK ){
        bot_pce.type = promo_type;
        this->set_piece_at( 0, col_idx, bot_pce );
    }else{
        if( verbose )
            cout << "Something wrong about the pawn colors when promoting." << endl;
        return false;
    }

    this->promo_lock = false;
    // Update all states in the game.
    this->upd_all();

    return true;

}


bool chess::play_ag_coord( char c1, int n1, char c2, int n2 ){
    return play( n1 - 1, ( c1 - 'a' ), n2 - 1, ( c2 - 'a' ) );
}

bool chess::play( chs_move tarMove ){
    return this->play( tarMove.pt_a.first, tarMove.pt_a.second, 
        tarMove.pt_b.first, tarMove.pt_b.second );
}

bool chess::play( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft )
{

    // Prevent play if the game is already in a win state.
    if( this->state == CHS_STATE::BWIN || this->state == CHS_STATE::WWIN || 
        this->state == CHS_STATE::DRAW ){
        return false;
    }

    // Record the game before.
    chess game_bef = *this;

    // Promotion lock check.
    if( promo_lock ){
        if( verbose )
            cout << "Play prevented by promotion lock." << endl;
        return false;
    }

    // Special boolean checking whether en-passant possibility has been triggered by a move.
    bool en_pass_posb = false;

    // Obtain the target piece.
    chs_piece currPiece = get_piece_at( i_bef, j_bef );

    if( this->is_move_valid( i_bef, j_bef, i_aft, j_aft ) ){

        // Perform the displacement.
        this->CHS_board[i_aft][j_aft] = this->CHS_board[i_bef][j_bef];
        this->CHS_board[i_aft][j_aft].not_moved = false;
        this->CHS_board[i_bef][j_bef].set_as_empty(); 

        // Only the castling move involves moving more than 1 piece at a time, and must
        // be treated as a special stand-alone case.
        if( currPiece.type == CHS_PIECE_TYPE::KING ){

            int j_displ = (int) j_aft - (int) j_bef;
            
            // Right-side castling.
            if( j_displ == 2 ){
                this->CHS_board[i_aft][j_aft-1] = this->CHS_board[i_aft][BOARDWIDTH-1];
                this->CHS_board[i_aft][j_aft-1].not_moved = false;
                this->CHS_board[i_aft][BOARDWIDTH-1].set_as_empty();

            // Left-side castling.
            }else if( j_displ == -2 ){
                this->CHS_board[i_aft][j_aft+1] = this->CHS_board[i_aft][0];
                this->CHS_board[i_aft][j_aft+1].not_moved = false;
                this->CHS_board[i_aft][0].set_as_empty();
            }

        }

        // The en-passant special trigger case.
        if( currPiece.type == CHS_PIECE_TYPE::PAWN ){            

            // First condition of possiblity of en-passant: pawn moved.
            en_pass_posb = true;
            this->en_pass_moves.clear();

            if( currPiece.color == CHS_PIECE_COLOR::WHITE ){

                // The white pawn jumped two squares from its starting position.
                en_pass_posb = en_pass_posb && i_bef == 1 && i_aft == 3;
                // If the white pawn is not on the first column.
                if( j_bef > 0 && en_pass_posb ){
                    if( get_piece_at( i_aft, j_bef - 1 ).type == CHS_PIECE_TYPE::PAWN &&
                        get_piece_at( i_aft, j_bef - 1 ).color == CHS_PIECE_COLOR::BLACK ){
                        this->en_pass_moves.push_back(
                            chs_move( i_aft, j_bef - 1, i_aft - 1, j_bef )
                        );
                    }
                }
                // If the white pawn is not on the last column.
                if( j_bef < BOARDWIDTH - 1 && en_pass_posb ){
                    if( get_piece_at( i_aft, j_bef + 1 ).type == CHS_PIECE_TYPE::PAWN &&
                        get_piece_at( i_aft, j_bef + 1 ).color == CHS_PIECE_COLOR::BLACK ){
                        this->en_pass_moves.push_back(
                            chs_move( i_aft, j_bef + 1, i_aft - 1, j_bef )
                        );
                    }
                }
                // There is at least one valid en-passant move.
                en_pass_posb = en_pass_posb && this->en_pass_moves.size() > 0;

            }else if( currPiece.color == CHS_PIECE_COLOR::BLACK ){

                // The black pawn jumped two squares from its starting position.
                en_pass_posb = en_pass_posb && i_bef == BOARDHEIGHT - 2 && 
                    i_aft == BOARDHEIGHT - 4;
                // If the black pawn is not on the first column.
                if( j_bef > 0 && en_pass_posb ){
                    if( get_piece_at( i_aft, j_bef - 1 ).type == CHS_PIECE_TYPE::PAWN &&
                        get_piece_at( i_aft, j_bef - 1 ).color == CHS_PIECE_COLOR::WHITE ){
                        this->en_pass_moves.push_back(
                            chs_move( i_aft, j_bef - 1, i_aft + 1, j_bef )
                        );
                    }
                }
                // If the black pawn is not on the last column.
                if( j_bef < BOARDWIDTH - 1 && en_pass_posb ){
                    if( get_piece_at( i_aft, j_bef + 1 ).type == CHS_PIECE_TYPE::PAWN &&
                    get_piece_at( i_aft, j_bef + 1 ).color == CHS_PIECE_COLOR::WHITE ){
                        this->en_pass_moves.push_back(
                            chs_move( i_aft, j_bef + 1, i_aft + 1, j_bef )
                        );
                    }
                }
                // There is at least one valid en-passant move.
                en_pass_posb = en_pass_posb && this->en_pass_moves.size() > 0;

            }else{
                throw runtime_error( "Unrecognized chess color." );
            }  

        }

    }else if( this->is_atk_valid( i_bef, j_bef, i_aft, j_aft ) ){


        // The en-passant attack is a unique attack where the end square is empty.
        bool is_en_pass = this->is_sq_empty( i_aft, j_aft );

        // Perform the attack.
        this->CHS_board[i_aft][j_aft] = this->CHS_board[i_bef][j_bef];
        this->CHS_board[i_aft][j_aft].not_moved = false;
        this->CHS_board[i_bef][j_bef].set_as_empty(); 

        // En-passant unique attack scenario additional step.
        if( is_en_pass ){
            if( currPiece.color == CHS_PIECE_COLOR::WHITE ){
                this->CHS_board[ i_aft - 1 ][j_aft].set_as_empty(); 
            }else if( currPiece.color == CHS_PIECE_COLOR::BLACK ){
                this->CHS_board[ i_aft + 1 ][j_aft].set_as_empty(); 
            }else{
                throw runtime_error( "Unrecognized chess color." );
            }
        }

    }else{
        return false;
    }

    // If the piece played is a pawn and it has reached the end of its column.
    if( currPiece.type == CHS_PIECE_TYPE::PAWN && ( i_aft == 0 || i_aft == BOARDHEIGHT - 1 ) ){
        promo_lock = true;
        promo_point.first = i_aft;
        promo_point.second = j_aft;
    }

    // Turn the en-passant flag to false when conditions are not met.
    if( en_pass_posb ){
        this->en_pass_flag = true;
    }else{
        this->en_pass_flag = false;
        this->en_pass_moves.clear();
    }

    // Increment the turn count.
    this->turn_cnt++;
    // Update all states of the game.
    try{
        this->upd_post_play();
    }catch( runtime_error e ){
        string tmp = e.what();
        string expect_msg = "Black and white kings both in check.";
        if( tmp == expect_msg ){
            *this = game_bef;
            return false;
        }else{
            // Rethrow the error if it is an unexpected runtime error.
            throw e;
        }
    }catch(...){
        throw;
    }

    // Record the game state after.
    CHS_STATE state_aft = this->state;

    // If white is still in check whilst going into black's turn, revert move.
    if( state_aft == CHS_STATE::WCHK && this->is_black_turn() ){
        if( verbose )
            cout << "White still in check in black's turn." << endl;
        *this = game_bef;
        return false;
    }
    // If black is still in check whilst going into white's turn, revert move.
    if( state_aft == CHS_STATE::BCHK && this->is_white_turn() ){
        if( verbose )
            cout << "Black still in check in white's turn." << endl;
        *this = game_bef;
        return false;
    }

    return true;

}

bool chess::ply_ag_comm( string alg_comm ){

// ---------------------------------------------------------------------- >>>>>
//      Resign Special Command Parse
// ---------------------------------------------------------------------- >>>>>

    // White won by black resignation!
    if( alg_comm == "1-0" ){
        this->state = CHS_STATE::WWIN;
        return true;
    // Black won by white resignation!
    }else if( alg_comm == "0-1" ){
        this->state = CHS_STATE::BWIN;
        return true;
    // Draw by mutual agreement.
    }else if( alg_comm == "½-½" ){
        this->state = CHS_STATE::DRAW;
        return true;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Castling Special Command Parse
// ---------------------------------------------------------------------- >>>>>

    if( alg_comm == "O-O" || alg_comm == "0-0" ){

        unsigned int row_idx = 0;
        if( this->is_white_turn() ){
            row_idx = 0;
        }else{
            row_idx = BOARDHEIGHT - 1;
        }

        if( this->get_piece_at( row_idx, 4 ).type == CHS_PIECE_TYPE::KING ){
            chs_move castle_mov( row_idx, 4, row_idx, 6 );
            return ply( castle_mov );
        }
        throw runtime_error( "Caslting move currently not valid." );

    }else if( alg_comm == "O-O-O" || alg_comm == "0-0-0" ){

        unsigned int row_idx = 0;
        if( this->is_white_turn() ){
            row_idx = 0;
        }else{
            row_idx = BOARDHEIGHT - 1;
        }

        if( this->get_piece_at( row_idx, 4 ).type == CHS_PIECE_TYPE::KING ){
            chs_move castle_mov( row_idx, 4, row_idx, 2 );
            return ply( castle_mov );
        }
        throw runtime_error( "Castling move currently not valid." );

    }

// ---------------------------------------------------------------------- <<<<<

    chs_move ret_move;
    // Obtain turn indicator.
    CHS_PIECE_COLOR pce_color = this->is_white_turn() ? CHS_PIECE_COLOR::WHITE : CHS_PIECE_COLOR::BLACK;
    // Variable indicating type of current piece.
    CHS_PIECE_TYPE pce_type;

    // A flag indicating whether the game is in check ('+') or checkmate state ('#').
    char check_flag = ' ';

// ---------------------------------------------------------------------- >>>>>
//      Check Status Flag Parse (Last Char(s))
// ---------------------------------------------------------------------- >>>>>

    // Take out last character is it is the check status flag.
    if( !std::isalnum( alg_comm[ alg_comm.size() - 1 ] ) ){
        if( alg_comm[ alg_comm.size() - 1 ] == '+' || alg_comm[ alg_comm.size() - 1 ] == '#' ){
            check_flag = alg_comm[ alg_comm.size() - 1 ];
            alg_comm = alg_comm.substr( 0, alg_comm.size() - 1 );
        }
    }

// ---------------------------------------------------------------------- <<<<<



// ---------------------------------------------------------------------- >>>>>
//      Piece Type Flag Parse (First char)
// ---------------------------------------------------------------------- >>>>>

    // Initialize the promotion target.
    CHS_PIECE_TYPE promo_tar = CHS_PIECE_TYPE::NO_P;

    // If the first letter is uppercase, non-pawn.
    if( (unsigned int)( alg_comm.at(0) - 'A' ) < 26 ){
        
        switch( alg_comm.at(0) ){
        case( 'B' ):
            pce_type = CHS_PIECE_TYPE::BISHOP;  break;
        case( 'N' ):
            pce_type = CHS_PIECE_TYPE::KNIGHT;  break;
        case( 'R' ):
            pce_type = CHS_PIECE_TYPE::ROOK;    break;
        case( 'Q' ):
            pce_type = CHS_PIECE_TYPE::QUEEN;   break;
        case( 'K' ):
            pce_type = CHS_PIECE_TYPE::KING;    break;
        default:
            throw invalid_argument( "First char is an invalid uppercase letter." );
            break;
        };

        // Take out the first char.
        alg_comm = alg_comm.substr( 1, alg_comm.size() );

    // If the first letter is not uppercase, pawn.
    }else{

        pce_type = CHS_PIECE_TYPE::PAWN;

        if( (unsigned int)( alg_comm.at( alg_comm.size() - 1 ) - 'A' ) < 26 ){

            switch( alg_comm.at( alg_comm.size() - 1 ) ){
            case( 'B' ):
                promo_tar = CHS_PIECE_TYPE::BISHOP; break;
            case( 'N' ):
                promo_tar = CHS_PIECE_TYPE::KNIGHT; break;
            case( 'R' ):
                promo_tar = CHS_PIECE_TYPE::ROOK;   break;
            case( 'Q' ):
                promo_tar = CHS_PIECE_TYPE::QUEEN;  break;
            case( 'K' ):
                promo_tar = CHS_PIECE_TYPE::KING;   break;
            default:
                throw invalid_argument( "Pawn promotion indicator is not a valid upper case letter." );
                break;
            }

            // Take out the promotion tag.
            alg_comm = alg_comm.substr( 0, alg_comm.size() - 1 );

        }

    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Attack Flag Parse (Mid 'x' symbol)
// ---------------------------------------------------------------------- >>>>>

    // Flag indicating whether the play is an attack or no.
    bool is_atk = false;
    // Initialize the string algebraic coordinates.
    string bef_coord_str = "";
    string aft_coord_str = "";

    // Subdivide the current remaining string into the before and after algebraic coordinates.
    for( unsigned int z = 0; z < alg_comm.size(); z++ ){
        if( alg_comm[z] == 'x' ){
            is_atk = true;
            bef_coord_str = alg_comm.substr( 0, z );
            aft_coord_str = alg_comm.substr( z + 1, alg_comm.size() - z - 1 );
        }
    }
    if( !is_atk ){
        aft_coord_str = alg_comm.substr( alg_comm.size() - 2, 2 );
        bef_coord_str = alg_comm.substr( 0, alg_comm.size() - 2 );
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Start and End Coordinates Parse And Then Ply
// ---------------------------------------------------------------------- >>>>>

    // Initialize the final coordinates.
    pair<int,int> aft_coord(-1,-1);
    pair<int,int> bef_coord(-1,-1);

    // Parse the after coordinate.
    if( aft_coord_str.size() == 2 ){
        if( std::isdigit( aft_coord_str[1] ) && std::isalpha( aft_coord_str[0] ) ){
            aft_coord = alg_to_cart( aft_coord_str[0], (int) aft_coord_str[1] - '0' );
        }else{
            throw invalid_argument( "Algebraic ending coordinate must be a two char pair of an alphabet letter (file) and a digit (rank)." );
        }
        
    }else{
        throw invalid_argument( "Algebraic abbreviated play notation must at least have ending coordinate (If not a special move)." );
    }

    // Parse the before coordinate.
    if( bef_coord_str.size() == 2 ){

        if( std::isdigit( bef_coord_str[1] ) && std::isalpha( bef_coord_str[0] ) ){
            bef_coord = alg_to_cart( bef_coord_str[0], (int) bef_coord_str[1] - '0' );
        }else{
            throw invalid_argument( "Algebraic starting coordinate of two char must consist of an alphabet letter (file) and a digit (rank)." );
        }

    // Case when the before coordinate is abbreviated to a single character.
    }else if( bef_coord_str.size() == 1 ){

        if( std::isdigit( bef_coord_str[0] ) ){

            int row_idx = (int) ( bef_coord_str[0] - '0' ) - 1;
            int fnd_cnt = 0;
            // Scan through the specified row for target piece.
            for( unsigned int z = 0; z < BOARDWIDTH; z++ ){
                pair<int,int> coord_z( row_idx, z );
                if( this->get_piece_at( coord_z ).type == pce_type && 
                    this->get_piece_at( coord_z ).color == pce_color )
                {
                    if( is_atk ){
                        if( this->is_atk_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }
                }
            }
            // If more than one correct piece is identified on same row, algebraic 
            // coord is invalid.
            if( fnd_cnt > 1 ){
                throw runtime_error( "Two identical pieces share the same rank and cannot be differentiated with the given algebraic coordinate." );
            }else if( fnd_cnt == 0 ){
                throw runtime_error( "No piece found on the board to play which fits the given algebraic coordinate." );
            }

        }else if( std::isalpha( bef_coord_str[0] ) ){

            int col_idx = (int) ( bef_coord_str[0] - 'a' );
            int fnd_cnt = 0;
            // Scan through the specified column for target piece.
            for( unsigned int z = 0; z < BOARDHEIGHT; z++ ){
                pair<int,int> coord_z( z, col_idx );
                if( this->get_piece_at( coord_z ).type == pce_type && 
                    this->get_piece_at( coord_z ).color == pce_color )
                {
                    if( is_atk ){
                        if( this->is_atk_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }
                }
            }
            // If more than one correct piece is identified on same column, algebraic 
            // coord is invalid.
            if( fnd_cnt > 1 ){
                throw runtime_error( "Two identical pieces share the same file and cannot be differentiated with the given algebraic coordinate." );
            }else if( fnd_cnt == 0 ){
                throw runtime_error( "No piece found on the board to play which fits the given algebraic coordinate." );
            }

        }else{
            throw invalid_argument( "Algebraic starting coordinate of one char must be either an alphabet letter (file) or a digit (rank)." );
        }

    // Case when the before coordinate is omitted.
    }else if( bef_coord_str.size() == 0 ){

        int fnd_cnt = 0;
        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
            pair<int,int> coord_z = chess::ind2sub(z);
            if( this->get_piece_at( coord_z ).type == pce_type && 
                this->get_piece_at( coord_z ).color == pce_color )
            {
                
                if( is_atk ){
                    if( this->is_atk_valid( coord_z, aft_coord ) ){
                        bef_coord = coord_z;
                        fnd_cnt++;
                    }
                }else{
                    if( this->is_move_valid( coord_z, aft_coord ) ){
                        bef_coord = coord_z;
                        fnd_cnt++;
                    }
                }
                
            }
        }
        // If more than one correct piece is identified on same column, algebraic 
        // coord is invalid.
        if( fnd_cnt > 1 ){
            throw runtime_error( "Two identical pieces share the same file and cannot be differentiated with the given algebraic coordinate." );
        }else if( fnd_cnt == 0 ){
            throw runtime_error( "No piece found on the board to play which fits the given algebraic coordinate." );
        }

    }else{
        throw invalid_argument( "Invalid algebraic play notation." );
    }


    bool res_bool = this->ply( chs_move( bef_coord, aft_coord ) );
    // Perform pawn promotion, if specified correctly in the command.
    if( promo_tar != CHS_PIECE_TYPE::NO_P && promo_tar != CHS_PIECE_TYPE::PAWN ){
        if( pce_type == CHS_PIECE_TYPE::PAWN ){
            this->promote( aft_coord.second, promo_tar );
        }else{
            throw runtime_error( "A pawn promotion is initialized even though the target of promotion isn't a pawn." );
        }
    }

    return res_bool;
// ---------------------------------------------------------------------- <<<<<

}

bool chess::ply_ag_coord( char c1, int n1, char c2, int n2 ){
    return ply( n1 - 1, ( c1 - 'a' ), n2 - 1, ( c2 - 'a' ) );
}

bool chess::ply( chs_move tarMove ){
    return this->ply( tarMove.pt_a.first, tarMove.pt_a.second, 
        tarMove.pt_b.first, tarMove.pt_b.second );
}


bool chess::ply( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft )
{
    bool play_success = false;
    play_success = this->play( i_bef, j_bef, i_aft, j_aft );

    // Check if the play induces an endgame state.
    if( play_success ){
        this->upd_end_game_state();
    }

    return play_success;
}

bool chess::is_move_valid( pair<int,int> coord_bef, pair<int,int> coord_aft ) const{
    return this->is_move_valid( coord_bef.first, coord_bef.second, 
        coord_aft.first, coord_aft.second );
}

bool chess::is_move_valid( chs_move tarMov ) const{
    return this->is_move_valid( tarMov.pt_a, tarMov.pt_b );
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
        unsigned int i_aft, unsigned int j_aft ) const
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
        if( tarPce.not_moved ){
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


bool chess::is_atk_valid( pair<int,int> coord_bef, pair<int,int> coord_aft ) const{
    return this->is_atk_valid( coord_bef.first, coord_bef.second, 
        coord_aft.first, coord_aft.second );
}

bool chess::is_atk_valid( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft  ) const
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

    // Obtain the color of the current piece.
    CHS_PIECE_COLOR tarColor = tarPce.color;
    // Turn check.
    if( this->turn_cnt % 2 == 0 && tarColor != CHS_PIECE_COLOR::WHITE ||
        this->turn_cnt % 2 == 1 && tarColor != CHS_PIECE_COLOR::BLACK ){
        return false;
    }

    // The unique scenario of en-passant pawn attack superseeds all remaining checks.
    if( tarPce.type == CHS_PIECE_TYPE::PAWN && this->en_pass_flag ){

        bool is_en_pass = false;

        // Determine if the current attack matches any of the currently active
        // en-passant possiblities.
        for( unsigned int z = 0; z < this->en_pass_moves.size(); z++ ){

            is_en_pass = is_en_pass ||
            ( en_pass_moves[z].pt_a.first == i_bef &&
            en_pass_moves[z].pt_a.second == j_bef &&
            en_pass_moves[z].pt_b.first == i_aft &&
            en_pass_moves[z].pt_b.second == j_aft );

        }

        if( is_en_pass ){
            return true;
        }

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

            auto tmp = atk_list_by_B[ sub2ind( i_aft, j_aft ) ];

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


bool chess::is_white_turn(){
    return ( this->turn_cnt % 2 == 0 );
}
bool chess::is_black_turn(){
    return ( this->turn_cnt % 2 != 0 );
}

bool chess::is_sq_empty( int i, int j ) const{
    if( i < 0 || i >= BOARDHEIGHT || j < 0 || j >= BOARDWIDTH ){
        throw invalid_argument( "Invalid chess board coordinates." );
    }
    return ( this->CHS_board[i][j].type == CHS_PIECE_TYPE::NO_P && 
        this->CHS_board[i][j].color == CHS_PIECE_COLOR::NO_C );
}


vector< pair<int,int> > chess::get_all_atk_sq( int i, int j ) const{

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


vector< pair<int,int> > chess::get_all_atk_sq_spec( int i, int j ) const{

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
            if( !this->is_sq_empty( i + NE_z, j + NE_z ) && 
                !( CHS_board[i + NE_z][j + NE_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i + NE_z][j + NE_z].color != atk_piece.color ) )
                {break;}
        }
        // North-West diagonal sweep.
        for( int NW_z = 1; NW_z <= min( top_dist, left_dist ) ; NW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NW_z, j - NW_z ) );
            if( !this->is_sq_empty( i + NW_z, j - NW_z ) && 
                !( CHS_board[i + NW_z][j - NW_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i + NW_z][j - NW_z].color != atk_piece.color ) )
                {break;}
        }
        // South-West diagonal sweep.
        for( int SW_z = 1; SW_z <= min( bottom_dist, left_dist ) ; SW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SW_z, j - SW_z ) );
            if( !this->is_sq_empty( i - SW_z, j - SW_z ) && 
                !( CHS_board[i - SW_z][j - SW_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i - SW_z][j - SW_z].color != atk_piece.color ) )
                {break;}
        }
        // South-East diagonal sweep.
        for( int SE_z = 1; SE_z <= min( bottom_dist, right_dist ) ; SE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SE_z, j + SE_z ) );
            if( !this->is_sq_empty( i - SE_z, j + SE_z ) && 
                !( CHS_board[i - SE_z][j + SE_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i - SE_z][j + SE_z].color != atk_piece.color ) )
                {break;}
        }

        break;

    case CHS_PIECE_TYPE::ROOK:

        // North sweep.
        for( int N_z = 1; N_z <= top_dist; N_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + N_z, j ) );
            if( !this->is_sq_empty( i + N_z, j ) && 
                !( CHS_board[i + N_z][j].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i + N_z][j].color != atk_piece.color ) )
                {break;}
        }
        // West sweep.
        for( int W_z = 1; W_z <= left_dist; W_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j - W_z ) );
            if( !this->is_sq_empty( i, j - W_z ) && 
                !( CHS_board[i][j - W_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i][j - W_z].color != atk_piece.color ) )
                {break;}
        }
        // South sweep.
        for( int S_z = 1; S_z <= bottom_dist; S_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - S_z, j ) );
            if( !this->is_sq_empty( i - S_z, j ) && 
                !( CHS_board[i - S_z][j].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i - S_z][j].color != atk_piece.color ) )
                {break;}
        }
        // East sweep.
        for( int E_z = 1; E_z <= right_dist; E_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j + E_z ) );
            if( !this->is_sq_empty( i, j + E_z ) && 
                !( CHS_board[i][j + E_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i][j + E_z].color != atk_piece.color ) )
                {break;}
        }

        break;

    case CHS_PIECE_TYPE::QUEEN:

        // North-East diagonal sweep.
        for( int NE_z = 1; NE_z <= min( top_dist, right_dist ) ; NE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NE_z, j + NE_z ) );
            if( !this->is_sq_empty( i + NE_z, j + NE_z ) && 
                !( CHS_board[i + NE_z][j + NE_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i + NE_z][j + NE_z].color != atk_piece.color ) )
                {break;}
        }
        // North-West diagonal sweep.
        for( int NW_z = 1; NW_z <= min( top_dist, left_dist ) ; NW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + NW_z, j - NW_z ) );
            if( !this->is_sq_empty( i + NW_z, j - NW_z ) && 
                !( CHS_board[i + NW_z][j - NW_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i + NW_z][j - NW_z].color != atk_piece.color ) )
                {break;}
        }
        // South-West diagonal sweep.
        for( int SW_z = 1; SW_z <= min( bottom_dist, left_dist ) ; SW_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SW_z, j - SW_z ) );
            if( !this->is_sq_empty( i - SW_z, j - SW_z ) && 
                !( CHS_board[i - SW_z][j - SW_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i - SW_z][j - SW_z].color != atk_piece.color ) )
                {break;}
        }
        // South-East diagonal sweep.
        for( int SE_z = 1; SE_z <= min( bottom_dist, right_dist ) ; SE_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - SE_z, j + SE_z ) );
            if( !this->is_sq_empty( i - SE_z, j + SE_z ) && 
                !( CHS_board[i - SE_z][j + SE_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i - SE_z][j + SE_z].color != atk_piece.color ) )
                {break;}
        }

        // North sweep.
        for( int N_z = 1; N_z <= top_dist; N_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i + N_z, j ) );
            if( !this->is_sq_empty( i + N_z, j ) && 
                !( CHS_board[i + N_z][j].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i + N_z][j].color != atk_piece.color ) )
                {break;}
        }
        // West sweep.
        for( int W_z = 1; W_z <= left_dist; W_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j - W_z ) );
            if( !this->is_sq_empty( i, j - W_z ) && 
                !( CHS_board[i][j - W_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i][j - W_z].color != atk_piece.color ) )
                {break;}
        }
        // South sweep.
        for( int S_z = 1; S_z <= bottom_dist; S_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i - S_z, j ) );
            if( !this->is_sq_empty( i - S_z, j ) && 
                !( CHS_board[i - S_z][j].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i - S_z][j].color != atk_piece.color ) )
                {break;}
        }
        // East sweep.
        for( int E_z = 1; E_z <= right_dist; E_z++ ){
            pos_atk_coords.push_back( pair<int,int>( i, j + E_z ) );
            if( !this->is_sq_empty( i, j + E_z ) && 
                !( CHS_board[i][j + E_z].type == CHS_PIECE_TYPE::KING &&
                CHS_board[i][j + E_z].color != atk_piece.color ) )
                {break;}
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


vector< pair<int,int> > chess::get_all_valid_atk_sq( int i, int j ) const{

    vector<pair<int,int>> all_atk_sq = this->get_all_atk_sq(i,j);
    vector<pair<int,int>> all_valid_atk_sq;
    all_valid_atk_sq.reserve( all_atk_sq.size() );

    for( pair<int,int> atk_sq_z : all_atk_sq ){

        if( is_atk_valid( i, j, atk_sq_z.first, atk_sq_z.second ) ){
            all_valid_atk_sq.push_back( atk_sq_z );
        }

    }

    return all_valid_atk_sq;

}


vector< pair<int,int> > chess::get_all_valid_move_sq( int i, int j ) const{

    // Obtain the target piece.
    chs_piece tarPce = this->get_piece_at( i, j );
    // Obtain the linear index of the target.
    int tarIndIdx = chess::sub2ind(i,j);

    // Initialize valid move vector
    vector< pair<int,int> > val_mov_vec;
    // Initialize attack list from (i, j)
    vector<int> atk_list_fr_ij;

    if( tarPce.color == CHS_PIECE_COLOR::WHITE ){

        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

            for( int ind_v : this->atk_list_by_W[z] ){
                if( tarIndIdx == ind_v ){
                    atk_list_fr_ij.push_back( z );
                    break;
                }
            }

        }

    }else if( tarPce.color == CHS_PIECE_COLOR::BLACK ){

        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

            for( int ind_v : this->atk_list_by_B[z] ){
                if( tarIndIdx == ind_v ){
                    atk_list_fr_ij.push_back( z );
                    break;
                }
            }

        }
        
    }else{
        // throw runtime_error( "Unrecognized chess piece color." );
        return val_mov_vec;
    }

    
    
    for( int atk_ij: atk_list_fr_ij ){

        pair<int,int> atk_ij_coord = chess::ind2sub( atk_ij );

        if( this->is_move_valid( i, j, atk_ij_coord.first, atk_ij_coord.second ) ){
            val_mov_vec.push_back( atk_ij_coord );
        }
        
    }

    if( tarPce.type == CHS_PIECE_TYPE::PAWN ){

        int sign_mult = 1;
        tarPce.color == CHS_PIECE_COLOR::BLACK ? sign_mult = -1 : sign_mult = 1;

        if( this->is_move_valid( i, j, i + sign_mult * 1, j ) ){
            val_mov_vec.push_back( pair<int,int>( i + sign_mult * 1, j ) );
        }
        if( this->is_move_valid( i, j, i + sign_mult * 2, j ) ){
            val_mov_vec.push_back( pair<int,int>( i + sign_mult * 2, j ) );
        }
       
    }
    if( tarPce.type == CHS_PIECE_TYPE::KING ){

        if( tarPce.not_moved ){
            // Right castling.
            if( this->is_move_valid( i, j, i, j + 2 ) ){
                val_mov_vec.push_back( pair<int,int>( i, j + 2 ) );
            }
            // Left castling.
            if( this->is_move_valid( i, j, i, j - 2 ) ){
                val_mov_vec.push_back( pair<int,int>( i, j - 2 ) );
            }
        }

    }

    return val_mov_vec;

}


vector<chess::chs_move> chess::get_all_valid_moves() const{

    vector<chess::chs_move> retVec;
    retVec.reserve( 200 );

    pair<int,int> sub_idx_z;
    vector< pair<int,int> > move_sq_list_z;
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        // Obtain current 2D coordinate.
        sub_idx_z = ind2sub(z);
        // Obtain all possible moves (if any) for the piece (if it exists) at the 
        // current coordinate 
        move_sq_list_z = get_all_valid_move_sq( sub_idx_z.first, sub_idx_z.second );

        // Add all current piece's possible moves to the batch.
        for( pair<int,int> move_v : move_sq_list_z ){
            retVec.push_back( chs_move( sub_idx_z.first, sub_idx_z.second, 
                move_v.first, move_v.second ) );
        }

    }

    retVec.shrink_to_fit();

    return retVec;

}


vector<chess::chs_move> chess::get_all_valid_atks() const{

    vector<chess::chs_move> retVec;
    retVec.reserve( 200 );

    pair<int,int> sub_idx_z;
    vector< pair<int,int> > atk_sq_list_z;

    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        // Obtain current 2D coordinate.
        sub_idx_z = ind2sub(z);
        // Obtain all possible moves (if any) for the piece (if it exists) at the 
        // current coordinate 
        atk_sq_list_z = get_all_valid_atk_sq( sub_idx_z.first, sub_idx_z.second );

        // Add all current piece's possible moves to the batch.
        for( pair<int,int> move_v : atk_sq_list_z ){
            retVec.push_back( chs_move( sub_idx_z.first, sub_idx_z.second, 
                move_v.first, move_v.second ) );
        }

    }

    retVec.shrink_to_fit();

    return retVec;

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
        // atk_list_z = get_all_atk_sq( coord_z.first, coord_z.second );
        atk_list_z = get_all_atk_sq_spec( coord_z.first, coord_z.second );
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

    if( this->en_pass_flag ){

        for( chs_move en_pass_move : this->en_pass_moves ){
            
            int def_ind_z = sub2ind( en_pass_move.pt_a.first, en_pass_move.pt_b.second );
            int atk_ind_z = sub2ind( en_pass_move.pt_a.first, en_pass_move.pt_a.second );

            // Attacker is black.
            if( en_pass_move.pt_a.first == 3 ){
                atk_list_by_B[ def_ind_z ].push_back( atk_ind_z );

            // Attacker is white.
            }else if( en_pass_move.pt_a.first == BOARDHEIGHT - 4 ){
                atk_list_by_W[ def_ind_z ].push_back( atk_ind_z );
            }

        }

    }

}


void chess::upd_mid_game_state(){

    // Set the state to the none case.
    this->state = CHS_STATE::NO_S;

    // Initialize current 2D coordinate variable.
    pair<int,int> sub_idx_z;
    // Initialize current chess piece.
    chs_piece pce_z;

    // Perform a full board scan to determine checks.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        sub_idx_z = ind2sub(z);
        pce_z = this->get_piece_at( sub_idx_z.first, sub_idx_z.second );

        if( pce_z.type == CHS_PIECE_TYPE::KING ){
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

                if( this->atk_list_by_B[z].size() != 0 ){
                    if( state == CHS_STATE::BCHK ){
                        throw runtime_error( "Black and white kings both in check." );
                    }else{
                        state = CHS_STATE::WCHK;
                    }
                }
                

            }
            if( pce_z.color == CHS_PIECE_COLOR::BLACK ){

                if( this->atk_list_by_W[z].size() != 0 ){
                    if( state == CHS_STATE::WCHK ){
                        throw runtime_error( "Black and white kings both in check." );
                    }else{
                        state = CHS_STATE::BCHK;
                    }
                }
                
            }
            if( pce_z.color == CHS_PIECE_COLOR::NO_C ){
                throw runtime_error( "Unrecognized chess piece color." );
            }
        }

    }

    // If no state has been determined to this point, set as on going by default.
    if( this->state == CHS_STATE::NO_S ){
        this->state = CHS_STATE::ONGOING;
    }

}


vector< string > chess::get_all_psbl_alg_comm() const{

    // Obtain all current possible plays.
    vector<chs_move> all_plays = this->get_all_valid_moves();
    vector<chs_move> all_atks = this->get_all_valid_atks();
    all_plays.insert( all_plays.end(), all_atks.begin(), all_atks.end() );

    // Initialize final vector of algebraic commands.
    vector< string > alg_comm_vec;
    alg_comm_vec.reserve( all_plays.size() + 12 );
    
    string alg_comm_z = "";         // Current algebraic command being constructed.
    CHS_PIECE_TYPE pce_type_z;      // The chess piece type of the current piece subject to play.
    pair<char,int> str_alg_z;       // Current piece starting algebraic position.
    pair<char,int> end_alg_z;       // Current piece ending algebraic position (after play).

    for( chs_move play_z : all_plays ){

        alg_comm_z = "";

        pce_type_z = this->get_piece_at( play_z.pt_a ).type;
        switch( pce_type_z ){
        case CHS_PIECE_TYPE::PAWN:
            break;
        case CHS_PIECE_TYPE::KNIGHT:
            alg_comm_z += 'N';
            break;
        case CHS_PIECE_TYPE::BISHOP:
            alg_comm_z += 'B';
            break;
        case CHS_PIECE_TYPE::ROOK:
            alg_comm_z += 'R';
            break;
        case CHS_PIECE_TYPE::QUEEN:
            alg_comm_z += 'Q';
            break;
        case CHS_PIECE_TYPE::KING:
            alg_comm_z += 'K';
            break;
        default:
            throw runtime_error( "Non-recognized chess piece type." );
        }

        str_alg_z = cart_to_alg( play_z.pt_a );
        end_alg_z = cart_to_alg( play_z.pt_b );

        alg_comm_z += str_alg_z.first;
        alg_comm_z += to_string( str_alg_z.second );
        alg_comm_z += end_alg_z.first;
        alg_comm_z += to_string( end_alg_z.second );

        

        // Special promotion options when a pawn is played to the last row.
        if( pce_type_z == CHS_PIECE_TYPE::PAWN && ( play_z.pt_b.first == 0 || 
            play_z.pt_b.first == chess::BOARDHEIGHT - 1 ) )
        {
            alg_comm_vec.push_back( alg_comm_z + 'N' );
            alg_comm_vec.push_back( alg_comm_z + 'B' );
            alg_comm_vec.push_back( alg_comm_z + 'R' );
            alg_comm_vec.push_back( alg_comm_z + 'Q' );

        // Any other case, just add the command to the list.
        }else{
            alg_comm_vec.push_back( alg_comm_z );
        }

    }


    

    alg_comm_vec.shrink_to_fit();
    
    return alg_comm_vec;

}


bool chess::is_check_mate(){

    // If the check state is true, determine if it is a checkmate.
    if( this->state == CHS_STATE::WCHK ){

        // Create a copy of the game.
        chess game_copy = *this;
        // Force white to play.
        game_copy.setTurn_cnt(0);
        // Turn verbose to false.
        game_copy.setVerbose(false);

        // Obtain all possible white plays.
        vector<chs_move> all_plays = game_copy.get_all_valid_moves();
        vector<chs_move> tmp = game_copy.get_all_valid_atks();
        all_plays.insert( all_plays.end(), tmp.begin(), tmp.end() );

        // Try to play all possibilities and check if the white check state 
        // changes.
        for( chs_move play_z : all_plays ){
            
            if( game_copy.play( play_z ) ){
                if( game_copy.getState() == CHS_STATE::WCHK ){
                    // If the play did not pull white out of check state, continue trying
                    // by resetting the copy to the starting check state.
                    game_copy = *this;
                    game_copy.setTurn_cnt(0);
                    game_copy.setVerbose(false);
                }else{
                    // Any move that successfully pulls white out of the check state is proof
                    // that the check is not a mate.
                    return false;
                }
            }

        }

        return true;

    }else if( state == CHS_STATE::BCHK ){

        // Create a copy of the game.
        chess game_copy = *this;
        // Force black to play.
        game_copy.setTurn_cnt(1);

        // Obtain all possible black plays.
        vector<chs_move> all_plays = game_copy.get_all_valid_moves();
        vector<chs_move> tmp = game_copy.get_all_valid_atks();
        all_plays.insert( all_plays.end(), tmp.begin(), tmp.end() );

        // Try to play all possibilities and check if the black check state 
        // changes.
        for( chs_move play_z : all_plays ){
            
            if( game_copy.play( play_z ) ){
                if( game_copy.getState() == CHS_STATE::BCHK ){
                    // If the play did not pull black out of check state, continue trying
                    // by resetting the copy to the starting check state.
                    game_copy = *this;
                    game_copy.setTurn_cnt(0);
                    game_copy.setVerbose(false);
                }else{
                    // Any move that successfully pulls black out of the check state is proof
                    // that the check is not a mate.
                    return false;
                }
            }

        }

        return true;

    }else{

        return false;

    }

}


bool chess::is_draw(){

    // State and/or lock check. A draw cannot be declared if the game
    // is not in an ongoing state or if is locked under some special
    // conditions such as awaiting a pawn promotion.
    if( this->promo_lock || this->state != CHS_STATE::ONGOING ){
        return false;
    }

    // Initialize return variable.
    bool is_draw = true;

// ---------------------------------------------------------------------- >>>>>
//      Stalemate Check
// ---------------------------------------------------------------------- >>>>>

    bool no_valid_moves = false;
    // If there is no move possible at all, stalemate.
    no_valid_moves = this->get_all_valid_atks().size() == 0 && 
        this->get_all_valid_moves().size() == 0;
    if( no_valid_moves ){
        if( verbose )
            cout << "Stalemate!!" << endl;
        return true;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Material Insufficiency Check
// ---------------------------------------------------------------------- >>>>>

    // [0] King, [1] Queen, [2] rook, [3] bishop, [4] knight, [5] pawn.
    // Create vector of numerical count.
    vector<unsigned int> B_pce_cnt = vector<unsigned int>(6,0);
    vector<unsigned int> W_pce_cnt = vector<unsigned int>(6,0);
    vector<unsigned int> total_pce_cnt = vector<unsigned int>(6,0);

    // Initialize piece variable.
    chs_piece pce_z;

    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        // Obtain current piece.
        pce_z = this->get_piece_at( chess::ind2sub(z) );
        switch( pce_z.type ){
        
        case CHS_PIECE_TYPE::KING:
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){
                W_pce_cnt[0]++;
            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){
                B_pce_cnt[0]++;
            }
            break;
        
        case CHS_PIECE_TYPE::QUEEN:
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){
                W_pce_cnt[1]++;
            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){
                B_pce_cnt[1]++;
            }
            break;

        case CHS_PIECE_TYPE::ROOK:
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){
                W_pce_cnt[2]++;
            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){
                B_pce_cnt[2]++;
            }
            break;

        case CHS_PIECE_TYPE::BISHOP:
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){
                W_pce_cnt[3]++;
            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){
                B_pce_cnt[3]++;
            }
            break;

        case CHS_PIECE_TYPE::KNIGHT:
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){
                W_pce_cnt[4]++;
            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){
                B_pce_cnt[4]++;
            }
            break;

        case CHS_PIECE_TYPE::PAWN:
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){
                W_pce_cnt[5]++;
            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){
                B_pce_cnt[5]++;
            }
            break;

        default:
        
            break;

        };

    }

    // [0] King, [1] Queen, [2] rook, [3] bishop, [4] knight, [5] pawn.
    for( unsigned int z = 0; z < W_pce_cnt.size(); z++ ){
        total_pce_cnt[z] = B_pce_cnt[z] + W_pce_cnt[z];
    }


    is_draw = is_draw && ( total_pce_cnt[1] == 0 );
    is_draw = is_draw && ( total_pce_cnt[2] == 0 );
    is_draw = is_draw && ( total_pce_cnt[5] == 0 );
    // If any pawn, rook or queen, no draw.
    if( !is_draw ){
        return is_draw;
    }

    is_draw = is_draw && ( B_pce_cnt[3] <= 1 );
    is_draw = is_draw && ( B_pce_cnt[4] <= 1 );

    bool B_insuf = true;
    bool W_insuf = true;

    // No knight.
    if( B_pce_cnt[4] == 0 ){
        
        // 1 bishop only.
        if( B_pce_cnt[3] <= 1 ){
            B_insuf = true;
        // 2 or more bishop only.
        }else{
            /*
            TODO: In actuality, there is ONE edge case. If all bishops are on 
            the same color spot, we still have insufficient material no matter 
            the number of bishops.
            */
            B_insuf = false;
        }

    // One knight and at least one bishop is sufficient.
    }else if( B_pce_cnt[4] == 1 ){

        if( B_pce_cnt[3] == 0 ){
            B_insuf = true;
        }else{
            B_insuf = false;
        }
    
    // At least two knight is sufficient.
    }else{
        B_insuf = false;
    }

    // No knight.
    if( W_pce_cnt[4] == 0 ){
        
        // 1 bishop only.
        if( W_pce_cnt[3] <= 1 ){
            W_insuf = true;
        // 2 or more bishop only.
        }else{
            /*
            TODO: In actuality, there is ONE edge case. If all bishops are on 
            the same color spot, we still have insufficient material no matter 
            the number of bishops.
            */
            W_insuf = false;
        }

    // One knight and at least one bishop is sufficient.
    }else if( W_pce_cnt[4] == 1 ){

        if( W_pce_cnt[3] == 0 ){
            W_insuf = true;
        }else{
            W_insuf = false;
        }
    
    // At least two knight is sufficient.
    }else{
        W_insuf = false;
    }

    // Tally the bishop + knight material insufficiency.
    is_draw = B_insuf && W_insuf;
    if( !is_draw ){
        return is_draw;
    }

// ---------------------------------------------------------------------- <<<<<
    
    return is_draw;

}


void chess::upd_post_play(){
    
    this->upd_atk_lists();

    this->upd_mid_game_state();

}

void chess::upd_all(){

    this->upd_atk_lists();

    this->upd_mid_game_state();

    this->upd_end_game_state();

}


void chess::upd_end_game_state(){

    if( this->is_check_mate() ){
        if( this->is_black_turn() ){
            this->state = CHS_STATE::WWIN;
        }else{
            this->state = CHS_STATE::BWIN;
        }
        return;
    }else{
        if( this->is_draw() ){
            this->state = CHS_STATE::DRAW;
        }
    }

}


void chess::printBoard() const{

    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){

        cout << BOARDHEIGHT - 1 - i << ' ';

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

    cout << "  ";
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        cout << j;
        if( j != BOARDWIDTH ){
            cout << "  ";
        }
    }
    cout << endl;

}

void chess::printBoard_ag_coord() const{

    for( unsigned int i = 0; i < BOARDHEIGHT; i++ ){

        cout << BOARDHEIGHT - i << ' ';

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

    cout << "  ";
    for( unsigned int j = 0; j < BOARDWIDTH; j++ ){
        cout << static_cast<char>( 'a' + j );
        if( j != BOARDWIDTH ){
            cout << "  ";
        }
    }
    cout << endl;

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Function
// ====================================================================== >>>>>

// n - 1, c - 'a'

pair<int,int> chess::alg_to_cart( pair<char,int> alg_coord ){
    return pair<int,int>( alg_coord.first - 1, alg_coord.second - 'a' );
}
pair<int,int> chess::alg_to_cart( char file, int rank ){
    return pair<int,int>( rank - 1, file - 'a' );
}

pair<char,int> chess::cart_to_alg( pair<int,int> cart_coord ){
    return pair<char,int>( (char)( 'a' + cart_coord.second ), cart_coord.first + 1 );
}
pair<char,int> chess::cart_to_alg( int row_idx, int col_idx ){
    return pair<char,int>( (char)( 'a' + col_idx ), row_idx + 1 );
}

chess::chs_move chess::alg_comm_to_move( string alg_comm ){
    
    chs_move ret_move;
    // Obtain turn indicator.
    CHS_PIECE_COLOR pce_color = this->is_white_turn() ? CHS_PIECE_COLOR::WHITE : CHS_PIECE_COLOR::BLACK;
    // Variable indicating type of current piece.
    CHS_PIECE_TYPE pce_type;

    // A flag indicating whether the game is in check ('+') or checkmate state ('#').
    char check_flag = ' ';

// ---------------------------------------------------------------------- >>>>>
//      Resign Special Command Parse
// ---------------------------------------------------------------------- >>>>>

    // White won by black resignation!
    if( alg_comm == "1-0" ){
        return ret_move;
    // Black won by white resignation!
    }else if( alg_comm == "0-1" ){
        return ret_move;
    // Draw by mutual agreement.
    }else if( alg_comm == "½-½" ){
        return ret_move;
    }

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Castling Special Command Parse
// ---------------------------------------------------------------------- >>>>>

    if( alg_comm == "O-O" || alg_comm == "0-0" ){

        unsigned int row_idx = 0;
        if( this->is_white_turn() ){
            row_idx = 0;
        }else{
            row_idx = BOARDHEIGHT - 1;
        }

        if( this->get_piece_at( row_idx, 4 ).type == CHS_PIECE_TYPE::KING ){
            chs_move castle_mov( row_idx, 4, row_idx, 6 );
            if( this->is_move_valid( castle_mov ) ){
                return castle_mov;
            }
        }
        throw runtime_error( "Caslting move currently not valid." );

    }else if( alg_comm == "O-O-O" || alg_comm == "0-0-0" ){

        unsigned int row_idx = 0;
        if( this->is_white_turn() ){
            row_idx = 0;
        }else{
            row_idx = BOARDHEIGHT - 1;
        }

        if( this->get_piece_at( row_idx, 4 ).type == CHS_PIECE_TYPE::KING ){
            chs_move castle_mov( row_idx, 4, row_idx, 2 );
            if( this->is_move_valid( castle_mov ) ){
                return castle_mov;
            }
        }
        throw runtime_error( "Castling move currently not valid." );

    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Check Status Flag Parse (Last Char(s))
// ---------------------------------------------------------------------- >>>>>

    // Take out last character is it is the check status flag.
    if( !std::isalnum( alg_comm[ alg_comm.size() - 1 ] ) ){
        if( alg_comm[ alg_comm.size() - 1 ] == '+' || alg_comm[ alg_comm.size() - 1 ] == '#' ){
            check_flag = alg_comm[ alg_comm.size() - 1 ];
            alg_comm = alg_comm.substr( 0, alg_comm.size() - 1 );
        }
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Piece Type Flag Parse (First char)
// ---------------------------------------------------------------------- >>>>>

    // If the first letter is uppercase, non-pawn.
    if( (unsigned int)( alg_comm.at(0) - 'A' ) < 26 ){
        
        switch( alg_comm.at(0) ){
        case( 'B' ):
            pce_type = CHS_PIECE_TYPE::BISHOP;
            break;
        case( 'N' ):
            pce_type = CHS_PIECE_TYPE::KNIGHT;
            break;
        case( 'R' ):
            pce_type = CHS_PIECE_TYPE::ROOK;
            break;
        case( 'Q' ):
            pce_type = CHS_PIECE_TYPE::QUEEN;
            break;
        case( 'K' ):
            pce_type = CHS_PIECE_TYPE::KING;
            break;
        default:
            throw invalid_argument( "First char is an invalid uppercase letter." );
            break;
        };

        // Take out the first char.
        alg_comm = alg_comm.substr( 1, alg_comm.size() );

    // If the first letter is not uppercase, pawn.
    }else{

        pce_type = CHS_PIECE_TYPE::PAWN;
        /*
        if( std::isalpha( alg_comm.at( alg_comm.size() - 1 ) ) &&
            (unsigned int)( alg_comm.at( alg_comm.size() - 1 ) - 'A' ) < 26 )
        */
        if( (unsigned int)( alg_comm.at( alg_comm.size() - 1 ) - 'A' ) < 26 ){
            switch( alg_comm.at( alg_comm.size() - 1 ) ){
            case( 'B' ):
            case( 'N' ):
            case( 'R' ):
            case( 'Q' ):
            case( 'K' ):
                alg_comm = alg_comm.substr( 0, alg_comm.size() - 1 );
                break;
            default:
                throw invalid_argument( "Pawn promotion indicator is not a valid upper case letter." );
                break;
            }
        }

    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Attack Flag Parse (Mid 'x' symbol)
// ---------------------------------------------------------------------- >>>>>

    // Flag indicating whether the play is an attack or no.
    bool is_atk = false;
    // Initialize the string algebraic coordinates.
    string bef_coord_str = "";
    string aft_coord_str = "";

    // Subdivide the current remaining string into the before and after algebraic coordinates.
    for( unsigned int z = 0; z < alg_comm.size(); z++ ){
        if( alg_comm[z] == 'x' ){
            is_atk = true;
            bef_coord_str = alg_comm.substr( 0, z );
            aft_coord_str = alg_comm.substr( z + 1, alg_comm.size() - z - 1 );
        }
    }
    if( !is_atk ){
        aft_coord_str = alg_comm.substr( alg_comm.size() - 2, 2 );
        bef_coord_str = alg_comm.substr( 0, alg_comm.size() - 2 );
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Start and End Coordinates Parse
// ---------------------------------------------------------------------- >>>>>

    // Initialize the final coordinates.
    pair<int,int> aft_coord(-1,-1);
    pair<int,int> bef_coord(-1,-1);

    // Parse the after coordinate.
    if( aft_coord_str.size() == 2 ){
        if( std::isdigit( aft_coord_str[1] ) && std::isalpha( aft_coord_str[0] ) ){
            aft_coord = alg_to_cart( aft_coord_str[0], (int) aft_coord_str[1] - '0' );
        }else{
            throw invalid_argument( "Algebraic ending coordinate must be a two char pair of an alphabet letter (file) and a digit (rank)." );
        }
        
    }else{
        throw invalid_argument( "Algebraic abbreviated play notation must at least have ending coordinate (If not a special move)." );
    }

    // Parse the before coordinate.
    if( bef_coord_str.size() == 2 ){

        if( std::isdigit( bef_coord_str[1] ) && std::isalpha( bef_coord_str[0] ) ){
            bef_coord = alg_to_cart( bef_coord_str[0], (int) bef_coord_str[1] - '0' );
        }else{
            throw invalid_argument( "Algebraic starting coordinate of two char must consist of an alphabet letter (file) and a digit (rank)." );
        }

    // Case when the before coordinate is abbreviated to a single character.
    }else if( bef_coord_str.size() == 1 ){

        if( std::isdigit( bef_coord_str[0] ) ){

            int row_idx = (int) ( bef_coord_str[0] - '0' ) - 1;
            int fnd_cnt = 0;
            // Scan through the specified row for target piece.
            for( unsigned int z = 0; z < BOARDWIDTH; z++ ){
                pair<int,int> coord_z( row_idx, z );
                if( this->get_piece_at( coord_z ).type == pce_type && 
                    this->get_piece_at( coord_z ).color == pce_color )
                {
                    if( is_atk ){
                        if( this->is_atk_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }
                }
            }
            // If more than one correct piece is identified on same row, algebraic 
            // coord is invalid.
            if( fnd_cnt > 1 ){
                throw runtime_error( "Two identical pieces share the same rank and cannot be differentiated with the given algebraic coordinate." );
            }else if( fnd_cnt == 0 ){
                throw runtime_error( "No piece found on the board to play which fits the given algebraic coordinate." );
            }

        }else if( std::isalpha( bef_coord_str[0] ) ){

            int col_idx = (int) ( bef_coord_str[0] - 'a' );
            int fnd_cnt = 0;
            // Scan through the specified column for target piece.
            for( unsigned int z = 0; z < BOARDHEIGHT; z++ ){
                pair<int,int> coord_z( z, col_idx );
                if( this->get_piece_at( coord_z ).type == pce_type && 
                    this->get_piece_at( coord_z ).color == pce_color )
                {
                    if( is_atk ){
                        if( this->is_atk_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_valid( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }
                }
            }
            // If more than one correct piece is identified on same column, algebraic 
            // coord is invalid.
            if( fnd_cnt > 1 ){
                throw runtime_error( "Two identical pieces share the same file and cannot be differentiated with the given algebraic coordinate." );
            }else if( fnd_cnt == 0 ){
                throw runtime_error( "No piece found on the board to play which fits the given algebraic coordinate." );
            }

        }else{
            throw invalid_argument( "Algebraic starting coordinate of one char must be either an alphabet letter (file) or a digit (rank)." );
        }

    // Case when the before coordinate is omitted.
    }else if( bef_coord_str.size() == 0 ){

        int fnd_cnt = 0;
        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
            pair<int,int> coord_z = chess::ind2sub(z);
            if( this->get_piece_at( coord_z ).type == pce_type && 
                this->get_piece_at( coord_z ).color == pce_color )
            {
                
                if( is_atk ){
                    if( this->is_atk_valid( coord_z, aft_coord ) ){
                        bef_coord = coord_z;
                        fnd_cnt++;
                    }
                }else{
                    if( this->is_move_valid( coord_z, aft_coord ) ){
                        bef_coord = coord_z;
                        fnd_cnt++;
                    }
                }
                
            }
        }
        // If more than one correct piece is identified on same column, algebraic 
        // coord is invalid.
        if( fnd_cnt > 1 ){
            throw runtime_error( "Two identical pieces share the same file and cannot be differentiated with the given algebraic coordinate." );
        }else if( fnd_cnt == 0 ){
            throw runtime_error( "No piece found on the board to play which fits the given algebraic coordinate." );
        }

    }else{
        throw invalid_argument( "Invalid algebraic play notation." );
    }

// ---------------------------------------------------------------------- <<<<<


    ret_move.pt_a = bef_coord;
    ret_move.pt_b = aft_coord;
    return ret_move;

}

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
chess::chs_piece chess::get_piece_at( pair<int,int> ij ) const{
    return this->get_piece_at( ij.first, ij.second );
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

array<vector<int>,chess::BOARDHEIGHT*chess::BOARDWIDTH> chess::getAtk_list_by_W() const
    {return this->atk_list_by_W;}
array<vector<int>,chess::BOARDHEIGHT*chess::BOARDWIDTH> chess::getAtk_list_by_B() const
    {return this->atk_list_by_B;}


bool chess::getEn_pass_flag() const
    {return this->en_pass_flag;}
void chess::setEn_pass_flag( bool en_pass_flag )
    {this->en_pass_flag = en_pass_flag;}

vector<chess::chs_move> chess::getEn_pass_moves() const
    {return this->en_pass_moves;}
void chess::setEn_pass_moves( vector<chs_move> en_pass_move_in )
    {this->en_pass_moves = en_pass_move_in;}

bool chess::getPromo_lock() const
    {return this->promo_lock;}
void chess::setPromo_lock( const bool promo_lock )
    {this->promo_lock = promo_lock;}

pair<int,int> chess::getPromo_point() const
    {return this->promo_point;}
void chess::setPromo_point( const pair<int,int> promo_point_in ){
    if( promo_point_in.first != 0 && promo_point_in.first != BOARDHEIGHT - 1 ){
        throw invalid_argument( "Specified chess board promotion coordinate must be on the first or last row." );
    }
    if( promo_point_in.second < 0 && promo_point_in.second >= BOARDHEIGHT ){
        throw out_of_range( "Specified chess board promotion coordinate is invalid." );
    }
    this->promo_point = promo_point_in;
}


void chess::setVerbose( bool verbose )
    {this->verbose = verbose;}

bool chess::getVerbose() const
    {return this->verbose;}

// ====================================================================== <<<<<

