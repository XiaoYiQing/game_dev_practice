#include "checkers.h"


using namespace gameEngine;


// ====================================================================== >>>>>
//      Class Enum "CHK_PIECE" Help Functions
// ====================================================================== >>>>>

string checkers::get_CHK_PIECE_Str( checkers::CHK_PIECE tar_CHK_PIECE ){
    return string( magic_enum::enum_name( tar_CHK_PIECE ) );
}

checkers::CHK_PIECE checkers::get_CHK_PIECE_AtIdx( int idx ){
    if( idx >= 0 && idx < checkers::CHK_PIECE_Count ){
        return static_cast<checkers::CHK_PIECE>(idx);
    }else{
        cout << "Invalid int index for accessing enum \"CHK_PIECE\"." << endl;
        return static_cast<checkers::CHK_PIECE>(-1);
    }
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHK_DIREC" Help Functions
// ====================================================================== >>>>>

string checkers::get_CHK_DIREC_Str( checkers::CHK_DIREC tar_CHK_DIREC ){
    return string( magic_enum::enum_name( tar_CHK_DIREC ) );
}

checkers::CHK_DIREC checkers::get_CHK_DIREC_AtIdx( int idx ){
    if( idx >= 0 && idx < checkers::CHK_DIREC_Count ){
        return static_cast<checkers::CHK_DIREC>(idx);
    }else{
        cout << "Invalid int index for accessing enum \"CHK_DIREC\"." << endl;
        return static_cast<checkers::CHK_DIREC>(-1);
    }
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHK_STATE" Help Functions
// ====================================================================== >>>>>

string checkers::get_CHK_STATE_Str( CHK_STATE tar_CHK_STATE ){
    return string( magic_enum::enum_name( tar_CHK_STATE ) );
}

checkers::CHK_STATE get_CHK_STATE_AtIdx( int idx ){
    if( idx >= 0 && idx < checkers::CHK_STATE_Count ){
        return static_cast<checkers::CHK_STATE>(idx);
    }else{
        cout << "Invalid int index for accessing enum \"CHK_STATE\"." << endl;
        return static_cast<checkers::CHK_STATE>(-1);
    }
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Specialized Nested Class for Moves
// ====================================================================== >>>>>

checkers::CHK_move::CHK_move( unsigned int i, unsigned int j, checkers::CHK_DIREC k ){
    this->i = i;
    this->j = j;
    this->k = k;
}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>
checkers::checkers(){

    turn_cnt = 0;
    no_change_turn_cnt = 0;
    pieceCounter = { 0, 0, 0, 0 };
    state = CHK_STATE::ONGOING;
    minmax_depth = 5;

    // Initialize the checker board.
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){
            CHK_board[i][j] = CHK_PIECE::NO_P;
        }
    }

    for( unsigned int i = 0; i < BOARD_SIZE/2 - 1; i++ ){
        for( unsigned int j = (unsigned int) remainder(i,2); j < BOARD_SIZE; j+=2 ){
            CHK_board[i][j] = CHK_PIECE::BLK_P;
            CHK_board[BOARD_SIZE - i - 1][BOARD_SIZE - j - 1] = CHK_PIECE::RED_P;
        }
    }

    

}
// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>


bool checkers::play( unsigned int i, unsigned int j, CHK_DIREC direction ){

    string playMsg = "Play [";
    playMsg = playMsg + "(" + to_string(i) + ", " + to_string(j) + ") => ";
    playMsg = playMsg + get_CHK_DIREC_Str(direction) + "]";
    
    /*
    Game state check before proceeding.
    */
    switch( this->state ){
        case CHK_STATE::ONGOING:
            break;
        case CHK_STATE::LOCKED:
            // When in locked state, the only piece allowed to be played is the
            // locked target piece.
            if( lock_tar.at(0) != i || lock_tar.at(1) != j ){
                cout << playMsg << " failed: when game is in locked state, the only piece allowed to be played is ";
                cout << "the locked target piece (" << lock_tar.at(0) << "," << lock_tar.at(1) << ")." << endl;
                return false;
            }
            break;
        case CHK_STATE::BWIN:
        case CHK_STATE::RWIN:
        case CHK_STATE::DRAW:
            cout << playMsg << " failed: game has ended." << endl;
            return false;
            break;
        default:
            cerr << playMsg << " resulted in an unrecognized game state. Abort." << endl;
            return false;
    }

    /*
    No piece case check.
    */
    CHK_PIECE currPiece = CHK_board[i][j];
    if( currPiece == CHK_PIECE::NO_P ){
        cout << playMsg << " failed: no piece is located at designated coordinate." << endl;
        return false;
    }

    int currPieceTurnID = getTurnID( currPiece );

    /*
    Attempts an attack immediately and obtain the coordinate of the piece 
    after the attack.
    */
    vector<unsigned int> atkLandCoord = attack( i, j, direction );
    // Check attempt result.
    if( !atkLandCoord.empty() ){
        
        if( currPieceTurnID == 0 ){
            crownBlkPiece( atkLandCoord.at(1) );
        }else if( currPieceTurnID == 1 ){
            crownRedPiece( atkLandCoord.at(1) );
        }

        // Check if the attacking piece has new targets after performing the 
        // initial attack.
        vector<CHK_DIREC> newAtkAvenues = 
            this->theoAtkCheckAll( atkLandCoord.at(0), atkLandCoord.at(1), currPiece );
        // If the attacking piece now has new targets, lock the game
        if( !newAtkAvenues.empty() ){

            // State is forcibly locked and normal state check is skipped.
            state = CHK_STATE::LOCKED;
            // Update the lock target to our piece that just performed an attack.
            lock_tar = atkLandCoord;
        
        // Continue the game as per usual.
        }else{
            
            // Release the lock if the game was in locked state.
            if( state == CHK_STATE::LOCKED ){
                lock_tar.clear();
                state = CHK_STATE::ONGOING;
            }
            // Increment turn count.
            this->turn_cnt++;
            // Update the state of the game after the move.
            this->upd_game_state();
        
        }

        // Update the list of pieces that can possibly attack.
        this->upd_atk_posb();

        return true;

    }else{
        // If an attack is not performed during a locked state, abort.
        if( state == CHK_STATE::LOCKED ){
            cout << playMsg << " failed: when the game is in locked state, only an attack can be performed with the locking piece." << endl;
            return false;
        }
    }


    /* 
    Make sure there are no other pieces of the same color that are capable of 
    attacking before trying to move the current piece.
    */
    if( currPieceTurnID == 0 ){

        /*
        The black piece is not allowed to move if another black piece is in 
        position to attack.
        */
        if( B_atk_list.size() > 0 ){
            cout << playMsg << " failed: current black piece cannot move if an attack by a black piece is possible." << endl;
            return false;
        }

    }else if( currPieceTurnID == 1 ){

        /*
        The red piece is not allowed to move if another red piece is in 
        position to attack.
        */
        if( R_atk_list.size() > 0 ){
            cout << playMsg << " failed: current red piece cannot move if an attack by a red piece is possible." << endl;
            return false;
        }

    }else{
        cerr << playMsg << " failed: unexpected turn ID detected. Abort." << endl;
        return false;
    }
    

    /*
    Attempts a move and obtain the coordinate of the piece the move.
    */
    vector<unsigned int> moveLandCoord = move( i, j, direction );
    if( !moveLandCoord.empty() ){
        
        if( currPieceTurnID == 0 ){
            crownBlkPiece( moveLandCoord.at(1) );
        }else if( currPieceTurnID == 1 ){
            crownRedPiece( moveLandCoord.at(1) );
        }

        // Increment turn count.
        this->turn_cnt++;
        // Update the list of pieces that can possibly attack.
        this->upd_atk_posb();
        // Update the state of the game after the move.
        this->upd_game_state();

        return true;

    }

    cout << playMsg << " failed: current piece's play is invalid." << endl;
    return false;

}



vector<unsigned int> checkers::attack( unsigned int i, unsigned int j, CHK_DIREC direction ){

    vector<unsigned int> landCoord;

    if( !validAtkCheck( i, j, direction ) ){
        return landCoord;
    }

    CHK_PIECE currPiece = CHK_board[i][j];

    // Determine the normalized vectors of attack.
    int di_norm = 0;
    int dj_norm = 0;
    switch( direction ){
        case( CHK_DIREC::UPLEFT ):
            di_norm = -1;    dj_norm = -1;
            break;
        case( CHK_DIREC::UPRIGHT ):
            di_norm = -1;    dj_norm = +1;
            break;
        case( CHK_DIREC::DOWNLEFT ):
            di_norm = +1;    dj_norm = -1;
            break;
        case( CHK_DIREC::DOWNRIGHT ):
            di_norm = +1;    dj_norm = +1;
            break;
    }

    // Empty starting square.
    CHK_board[i][j] = CHK_PIECE::NO_P;
    // Empty attacked square.
    CHK_board[i + di_norm][j + dj_norm] = CHK_PIECE::NO_P;
    // Put original piece at landing.
    CHK_board[i + 2*di_norm][j + 2*dj_norm] = currPiece;

    // Insert the coordinate where the attack piece ended up at.
    landCoord.push_back(i + 2*di_norm);
    landCoord.push_back(j + 2*dj_norm);

    return landCoord;

}


vector<unsigned int> checkers::move( unsigned int i, unsigned int j, CHK_DIREC direction ){

    vector<unsigned int> landCoord;

    if( !validMoveCheck( i, j, direction ) ){
        return landCoord;
    }

    CHK_PIECE currPiece = CHK_board[i][j];

    // Determine the normalized vectors of attack.
    int di_norm = 0;
    int dj_norm = 0;
    switch( direction ){
        case( CHK_DIREC::UPLEFT ):
            di_norm = -1;    dj_norm = -1;
            break;
        case( CHK_DIREC::UPRIGHT ):
            di_norm = -1;    dj_norm = +1;
            break;
        case( CHK_DIREC::DOWNLEFT ):
            di_norm = +1;    dj_norm = -1;
            break;
        case( CHK_DIREC::DOWNRIGHT ):
            di_norm = +1;    dj_norm = +1;
            break;
    }

    // Empty starting square.
    CHK_board[i][j] = CHK_PIECE::NO_P;
    // Empty attacked square.
    CHK_board[i + di_norm][j + dj_norm] = currPiece;

    // Insert the coordinate where the attack piece ended up at.
    landCoord.push_back(i + di_norm);
    landCoord.push_back(j + dj_norm);

    return landCoord;

}


bool checkers::crownBlkPiece( unsigned int j ){
    if( CHK_board[ BOARD_SIZE - 1 ][j] != CHK_PIECE::BLK_P ){
        return false;
    }else{
        CHK_board[ BOARD_SIZE - 1 ][j] = CHK_PIECE::CBLK_P;
    }
    return true;
}

bool checkers::crownRedPiece( unsigned int j ){
    if( CHK_board[0][j] != CHK_PIECE::RED_P ){
        return false;
    }else{
        CHK_board[0][j] = CHK_PIECE::CRED_P;
    }
    return true;
}



bool checkers::validAtkCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const{

    // Check base validities.
    if( !this->validBasicCheck( i, j, direction ) ){
        return false;
    }

    // Check attack validity through theoretical check.
    if( !this->theoAtkCheck( i, j, this->CHK_board[i][j], direction ) ){
        return false;
    }

    return true;

}


bool checkers::validMoveCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const{

    // Check base validities.
    if( !this->validBasicCheck( i, j, direction ) ){
        return false;
    }

    // Check move validity through theoretical check.
    if( !this->theoMoveCheck( i, j, this->CHK_board[i][j], direction ) ){
        return false;
    }

    return true;

}


bool checkers::validBasicCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const{

    // Bad coordinate.
    if( i >= BOARD_SIZE || j >= BOARD_SIZE ){
        cerr << "Coordinate exceeds board limits." << endl;
        return false;
    }

    // Obtain current piece type.
    CHK_PIECE currPiece = CHK_board[i][j];

    // No piece at select coordinate.
    if( currPiece == CHK_PIECE::NO_P ){
        return false;
    }

    /*
    Turn vs piece color match validation.
    */
    if( currPiece == CHK_PIECE::BLK_P || currPiece == CHK_PIECE::CBLK_P ){
        // Piece is black but current turn belongs to red.
        if( getCurrTurn() == 1 ){
            return false;
        }
    }
    if( currPiece == CHK_PIECE::RED_P || currPiece == CHK_PIECE::CRED_P ){
        // Piece is red but current turn belongs to black.
        if( getCurrTurn() == 0 ){
            return false;
        }
    }

    return true;
    
}


bool checkers::theoAtkCheck( unsigned int i, unsigned int j, CHK_PIECE piece, CHK_DIREC direction ) const{

    if( piece == CHK_PIECE::NO_P ){
        return false;
    }

    // Move direction vs piece's capability check.
    switch( piece ){
        case CHK_PIECE::RED_P:
            if( direction == CHK_DIREC::DOWNLEFT || direction == CHK_DIREC::DOWNRIGHT ){
                return false;
            }
            break;
        case CHK_PIECE::BLK_P:
            if( direction == CHK_DIREC::UPLEFT || direction == CHK_DIREC::UPRIGHT ){
                return false;
            }
            break;
        default:
            break;
    }

    // Obtain the integer version of the coordinates.
    int i_int = i;
    int j_int = j;

    // The amount of movement following the moving direction.
    int di = 0;
    int dj = 0;

    // Determine expected coordinate shift.
    switch( direction ){
        case( CHK_DIREC::UPLEFT ):
            di = -2;    dj = -2;
            break;
        case( CHK_DIREC::UPRIGHT ):
            di = -2;    dj = +2;
            break;
        case( CHK_DIREC::DOWNLEFT ):
            di = +2;    dj = -2;
            break;
        case( CHK_DIREC::DOWNRIGHT ):
            di = +2;    dj = +2;
            break;
    }
    // Compute expected destination coordinates.
    int new_i = i_int + di;
    int new_j = j_int + dj;

    // Board limits violation check.
    if( new_i < 0 || new_i >= BOARD_SIZE ||
        new_j < 0 || new_j >= BOARD_SIZE ){
        return false;
    }

    // Attack movement landing square check.
    if( CHK_board[new_i][new_j] != CHK_PIECE::NO_P ){
        return false;
    }

    // Compute expected midpoint coordinates.
    int new_mid_i = i_int + di/2;
    int new_mid_j = j_int + dj/2;

    // Attack movement midpoint square check.
    if( getTurnID( piece ) == 1 ){
        // Midpoint square must have a black piece to jump on.
        if( CHK_board[new_mid_i][new_mid_j] != CHK_PIECE::BLK_P && 
            CHK_board[new_mid_i][new_mid_j] != CHK_PIECE::CBLK_P ){
            return false;
        }
    }else if( getTurnID( piece ) == 0 ){
        // Midpoint square must have a red piece to jump on.
        if( CHK_board[new_mid_i][new_mid_j] != CHK_PIECE::RED_P && 
            CHK_board[new_mid_i][new_mid_j] != CHK_PIECE::CRED_P ){
            return false;
        }
    }

    return true;

}

bool checkers::theoMoveCheck( unsigned int i, unsigned int j, CHK_PIECE piece, CHK_DIREC direction ) const{

    if( piece == CHK_PIECE::NO_P ){
        return false;
    }

    // Move direction vs piece's capability check.
    switch( piece ){
        case CHK_PIECE::RED_P:
            if( direction == CHK_DIREC::DOWNLEFT || direction == CHK_DIREC::DOWNRIGHT ){
                return false;
            }
            break;
        case CHK_PIECE::BLK_P:
            if( direction == CHK_DIREC::UPLEFT || direction == CHK_DIREC::UPRIGHT ){
                return false;
            }
            break;
        default:
            break;
    }

    // Obtain the integer version of the coordinates.
    int i_int = i;
    int j_int = j;

    // The amount of movement following the moving direction.
    int di = 0;
    int dj = 0;

    // Determine expected coordinate shift.
    switch( direction ){
        case( CHK_DIREC::UPLEFT ):
            di = -1;    dj = -1;
            break;
        case( CHK_DIREC::UPRIGHT ):
            di = -1;    dj = +1;
            break;
        case( CHK_DIREC::DOWNLEFT ):
            di = +1;    dj = -1;
            break;
        case( CHK_DIREC::DOWNRIGHT ):
            di = +1;    dj = +1;
            break;
    }
    // Compute expected destination coordinate.
    int new_i = i_int + di;
    int new_j = j_int + dj;

    // Board limits violation check.
    if( new_i < 0 || new_i >= BOARD_SIZE ||
        new_j < 0 || new_j >= BOARD_SIZE ){
        return false;
    }
    // Movement impediment check.
    if( CHK_board[new_i][new_j] != CHK_PIECE::NO_P ){
        return false;
    }

    return true;

}


vector<checkers::CHK_DIREC> checkers::theoAtkCheckAll( unsigned int i, unsigned int j, CHK_PIECE piece ) const{

    vector<CHK_DIREC> atkDirects;

    vector<CHK_DIREC> direcVec = { CHK_DIREC::UPLEFT, CHK_DIREC::UPRIGHT, CHK_DIREC::DOWNLEFT, CHK_DIREC::DOWNRIGHT };
    for( CHK_DIREC direc_i : direcVec ){
        if( theoAtkCheck( i, j, piece, direc_i ) ){
            atkDirects.push_back( direc_i );
        }
    }

    return atkDirects;

}

vector<checkers::CHK_DIREC> checkers::theoMoveCheckAll( unsigned int i, unsigned int j, CHK_PIECE piece ) const{

    vector<CHK_DIREC> moveDirects;

    vector<CHK_DIREC> direcVec = { CHK_DIREC::UPLEFT, CHK_DIREC::UPRIGHT, CHK_DIREC::DOWNLEFT, CHK_DIREC::DOWNRIGHT };
    for( CHK_DIREC direc_i : direcVec ){
        if( theoMoveCheck( i, j, piece, direc_i ) ){
            moveDirects.push_back( direc_i );
        }
    }

    return moveDirects;

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

int checkers::getCurrTurn() const{
    return turn_cnt % 2;
}

bool checkers::isBlackTurn() const{
    return ( turn_cnt % 2 == 0 );
}

int checkers::getTurnID( CHK_PIECE piece ) const{
    switch(piece){
        case( CHK_PIECE::NO_P ):
            return -1;
            break;
        case( CHK_PIECE::BLK_P ):
            return 0;
            break;
        case( CHK_PIECE::CBLK_P ):
            return 0;
            break;
        case( CHK_PIECE::RED_P ):
            return 1;
            break;
        case( CHK_PIECE::CRED_P ):
            return 1;
            break;
        default:
            return -1;
            break;
    }
}


void checkers::upd_game_state(){

    unsigned int red_cnt = 0;
    unsigned int cred_cnt = 0;
    unsigned int blk_cnt = 0;
    unsigned int cblk_cnt = 0;

    // Initialize turn ID.
    int turnID = -1;

    // Count the current number of each piece type.
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){

            switch( CHK_board[i][j] ){
                case CHK_PIECE::RED_P:
                    red_cnt++;
                    break;
                case CHK_PIECE::CRED_P:
                    cred_cnt++;
                    break;
                case CHK_PIECE::BLK_P:
                    blk_cnt++;
                    break;
                case CHK_PIECE::CBLK_P:
                    cblk_cnt++;
                    break;
                default:
                    break;
            }
            
        }
    }

    // Pieces counter update and draw condition update.
    bool noChange = true;
    noChange = noChange && ( pieceCounter.at(0) == red_cnt );
    pieceCounter.at(0) = red_cnt;
    noChange = noChange && ( pieceCounter.at(1) == blk_cnt );
    pieceCounter.at(1) = blk_cnt;
    noChange = noChange && ( pieceCounter.at(2) == cred_cnt );
    pieceCounter.at(2) = cred_cnt;
    noChange = noChange && ( pieceCounter.at(3) == cblk_cnt );
    pieceCounter.at(3) = cblk_cnt;
    if( noChange ){
        no_change_turn_cnt++;
    }else{
        no_change_turn_cnt = 0;
    }


    // Game State Update.
    if( ( blk_cnt + cblk_cnt ) == 0 && ( red_cnt + cred_cnt ) != 0 ){
        state = CHK_STATE::RWIN;
    }else if( ( blk_cnt + cblk_cnt ) != 0 && ( red_cnt + cred_cnt ) == 0 ){
        state = CHK_STATE::BWIN;
    }else if( no_change_turn_cnt >= DRAWTURNCOUNTMAX || 
        ( blk_cnt + cblk_cnt + red_cnt + cred_cnt ) == 0 ){
        state = CHK_STATE::DRAW;
    }else if( ( blk_cnt + cblk_cnt ) != 0 && ( red_cnt + cred_cnt ) != 0 ){
        state = CHK_STATE::ONGOING;
    }

}

