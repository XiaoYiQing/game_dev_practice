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

/**
 * Define an impossible move serving as reference for indicating failure to
 * attain a usable move.
 */
const chess::chs_move chess::IMPOS_MOVE( -1, -1, -1, -1 );
/**
 * Define an impossible chess algebraic command serving as reference for indicating 
 * failure to attain a usable move.
 */
const string chess::IMPOS_ALG_COMM = "";
/**
 * Define an impossible 2D coordinate on the chess board.
 */
const pair<int,int> chess::IMPOS_COORD = {-1,-1};

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

chess::chess(){

    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
        this->atk_list_by_B[z].reserve( BOARDHEIGHT*BOARDWIDTH );
        this->atk_list_by_W[z].reserve( BOARDHEIGHT*BOARDWIDTH );
    }

    // Initialize piece counter.
    wPieceCounter[ CHS_PIECE_TYPE::PAWN ] = 0;
    wPieceCounter[ CHS_PIECE_TYPE::KNIGHT ] = 0;
    wPieceCounter[ CHS_PIECE_TYPE::BISHOP ] = 0;
    wPieceCounter[ CHS_PIECE_TYPE::ROOK ] = 0;
    wPieceCounter[ CHS_PIECE_TYPE::QUEEN ] = 0;
    wPieceCounter[ CHS_PIECE_TYPE::KING ] = 0;
    bPieceCounter[ CHS_PIECE_TYPE::PAWN ] = 0;
    bPieceCounter[ CHS_PIECE_TYPE::KNIGHT ] = 0;
    bPieceCounter[ CHS_PIECE_TYPE::BISHOP ] = 0;
    bPieceCounter[ CHS_PIECE_TYPE::ROOK ] = 0;
    bPieceCounter[ CHS_PIECE_TYPE::QUEEN ] = 0;
    bPieceCounter[ CHS_PIECE_TYPE::KING ] = 0;


    this->verbose = false;

    // Default AI option is standard minmax with AB-pruning.
    AI_opt = CHS_AI_OPT::STD_AB_MM;
    minmax_depth = 3;
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

    this->minmax_vals["win"] = chs_pce_val_map[ CHS_PIECE_TYPE::KING ];
    this->minmax_vals["draw"] = 0;
    this->minmax_vals["check"] = 1;

    this->force_lists_upd = false;
    this->is_atk_lists_upd = false;
    this->is_psbl_alg_comm_upd = false;
    this->is_all_legal_moves_upd = false;
    this->is_all_legal_atks_upd = false;
    this->is_valid_moves_upd = false;
    this->is_valid_atks_upd = false;

    for( unsigned int z = 0; z < this->valid_W_moves_map.size(); z++ ){
        this->valid_W_moves_map[z].reserve(27);
        this->valid_B_moves_map[z].reserve(27);
        this->valid_W_atks_map[z].reserve(8);
        this->valid_B_atks_map[z].reserve(8);
        this->legal_moves_map[z].reserve(27);
        this->legal_atks_map[z].reserve(8);
    }

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

    this->game_tracking_signal();

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

    this->game_tracking_signal();
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

    this->game_tracking_signal();
    // Update all remaining state related variables.
    upd_all();

}




void chess::clearSquare( unsigned int i, unsigned int j ){
    if( i >= BOARDHEIGHT || j >= BOARDWIDTH ){
        throw out_of_range( "clearSquare: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j].set_as_empty();
    this->game_tracking_signal();
    this->upd_all();
}

void chess::set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce ){
    if( i >= BOARDHEIGHT || j >= BOARDWIDTH ){
        throw out_of_range( "set_piece_at: the specified coordinate is out of bound." );
    }
    this->CHS_board[i][j] = inPce;
    this->game_tracking_signal();
    this->upd_all();
}
void chess::set_piece_at_ag_coord( const char c, const unsigned int n, const chs_piece inPce ){
    set_piece_at( n - 1, c - 'a', inPce );
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      AI Related Functions
// ====================================================================== >>>>>

std::mutex chess::mtx_shared_move_list;

stack<string> chess::shared_move_stk;

stack< pair<int,string> > chess::shared_minmax_res;

int chess::gameStateEval(){

    int stateValue = 0;

    // Update the game state before proceeding.
    this->upd_all();

    switch( this->state ){
    case CHS_STATE::WWIN: 
        stateValue += this->minmax_vals["win"];
        break;
    case CHS_STATE::BWIN: 
        stateValue -= this->minmax_vals["win"];
        break;
    case CHS_STATE::DRAW:
        stateValue -= this->minmax_vals["draw"];
        break;
    case CHS_STATE::WCHK:
        stateValue -= this->minmax_vals["check"];
        for( pair<CHS_PIECE_TYPE,int> type_z : this->wPieceCounter ){
            stateValue += this->chs_pce_val_map[type_z.first] * this->wPieceCounter[type_z.first];
            stateValue -= this->chs_pce_val_map[type_z.first] * this->bPieceCounter[type_z.first];
        }
        break;
    case CHS_STATE::BCHK:
        stateValue += this->minmax_vals["check"];
        for( pair<CHS_PIECE_TYPE,int> type_z : this->wPieceCounter ){
            stateValue += this->chs_pce_val_map[type_z.first] * this->wPieceCounter[type_z.first];
            stateValue -= this->chs_pce_val_map[type_z.first] * this->bPieceCounter[type_z.first];
        }
        break;
    case CHS_STATE::ONGOING:
        for( pair<CHS_PIECE_TYPE,int> type_z : this->wPieceCounter ){
            stateValue += this->chs_pce_val_map[type_z.first] * this->wPieceCounter[type_z.first];
            stateValue -= this->chs_pce_val_map[type_z.first] * this->bPieceCounter[type_z.first];
        }
        break;
    default:
        throw runtime_error( "gameStateEval: Unrecognized chess game state. Abort." );
    }

    return stateValue;

}


int chess::minmax_debug( bool isMaximizing, int depth ){

    return minmax_debug_loop( isMaximizing, depth, depth );

}

int chess::minmax_debug_loop( bool isMaximizing, int depth, int max_depth ){

    if( ( this->is_white_turn() && !isMaximizing ) ||
        this->is_black_turn() && isMaximizing ){
        throw invalid_argument( "minmax: Mismatch of minmax objective with the current turn order." );
    }

    switch( this->state ){
    case CHS_STATE::WWIN:
    case CHS_STATE::BWIN:
    case CHS_STATE::DRAW:
        // When game is over, return value immediately.
        // When game is over, return value immediately.
        for( int i = 0 ; i < max_depth - depth; i++ ){
            cout << "  ";
        }
        cout << "Score: " << this->gameStateEval() << " <--- ";
        return this->gameStateEval();
        break;
    case CHS_STATE::WCHK:
    case CHS_STATE::BCHK:
    case CHS_STATE::ONGOING:
        // If we reached the maximum allowed depth, return value immediately.
        if( depth <= 0 ){
            for( int i = 0 ; i < max_depth - depth; i++ ){
                cout << "  ";
            }
            cout << "Score: " << this->gameStateEval() << " <--- ";
            return this->gameStateEval();
        }
        break;
    default:
        throw runtime_error( "minmax: Unrecognized game state. Abort." );
    }

    int bestScore = 0;
    int currScore = 0;

    vector<string> validMovesVect = this->get_all_psbl_alg_comm();


    if ( isMaximizing ) {        
        bestScore = std::numeric_limits<int>::min();
    }else{
        bestScore = std::numeric_limits<int>::max();
    }

    for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

        // Current valid move.
        string move_z = validMovesVect.at(z);

        // Make a copy of the current game.
        chess newGame = *this;

        // In the game copy, make a play with the next available move.
        bool tmp = newGame.ply_ag_comm( move_z );

        for( int i = 0 ; i < max_depth - depth; i++ ){
            cout << "  ";
        }
        cout << move_z << endl;

        // Perform next layer minmax.
        if( newGame.is_white_turn() ){
            currScore = newGame.minmax_debug_loop( true, depth - 1, max_depth );
        }else if( newGame.is_black_turn() ){
            currScore = newGame.minmax_debug_loop( false, depth - 1, max_depth );
        }
        // Thread exit point.
        if( !this->AI_proc_flag ){
            return bestScore;
        }

        for( int i = 0 ; i < max_depth - depth; i++ ){
            cout << "  ";
        }
        cout << "MAX: currScore = " << currScore << ", " <<
            "bestScore = " << bestScore << endl;

        if ( isMaximizing ) {        
            // Update the highest score up to now.
            bestScore = std::max( bestScore, currScore );
        }else{
            // Update the highest score up to now.
            bestScore = std::min( bestScore, currScore );
        }

    }

    return bestScore;
    
}



int chess::minmax( bool isMaximizing, int depth ){

    if( ( this->is_white_turn() && !isMaximizing ) ||
        this->is_black_turn() && isMaximizing ){
        throw invalid_argument( "minmax: Mismatch of minmax objective with the current turn order." );
    }

    switch( this->state ){
    case CHS_STATE::WWIN:
    case CHS_STATE::BWIN:
    case CHS_STATE::DRAW:
        // When game is over, return value immediately.
        return this->gameStateEval();
        break;
    case CHS_STATE::WCHK:
    case CHS_STATE::BCHK:
    case CHS_STATE::ONGOING:
        // If we reached the maximum allowed depth, return value immediately.
        if( depth <= 0 ){
            return this->gameStateEval();
        }
        break;
    default:
        throw runtime_error( "minmax: Unrecognized game state. Abort." );
    }

    int bestScore = 0;
    int currScore = 0;

    // Obtain the entire set of currently valid moves.
    vector<string> validMovesVect = this->get_all_psbl_alg_comm();


    if ( isMaximizing ) {        
        bestScore = std::numeric_limits<int>::min();
    }else{
        bestScore = std::numeric_limits<int>::max();
    }

    for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

        // Current valid move.
        string move_z = validMovesVect.at(z);

        // Make a copy of the current game.
        chess newGame = *this;

        // In the game copy, make a play with the next available move.
        newGame.ply_ag_comm( move_z );

        // Perform next layer minmax.
        if( newGame.is_white_turn() ){
            currScore = newGame.minmax( true, depth - 1 );
        }else if( newGame.is_black_turn() ){
            currScore = newGame.minmax( false, depth - 1 );
        }
        // Thread exit point.
        if( !this->AI_proc_flag ){
            return bestScore;
        }

        if ( isMaximizing ) {        
            // Update the highest score up to now.
            bestScore = std::max( bestScore, currScore );
        }else{
            // Update the highest score up to now.
            bestScore = std::min( bestScore, currScore );
        }

    }

    return bestScore;
}


pair<int,string> chess::minmax_bestMove( bool isMaximizing, int depth ){

    if( ( this->is_white_turn() && !isMaximizing ) ||
        this->is_black_turn() && isMaximizing ){
        throw invalid_argument( "minmax: Mismatch of minmax objective with the current turn order." );
    }

    switch( this->state ){
    case CHS_STATE::WWIN:
    case CHS_STATE::BWIN:
    case CHS_STATE::DRAW:
        // When game is over, return value immediately.
        return pair<int,string>( this->gameStateEval(), chess::IMPOS_ALG_COMM );
        break;
    case CHS_STATE::WCHK:
    case CHS_STATE::BCHK:
    case CHS_STATE::ONGOING:
        // If we reached the maximum allowed depth, return value immediately.
        if( depth <= 0 ){
            return pair<int,string>( this->gameStateEval(), chess::IMPOS_ALG_COMM );
        }
        break;
    default:
        throw runtime_error( "minmax: Unrecognized game state. Abort." );
    }

    int bestScore = 0;
    int currScore = 0;
    string bestPlay = chess::IMPOS_ALG_COMM;
    

    // Obtain the entire set of currently valid moves.
    vector<string> validMovesVect = this->get_all_psbl_alg_comm();

    if ( isMaximizing ) {        
        bestScore = std::numeric_limits<int>::min();
    }else{
        bestScore = std::numeric_limits<int>::max();
    }
    
    for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

        // Current valid move.
        string move_z = validMovesVect.at(z);

        // Make a copy of the current game.
        chess newGame = *this;

        // In the game copy, make a play with the next available move.
        newGame.ply_ag_comm( move_z );

        // Perform next layer minmax.
        if( newGame.is_white_turn() ){
            currScore = newGame.minmax( true, depth - 1 );
        }else if( newGame.is_black_turn() ){
            currScore = newGame.minmax( false, depth - 1 );
        }
        // Thread exit point.
        if( !this->AI_proc_flag ){
            return pair<int,string>( bestScore, bestPlay );
        }

        if ( isMaximizing ) {        
            // Update the highest score and play up to now.
            if( currScore > bestScore ){
                bestScore = currScore;
                bestPlay = move_z;
            }
        }else{
            // Update the highest score and play up to now.
            if( currScore < bestScore ){
                bestScore = currScore;
                bestPlay = move_z;
            }
        }

    }

    return pair<int,string>( bestScore, bestPlay );

}


int chess::minmaxAB_init( bool isMaximizing, int depth ){

    // Initial alpha and beta.
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    // Initialize the minmiax process with AB-pruning.
    return minmaxAB_loop( isMaximizing, alpha, beta, depth );

}