void checkers::upd_atk_posb(){

    // Clear the previous list of possible attack points.
    B_atk_list.clear();
    R_atk_list.clear();
    
    /* 
    Initialize vector keeping track of all directions of possible attack
    at each piece investogated.
    */
    vector<CHK_DIREC> direcVec;

    // Check the special case when a piece is locking the game in an attack sequence.
    if( this->state == CHK_STATE::LOCKED ){

        // Obtain the target piece coordinate.
        int i = lock_tar.at(0);
        int j = lock_tar.at(1);

        // Obtain current piece.
        CHK_PIECE currPiece = CHK_board[i][j];

        // Check current piece's all possible direction of attack
        direcVec = theoAtkCheckAll( i, j, currPiece );
        // Check curr piece color.
        int currColor = getTurnID( currPiece );

        // Black
        if( currColor == 0 ){
            for( checkers::CHK_DIREC tmp_direct : direcVec ){
                B_atk_list.push_back( CHK_move( i, j, tmp_direct ) );
            }
        // Red
        }else if( currColor == 1 ){
            for( checkers::CHK_DIREC tmp_direct : direcVec ){
                R_atk_list.push_back( CHK_move( i, j, tmp_direct ) );
            }
        }else{
            cerr << "A checker piece of unrecognized color somehow got a possible attack." << endl;
            return;
        }

        return;

    }



        

    // Parse through the entire board.
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){

            // Obtain current piece.
            CHK_PIECE currPiece = CHK_board[i][j];
            // Skip if no piece at current coordinate.
            if( currPiece == CHK_PIECE::NO_P ){
                continue;
            }
            // Check curr piece color.
            int currColor = getTurnID( currPiece );
            // Check current piece's all possible direction of attack
            direcVec = theoAtkCheckAll( i, j, currPiece );
            // Add current coordinate as possible attack point in appropriate vector.
            if( direcVec.size() != 0 ){
                // Black
                if( currColor == 0 ){
                    for( checkers::CHK_DIREC tmp_direct : direcVec ){
                        B_atk_list.push_back( CHK_move( i, j, tmp_direct ) );
                    }
                // Red
                }else if( currColor == 1 ){
                    for( checkers::CHK_DIREC tmp_direct : direcVec ){
                        R_atk_list.push_back( CHK_move( i, j, tmp_direct ) );
                    }
                }else{
                    cerr << "A checker piece of unrecognized color somehow got a possible attack." << endl;
                    continue;
                }
            }

        }
    }

}


void checkers::upd_displ_posb(){
    
    // Clear the previous list of possible attack points.
    B_displ_list.clear();
    R_displ_list.clear();

    /* 
    Initialize vector keeping track of all directions of possible attack
    at each piece investogated.
    */
    vector<CHK_DIREC> direcVec;   

    // Parse through the entire board.
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){

            // Obtain current piece.
            CHK_PIECE currPiece = CHK_board[i][j];
            // Skip if no piece at current coordinate.
            if( currPiece == CHK_PIECE::NO_P ){
                continue;
            }
            // Check curr piece color.
            int currColor = getTurnID( currPiece );
            // Check current piece's all possible direction of displacement.
            direcVec = theoMoveCheckAll( i, j, currPiece );
            // Add current coordinate as possible move point in appropriate vector.
            if( direcVec.size() != 0 ){
                // Black
                if( currColor == 0 ){
                    for( checkers::CHK_DIREC tmp_direct : direcVec ){
                        B_displ_list.push_back( CHK_move( i, j, tmp_direct ) );
                    }
                // Red
                }else if( currColor == 1 ){
                    for( checkers::CHK_DIREC tmp_direct : direcVec ){
                        R_displ_list.push_back( CHK_move( i, j, tmp_direct ) );
                    }
                }else{
                    cerr << "A checker piece of unrecognized color somehow got a possible move." << endl;
                    continue;
                }
            }

        }
    }
}