int chess::minmaxAB_loop( bool isMaximizing, int alpha, int beta, int depth ){

    if( ( this->is_white_turn() && !isMaximizing ) ||
        this->is_black_turn() && isMaximizing )
    {
        throw invalid_argument( "minmaxAB_loop: Mismatch of minmax objective with the current turn order." );
    }

    switch( this->state ){
    case CHS_STATE::WWIN:
    case CHS_STATE::BWIN:
    case CHS_STATE::DRAW:
        // When game is over, return value immediately.
        return this->gameStateEval();
        break;
    case CHS_STATE::WCHK:
    case CHS_STATE::BCHK:
    case CHS_STATE::ONGOING:
        // If we reached the maximum allowed depth, return value immediately.
        if( depth <= 0 ){
            return this->gameStateEval();
        }
        break;
    default:
        throw runtime_error( "minmax: Unrecognized game state. Abort." );
    }

    int bestScore = 0;
    int currScore = 0;

    // Obtain the entire set of currently valid moves.
    vector<string> validMovesVect = this->get_all_psbl_alg_comm();

    if ( isMaximizing ) {        
        bestScore = std::numeric_limits<int>::min();
    }else{
        bestScore = std::numeric_limits<int>::max();
    }

    for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

        // Current valid move.
        string move_z = validMovesVect.at(z);

        // Make a copy of the current game.
        chess newGame = *this;

        // In the game copy, make a play with the next available move.
        newGame.ply_ag_comm( move_z );

        // Perform next layer minmax.
        if( newGame.is_white_turn() ){
            currScore = newGame.minmaxAB_loop( true, alpha, beta, depth - 1 );
        }else if( newGame.is_black_turn() ){
            currScore = newGame.minmaxAB_loop( false, alpha, beta, depth - 1 );
        }
        // Thread exit point.
        if( !this->AI_proc_flag ){
            return bestScore;
        }

        if ( isMaximizing ) {        
            // Update the highest score up to now.
            bestScore = std::max( bestScore, currScore );
            // Update the alpha value.
            alpha = std::max( alpha, currScore );
            // If current alpha exceeds previous beta, no need to keep looking in 
            // this search branch.
            if (beta <= alpha){
                break;
            }
        }else{
            // Update the highest score up to now.
            bestScore = std::min( bestScore, currScore );
            // Update the alpha value.
            beta = std::min( beta, currScore );
            // If current beta is inferior to previous alpha, no need to keep looking in 
            // this search branch.
            if( beta <= alpha ){
                break;
            }
        }

    }

    return bestScore;

}


pair<int,string> chess::minmaxAB_bestMove( bool isMaximizing, int depth ){

    if( ( this->is_white_turn() && !isMaximizing ) ||
        this->is_black_turn() && isMaximizing )
    {
        throw invalid_argument( "minmaxAB_loop: Mismatch of minmax objective with the current turn order." );
    }

    switch( this->state ){
    case CHS_STATE::WWIN:
    case CHS_STATE::BWIN:
    case CHS_STATE::DRAW:
        // When game is over, return value immediately.
        return pair<int,string>( this->gameStateEval(), chess::IMPOS_ALG_COMM );
        break;
    case CHS_STATE::WCHK:
    case CHS_STATE::BCHK:
    case CHS_STATE::ONGOING:
        // If we reached the maximum allowed depth, return value immediately.
        if( depth <= 0 ){
            return pair<int,string>( this->gameStateEval(), chess::IMPOS_ALG_COMM );
        }
        break;
    default:
        throw runtime_error( "minmaxAB_bestMove: Unrecognized game state. Abort." );
    }

    
    // Initial alpha and beta.
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    int bestScore = 0;
    int currScore = 0;
    string bestPlay = chess::IMPOS_ALG_COMM;

    // Obtain the entire set of currently valid moves.
    vector<string> validMovesVect = this->get_all_psbl_alg_comm();

    if ( isMaximizing ) {        
        bestScore = std::numeric_limits<int>::min();
    }else{
        bestScore = std::numeric_limits<int>::max();
    }

    for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

        // Current valid move.
        string move_z = validMovesVect.at(z);

        // Make a copy of the current game.
        chess newGame = *this;

        // In the game copy, make a play with the next available move.
        newGame.ply_ag_comm( move_z );

        // Perform next layer minmax.
        currScore = newGame.minmaxAB_loop( newGame.is_white_turn(), alpha, beta, depth - 1 );
        // Thread exit point.
        if( !this->AI_proc_flag ){
            return pair<int,string>( bestScore, bestPlay );
        }

        if( isMaximizing ){

            // Update the highest score and play up to now.
            if( currScore > bestScore ){
                bestScore = currScore;
                bestPlay = move_z;
            }
            // Update the alpha value.
            alpha = std::max( alpha, currScore );
            // If current alpha exceeds previous beta, no need to keep looking in 
            // this search branch.
            if ( beta <= alpha ){
                break;
            }

        }else{

            // Update the highest score and play up to now.
            if( currScore < bestScore ){
                bestScore = currScore;
                bestPlay = move_z;
            }
            // Update the beta value.
            beta = std::min( beta, currScore );
            // If current beta is inferior to previous alpha, no need to keep looking in 
            // this search branch.
            if( beta <= alpha ){
                break;
            }

        }

    }

    return pair<int,string>( bestScore, bestPlay );

}


pair<int,string> chess::minmaxAB_split_init( chess& tarGame, bool isMaximizing, 
    int depth )
{

    // Define number of threads.
    unsigned int thread_cnt = min( tarGame.thread_to_use, 
        std::thread::hardware_concurrency() );
    // Empty the shared move stack.
    while ( !shared_move_stk.empty() ) {
        shared_move_stk.pop(); 
    }
    // Obtain the entire set of currently valid moves.
    vector<string> validMovesVect = tarGame.get_all_psbl_alg_comm();

    // Push the entire set of valid moves unto the shared stack.
    for( string move_z : validMovesVect ){
        shared_move_stk.push( move_z );
    }

    // Create separate threads to run the split minmax function.
    vector< std::thread > myThreads;
    for( unsigned int z = 0; z < thread_cnt - 1; z++ ){
        myThreads.emplace_back( chess::minmaxAB_split, ref( tarGame ), isMaximizing, depth );
    }
    // The current thread starts its own split minmax run after initiating the 
    // other threads.
    minmaxAB_split( ref( tarGame ), isMaximizing, depth );

    // Wait for all separate threads to finish.
    for( unsigned int z = 0; z < thread_cnt - 1; z++ ){
        if( myThreads.at(z).joinable() ){
            myThreads.at(z).join();
        }
    }

    // Summarize the best score results from the individual results generated
    // from the threads.
    int bestScore = 0;
    string bestPlay = chess::IMPOS_ALG_COMM;

    pair<int, string> bestRes;

    if( isMaximizing ){
        bestScore = std::numeric_limits<int>::min();
        while( !tarGame.shared_minmax_res.empty() ){
            if( shared_minmax_res.top().first > bestScore ){
                bestScore = shared_minmax_res.top().first;
                bestRes = shared_minmax_res.top();
            }
            shared_minmax_res.pop();
        }
    }else{
        bestScore = std::numeric_limits<int>::max();
        while( !tarGame.shared_minmax_res.empty() ){
            if( shared_minmax_res.top().first < bestScore ){
                bestScore = shared_minmax_res.top().first;
                bestRes = shared_minmax_res.top();
            }
            shared_minmax_res.pop();
        }
    }

    return bestRes;

}