void checkers::printBoard() const{

    cout << "  ";
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        cout << i << " ";
    }
    cout << endl;

    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){

        cout << i << " ";
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){

            switch( CHK_board[i][j] ){
                case CHK_PIECE::NO_P:
                    cout << "." << " ";
                    break;
                case CHK_PIECE::RED_P:
                    cout << "r" << " ";
                    break;
                case CHK_PIECE::BLK_P:
                    cout << "b" << " ";
                    break;
                case CHK_PIECE::CRED_P:
                    cout << "R" << " ";
                    break;
                case CHK_PIECE::CBLK_P:
                    cout << "B" << " ";
                    break;
                default:
                    break;
            };

        }
        cout << endl;
    }
    
    cout << "[Turn ID: " << this->getCurrTurn() << "], ";
    cout << "[Game state: " << this->get_CHK_STATE_Str(state) << "]" << endl;
    cout << endl;

}
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

void checkers::clearBoard(){
    // Clear the checker board.
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){
            CHK_board[i][j] = CHK_PIECE::NO_P;
        }
    }
}

bool checkers::insertPiece( unsigned int i, unsigned int j, checkers::CHK_PIECE newPiece ){

    // Bad coordinate.
    if( i >= BOARD_SIZE || j >= BOARD_SIZE ){
        cerr << "Coordinate exceeds board limits." << endl;
        return false;
    }

    CHK_board[i][j] = newPiece;

    return true;

}

void checkers::insertBoard( CHK_PIECE in_CHK_board[BOARD_SIZE][BOARD_SIZE] ){

    // Make a copy of the board.
    for( unsigned int i = 0; i < BOARD_SIZE; i++ ){
        for( unsigned int j = 0; j < BOARD_SIZE; j++ ){
            CHK_board[i][j] = in_CHK_board[i][j];
        }
    }

}

void checkers::resetBoard(){
    
    // Clear the board first.
    this->clearBoard();

    for( unsigned int i = 0; i < BOARD_SIZE/2 - 1; i++ ){
        for( unsigned int j = (unsigned int) remainder(i,2); j < BOARD_SIZE; j+=2 ){
            CHK_board[i][j] = CHK_PIECE::BLK_P;
            CHK_board[BOARD_SIZE - i - 1][BOARD_SIZE - j - 1] = CHK_PIECE::RED_P;
        }
    }

    turn_cnt = 0;
    state = CHK_STATE::ONGOING;

    // Clear the possible attack lists.
    R_atk_list.clear();
    B_atk_list.clear();
    R_displ_list.clear();
    B_displ_list.clear();

    // Clear the lock target.
    lock_tar.clear();

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      AI Related Functions
// ====================================================================== >>>>>

/*
Provide a numerical score to the current state of the game.
*/
int checkers::gameStateEval(){

    int stateValue = 0;

    // Update the game state before proceeding.
    this->upd_game_state();

    /*
    Values of pieces.
    TODO: eventually, you should put these values as constant static variables 
    for this class.
    */
    int RED_P_val = -5;
    int CRED_P_val = -20;
    int BLK_P_val = 5;
    int CBLK_P_val = 20;

    int RED_win_val = -1000;
    int BLK_win_val = 1000;
    int draw_val = 0;


    switch( this->state ){
        case CHK_STATE::BWIN:
            stateValue = BLK_win_val;
            break;
        case CHK_STATE::RWIN:
            stateValue = RED_win_val;
            break;
        case CHK_STATE::DRAW:
            stateValue = draw_val;
            break;
        case CHK_STATE::ONGOING:
        case CHK_STATE::LOCKED:
            stateValue += RED_P_val * pieceCounter.at(0);
            stateValue += BLK_P_val * pieceCounter.at(1);
            stateValue += CRED_P_val * pieceCounter.at(2);
            stateValue += CBLK_P_val * pieceCounter.at(3);
            break;

        default:
            cerr << "Unrecognized game state error. Abort." << endl;
    }

    return stateValue;

}



vector<checkers::CHK_move> checkers::get_valid_moves(){

    vector<checkers::CHK_move> valid_move_vect;
    
    switch( this->getCurrTurn() ){
    
    // Black turn
    case 0:

        if( B_atk_list.size() == 0 ){
            // Return list of possible displacements if no attack possible.
            this->upd_displ_posb();
            valid_move_vect = B_displ_list;
        }else{
            // Return list of possible attacks if even one attack is possible.
            valid_move_vect = B_atk_list;
        }
        break;

    // Red turn
    case 1:
        
        if( R_atk_list.size() == 0 ){
            // Return list of possible displacements if no attack possible.
            this->upd_displ_posb();
            valid_move_vect = R_displ_list;
        }else{
            // Return list of possible attacks if even one attack is possible.
            valid_move_vect = R_atk_list;
        }
        break;

    default:
        cerr << "Invalid turn ID." << endl;
        return valid_move_vect;

    };


    return valid_move_vect;

}


int checkers::minmax_debug( bool isMaximizing, int depth ){

    return minmax_debug_loop( isMaximizing, depth, depth );

}


int checkers::minmax_debug_loop( bool isMaximizing, int depth, int max_depth ){

    if( ( this->getCurrTurn() == 0 && !isMaximizing ) ||
    this->getCurrTurn() == 1 && isMaximizing ){
        cout << "Mismatch of minmax objective with the current turn order." << endl;
        return 0;
    }

    switch( this->state ){

        case CHK_STATE::BWIN:
        case CHK_STATE::RWIN:
        case CHK_STATE::DRAW:
            // When game is over, return value immediately.
            for( int i = 0 ; i < max_depth - depth; i++ ){
                cout << "  ";
            }
            cout << "Score: " << this->gameStateEval() << endl;
            return this->gameStateEval();
            break;
        case CHK_STATE::ONGOING:
        case CHK_STATE::LOCKED:
            // If we reached the maximum allowed depth, return value immediately.
            if( depth <= 0 ){
                for( int i = 0 ; i < max_depth - depth; i++ ){
                    cout << "  ";
                }
                cout << "Score: " << this->gameStateEval() << endl;
                return this->gameStateEval();
            }
            break;
        default:
            cout << "Unrecognized game state. Abort." << endl;
            return false;

    }


    int bestScore = 0;
    int currScore = 0;

    // Obtain the entire set of currently valid moves.
    vector <checkers::CHK_move> validMovesVect = this->get_valid_moves();

    if ( isMaximizing ) {

        bestScore = std::numeric_limits<int>::min();

        for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

            // Current valid move.
            checkers::CHK_move move_z = validMovesVect.at(z);
    
            // Make a copy of the current game.
            checkers newGame = *this;

            // In the game copy, make a play with the next available move.
            if( newGame.play( move_z.i, move_z.j, move_z.k ) ){
                // cout << "Played! " << newGame.getCurrTurn() << endl;
            }else{
                // cout << "Failed to play! " << newGame.getCurrTurn() << endl;
            }
            
            for( int i = 0 ; i < max_depth - depth; i++ ){
                cout << "  ";
            }
            cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ") MAX" << endl;

            // Perform next layer minmax.
            if( newGame.getCurrTurn() == 0 ){
                currScore = newGame.minmax_debug_loop( true, depth - 1, max_depth );
            }else if( newGame.getCurrTurn() == 1 ){
                currScore = newGame.minmax_debug_loop( false, depth - 1, max_depth );
            }

            for( int i = 0 ; i < max_depth - depth; i++ ){
                cout << "  ";
            }
            cout << "MAX: currScore = " << currScore << ", " <<
                "bestScore = " << bestScore << endl;

            // Update the highest score up to now.
            bestScore = std::max( bestScore, currScore );

        }

    }else{

        bestScore = std::numeric_limits<int>::max();

        for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

            // Current valid move.
            checkers::CHK_move move_z = validMovesVect.at(z);
    
            // Make a copy of the current game.
            checkers newGame = *this;

            // In the game copy, make a play with the next available move.
            newGame.play( move_z.i, move_z.j, move_z.k );

            for( int i = 0 ; i < max_depth - depth; i++ ){
                cout << "  ";
            }
            cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ") MIN" << endl;

            // Perform next layer minmax.
            if( newGame.getCurrTurn() == 0 ){
                currScore = newGame.minmax_debug_loop( true, depth - 1, max_depth );
            }else if( newGame.getCurrTurn() == 1 ){
                currScore = newGame.minmax_debug_loop( false, depth - 1, max_depth );
            }

            for( int i = 0 ; i < max_depth - depth; i++ ){
                cout << "  ";
            }
            cout << "MIN: CS = " << currScore << ", " <<
                "BS = " << bestScore << endl;

            // Update the highest score up to now.
            bestScore = std::min( bestScore, currScore );
            
        }

    }

    return bestScore;

}