pair<int,string> chess::minmaxAB_split( chess& tarGame, bool isMaximizing, int depth ){
    
    if( ( tarGame.is_white_turn() && !isMaximizing ) ||
        tarGame.is_black_turn() && isMaximizing )
    {
        throw invalid_argument( "minmaxAB_split: Mismatch of minmax objective with the current turn order." );
    }

    pair<int,string> finalRes;

    switch( tarGame.state ){

        case CHS_STATE::WWIN:
        case CHS_STATE::BWIN:
        case CHS_STATE::DRAW:

            finalRes = pair<int,string>( tarGame.gameStateEval(), chess::IMPOS_ALG_COMM );
            // When game is over, return value immediately.
            mtx_shared_move_list.lock(); // mutex lock start ------------ >>>>>
            // Add the best score to the shared stack.
            shared_minmax_res.push( finalRes );
            mtx_shared_move_list.unlock(); // mutex lock end ------------ <<<<<
            return finalRes;
            break;

        case CHS_STATE::WCHK:
        case CHS_STATE::BCHK:
        case CHS_STATE::ONGOING:

            // If we reached the maximum allowed depth, return value immediately.
            if( depth <= 0 ){
                
                finalRes = pair<int,string>( tarGame.gameStateEval(), chess::IMPOS_ALG_COMM );
                // When game is over, return value immediately.
                mtx_shared_move_list.lock(); // mutex lock start ------------ >>>>>
                // Add the best score to the shared stack.
                shared_minmax_res.push( finalRes );
                mtx_shared_move_list.unlock(); // mutex lock end ------------ <<<<<
                return finalRes;
            }
            break;

        default:
            throw runtime_error( "minmaxAB_split: Unrecognized game state." );

    }

    // Initial alpha and beta.
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    int bestScore = 0;
    int currScore = 0;
    bool hasMoveLeft = false;
    string move_z = chess::IMPOS_ALG_COMM;
    string bestPlay = chess::IMPOS_ALG_COMM;

    if ( isMaximizing ) {        
        bestScore = std::numeric_limits<int>::min();
    }else{
        bestScore = std::numeric_limits<int>::max();
    }

    while(true){

        mtx_shared_move_list.lock(); // mutex lock start ------------ >>>>>
        hasMoveLeft = !( chess::shared_move_stk.empty() );
        if( hasMoveLeft ){
            // Get current valid move.
            move_z = shared_move_stk.top();
            // Delete obtained move from stack.
            shared_move_stk.pop();
        }
        mtx_shared_move_list.unlock(); // mutex lock end ------------ <<<<<

        // Exit condition.
        if( !hasMoveLeft ){
            break;
        }

        // Make a copy of the current game.
        chess newGame = tarGame;

        // In the game copy, make a play with the next available move.
        newGame.ply_ag_comm( move_z );

        // Perform next layer minmax.
        currScore = newGame.minmaxAB_loop( newGame.is_white_turn(), alpha, beta, 
            depth - 1 );
        // Thread exit point.
        if( !tarGame.AI_proc_flag ){
            break;
        }

        if( isMaximizing ){

            // Update the highest score and play up to now.
            if( currScore > bestScore ){
                bestScore = currScore;
                bestPlay = move_z;
            }
            // Update the alpha value.
            alpha = std::max( alpha, currScore );
            // If current alpha exceeds previous beta, no need to keep looking in 
            // this search branch.
            if ( beta <= alpha ){
                break;
            }

        }else{

            // Update the highest score and play up to now.
            if( currScore < bestScore ){
                bestScore = currScore;
                bestPlay = move_z;
            }
            // Update the beta value.
            beta = std::min( beta, currScore );
            // If current beta is inferior to previous alpha, no need to keep looking in 
            // this search branch.
            if( beta <= alpha ){
                break;
            }

        }

    }

    mtx_shared_move_list.lock(); // mutex lock start ------------ >>>>>
    // Add the best score to the shared stack.
    shared_minmax_res.push( pair<int,string>( bestScore, bestPlay ) );
    mtx_shared_move_list.unlock(); // mutex lock end ------------ <<<<<

    return pair<int,string>( bestScore, bestPlay );

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
    this->game_tracking_signal();
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

    // Attack condition.
    bool is_atk = !this->is_sq_empty( i_aft, j_aft );
    // Special en-passant attack condition.
    if( currPiece.type == CHS_PIECE_TYPE::PAWN ){
        is_atk = j_bef != j_aft;
    }


    if( !is_atk ){

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

    }else{

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

    // Signal for change of board state.
    this->game_tracking_signal();
        
    // Increment the turn count.
    this->turn_cnt++;
    // Update all states of the game.
    if( this->upd_post_play() ){

    }else{
        throw runtime_error( "Chess: A play is made all the way to post play update and the update failed." );
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

        if( this->verbose ){
            cout << "Castling move is currently invalid." << endl;
        }
        return false;

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

        if( this->verbose ){
            cout << "Castling move is currently invalid." << endl;
        }
        return false;

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

        // Promotion indicator check and parse.
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
                        if( this->is_atk_legal( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_legal( coord_z, aft_coord ) ){
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
                        if( this->is_atk_legal( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_legal( coord_z, aft_coord ) ){
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
                    if( this->is_atk_legal( coord_z, aft_coord ) ){
                        bef_coord = coord_z;
                        fnd_cnt++;
                    }
                }else{
                    if( this->is_move_legal( coord_z, aft_coord ) ){
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


    // bool res_bool = this->ply( chs_move( bef_coord, aft_coord ) );
    bool res_bool = this->play( chs_move( bef_coord, aft_coord ) );
    // Check if the play induces an endgame state.
    if( res_bool ){
        this->upd_end_game_state();
    }

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
    if( this->is_move_legal( i_bef, j_bef, i_aft, j_aft ) ||
        this->is_atk_legal( i_bef, j_bef, i_aft, j_aft ) )
    {
        play_success = this->play( i_bef, j_bef, i_aft, j_aft );
    }else{
        return false;
    }

    // Check if the play induces an endgame state.
    if( play_success ){
        this->upd_end_game_state();
    }

    // auto start = std::chrono::steady_clock::now();  // TODO: DELETE THIS
    // auto end = std::chrono::steady_clock::now();    // TODO: DELETE THIS
    // auto time_AB = std::chrono::duration_cast<std::chrono::microseconds>( end - start).count();  // TODO: DELETE THIS
    // cout << "Piece count: " << time_AB << endl;

    return play_success;

}

bool chess::is_move_legal( pair<int,int> coord_bef, pair<int,int> coord_aft ) const{
    return this->is_move_legal( coord_bef.first, coord_bef.second, 
        coord_aft.first, coord_aft.second );
}

bool chess::is_move_legal( chs_move tarMov ) const{
    return this->is_move_legal( tarMov.pt_a, tarMov.pt_b );
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

bool chess::is_move_legal( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft ) const
{

    // If list of valid moves is up-to-date, just refer to it for answer.
    if( this->is_all_legal_moves_upd ){
        int ij_bef = sub2ind( i_bef, j_bef );
        int ij_aft = sub2ind( i_aft, j_aft );
        for( int tmp : this->legal_moves_map[ ij_bef ] )
            if( tmp == ij_aft )
                return true;
        return false;
    }

    // Obtain the color of the current piece.
    CHS_PIECE_COLOR tarColor = this->CHS_board[i_bef][j_bef].color;
    // Turn check.
    if( this->turn_cnt % 2 == 0 && tarColor != CHS_PIECE_COLOR::WHITE ||
        this->turn_cnt % 2 == 1 && tarColor != CHS_PIECE_COLOR::BLACK ){
        return false;
    }
    

    bool is_legal = true;

    is_legal = is_legal && this->is_move_valid( i_bef, j_bef, i_aft, j_aft );

    // Determine if the move causes own king's check state to end (if it was in check).
    if( is_legal && this->CHS_board[i_bef][j_bef].type != CHS_PIECE_TYPE::KING ){
        is_legal = is_legal && !( this->is_chk_persist( i_bef, j_bef, i_aft, j_aft ) );
    }
    if( is_legal && this->CHS_board[i_bef][j_bef].type != CHS_PIECE_TYPE::KING ){
        // Determine if the move causes own king to be exposed to a check.
        is_legal = is_legal && ( this->is_incidental_safe( i_bef, j_bef, i_aft, j_aft ) );
    }

    return is_legal;

}



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

    if( this->is_valid_moves_upd ){

        // Obtain the linear indices of the before and after coordinates.
        int ij_bef = sub2ind( i_bef, j_bef );
        int ij_aft = sub2ind( i_aft, j_aft );

        if( tarColor == CHS_PIECE_COLOR::WHITE ){
            for( int z : this->valid_W_moves_map[ ij_bef ] )
                if( z == ij_aft ){ return true; }
            return false;
        }else if( tarColor == CHS_PIECE_COLOR::BLACK ){
            for( int z : this->valid_B_moves_map[ ij_bef ] )
                if( z == ij_aft ){ return true; }
            return false;
        }else{
            return false;
        }

    }

    // Define flag for unique castling movement which involves two pieces been moved
    // in one action. 
    bool cast_poss = false;

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

            cast_poss = true;

            if( tarColor == CHS_PIECE_COLOR::WHITE ){
                
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

    // Initialize temporary boolean flag.
    bool state_ok = true;
    /*
    If not castling, check if the game change of state is legal after the move.
    */ 
    // if( !cast_poss && tarType != CHS_PIECE_TYPE::KING ){

    //     // Determine if the move causes own king's check state to end (if it was in check).
    //     state_ok = state_ok && !( this->is_chk_persist( i_bef, j_bef, i_aft, j_aft ) );
    //     if( state_ok ){
    //         // Determine if the move causes own king to be exposed to a check.
    //         state_ok = state_ok && ( this->is_incidental_safe( i_bef, j_bef, i_aft, j_aft ) );
    //     }

    // }

    return state_ok;

}

bool chess::is_move_valid( int ind_a, int ind_b ) const{

    pair<int,int> sub_a = ind2sub( ind_a );
    pair<int,int> sub_b = ind2sub( ind_b );

    return this->is_move_valid( sub_a.first, sub_a.second, sub_b.first, sub_b.second );

}

bool chess::is_incidental_safe( int i_bef, int j_bef, int i_aft, int j_aft ) const{

    chs_piece tarPce = this->get_piece_at( i_bef, j_bef );
    CHS_PIECE_COLOR tarColor = tarPce.color;
    CHS_PIECE_TYPE tarType = tarPce.type;

    // Obtain the position of the king of the same color as the current piece.
    pair<int,int>king_pos;
    if( tarColor == CHS_PIECE_COLOR::WHITE ){
        king_pos = this->get_W_king_pos();
    }else if( tarColor == CHS_PIECE_COLOR::BLACK ){
        king_pos = this->get_B_king_pos();
    }else{
        return false;
    }
    // If there is no king, there is no danger of incidental check.
    if( king_pos == IMPOS_COORD )
        return true;

    // Calculate the distance between the target piece and its king.
    int i_diff = i_bef - king_pos.first;
    int j_diff = j_bef - king_pos.second;
    // King moving is incidental safe by default.
    if( i_diff == 0 && j_diff == 0 ){
        return true;
    }
    // Calculate the distance between the displaced position and the starting position.
    int i_displ = i_aft - i_bef;
    int j_displ = j_aft - j_bef;
    // If no displacement, just return safe.
    if( i_displ == 0 && j_displ == 0 ){
        return true;
    }

    // Initialize the unit step from the king to the target piece.
    int i_step = 0; int j_step = 0;

    // Make sure the target piece aligns with the king along a row, column, 
    // or diagonal.
    if( i_diff == 0 || j_diff == 0 || abs( i_diff ) == abs( j_diff ) )
    {

        // If the displacement is on the same row and the king shares the same row,
        // there won't be incidental reveal.
        if( i_displ == 0 && i_diff == 0 ){
            return true;
        }
        // If the displacement is on the same column and the king shares the same column,
        // there won't be incidental reveal.
        if( j_displ == 0 && j_diff == 0 ){
            return true;
        }
        // If the displacement is on the same diagonal and the king shares the same 
        // diagonal, there won't be incidental reveal.
        if( ( abs( i_diff ) == abs( j_diff ) ) && ( abs( i_displ ) == abs( j_displ ) ) ){
            int displ_sign = i_displ * j_displ;
            int diff_sign = i_diff * j_diff;
            if( ( ( displ_sign > 0 ) && ( diff_sign > 0 ) ) ||
                ( ( displ_sign < 0 ) && ( diff_sign < 0 ) ) ){
                return true;
            }
        }

        // Determine step directions depending on relative position w.r.t. the king.
        if( i_diff > 0 ){
            i_step = 1;
        }else if( i_diff < 0 ){
            i_step = -1;
        }
        if( j_diff > 0 ){
            j_step = 1;
        }else if( j_diff < 0 ){
            j_step = -1;
        }

        // Initialize current tracking position.
        int i_z = king_pos.first + i_step;
        int j_z = king_pos.second + j_step;

        // Determine if any piece is placed in-between the target piece and its
        // king.
        while( i_z != i_bef || j_z != j_bef ){

            // If any obstacle between the piece and the king, no need
            // to check further.
            if( !this->is_sq_empty( i_z, j_z ) ){
                return true;
            }
            i_z += i_step;  j_z += j_step;

        }

        // Take one step away from the current piece.
        i_z += i_step;  j_z += j_step;

        // Assess any piece beyond curent piece.
        while( i_z >= 0 && j_z >= 0 && i_z < chess::BOARDHEIGHT && 
            j_z < chess::BOARDWIDTH )
        {

            if( !this->is_sq_empty( i_z, j_z ) ){
                
                // If the piece share the same color, then there is no danger.
                if( this->CHS_board[i_z][j_z].color == tarColor ){
                    return true;
                }

                // If the piece is an enemy queen.
                if( this->CHS_board[i_z][j_z].type == CHS_PIECE_TYPE::QUEEN ){
                    return false;
                }

                // If the piece is an enemy rook and we are searching for row
                // or column alignement.
                if( this->CHS_board[i_z][j_z].type == CHS_PIECE_TYPE::ROOK &&
                    ( i_step == 0 || j_step == 0 ) )
                {   
                    return false;
                }

                // If the piece is an enemy bishop and we are searching for diagonal
                // alignment.
                if( this->CHS_board[i_z][j_z].type == CHS_PIECE_TYPE::BISHOP &&
                    ( i_step != 0 && j_step != 0 ) ){
                    return false;
                }

                // Reaching this point means the investigated piece is an enemy
                // piece that poses no threat through alignment.
                return true;

            }

            // Increment the scan position.
            i_z += i_step;  j_z += j_step;

        }

        // No piece beyond target piece that could pose a threat to the king.
        return true;

    // A piece not aligned with its king can move freely without worrying
    // about exposing its king to danger.
    }else{
        return true;
    }

}

bool chess::is_chk_persist( int i_bef, int j_bef, int i_aft, int j_aft ) const{

    chs_piece tarPce = this->get_piece_at( i_bef, j_bef );
    CHS_PIECE_COLOR tarColor = tarPce.color;
    
// ---------------------------------------------------------------------- >>>>>
//      Make Sure Correct Check State
// ---------------------------------------------------------------------- >>>>>

    if( tarColor == CHS_PIECE_COLOR::WHITE ){
        // If the white king is not in check, no point calling this function to check
        // a white move.
        if( this->state != CHS_STATE::WCHK )
            return false;

    }else if( tarColor == CHS_PIECE_COLOR::BLACK ){
        // If the black king is not in check, no point calling this function to check
        // a black move.
        if( this->state != CHS_STATE::BCHK )
            return false;

    }else{
        throw runtime_error( "No piece at the specified coordinate." );
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Special King Move Case
// ---------------------------------------------------------------------- >>>>>

    // Obtain the piece's type.
    CHS_PIECE_TYPE tarType = tarPce.type;

    // If king, simply check whether the destination is clear of danger.
    if( tarType == CHS_PIECE_TYPE::KING ){
        if( tarColor == CHS_PIECE_COLOR::WHITE ){
            return ( this->atk_list_by_B[ chess::sub2ind( i_aft, j_aft ) ].size() != 0 );
        }else{
            return ( this->atk_list_by_W[ chess::sub2ind( i_aft, j_aft ) ].size() != 0 );
        }
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      King and Attacker(s) Coordinate Fetch
// ---------------------------------------------------------------------- >>>>>

    // Obtain the position of the king of the same color as the current piece.
    pair<int,int>king_pos;
    if( tarColor == CHS_PIECE_COLOR::WHITE ){
        king_pos = this->get_W_king_pos();
    }else{
        king_pos = this->get_B_king_pos();
    }
    // If there is no king, there is no danger of incidental check.
    if( king_pos == IMPOS_COORD )
        throw runtime_error( "The game has no target's king yet it is in a check state for said king." );


    // Initialize the coordinate of the attacking piece.
    pair<int,int> atk_pce_ij;
    // Obtain the attacking piece coordinate.
    if( tarColor == CHS_PIECE_COLOR::WHITE ){

        // The check state cannot be disolved if two or more enemy pieces are attacking
        // the king at the same time.
        if( this->atk_list_by_B[ chess::sub2ind( king_pos ) ].size() > 1 ){
            return true;
        // Obtain the only attacker's coordinate.
        }else if( this->atk_list_by_B[ chess::sub2ind( king_pos ) ].size() == 1 ){
            atk_pce_ij = chess::ind2sub( this->atk_list_by_B[ chess::sub2ind( king_pos ) ].at(0) );
        }else{
            throw runtime_error( "The white king is not under any threat despite white being in check state." );
        }

    }else{
        
        // The check state cannot be disolved if two or more enemy pieces are attacking
        // the king at the same time.
        if( this->atk_list_by_W[ chess::sub2ind( king_pos ) ].size() > 1 ){
            return true;
        // Obtain the only attacker's coordinate.
        }else if( this->atk_list_by_W[ chess::sub2ind( king_pos ) ].size() == 1 ){
            atk_pce_ij = chess::ind2sub( this->atk_list_by_W[ chess::sub2ind( king_pos ) ].at(0) );
        }else{
            throw runtime_error( "The black king is not under any threat despite black being in check state." );
        }

    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Check State Absolution Analysis
// ---------------------------------------------------------------------- >>>>>

    chs_piece atk_pce = this->get_piece_at( atk_pce_ij );
    CHS_PIECE_TYPE atkType = atk_pce.type;

    pair<int,int> atk_to_tar_diff;
    pair<int,int> tar_to_king_diff;

    // Analysis selection based on the attacker's piece type.
    switch( atkType ){
    case CHS_PIECE_TYPE::PAWN:

        // Special en-passant case.
        if( this->en_pass_flag ){
                
            bool valid_enpass = true;
            // Try to match current pawn move to any available en-passant move.
            for( chs_move move_z : this->en_pass_moves ){

                valid_enpass = true;
                // Verify if the target move is a pawn performing en-passant.
                valid_enpass = valid_enpass && ( i_bef == move_z.pt_a.first );
                valid_enpass = valid_enpass && ( j_bef == move_z.pt_a.second );
                valid_enpass = valid_enpass && ( i_aft == move_z.pt_b.first );
                valid_enpass = valid_enpass && ( j_aft == move_z.pt_b.second );
                // Verify if the en-passant target is the attacking pawn.
                valid_enpass = valid_enpass && ( atk_pce_ij.first == i_bef );
                valid_enpass = valid_enpass && ( atk_pce_ij.second == j_aft );

                if( valid_enpass )
                    break;

            }
            // If a match is found, 
            if( valid_enpass ){
                return false;
            }
                
        }

    case CHS_PIECE_TYPE::KNIGHT:

        // A pawn or knight can only be stopped through elimination.
        if( ( i_aft == atk_pce_ij.first ) && ( j_aft == atk_pce_ij.second ) ){
            return false;
        }else{
            return true;
        }
        break;

    case CHS_PIECE_TYPE::BISHOP:

        // Compute the distance between the attacker and the target.
        atk_to_tar_diff = { i_aft - atk_pce_ij.first, j_aft - atk_pce_ij.second };
        // Compute the distance between the the target and its king.
        tar_to_king_diff = { king_pos.first - i_aft, king_pos.second - j_aft };

        // The target piece destination must share a diagonal with the attacker and the
        // king in order to be able to block the check.
        if( ( abs( atk_to_tar_diff.first ) != abs( atk_to_tar_diff.second ) ) ||
            ( abs( tar_to_king_diff.first ) != abs( tar_to_king_diff.second ) ) )
            return true;

        /*
        Note: Having just the knowledge that the target piece ends up along a diagonal
        with the king as well as with the attacker is sufficient to determine that
        the target piece is ending up on the same diagonal as both the king and the
        attacker.
        This is because we know that the attacker is on the same diagonal as the king by
        virtue of the fact that it is a bishop attacking the king.
        */

        // The target piece ending destination must be in-between the attacker
        // and the king for the check to be blocked.
        if( ( atk_to_tar_diff.first >= 0 && tar_to_king_diff.first > 0 ) || 
            ( atk_to_tar_diff.first <= 0 && tar_to_king_diff.first < 0 ) ){
            return false;
        }else{
            return true;
        }

        break;

    case CHS_PIECE_TYPE::ROOK:

        // Row share.
        if( king_pos.first == atk_pce_ij.first ){

            // The playing piece must end on the same row as the king and the attacker.
            if( i_aft != king_pos.first )
                return true;

            // Assessment depends on whether the column index of the king is higher 
            // or lower than its attacker.
            if( king_pos.second > atk_pce_ij.second ){
                return !( j_aft >= atk_pce_ij.second && j_aft < king_pos.second );
            }else{
                return !( j_aft <= atk_pce_ij.second && j_aft > king_pos.second );
            }

        // Column share.
        }else if( king_pos.second == atk_pce_ij.second ){

            // The playing piece must end on the same row as the king and the attacker.
            if( j_aft != king_pos.second )
                return true;

            // Assessment depends whether the row index of the king is higher 
            // or lower than its attacker.
            if( king_pos.first > atk_pce_ij.first ){
                return !( i_aft >= atk_pce_ij.first && i_aft < king_pos.first );
            }else{
                return !( i_aft <= atk_pce_ij.first && i_aft > king_pos.first );
            }

        }else{
            throw runtime_error( "A rook checking a king must share either the row or column with said king." );
        }

        break;

    case CHS_PIECE_TYPE::QUEEN:

        // Same row case.
        if( king_pos.first == atk_pce_ij.first ){
            
            // The playing piece must end on the same row as the king and the attacker.
            if( i_aft != king_pos.first )
                return true;

            // Assessment depends on whether the column index of the king is higher 
            // or lower than its attacker.
            if( king_pos.second > atk_pce_ij.second ){
                return !( j_aft >= atk_pce_ij.second && j_aft < king_pos.second );
            }else{
                return !( j_aft <= atk_pce_ij.second && j_aft > king_pos.second );
            }

        // Same column case.
        }else if( king_pos.second == atk_pce_ij.second ){

            // The playing piece must end on the same row as the king and the attacker.
            if( j_aft != king_pos.second )
                return true;

            // Assessment depends whether the row index of the king is higher 
            // or lower than its attacker.
            if( king_pos.first > atk_pce_ij.first ){
                return !( i_aft >= atk_pce_ij.first && i_aft < king_pos.first );
            }else{
                return !( i_aft <= atk_pce_ij.first && i_aft > king_pos.first );
            }

        // Same diagonal case.
        }else{

            // Compute the distance between the attacker and the target.
            atk_to_tar_diff = { i_aft - atk_pce_ij.first, j_aft - atk_pce_ij.second };
            // Compute the distance between the the target and its king.
            tar_to_king_diff = { king_pos.first - i_aft, king_pos.second - j_aft };

            // The target piece destination must share a diagonal with the attacker and the
            // king in order to be able to block the check.
            if( ( abs( atk_to_tar_diff.first ) != abs( atk_to_tar_diff.second ) ) ||
                ( abs( tar_to_king_diff.first ) != abs( tar_to_king_diff.second ) ) )
                return true;

            // The target piece ending destination must be in-between the attacker
            // and the king for the check to be blocked.
            if( ( atk_to_tar_diff.first >= 0 && tar_to_king_diff.first > 0 ) || 
                ( atk_to_tar_diff.first <= 0 && tar_to_king_diff.first < 0 ) ){
                return false;
            }else{
                return true;
            }

        }

        break;
        
    default:
        break;
    };

// ---------------------------------------------------------------------- <<<<<

    return false;

}

bool chess::is_atk_legal( pair<int,int> coord_bef, pair<int,int> coord_aft ) const{
    return this->is_atk_legal( coord_bef.first, coord_bef.second, 
        coord_aft.first, coord_aft.second );
}

bool chess::is_atk_legal( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft  ) const
{

    // If list of valid moves is up-to-date, just refer to it for answer.
    if( this->is_all_legal_atks_upd ){
        int ij_bef = sub2ind( i_bef, j_bef );
        int ij_aft = sub2ind( i_aft, j_aft );
        for( int tmp : this->legal_atks_map[ ij_bef ] )
            if( tmp == ij_aft )
                return true;
        return false;
    }

    // Obtain the color of the current piece.
    CHS_PIECE_COLOR tarColor = this->CHS_board[i_bef][j_bef].color;
    // Turn check.
    if( this->turn_cnt % 2 == 0 && tarColor != CHS_PIECE_COLOR::WHITE ||
        this->turn_cnt % 2 == 1 && tarColor != CHS_PIECE_COLOR::BLACK ){
        return false;
    }

    bool is_legal = true;

    is_legal = is_legal && ( this->is_atk_valid( i_bef, j_bef, i_aft, j_aft ) );

    if( is_legal )
        // Determine if the attack causes own king's check state to end (if it was in check).
        is_legal = is_legal && !( this->is_chk_persist( i_bef, j_bef, i_aft, j_aft ) );
    if( is_legal )
        // Determine if the attack causes own king to be exposed to a check.
        is_legal = is_legal && ( this->is_incidental_safe( i_bef, j_bef, i_aft, j_aft ) );

    return is_legal;

}

bool chess::is_atk_valid( unsigned int i_bef, unsigned int j_bef, 
    unsigned int i_aft, unsigned int j_aft ) const
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

    if( this->is_valid_atks_upd ){
        
        // Obtain the linear indices of the before and after coordinates.
        int ind_ij_bef = sub2ind( i_bef, j_bef );
        int ind_ij_aft = sub2ind( i_aft, j_aft );

        if( tarColor == CHS_PIECE_COLOR::WHITE ){
            for( int z : this->valid_W_atks_map[ ind_ij_bef ] )
                if( z == ind_ij_aft ){ return true; }
            return false;
        }else if( tarColor == CHS_PIECE_COLOR::BLACK ){
            for( int z : this->valid_B_atks_map[ ind_ij_bef ] )
                if( z == ind_ij_aft ){ return true; }
            return false;
        }else{
            return false;
        }

    }

    // Flag indicating whether the current move is an en-passant attack.
    bool is_en_pass = false;
    // The unique scenario of en-passant pawn attack superseeds all remaining checks.
    if( tarPce.type == CHS_PIECE_TYPE::PAWN && this->en_pass_flag ){

        // Determine if the current attack matches any of the currently active
        // en-passant possiblities.
        for( unsigned int z = 0; z < this->en_pass_moves.size(); z++ ){

            is_en_pass = is_en_pass ||
            ( en_pass_moves[z].pt_a.first == i_bef &&
            en_pass_moves[z].pt_a.second == j_bef &&
            en_pass_moves[z].pt_b.first == i_aft &&
            en_pass_moves[z].pt_b.second == j_aft );

        }

    }

    // Obtain piece at destination.
    chs_piece endPce = this->get_piece_at( i_aft, j_aft );
    // Check empty space at destination.
    if( !is_en_pass && ( endPce.type == CHS_PIECE_TYPE::NO_P || endPce.color == CHS_PIECE_COLOR::NO_C ) ){
        return false;
    }
    // Make sure the attacker and the defender are of different colors.
    if( !is_en_pass && ( tarPce.color == endPce.color ) ){
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

    // Initialize temporary boolean flag.
    bool state_ok = true;
    // // Determine if the attack causes own king's check state to end (if it was in check).
    // state_ok = state_ok && !( this->is_chk_persist( i_bef, j_bef, i_aft, j_aft ) );
    // if( state_ok ){
    //     // Determine if the attack causes own king to be exposed to a check.
    //     state_ok = state_ok && ( this->is_incidental_safe( i_bef, j_bef, i_aft, j_aft ) );
    // }

    return state_ok;

}

bool chess::is_atk_valid( int ind_a, int ind_b ) const{
    pair<int,int> sub_a = ind2sub(ind_a);
    pair<int,int> sub_b = ind2sub(ind_b);
    return this->is_atk_valid( sub_a.first, sub_a.second, sub_b.first, sub_b.second );
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>


bool chess::is_white_turn() const{
    return ( this->turn_cnt % 2 == 0 );
}
bool chess::is_black_turn() const{
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


vector< pair<int,int> > chess::get_all_legal_atk_sq( int i, int j ) const{

    auto valid_atk_vec = this->get_all_valid_atk_sq( i, j );

    // Initialize legal attack vector
    vector< pair<int,int> > legal_atk_vec;

    for( pair<int,int> move_z : valid_atk_vec ){
        if( is_atk_legal( i, j, move_z.first, move_z.second ) ){
            legal_atk_vec.push_back( move_z );
        }
    }

    return legal_atk_vec;

}

vector< pair<int,int> > chess::get_all_valid_atk_sq( int i, int j ) const{

    auto all_valid_sub_atk_sq = this->get_all_valid_atk_sq( chess::sub2ind( i, j ) );

    vector<pair<int,int>> all_valid_atk_sq;
    all_valid_atk_sq.reserve( all_valid_sub_atk_sq.size() );

    for( int tarInd_z : all_valid_sub_atk_sq ){
        all_valid_atk_sq.push_back( chess::ind2sub( tarInd_z ) );
    }

    return all_valid_atk_sq;

}


vector<int> chess::get_all_valid_atk_sq( int tarIndIdx ) const{
    
    // If the valid move squares maps are up-to-date, just use them.
    if( this->is_valid_atks_upd ){

        // Obtain existing list of valid attacks (Based on piece color).
        chs_piece tarPce = this->get_piece_at( tarIndIdx );
        if( tarPce.color == CHS_PIECE_COLOR::WHITE ){
            return this->valid_W_atks_map[ tarIndIdx ];
        }else if( tarPce.color == CHS_PIECE_COLOR::BLACK ){
            return this->valid_B_atks_map[ tarIndIdx ];

        // Non-colored piece is considered empty square.
        }else{
            return vector<int>();
        }

    }

    // Linear to 2D coordinate.
    pair<int,int> ij = chess::ind2sub( tarIndIdx );
    
    vector<pair<int,int>> all_atk_sq = this->get_all_atk_sq( ij.first, ij.second );
    vector<int>all_valid_atk_sq;
    
    for( pair<int,int> atk_sq_z : all_atk_sq )
        if( this->is_atk_valid( ij.first, ij.second, atk_sq_z.first, atk_sq_z.second ) ){
            all_valid_atk_sq.push_back( chess::sub2ind( atk_sq_z ) );
        }

    return all_valid_atk_sq;
    
}


vector< pair<int,int> > chess::get_all_legal_move_sq( int i, int j ) const{

    auto valid_mov_vec = this->get_all_valid_move_sq( i, j );

    // Initialize legal move vector
    vector< pair<int,int> > legal_mov_vec;

    for( pair<int,int> move_z : valid_mov_vec ){
        if( is_move_legal( i, j, move_z.first, move_z.second ) ){
            legal_mov_vec.push_back( move_z );
        }
    }

    return legal_mov_vec;

}


vector< pair<int,int> > chess::get_all_valid_move_sq( int i, int j ) const{

    // Obtain linear move coordinates.
    vector<int> val_mov_ind_vec = 
        this->get_all_valid_move_sq( sub2ind( i, j ) );

    // Translate coordinates to 2D format.
    vector< pair<int,int> > val_mov_vec;
    val_mov_vec.reserve( val_mov_ind_vec.size() );
    for( int ind_z : val_mov_ind_vec ){
        val_mov_vec.push_back( chess::ind2sub( ind_z ) );
    }
    
    return val_mov_vec;

}


vector< int > chess::get_all_valid_move_sq( int tarIndIdx ) const{

    // Obtain the target piece.
    chs_piece tarPce = this->get_piece_at( tarIndIdx );
    
    if( this->is_valid_moves_upd ){

        // If the valid move squares maps are up-to-date, just use them.
        if( tarPce.color == CHS_PIECE_COLOR::WHITE ){
            return this->valid_W_moves_map[ tarIndIdx ];
        }else if( tarPce.color == CHS_PIECE_COLOR::BLACK ){
            return this->valid_B_moves_map[ tarIndIdx ];

        // Non-colored piece is considered empty square.
        }else{
            return vector<int>();
        }

    }

    // Obtain the 2D coordinate.
    pair<int,int> ij = chess::ind2sub( tarIndIdx );
    int i = ij.first;
    int j = ij.second;
    
    // Initialize valid move vector.
    vector<int> val_mov_vec;
    // Initialize attack list from (i, j).
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
        return val_mov_vec;
    }



    for( int atk_ij: atk_list_fr_ij ){
        if( this->is_move_valid( tarIndIdx, atk_ij ) ){
            val_mov_vec.push_back( atk_ij );
        }
    }

    

    // Pawn moves that do not attack.
    if( tarPce.type == CHS_PIECE_TYPE::PAWN ){

        int sign_mult = 1;
        tarPce.color == CHS_PIECE_COLOR::BLACK ? sign_mult = -1 : sign_mult = 1;

        if( this->is_move_valid( tarIndIdx, tarIndIdx + sign_mult * chess::BOARDWIDTH ) ){
            val_mov_vec.push_back( tarIndIdx + sign_mult * chess::BOARDWIDTH );
        }
        if( this->is_move_valid( tarIndIdx, tarIndIdx + sign_mult * 2 * chess::BOARDWIDTH ) ){
            val_mov_vec.push_back( tarIndIdx + sign_mult * 2 * chess::BOARDWIDTH );
        }
       
    }
    // King moves that do not attack.
    if( tarPce.type == CHS_PIECE_TYPE::KING ){

        if( tarPce.not_moved ){
            // Right castling.
            if( this->is_move_valid( tarIndIdx, tarIndIdx + 2 ) ){
                val_mov_vec.push_back( tarIndIdx + 2 );
            }
            // Left castling.
            if( this->is_move_valid( tarIndIdx, tarIndIdx - 2 ) ){
                val_mov_vec.push_back( tarIndIdx - 2 );
            }
        }

    }

    return val_mov_vec;

}






pair<bool,bool> chess::is_in_check(){

    pair<bool,bool> chk_ans = { false, false };

    pair<int,int> sub_idx_z = {-1,-1};
    chs_piece pce_z;

    // Perform a full board scan to determine checks.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        sub_idx_z = ind2sub(z);
        pce_z = this->get_piece_at( sub_idx_z.first, sub_idx_z.second );

        if( pce_z.type == CHS_PIECE_TYPE::KING ){
            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

                if( this->atk_list_by_B[z].size() != 0 ){
                    chk_ans.first = true;
                }
                
            }
            if( pce_z.color == CHS_PIECE_COLOR::BLACK ){

                if( this->atk_list_by_W[z].size() != 0 ){
                    chk_ans.second = true;
                }
                
            }
        }

    }

    return chk_ans;

}


bool chess::is_check_mate(){

    // If the check state is true, determine if it is a checkmate.
    if( this->state == CHS_STATE::WCHK || this->state == CHS_STATE::BWIN ){

        bool no_options = true;
        if( !this->is_all_legal_atks_upd )
            { this->upd_all_legal_atks(); }
        if( !this->is_all_legal_moves_upd )
            { this->upd_all_legal_moves(); }

        for( unsigned int z = 0; z < this->legal_atks_map.size(); z++ ){
            no_options = no_options && this->legal_atks_map[z].size() == 0;
        }
        for( unsigned int z = 0; z < this->legal_moves_map.size(); z++ ){
            no_options = no_options && this->legal_moves_map[z].size() == 0;
        }
        

        return no_options;

    }else if( this->state == CHS_STATE::BCHK || this->state == CHS_STATE::WWIN ){

        bool no_options = true;
        if( !this->is_all_legal_atks_upd )
            { this->upd_all_legal_atks(); }
        if( !this->is_all_legal_moves_upd )
            { this->upd_all_legal_moves(); }

        for( unsigned int z = 0; z < this->legal_atks_map.size(); z++ ){
            no_options = no_options && this->legal_atks_map[z].size() == 0;
        }
        for( unsigned int z = 0; z < this->legal_moves_map.size(); z++ ){
            no_options = no_options && this->legal_moves_map[z].size() == 0;
        }

        return no_options;

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

    if( !this->is_all_legal_moves_upd )
        this->upd_all_legal_moves();
    if( !this->is_all_legal_atks_upd )
        this->upd_all_legal_atks();

    bool no_valid_moves = true;
    // If there is no move possible at all, stalemate.
    for( unsigned int z = 0; z < this->legal_atks_map.size(); z++ ){
        no_valid_moves = no_valid_moves && this->legal_atks_map[z].size() == 0;
    }
    for( unsigned int z = 0; z < this->legal_moves_map.size(); z++ ){
        no_valid_moves = no_valid_moves && this->legal_moves_map[z].size() == 0;
    }

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



bool chess::upd_all(){

    bool upd_res = true;

    upd_res = upd_res && ( this->upd_post_play() );

    this->upd_end_game_state();

    return upd_res;

}



bool chess::upd_post_play(){

    bool upd_res = true;    

    this->upd_pce_cnt_list();

    this->upd_pre_legal_plays();

    upd_res = upd_res && ( this->upd_mid_game_state() );

    this->upd_all_legal_moves();
    this->upd_all_legal_atks();

    return upd_res;

}



bool chess::upd_mid_game_state(){

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
                        if( this->verbose ){
                            cout << "Black and white kings both in check." << endl;
                        }
                        return false;
                    }else{
                        state = CHS_STATE::WCHK;
                    }
                }
                

            }
            if( pce_z.color == CHS_PIECE_COLOR::BLACK ){

                if( this->atk_list_by_W[z].size() != 0 ){
                    if( state == CHS_STATE::WCHK ){
                        if( this->verbose ){
                            cout << "Black and white kings both in check." << endl;
                        }
                        return false;
                    }else{
                        state = CHS_STATE::BCHK;
                    }
                }
                
            }
            if( pce_z.color == CHS_PIECE_COLOR::NO_C ){
                if( this->verbose ){
                    cout << "Unrecognized chess piece color." << endl;
                }
                return false;
            }
        }

    }

    // If no state has been determined to this point, set as on going by default.
    if( this->state == CHS_STATE::NO_S ){
        this->state = CHS_STATE::ONGOING;
    }

    return true;

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


void chess::game_tracking_signal(){

    this->is_atk_lists_upd = false;

    this->is_psbl_alg_comm_upd = false;
    this->is_all_legal_moves_upd = false;
    this->is_all_legal_atks_upd = false;

    this->is_valid_moves_upd = false;
    this->is_valid_atks_upd = false;

}



void chess::upd_pce_cnt_list(){

    // Reset all counters.
    for( pair< CHS_PIECE_TYPE, int > cnt_z : this->wPieceCounter ){
        this->wPieceCounter[ cnt_z.first ] = 0;
        this->bPieceCounter[ cnt_z.first ] = 0;
    }

    chs_piece currPce;
    // Parse through the entire board and counter the number of pieces.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
        currPce = this->get_piece_at( ind2sub( z ) );
        if( currPce.type != CHS_PIECE_TYPE::NO_P ){
            if( currPce.color == CHS_PIECE_COLOR::WHITE ){
                this->wPieceCounter[ currPce.type ]++;
            }else if( currPce.color == CHS_PIECE_COLOR::BLACK ){
                this->bPieceCounter[ currPce.type ]++;
            }
        }
    }

}


/*
TODO: This function must be THE most efficient function in the class.
The information it updates is fundamental too all other info, and is
thus one of the most called function.
It is also the most resource intensive function, as it has no choice but to
check all pieces on the board.
*/
void chess::upd_atk_lists(){

    if( this->is_atk_lists_upd && !this->force_lists_upd ){
        return;
    }

    // Empty the existing attack list vectors.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
        this->atk_list_by_W[z].clear();
        this->atk_list_by_B[z].clear();
    }
    this->is_atk_lists_upd = false;
    
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
        if( this->CHS_board[coord_z.first][coord_z.second].type == CHS_PIECE_TYPE::NO_P ){
            continue;
        }

        // Obtain the list of all squares attacked by the current piece.
        // atk_list_z = get_all_atk_sq( coord_z.first, coord_z.second );
        atk_list_z = get_all_atk_sq_spec( coord_z.first, coord_z.second );
        // Translate into linear indexing.
        atk_sub_list_z = sub2ind( atk_list_z );

        if( this->CHS_board[coord_z.first][coord_z.second].color == CHS_PIECE_COLOR::WHITE ){

            for( int sq_lin_idx : atk_sub_list_z ){
                this->atk_list_by_W[sq_lin_idx].push_back(z);
            }

        }else if( this->CHS_board[coord_z.first][coord_z.second].color == CHS_PIECE_COLOR::BLACK ){

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

    this->is_atk_lists_upd = true;

}


void chess::upd_all_legal_moves(){


    if( this->is_all_legal_moves_upd && !this->force_lists_upd ){
        return;
    }
    if( !this->is_valid_moves_upd || this->force_lists_upd ){
        this->upd_all_valid_moves();
    }

    this->is_all_legal_moves_upd = false;

    // Clear all currently saved possible plays.
    for( unsigned int z = 0; z < this->legal_moves_map.size(); z++ ){
        this->legal_moves_map[z].clear();
    }
    
    // Scan for legal moves based on current turn.
    if( this->is_white_turn() ){
        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
            for( int move_zz : this->valid_W_moves_map[z] ){
                if( this->is_move_legal( chess::ind2sub(z), chess::ind2sub(move_zz) ) ){
                    this->legal_moves_map[z].push_back(move_zz);
                }
            }
        }
    }else{
        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
            for( int move_zz : this->valid_B_moves_map[z] ){
                if( this->is_move_legal( chess::ind2sub(z), chess::ind2sub(move_zz) ) ){
                    this->legal_moves_map[z].push_back(move_zz);
                }
            }
        }
    }

    this->is_all_legal_moves_upd = true;

}


void chess::upd_all_legal_atks(){

    if( this->is_all_legal_atks_upd && !this->force_lists_upd ){
        return;
    }
    if( !this->is_valid_atks_upd || this->force_lists_upd ){
        this->upd_all_valid_atks();
    }

    this->is_all_legal_atks_upd = false;

    // Clear all currently saved possible plays.
    for( unsigned int z = 0; z < this->legal_atks_map.size(); z++ ){
        this->legal_atks_map[z].clear();
    }
    // Scan for legal attack based on current turn.
    if( this->is_white_turn() ){
        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
            for( int atk_zz : this->valid_W_atks_map[z] ){
                if( this->is_atk_legal( chess::ind2sub(z), chess::ind2sub(atk_zz) ) ){
                    this->legal_atks_map[z].push_back( atk_zz );
                }
            }
        }
    }else{
        for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){
            for( int atk_zz : this->valid_B_atks_map[z] ){
                if( this->is_atk_legal( chess::ind2sub(z), chess::ind2sub(atk_zz) ) ){
                    this->legal_atks_map[z].push_back( atk_zz );
                }
            }
        }
    }

    this->is_all_legal_atks_upd = true;

}


void chess::upd_all_valid_moves(){

    if( this->is_valid_moves_upd && !this->force_lists_upd ){
        return;
    }

    for( unsigned int z = 0; z < chess::BOARDHEIGHT*chess::BOARDWIDTH; z++ ){
        this->valid_W_moves_map[z].clear();
        this->valid_B_moves_map[z].clear();
    }
    this->is_valid_moves_upd = false;

    pair<int,int> sub_idx_z;
    vector<int> move_sq_list_z;


    // Parse through the board and verify all possible moves in the attack lists.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        for( int ind_v : this->atk_list_by_W[z] ){
            if( is_move_valid( ind_v, z ) ){
                valid_W_moves_map[ind_v].push_back( z );
            }
        }
        for( int ind_v : this->atk_list_by_B[z] ){
            if( is_move_valid( ind_v, z ) ){
                valid_B_moves_map[ind_v].push_back( z );
            }
        }

    }

    int tarIndIdx = -1;
    int sign_mult = 1;
    // Parse through the board and look for pawns and the king who have moves that
    // aren't equivalent to attacks.
    for( unsigned int i = 0; i < chess::BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < chess::BOARDWIDTH; j++ ){
        
        if( this->CHS_board[i][j].type == CHS_PIECE_TYPE::PAWN ){
            
            tarIndIdx = sub2ind(i,j);
            if( this->CHS_board[i][j].color == CHS_PIECE_COLOR::WHITE ){
                sign_mult = 1;
                if( this->is_move_valid( tarIndIdx, tarIndIdx + sign_mult * chess::BOARDWIDTH ) ){
                    valid_W_moves_map[tarIndIdx].push_back( tarIndIdx + sign_mult * chess::BOARDWIDTH );
                }
                if( this->is_move_valid( tarIndIdx, tarIndIdx + sign_mult * 2 * chess::BOARDWIDTH ) ){
                    valid_W_moves_map[tarIndIdx].push_back( tarIndIdx + sign_mult * 2 * chess::BOARDWIDTH );
                }
            }else{
                sign_mult = -1;
                if( this->is_move_valid( tarIndIdx, tarIndIdx + sign_mult * chess::BOARDWIDTH ) ){
                    valid_B_moves_map[tarIndIdx].push_back( tarIndIdx + sign_mult * chess::BOARDWIDTH );
                }
                if( this->is_move_valid( tarIndIdx, tarIndIdx + sign_mult * 2 * chess::BOARDWIDTH ) ){
                    valid_B_moves_map[tarIndIdx].push_back( tarIndIdx + sign_mult * 2 * chess::BOARDWIDTH );
                }
            }

        }else if( this->CHS_board[i][j].type == CHS_PIECE_TYPE::KING ){

            if( this->CHS_board[i][j].not_moved ){
                tarIndIdx = sub2ind(i,j);

                if( this->CHS_board[i][j].color == CHS_PIECE_COLOR::WHITE ){
                    // White right castling.
                    if( this->is_move_valid( tarIndIdx, tarIndIdx + 2 ) )
                        valid_W_moves_map[tarIndIdx].push_back( tarIndIdx + 2 );
                    // White left castling.
                    if( this->is_move_valid( tarIndIdx, tarIndIdx - 2 ) )
                        valid_W_moves_map[tarIndIdx].push_back( tarIndIdx - 2 );
                }else{
                    // Black right castling.
                    if( this->is_move_valid( tarIndIdx, tarIndIdx + 2 ) )
                        valid_B_moves_map[tarIndIdx].push_back( tarIndIdx + 2 );
                    // Black left castling.
                    if( this->is_move_valid( tarIndIdx, tarIndIdx - 2 ) )
                        valid_B_moves_map[tarIndIdx].push_back( tarIndIdx - 2 );
                }
                
            }

        }
        
    }
    }

    this->is_valid_moves_upd = true;

}