int checkers::minmax( bool isMaximizing, int depth ){

    if( ( this->getCurrTurn() == 0 && !isMaximizing ) ||
    this->getCurrTurn() == 1 && isMaximizing ){
        cout << "Mismatch of minmax objective with the current turn order." << endl;
        return 0;
    }

    switch( this->state ){

        case CHK_STATE::BWIN:
        case CHK_STATE::RWIN:
        case CHK_STATE::DRAW:
            // When game is over, return value immediately.
            return this->gameStateEval();
            break;
        case CHK_STATE::ONGOING:
        case CHK_STATE::LOCKED:
            // If we reached the maximum allowed depth, return value immediately.
            if( depth <= 0 ){
                return this->gameStateEval();
            }
            break;
        default:
            cout << "Unrecognized game state. Abort." << endl;
            return false;

    }


    int bestScore = 0;
    int currScore = 0;

    // Obtain the entire set of currently valid moves.
    vector <checkers::CHK_move> validMovesVect = this->get_valid_moves();

    if ( isMaximizing ) {

        bestScore = std::numeric_limits<int>::min();

        for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

            // Current valid move.
            checkers::CHK_move move_z = validMovesVect.at(z);
    
            // Make a copy of the current game.
            checkers newGame = *this;

            // In the game copy, make a play with the next available move.
            if( newGame.play( move_z.i, move_z.j, move_z.k ) ){

            }else{

            }
            

            // Perform next layer minmax.
            if( newGame.getCurrTurn() == 0 ){
                currScore = newGame.minmax( true, depth - 1 );
            }else if( newGame.getCurrTurn() == 1 ){
                currScore = newGame.minmax( false, depth - 1 );
            }

            // Update the highest score up to now.
            bestScore = std::max( bestScore, currScore );

        }

    }else{

        bestScore = std::numeric_limits<int>::max();

        for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

            // Current valid move.
            checkers::CHK_move move_z = validMovesVect.at(z);
    
            // Make a copy of the current game.
            checkers newGame = *this;

            // In the game copy, make a play with the next available move.
            newGame.play( move_z.i, move_z.j, move_z.k );


            // Perform next layer minmax.
            if( newGame.getCurrTurn() == 0 ){
                currScore = newGame.minmax( true, depth - 1 );
            }else if( newGame.getCurrTurn() == 1 ){
                currScore = newGame.minmax( false, depth - 1 );
            }


            // Update the highest score up to now.
            bestScore = std::min( bestScore, currScore );
            
        }

    }

    return bestScore;

}