void chess::upd_all_valid_atks(){

    if( this->is_valid_atks_upd && !this->force_lists_upd ){
        return;
    }

    for( unsigned int z = 0; z < chess::BOARDHEIGHT*chess::BOARDWIDTH; z++ ){
        this->valid_W_atks_map[z].clear();
        this->valid_B_atks_map[z].clear();
    }
    this->is_valid_atks_upd = false;

    // Parse through the board and verify all possible moves in the attack lists.
    for( unsigned int z = 0; z < BOARDHEIGHT*BOARDWIDTH; z++ ){

        for( int ind_v : this->atk_list_by_W[z] ){
            if( is_atk_valid( ind_v, z ) ){
                valid_W_atks_map[ind_v].push_back( z );
            }
        }
        for( int ind_v : this->atk_list_by_B[z] ){
            if( is_atk_valid( ind_v, z ) ){
                valid_B_atks_map[ind_v].push_back( z );
            }
        }

    }


    this->is_valid_atks_upd = true;

}


void chess::upd_pre_legal_plays(){

    if( !this->force_lists_upd && this->is_atk_lists_upd &&
        this->is_valid_moves_upd && this->is_valid_atks_upd ){
        return;
    }

    // Empty the existing vectors.
    for( unsigned int z = 0; z < chess::BOARDHEIGHT*chess::BOARDWIDTH; z++ ){
        this->atk_list_by_W[z].clear();
        this->atk_list_by_B[z].clear();
        this->valid_W_moves_map[z].clear();
        this->valid_B_moves_map[z].clear();
        this->valid_W_atks_map[z].clear();
        this->valid_B_atks_map[z].clear();
    }
    this->is_atk_lists_upd = false;
    this->is_valid_moves_upd = false;
    this->is_valid_atks_upd = false;

    // The number of squares on the board.
    int sq_cnt = chess::BOARDHEIGHT * chess::BOARDWIDTH;
    // Current sub index.
    pair<int,int> coord_z;
    int i = 0;     int j = 0;
    int aim_z = 0;
    // The king indices.
    unsigned int W_king_idx = 0;    unsigned int B_king_idx = 0;
    // The piece being investigated.
    chs_piece pce_z;
    // The piece currently at the scan location.
    chs_piece pce_tmp;

    // Knight and king evaluation scenarios.
    int kn_aims[8] = {0,0,0,0,0,0,0,0};
    bool kn_bools[8] = {0,0,0,0,0,0,0,0};

    // Line evaluation scenarios.
    array< vector<int>, 8 > line_aims;
    for( unsigned int z = 0; z < line_aims.size(); z++ ){
        line_aims[z].reserve(7);
    }
    // Define number of lines of current piece.
    unsigned int line_aims_cnt = 0;


    // Obstruction boolean.
    bool is_obstr = false;
    // Loop continue flag.
    bool cont_flag = false;
    // Castling possibility.
    bool W_cast_posb = false;
    bool B_cast_posb = false;

    for( int z = 0; z < sq_cnt; z++ ){

        coord_z = chess::ind2sub(z);
        i = coord_z.first;      j = coord_z.second;

        pce_z = this->CHS_board[i][j];

        // Skip if empty.
        if( pce_z.type == CHS_PIECE_TYPE::NO_P ){
            continue;
        }

// ---------------------------------------------------------------------- >>>>>
//      Get All Atk Squares
// ---------------------------------------------------------------------- >>>>>

        /*
        Compute the distance (number of squares away) of the piece to each of the 
        board borders.
        */
        int top_dist = BOARDHEIGHT - 1 - i;
        int right_dist = BOARDWIDTH - 1 - j;
        int bottom_dist = i;
        int left_dist = j;
        
        cont_flag = false;

        // Non-line based movement pieces.
        switch( pce_z.type ){

        case CHS_PIECE_TYPE::PAWN:

            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

                if( top_dist > 0 ){

                    // Attacks right.
                    aim_z = z + chess::BOARDWIDTH + 1;
                    if( ( aim_z < sq_cnt ) && ( j < chess::BOARDWIDTH - 1 ) ){

                        this->atk_list_by_W[ aim_z ].push_back( z );

                        if( top_dist > 0 && right_dist > 0 &&
                            this->CHS_board[i+1][j+1].type != CHS_PIECE_TYPE::NO_P &&
                            this->CHS_board[i+1][j+1].color != pce_z.color )
                            this->valid_W_atks_map[z].push_back( aim_z );

                    }

                    // Attacks left.
                    aim_z = z + chess::BOARDWIDTH - 1;
                    if( ( aim_z < sq_cnt ) && ( j > 0 ) ){
                        
                        this->atk_list_by_W[ aim_z ].push_back( z );

                        if( top_dist > 0 && left_dist > 0 &&
                            this->CHS_board[i+1][j-1].type != CHS_PIECE_TYPE::NO_P &&
                            this->CHS_board[i+1][j-1].color != pce_z.color )
                            this->valid_W_atks_map[z].push_back( aim_z );

                    }

                    // Moves.
                    aim_z = z + chess::BOARDWIDTH;
                    if( top_dist > 0 && this->CHS_board[i+1][j].type == CHS_PIECE_TYPE::NO_P ){
                        valid_W_moves_map[z].push_back( aim_z );

                        // Double jump.
                        if( pce_z.not_moved && top_dist > 1 &&
                            this->CHS_board[i+2][j].type == CHS_PIECE_TYPE::NO_P )
                        {
                            valid_W_moves_map[z].push_back( z + 2 * chess::BOARDWIDTH );
                        }

                    }

                }

                

            }else if( pce_z.color == CHS_PIECE_COLOR::BLACK ){

                if( bottom_dist > 0 ){

                    // Attacks right (black POV).
                    aim_z = z - chess::BOARDWIDTH - 1;
                    if( ( aim_z >= 0 ) && ( j > 0 ) ){

                        this->atk_list_by_B[ aim_z ].push_back( z );

                        if( bottom_dist > 0 && left_dist > 0 &&
                            this->CHS_board[i-1][j-1].type != CHS_PIECE_TYPE::NO_P &&
                            this->CHS_board[i-1][j-1].color != pce_z.color )
                            this->valid_B_atks_map[z].push_back( aim_z );

                    }
                                        
                    // Attacks left (black POV).
                    aim_z = z - chess::BOARDWIDTH + 1;
                    if( ( aim_z >= 0 ) && ( j < chess::BOARDWIDTH - 1 ) ){

                        this->atk_list_by_B[ aim_z ].push_back( z );
   
                        if( bottom_dist > 0 && right_dist > 0 &&
                            this->CHS_board[i-1][j+1].type != CHS_PIECE_TYPE::NO_P &&
                            this->CHS_board[i-1][j+1].color != pce_z.color )
                            this->valid_B_atks_map[z].push_back( aim_z );

                    }
                    

                    // Moves.
                    aim_z = z - chess::BOARDWIDTH;
                    if( bottom_dist > 0 && this->CHS_board[i-1][j].type == CHS_PIECE_TYPE::NO_P ){
                        valid_B_moves_map[z].push_back( aim_z );

                        // Double jump.
                        if( pce_z.not_moved && bottom_dist > 1 &&
                            this->CHS_board[i-2][j].type == CHS_PIECE_TYPE::NO_P )
                        {
                            valid_B_moves_map[z].push_back( z - 2 * chess::BOARDWIDTH );
                        }

                    }

                }

            }

            cont_flag = true;
            break;

        case CHS_PIECE_TYPE::KNIGHT:

            // Identifying all 8 jump squares around the knight and whether they are 
            // on the board.
            kn_aims[0] = z - 2 * chess::BOARDWIDTH - 1;
            kn_bools[0] = ( kn_aims[0] >= 0 ) && ( j > 0 );
            kn_aims[1] = z - 2 * chess::BOARDWIDTH + 1;
            kn_bools[1] = ( kn_aims[1] >= 0 ) && ( j < BOARDWIDTH - 1 );
            kn_aims[2] = z - chess::BOARDWIDTH - 2;
            kn_bools[2] = ( kn_aims[2] >= 0 ) && ( j > 1 );
            kn_aims[3] = z - chess::BOARDWIDTH + 2;
            kn_bools[3] = ( kn_aims[3] >= 0 ) && ( j < BOARDWIDTH - 2 );
            kn_aims[4] = z + chess::BOARDWIDTH - 2;
            kn_bools[4] = kn_aims[4] < sq_cnt && ( j > 1 );
            kn_aims[5] = z + chess::BOARDWIDTH + 2;
            kn_bools[5] = kn_aims[5] < sq_cnt && ( j < BOARDWIDTH - 2 );
            kn_aims[6] = z + 2 * chess::BOARDWIDTH - 1;
            kn_bools[6] = kn_aims[6] < sq_cnt && ( j > 0 );
            kn_aims[7] = z + 2 * chess::BOARDWIDTH + 1;
            kn_bools[7] = kn_aims[7] < sq_cnt && ( j < BOARDWIDTH - 1 );


            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

                for( int t = 0; t < 8; t++ ){
                    if( kn_bools[t] ){
                        aim_z = kn_aims[t];
                        this->atk_list_by_W[ aim_z ].push_back( z );
                        if( this->get_piece_at( aim_z ).type == CHS_PIECE_TYPE::NO_P ){
                            this->valid_W_moves_map[z].push_back( aim_z );
                        }else if( this->get_piece_at( aim_z ).color == CHS_PIECE_COLOR::BLACK ){
                            this->valid_W_atks_map[z].push_back( aim_z );
                        }
                    }
                }

            }else{

                for( int t = 0; t < 8; t++ ){
                    if( kn_bools[t] ){
                        aim_z = kn_aims[t];
                        this->atk_list_by_B[ aim_z ].push_back( z );
                        if( this->get_piece_at( aim_z ).type == CHS_PIECE_TYPE::NO_P ){
                            this->valid_B_moves_map[z].push_back( aim_z );
                        }else if( this->get_piece_at( aim_z ).color == CHS_PIECE_COLOR::WHITE ){
                            this->valid_B_atks_map[z].push_back( aim_z );
                        }
                    }
                }

            }

            cont_flag = true;
            break;

        case CHS_PIECE_TYPE::KING:
          

            if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

                // Update the white king's index.
                W_king_idx = z;
                // Update castling possiblity for white.
                W_cast_posb = pce_z.not_moved && z == 4;

            }else{

                // Update the black king's index.
                B_king_idx = z;
                // Update castling possiblity for black.
                B_cast_posb = pce_z.not_moved && z == 60;

            }

            cont_flag = true;
            break;

        default:
            break;
        }

        // Conitnue to next square if job already done.
        if( cont_flag )
            continue;

        line_aims_cnt = 0;
        // Clear the lines.
        for( unsigned int t = 0; t < line_aims.size(); t++ )
            line_aims[t].clear();

        // Line based movement pieces.
        switch( pce_z.type ){

            case CHS_PIECE_TYPE::BISHOP:

            // North-East diagonal squares.
            line_aims[0].clear();
            for( int NE_z = 1; NE_z <= min( top_dist, right_dist ) ; NE_z++ ){
                line_aims[0].push_back( z + NE_z * chess::BOARDWIDTH + NE_z );
            }
            line_aims[1].clear();
            // North-West diagonal squares.
            for( int NW_z = 1; NW_z <= min( top_dist, left_dist ) ; NW_z++ ){
                line_aims[1].push_back( z + NW_z * chess::BOARDWIDTH - NW_z );
            }
            line_aims[2].clear();
            // South-West diagonal squares.
            for( int SW_z = 1; SW_z <= min( bottom_dist, left_dist ) ; SW_z++ ){
                line_aims[2].push_back( z - SW_z * chess::BOARDWIDTH - SW_z );
            }
            line_aims[3].clear();
            // South-East diagonal squares.
            for( int SE_z = 1; SE_z <= min( bottom_dist, right_dist ) ; SE_z++ ){
                line_aims[3].push_back( z - SE_z * chess::BOARDWIDTH + SE_z );
            }

            line_aims_cnt = 4;
            break;

        case CHS_PIECE_TYPE::ROOK:

            // North sweep.
            line_aims[0].clear();
            for( int N_z = 1; N_z <= top_dist; N_z++ )
                line_aims[0].push_back( z + N_z * chess::BOARDWIDTH );
            // West sweep.
            line_aims[1].clear();
            for( int W_z = 1; W_z <= left_dist; W_z++ )
                line_aims[1].push_back( z - W_z );
            // South sweep.
            line_aims[2].clear();
            for( int S_z = 1; S_z <= bottom_dist; S_z++ )
                line_aims[2].push_back( z - S_z * chess::BOARDWIDTH );
            // East sweep.
            line_aims[3].clear();
            for( int E_z = 1; E_z <= right_dist; E_z++ )
                line_aims[3].push_back( z + E_z );
            
            line_aims_cnt = 4;
            break;

        case CHS_PIECE_TYPE::QUEEN:

            // North-East diagonal squares.
            for( int NE_z = 1; NE_z <= min( top_dist, right_dist ) ; NE_z++ )
                line_aims[0].push_back( z + NE_z * chess::BOARDWIDTH + NE_z );
            // North-West diagonal squares.
            for( int NW_z = 1; NW_z <= min( top_dist, left_dist ) ; NW_z++ )
                line_aims[1].push_back( z + NW_z * chess::BOARDWIDTH - NW_z );
            // South-West diagonal squares.
            for( int SW_z = 1; SW_z <= min( bottom_dist, left_dist ) ; SW_z++ )
                line_aims[2].push_back( z - SW_z * chess::BOARDWIDTH - SW_z );
            // South-East diagonal squares.
            for( int SE_z = 1; SE_z <= min( bottom_dist, right_dist ) ; SE_z++ )
                line_aims[3].push_back( z - SE_z * chess::BOARDWIDTH + SE_z );
            // North sweep.
            for( int N_z = 1; N_z <= top_dist; N_z++ )
                line_aims[4].push_back( z + N_z * chess::BOARDWIDTH );
            // West sweep.
            for( int W_z = 1; W_z <= left_dist; W_z++ )
                line_aims[5].push_back( z - W_z );
            // South sweep.
            for( int S_z = 1; S_z <= bottom_dist; S_z++ )
                line_aims[6].push_back( z - S_z * chess::BOARDWIDTH );
            // East sweep.
            for( int E_z = 1; E_z <= right_dist; E_z++ )
                line_aims[7].push_back( z + E_z );
            
            line_aims_cnt = 8;
            break;


        default:
            break;
        }

        // Perform the actual list updates by screening through all recorded lines.
        if( pce_z.color == CHS_PIECE_COLOR::WHITE ){

            for( unsigned int t = 0; t < line_aims_cnt; t++ ){

                is_obstr = false;
                for( int aim_zt : line_aims[t] ){

                    pce_tmp = this->get_piece_at( aim_zt );
                    this->atk_list_by_W[ aim_zt ].push_back( z );

                    // Obstruction check.
                    if( !( pce_tmp.type == CHS_PIECE_TYPE::NO_P ) ){ 

                        // Add to attack map if valid.
                        if( !is_obstr && pce_tmp.color == CHS_PIECE_COLOR::BLACK ){
                            this->valid_W_atks_map[z].push_back( aim_zt );
                        }

                        // Only break if obstruction is not enemy king.
                        if( !( pce_tmp.type == CHS_PIECE_TYPE::KING &&
                        pce_tmp.color != pce_z.color ) )
                            break;
                        else{
                            is_obstr = true;
                        }

                    }else{

                        // Add to move map if valid.
                        if( !is_obstr ){
                            this->valid_W_moves_map[z].push_back( aim_zt );
                        }

                    }

                }
                
            }

        }else{
            
            for( unsigned int t = 0; t < line_aims.size(); t++ ){

                is_obstr = false;
                for( int aim_zt : line_aims[t] ){

                    pce_tmp = this->get_piece_at( aim_zt );
                    this->atk_list_by_B[ aim_zt ].push_back( z );

                    // Obstruction check.
                    if( !( pce_tmp.type == CHS_PIECE_TYPE::NO_P ) ){ 

                        // Add to attack map if valid.
                        if( !is_obstr && pce_tmp.color == CHS_PIECE_COLOR::WHITE ){
                            this->valid_B_atks_map[z].push_back( aim_zt );
                        }

                        // Only break if obstruction is not enemy king.
                        if( !( pce_tmp.type == CHS_PIECE_TYPE::KING &&
                        pce_tmp.color != pce_z.color ) )
                            break;
                        else{
                            is_obstr = true;
                        }

                    }else{

                        // Add to move map if valid.
                        if( !is_obstr ){
                            this->valid_B_moves_map[z].push_back( aim_zt );
                        }

                    }

                }
                
            }

        }