checkers::CHK_move checkers::bestMove( ){

    return bestMove( this->minmax_depth );

}

checkers::CHK_move checkers::bestMove( int depth ){

    // Initialize the best move coordindate.
    CHK_move optimMove = CHK_move( UINT_MAX, UINT_MAX, CHK_DIREC::NO_D );

    if( this->state == CHK_STATE::BWIN || this->state == CHK_STATE::RWIN || 
        this->state == CHK_STATE::DRAW ){
        // Return impossible coordinate if the game is already over or not active.
        return optimMove;
    }

    // Determine the turn.
    bool is_BLK_init_turn = this->isBlackTurn();

    // Initialize score recording variables.
    int bestScore = 0;
    int score_z = 0;

    // Obtain the current best score.
    if( is_BLK_init_turn ){
        bestScore = this->minmax( true, depth );
        // bestScore = this->minmax_debug( true, depth );
    }else{
        bestScore = this->minmax( false, depth );
        // bestScore = this->minmax_debug( false, depth );
    }

    // Obtain the entire set of currently valid moves.
    vector <checkers::CHK_move> validMovesVect = this->get_valid_moves();
    
    for( unsigned int z = 0; z < validMovesVect.size(); z++ ){

        // Current valid move.
        checkers::CHK_move move_z = validMovesVect.at(z);
    
        // Make a copy of the current game.
        checkers newGame = *this;

        // Perform the current play.
        newGame.play( move_z.i, move_z.j, move_z.k );

        // Perform next layer minmax.
        if( newGame.isBlackTurn() ){
            score_z = newGame.minmax( true, depth - 1 );
        }else{
            score_z = newGame.minmax( false, depth - 1 );
        }

        if( is_BLK_init_turn ){
            if( score_z >= bestScore ){
                
                optimMove = move_z;
                bestScore = score_z;

            }
        }else{
            if( score_z <= bestScore ){

                optimMove = move_z;
                bestScore = score_z;
                
            }
        }
    }

    return optimMove;

}