// // ---------------------------------------------------------------------- <<<<<

    }


// ---------------------------------------------------------------------- >>>>>
//      En-Passant Check
// ---------------------------------------------------------------------- >>>>>

    if( this->en_pass_flag ){
        for( chs_move move_z : this->en_pass_moves ){
            int str_pt = chess::sub2ind( move_z.pt_a );
            int atk_pt = chess::sub2ind( move_z.pt_b );

            if( this->CHS_board[move_z.pt_a.first][move_z.pt_a.second].color == 
                CHS_PIECE_COLOR::WHITE )
            {
                this->atk_list_by_W[atk_pt - chess::BOARDWIDTH].push_back(str_pt);
                this->valid_W_atks_map[str_pt].push_back(atk_pt);
            }else{
                this->atk_list_by_B[atk_pt + chess::BOARDWIDTH].push_back(str_pt);
                this->valid_B_atks_map[str_pt].push_back(atk_pt);
            }
        }
    }

// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      King Moves and Attacks Check
// ---------------------------------------------------------------------- >>>>>

    // Obtain the columsn of the kings.
    int wj = ( chess::ind2sub( W_king_idx ) ).second;
    int bj = ( chess::ind2sub( B_king_idx ) ).second;

    // Initialize arrays representing the reach of the kings.
    int WK_aims[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool WK_bools[8] = { false, false, false, false, false, false, false, false };
    int BK_aims[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool BK_bools[8] = { false, false, false, false, false, false, false, false };

    // Identifying all 8 squares around the white king and whether they are 
    // on the board.
    WK_aims[0] = W_king_idx + chess::BOARDWIDTH + 1;
    WK_bools[0] = WK_aims[0] < sq_cnt && ( wj < chess::BOARDWIDTH - 1 );
    WK_aims[1] = W_king_idx + chess::BOARDWIDTH;
    WK_bools[1] = WK_aims[1] < sq_cnt;
    WK_aims[2] = W_king_idx + chess::BOARDWIDTH - 1;
    WK_bools[2] = WK_aims[2] < sq_cnt && ( wj > 0 );
    WK_aims[3] = W_king_idx - 1;
    WK_bools[3] = ( wj > 0 );
    WK_aims[4] = W_king_idx - chess::BOARDWIDTH - 1;
    WK_bools[4] = ( WK_aims[4] >= 0 ) && ( wj > 0 );
    WK_aims[5] = W_king_idx - chess::BOARDWIDTH;
    WK_bools[5] = ( WK_aims[5] >= 0 );
    WK_aims[6] = W_king_idx - chess::BOARDWIDTH + 1;
    WK_bools[6] = ( WK_aims[6] >= 0 ) && ( wj < chess::BOARDWIDTH - 1 );
    WK_aims[7] = W_king_idx + 1;
    WK_bools[7] = ( wj < chess::BOARDWIDTH - 1 );

    // Identifying all 8 squares around the black king and whether they are 
    // on the board.
    BK_aims[0] = B_king_idx + chess::BOARDWIDTH + 1;
    BK_bools[0] = BK_aims[0] < sq_cnt && ( bj < chess::BOARDWIDTH - 1 );
    BK_aims[1] = B_king_idx + chess::BOARDWIDTH;
    BK_bools[1] = BK_aims[1] < sq_cnt;
    BK_aims[2] = B_king_idx + chess::BOARDWIDTH - 1;
    BK_bools[2] = BK_aims[2] < sq_cnt && ( bj > 0 );
    BK_aims[3] = B_king_idx - 1;
    BK_bools[3] = ( bj > 0 );
    BK_aims[4] = B_king_idx - chess::BOARDWIDTH - 1;
    BK_bools[4] = ( BK_aims[4] >= 0 ) && ( bj > 0 );
    BK_aims[5] = B_king_idx - chess::BOARDWIDTH;
    BK_bools[5] = ( BK_aims[5] >= 0 );
    BK_aims[6] = B_king_idx - chess::BOARDWIDTH + 1;
    BK_bools[6] = ( BK_aims[6] >= 0 ) && ( bj < chess::BOARDWIDTH - 1 );
    BK_aims[7] = B_king_idx + 1;
    BK_bools[7] = ( bj < chess::BOARDWIDTH - 1 );


    // Update the reach of the white king.
	for( unsigned int zz = 0; zz < 8u; zz++ ){
		if( WK_bools[zz] ){
            aim_z = WK_aims[zz];
			this->atk_list_by_W[ aim_z ].push_back( W_king_idx );
		}
    }
    // Update the reach of the black king.
    for( unsigned int t = 0; t < 8u; t++ ){
		if( BK_bools[t] ){
            aim_z = BK_aims[t];
			this->atk_list_by_B[ aim_z ].push_back( B_king_idx );
		}
    }
    
    // Update the valid plays for the white king.
    for( int t = 0; t < 8; t++ ){
		if( WK_bools[t] ){
            aim_z = WK_aims[t];
            if( this->atk_list_by_B[aim_z].size() != 0 )
                continue;
            if( this->get_piece_at( aim_z ).type == CHS_PIECE_TYPE::NO_P ){
				this->valid_W_moves_map[ W_king_idx ].push_back( aim_z );
			}else if( this->get_piece_at( aim_z ).color == CHS_PIECE_COLOR::BLACK ){
				this->valid_W_atks_map[ W_king_idx ].push_back( aim_z );
			}
        }
    }
    // Update the valid plays for the black king.
    for( int t = 0; t < 8; t++ ){
		if( BK_bools[t] ){
			aim_z = BK_aims[t];
            if( this->atk_list_by_W[aim_z].size() != 0 )
                continue;
            if( this->get_piece_at( aim_z ).type == CHS_PIECE_TYPE::NO_P ){
				this->valid_B_moves_map[ B_king_idx ].push_back( aim_z );
			}else if( this->get_piece_at( aim_z ).color == CHS_PIECE_COLOR::WHITE ){
				this->valid_B_atks_map[ B_king_idx ].push_back( aim_z );
			}
        }
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Castling Moves Check
// ---------------------------------------------------------------------- >>>>>

    // White king danger moves/atks check
    

    // White castling possibility check.
    if( W_cast_posb ){

        bool cast_poss = true;
        // Right-side castling check.
        cast_poss = cast_poss && ( this->CHS_board[0][7].type == CHS_PIECE_TYPE::ROOK );
        cast_poss = cast_poss && ( this->CHS_board[0][7].color == CHS_PIECE_COLOR::WHITE );
        cast_poss = cast_poss && ( this->CHS_board[0][7].not_moved );
        cast_poss = cast_poss && ( this->CHS_board[0][6].type == CHS_PIECE_TYPE::NO_P );
        cast_poss = cast_poss && ( this->CHS_board[0][5].type == CHS_PIECE_TYPE::NO_P );
        // Make sure the entire path is clear from black threats.
        cast_poss = cast_poss && ( this->atk_list_by_B[4].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_B[5].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_B[6].empty() );
        if( cast_poss )
            this->valid_W_moves_map[4].push_back( 6 );

        cast_poss = true;
        // Right-side castling check.
        cast_poss = cast_poss && ( this->CHS_board[0][0].type == CHS_PIECE_TYPE::ROOK );
        cast_poss = cast_poss && ( this->CHS_board[0][0].color == CHS_PIECE_COLOR::WHITE );
        cast_poss = cast_poss && ( this->CHS_board[0][0].not_moved );
        cast_poss = cast_poss && ( this->CHS_board[0][1].type == CHS_PIECE_TYPE::NO_P );
        cast_poss = cast_poss && ( this->CHS_board[0][2].type == CHS_PIECE_TYPE::NO_P );
        cast_poss = cast_poss && ( this->CHS_board[0][3].type == CHS_PIECE_TYPE::NO_P );
        // Make sure the entire path is clear from black threats.
        cast_poss = cast_poss && ( this->atk_list_by_B[4].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_B[3].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_B[2].empty() );
        if( cast_poss )
            this->valid_W_moves_map[4].push_back( 2 );

    }

    // Black castling possibility check.
    if( B_cast_posb ){

        bool cast_poss = true;
        // Left-side castling check.
        cast_poss = cast_poss && ( this->CHS_board[7][7].type == CHS_PIECE_TYPE::ROOK );
        cast_poss = cast_poss && ( this->CHS_board[7][7].color == CHS_PIECE_COLOR::BLACK );
        cast_poss = cast_poss && ( this->CHS_board[7][7].not_moved );
        cast_poss = cast_poss && ( this->CHS_board[7][6].type == CHS_PIECE_TYPE::NO_P );
        cast_poss = cast_poss && ( this->CHS_board[7][5].type == CHS_PIECE_TYPE::NO_P );
        // Make sure the entire path is clear from white threats.
        cast_poss = cast_poss && ( this->atk_list_by_W[60].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_W[61].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_W[62].empty() );
        if( cast_poss )
            this->valid_B_moves_map[60].push_back( 62 );

        cast_poss = true;
        // Right-side castling check.
        cast_poss = cast_poss && ( this->CHS_board[7][0].type == CHS_PIECE_TYPE::ROOK );
        cast_poss = cast_poss && ( this->CHS_board[7][0].color == CHS_PIECE_COLOR::BLACK );
        cast_poss = cast_poss && ( this->CHS_board[7][0].not_moved );
        cast_poss = cast_poss && ( this->CHS_board[7][1].type == CHS_PIECE_TYPE::NO_P );
        cast_poss = cast_poss && ( this->CHS_board[7][2].type == CHS_PIECE_TYPE::NO_P );
        cast_poss = cast_poss && ( this->CHS_board[7][3].type == CHS_PIECE_TYPE::NO_P );
        // Make sure the entire path is clear from white threats.
        cast_poss = cast_poss && ( this->atk_list_by_W[60].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_W[59].empty() );
        cast_poss = cast_poss && ( this->atk_list_by_W[58].empty() );
        if( cast_poss )
            this->valid_B_moves_map[60].push_back( 58 );

    }

// ---------------------------------------------------------------------- <<<<<

    this->is_atk_lists_upd = true;
    this->is_valid_moves_upd = true;
    this->is_valid_atks_upd = true;

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
            if( this->is_move_legal( castle_mov ) ){
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
            if( this->is_move_legal( castle_mov ) ){
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
                        if( this->is_atk_legal( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_legal( coord_z, aft_coord ) ){
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
                        if( this->is_atk_legal( coord_z, aft_coord ) ){
                            bef_coord = coord_z;
                            fnd_cnt++;
                        }
                    }else{
                        if( this->is_move_legal( coord_z, aft_coord ) ){
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
                    if( this->is_atk_legal( coord_z, aft_coord ) ){
                        bef_coord = coord_z;
                        fnd_cnt++;
                    }
                }else{
                    if( this->is_move_legal( coord_z, aft_coord ) ){
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
chess::chs_piece chess::get_piece_at( int linIdx ) const{
    pair<int,int> tmp_idx = chess::ind2sub( linIdx );
    return this->get_piece_at( tmp_idx.first, tmp_idx.second );
}

unsigned int chess::getTurn_cnt() const
    { return this->turn_cnt; }
void chess::setTurn_cnt( const unsigned int turn_cnt ){ 
    this->turn_cnt = turn_cnt; 
    this->game_tracking_signal();
}

pair<int,int> chess::get_W_king_pos() const{
    for( unsigned int i = 0; i < chess::BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < chess::BOARDWIDTH; j++ ){
        if( this->CHS_board[i][j].type == CHS_PIECE_TYPE::KING && 
            this->CHS_board[i][j].color == CHS_PIECE_COLOR::WHITE ){
            return pair<int,int>(i,j);
        }
    }
    }
    return chess::IMPOS_COORD;
}
pair<int,int> chess::get_B_king_pos() const{
    for( unsigned int i = 0; i < chess::BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < chess::BOARDWIDTH; j++ ){
        if( this->CHS_board[i][j].type == CHS_PIECE_TYPE::KING && 
            this->CHS_board[i][j].color == CHS_PIECE_COLOR::BLACK ){
            return pair<int,int>(i,j);
        }
    }
    }
    return chess::IMPOS_COORD;
}

chess::CHS_STATE chess::getState() const
    { return this->state; }
void chess::setState( const CHS_STATE state ){ 
    this->state = state; 
    this->game_tracking_signal();
}

unsigned int chess::getNo_change_turn_cnt() const
    { return this->no_change_turn_cnt; }
void chess::setNo_change_turn_cnt( const unsigned int no_change_turn_cnt ){ 
    this->no_change_turn_cnt = no_change_turn_cnt; 
    this->game_tracking_signal();
}




bool chess::getEn_pass_flag() const
    {return this->en_pass_flag;}
void chess::setEn_pass_flag( bool en_pass_flag ){
    this->en_pass_flag = en_pass_flag;
    this->game_tracking_signal();
}

vector<chess::chs_move> chess::getEn_pass_moves() const
    {return this->en_pass_moves;}
void chess::setEn_pass_moves( vector<chs_move> en_pass_move_in ){
    this->en_pass_moves = en_pass_move_in;
    this->game_tracking_signal();
}

bool chess::getPromo_lock() const
    {return this->promo_lock;}
void chess::setPromo_lock( const bool promo_lock ){
    this->promo_lock = promo_lock;
    this->game_tracking_signal();
}

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
    this->game_tracking_signal();
}


void chess::setVerbose( bool verbose )
    {this->verbose = verbose;}

bool chess::getVerbose() const
    {return this->verbose;}

int chess::getChs_pce_val( chess::CHS_PIECE_TYPE tarType ) const{
    if( tarType == CHS_PIECE_TYPE::NO_P ){
        throw invalid_argument( "The no piece type is not assigned a value." );
    }
    return this->chs_pce_val_map.at( tarType );
}
map<chess::CHS_PIECE_TYPE,int> chess::getChs_pce_val_map() const
    {return this->chs_pce_val_map;}
void chess::setChs_pce_val( chess::CHS_PIECE_TYPE tarType, int newVal ){
    if( tarType == CHS_PIECE_TYPE::NO_P ){
        throw invalid_argument( "The no piece type cannot be given a value." );
    }
    this->chs_pce_val_map[ tarType ] = newVal;
    this->game_tracking_signal();
}

map<string, int> chess::getMinmax_vals() const
    { return this->minmax_vals; }
void chess::setMinmax_vas( string tarVal, int newVal ){
    for( pair<string, int> pair_z : this->minmax_vals ){
        if( pair_z.first == tarVal ){
            this->minmax_vals[tarVal] = newVal;
            this->game_tracking_signal();
            return;
        }
    }
    throw invalid_argument( "Given minmax value string description is invalid." );
}

void chess::setMinmax_depth( unsigned int minmax_depth_in ){ 
    this->minmax_depth = minmax_depth_in; 
    this->game_tracking_signal();
}
unsigned int chess::getMinmax_depth() const
    { return this->minmax_depth; }

bool chess::getAI_first() const
    { return this->AI_first; }
void chess::setAI_first( bool AI_first_in ){ 
    this->AI_first = AI_first_in; 
    this->game_tracking_signal();
}

bool chess::getAI_proc_flag() const
    { return this->AI_proc_flag; }
void chess::setAI_proc_flag( const bool AI_proc_flag_in ){ 
    this->AI_proc_flag = AI_proc_flag_in; 
    this->game_tracking_signal();
}

unsigned int chess::getThread_to_use() const
    { return this->thread_to_use; }
void chess::setThread_to_use( unsigned int thr_cnt )
    { this->thread_to_use = thr_cnt; }


array<vector<int>,chess::BOARDHEIGHT*chess::BOARDWIDTH> chess::getAtk_list_by_W()
{
    if( !this->is_atk_lists_upd ){
        this->upd_atk_lists();
    }
    return this->atk_list_by_W;
}
array<vector<int>,chess::BOARDHEIGHT*chess::BOARDWIDTH> chess::getAtk_list_by_B()
{
    if( !this->is_atk_lists_upd ){
        this->upd_atk_lists();
    }
    return this->atk_list_by_B;
}


bool chess::getIs_psbl_alg_comm_upd() const
    { return this->is_psbl_alg_comm_upd; }
vector<string> chess::get_all_psbl_alg_comm(){ 
    if( !this->is_psbl_alg_comm_upd ){
        this->upd_all_psbl_alg_comm();
    }
    return this->all_psbl_alg_comm; 
}

bool chess::getIs_all_legal_moves_upd() const
    { return this->is_all_legal_moves_upd; }
vector<chess::chs_move> chess::get_all_legal_moves(){
    if( !this->is_all_legal_moves_upd ){
        this->upd_all_legal_moves();
    }

    vector<chess::chs_move> all_legal_moves_tmp;
    all_legal_moves_tmp.reserve(200);
    pair<int,int> ij_sub_bef = {-1,-1};
    pair<int,int> ij_sub_aft = {-1,-1};
    for( unsigned int z = 0; z < this->legal_moves_map.size(); z++ ){

        if( legal_moves_map[z].size() > 0 ){
            ij_sub_bef = chess::ind2sub(z);
            for( int ij_aft_zz : legal_moves_map[z] ){
                ij_sub_aft = chess::ind2sub( ij_aft_zz );
                all_legal_moves_tmp.push_back( chs_move( ij_sub_bef, ij_sub_aft ) );
            }
        }
    }
    all_legal_moves_tmp.shrink_to_fit();

    return all_legal_moves_tmp; 
}
array< vector<int>, chess::BOARDHEIGHT*chess::BOARDWIDTH > chess::get_legal_moves_map(){
    if( !this->is_all_legal_moves_upd ){
        this->upd_all_legal_moves();
    }
    return this->legal_moves_map;
}


bool chess::getForce_lists_upd() const
    { return this->force_lists_upd; }
void chess::setForce_lists_upd( bool in_force_lists_upd )
    { this->force_lists_upd = in_force_lists_upd; }

bool chess::getIs_atk_lists_upd() const{
    return this->is_atk_lists_upd;
}

bool chess::getIs_valid_moves_upd() const{
    return this->is_valid_moves_upd;
}
array< vector<int>, chess::BOARDHEIGHT*chess::BOARDWIDTH > chess::get_valid_W_moves_map(){
    if( !this->is_valid_moves_upd ){
        this->upd_all_valid_moves();
    }
    return this->valid_W_moves_map; 
}
array< vector<int>, chess::BOARDHEIGHT*chess::BOARDWIDTH > chess::get_valid_B_moves_map(){
    if( !this->is_valid_moves_upd ){
        this->upd_all_valid_moves();
    }
    return this->valid_B_moves_map; 
}

bool chess::getIs_all_legal_atks_upd() const
    { return this->is_all_legal_atks_upd; }
vector<chess::chs_move> chess::get_all_legal_atks(){
    if( !this->is_all_legal_atks_upd ){
        this->upd_all_legal_atks();
    }

    vector<chess::chs_move> all_legal_atks_tmp;
    all_legal_atks_tmp.reserve(200);
    pair<int,int> ij_sub_bef = {-1,-1};
    pair<int,int> ij_sub_aft = {-1,-1};
    for( unsigned int z = 0; z < this->legal_atks_map.size(); z++ ){
        if( legal_atks_map[z].size() > 0 ){
            ij_sub_bef = chess::ind2sub(z);
            for( int ij_aft_zz : legal_atks_map[z] ){
                ij_sub_aft = chess::ind2sub( ij_aft_zz );
                all_legal_atks_tmp.push_back( chs_move( ij_sub_bef, ij_sub_aft ) );
            }
        }
    }
    all_legal_atks_tmp.shrink_to_fit();

    return all_legal_atks_tmp; 
}
array< vector<int>, chess::BOARDHEIGHT*chess::BOARDWIDTH > chess::get_legal_atks_map(){
    if( !this->is_all_legal_atks_upd ){
        this->upd_all_legal_atks();
    }
    return this->legal_moves_map;
}

bool chess::getIs_valid_atks_upd() const
    { return this->is_valid_atks_upd; }
array< vector<int>, chess::BOARDHEIGHT*chess::BOARDWIDTH > chess::get_valid_W_atks_map(){
    if( !this->is_valid_atks_upd ){
        this->upd_all_valid_atks();
    }
    return this->valid_W_atks_map; 
}
array< vector<int>, chess::BOARDHEIGHT*chess::BOARDWIDTH > chess::get_valid_B_atks_map(){
    if( !this->is_valid_atks_upd ){
        this->upd_all_valid_atks();
    }
    return this->valid_B_atks_map; 
}


// ====================================================================== <<<<<



void chess::upd_all_psbl_alg_comm(){

    // Clear all currently saved possible plays.
    this->all_psbl_alg_comm.clear();
    this->is_psbl_alg_comm_upd = false;

    // Obtain all current possible plays.
    vector<chs_move> all_atks = this->get_all_legal_atks();
    vector<chs_move> all_plays = this->get_all_legal_moves();
    all_plays.insert( all_plays.end(), all_atks.begin(), all_atks.end() );

    // Initialize final vector of algebraic commands.
    all_psbl_alg_comm.reserve( all_plays.size() + 12 );
    
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
            all_psbl_alg_comm.push_back( alg_comm_z + 'N' );
            all_psbl_alg_comm.push_back( alg_comm_z + 'B' );
            all_psbl_alg_comm.push_back( alg_comm_z + 'R' );
            all_psbl_alg_comm.push_back( alg_comm_z + 'Q' );

        // Any other case, just add the command to the list.
        }else{
            all_psbl_alg_comm.push_back( alg_comm_z );
        }

    }

    all_psbl_alg_comm.shrink_to_fit();
    // Update the flag variable.
    this->is_psbl_alg_comm_upd = true;

}