checkers::CHK_move checkers::AI_play(){

    // Return empty vector if no AI play enabled.
    if( !( this->vsAI ) ){
        return CHK_move( INT_MAX, INT_MAX, CHK_DIREC::NO_D );
    }


    // Let AI perform the next move.
    checkers::CHK_move AI_move = this->bestMove();

    // Perform the play determined as the current best by the AI.
    bool AIPlayRes = play( AI_move.i, AI_move.j, AI_move.k );

    if( AIPlayRes ){
        return AI_move;
    }else{
        return CHK_move( INT_MAX, INT_MAX, CHK_DIREC::NO_D );
    }

}

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Variables Access Functions
// ====================================================================== >>>>>

vector<checkers::CHK_move> checkers::getR_atk_list() const
    {return R_atk_list;}
vector<checkers::CHK_move> checkers::getB_atk_list() const
    {return B_atk_list;}
vector<checkers::CHK_move> checkers::getR_displ_list() const
    {return R_displ_list;}
vector<checkers::CHK_move> checkers::getB_displ_list() const
    {return B_displ_list;}

unsigned int checkers::getTurn_cnt() const
    {return this->turn_cnt;}
void checkers::setTurn_cnt( unsigned int turn_cnt )
    {this->turn_cnt = turn_cnt;}

int checkers::getMinmax_depth() const
    {return this->minmax_depth;}
void checkers::setMinmax_depth( int in_minmax_depth )
    {this->minmax_depth = in_minmax_depth;}

void checkers::enabledAI()
    { this->vsAI = true; }
void checkers::disableAI()
    { this->vsAI = false; }
void checkers::toggleAI()
    { this->vsAI = !( this->vsAI ); }
bool checkers::is_vsAI() const
    { return this->vsAI; }

// ====================================================================== <<<<<





// DONE: update the chain attack functionality.

// DONE: update the crowning functionality.

// DONE: somehow implement the draw state management.