#include "TikTakTok.h"



using namespace gameEngine;


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

TikTakTok::TikTakTok(){
    
    state = 0;
    
    TTT_press_cnt = 0;

}

// ====================================================================== <<<<<


unsigned int TikTakTok::checkState(){

    unsigned int rowSum[3] = { 0, 0, 0 };
    unsigned int colSum[3] = { 0, 0, 0 };
    unsigned int diagSum[2] = { 0, 0 };

    // Numerical tally.
    for( unsigned int i = 0; i < 3; i++ ){
        rowSum[0] += TTT_board[0][i];
        rowSum[1] += TTT_board[1][i];
        rowSum[2] += TTT_board[2][i];

        colSum[0] += TTT_board[i][0];
        colSum[1] += TTT_board[i][1];
        colSum[2] += TTT_board[i][2];
        
        diagSum[0] += TTT_board[i][i];
        diagSum[1] += TTT_board[i][2-i];
    }

    unsigned int O_win_val = 3*O_val;
    unsigned int X_win_val = 3*X_val;

    // Win case evaluation.
    for( unsigned int i = 0; i < 2; i++ ){
        if( rowSum[i] == O_win_val || colSum[i] == O_win_val || diagSum[i] == O_win_val ){
            return 1;
        }
        if( rowSum[i] == X_win_val || colSum[i] == X_win_val || diagSum[i] == X_win_val ){
            return 2;
        }
    }
    if( rowSum[2] == O_win_val || colSum[2] == O_win_val ){
        return 1;
    }
    if( rowSum[2] == X_win_val || colSum[2] == X_win_val ){
        return 2;
    }

    // Draw case evaluation.
    if( rowSum[0] + rowSum[1] + rowSum[2] > 4*( O_val + X_val ) ){
        return 3;
    }

    return 0;

}





// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

unsigned int TikTakTok::play( unsigned int row_id, unsigned int col_id ){

    // Only an empty square can be played. A play can be made only before game is finished.
    if( state == 0 && TTT_board[row_id][col_id] == TikTakTok::n_val ){

        unsigned int myans = 0;
        // Play O or X depending on current turn number.
        if( remainder( TTT_press_cnt, 2 ) ){
            TTT_board[row_id][col_id] = TikTakTok::X_val;
            myans = 2;
        }else{
            TTT_board[row_id][col_id] = TikTakTok::O_val;
            myans = 1;
        }
        // Press count increment.
        TTT_press_cnt++;
        // Game state update.
        this->updState();

        return myans;
        
    }else{
        return 0;
    }

}

void TikTakTok::updState(){
    this->state = checkState();
    return;
}

unsigned int TikTakTok::getState() const{
    return this->state;
}

void TikTakTok::reset(){

    // Reset the board values.
    for( unsigned int i = 0; i < 3; i++ ){
    for( unsigned int j = 0; j < 3; j++ ){
        TTT_board[i][j] = 0;
    }
    }

    // Reset the game state.
    state = 0;
    // Reset the press count.
    TTT_press_cnt = 0;

}



void TikTakTok::printBoard() const{

    for( unsigned int i = 0; i < 3; i++ ){
        for( unsigned int j = 0; j < 3; j++ ){
            if( TTT_board[i][j] == O_val ){
                cout << "O" << " ";
            }else if( TTT_board[i][j] == X_val ){
                cout << "X" << " ";
            }else{
                cout << "." << " ";
            }
        }
        cout << endl;
    }
    string stateMsg = "Game: ";
    switch( state ){
        case 0:
            stateMsg += "ongoing.";
            break;
        case 1:
            stateMsg += "O won!";
            break;
        case 2:
            stateMsg += "X won!";
            break;
        case 3:
            stateMsg += "draw.";
            break;
    }
    cout << stateMsg << endl;

}


int TikTakTok::minmax( bool isMaximizing ){

    // Return the end game cases;
    switch( this->state ){
    case 1:     // O wins
        return 10;
        break;
    case 2:     // X wins
        return -10;
        break;
    case 3:     // Draw
        // No point for game draw.
        return 0;
        break;
    }

    int bestScore = 0;
    int currScore = 0;
    if ( isMaximizing ) {

        bestScore = std::numeric_limits<int>::min();

        for( unsigned int i = 0; i < 3; i++ ){
            for( unsigned int j = 0; j < 3; j++ ){

                if( TTT_board[i][j] == n_val ){
                    TTT_board[i][j] = O_val;   TTT_press_cnt++;
                    this->updState();
                    // Recursive call to the next iteration.
                    currScore = this->minmax( false );
                    // Revert theoretical move.
                    TTT_board[i][j] = n_val;   TTT_press_cnt--;
                    // Update the highest score up to now.
                    bestScore = std::max( bestScore, currScore );
                }

            }
        }

        this->updState();
        return bestScore;

    }else{

        bestScore = std::numeric_limits<int>::max();

        for( unsigned int i = 0; i < 3; i++ ){
            for( unsigned int j = 0; j < 3; j++ ){

                if( TTT_board[i][j] == n_val ){
                    TTT_board[i][j] = X_val;   TTT_press_cnt++;
                    this->updState();
                    // Recursive call to the next iteration.
                    currScore = this->minmax( true );
                    // Revert theoretical move.
                    TTT_board[i][j] = n_val;   TTT_press_cnt--;
                    // Update the lowest score up to now.
                    bestScore = std::min( bestScore, currScore );
                }

            }
        }

        this->updState();
        return bestScore;

    }

}

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Access Functions
// ====================================================================== >>>>>

unsigned int TikTakTok::getTTT_press_cnt() const{
    return TTT_press_cnt;
}

bool TikTakTok::setBoard( unsigned int in_TTT_board[3][3] ){
    
    bool success = true;

    unsigned int tmp_O_cnt = 0;
    unsigned int tmp_X_cnt = 0;

    // Check for illegal values on the board as well as count O and X.
    for( unsigned int i = 0; i < 3; i++ ){
        for( unsigned int j = 0; j < 3; j++ ){
            
            if( in_TTT_board[i][j] == n_val ){

            }else if( in_TTT_board[i][j] == O_val ){
                tmp_O_cnt++;
            }else if( in_TTT_board[i][j] == X_val ){
                tmp_X_cnt++;
            }else{
                cerr << "Invalid value in on the TTT board." << endl;
                return false;
            }

        }
    }

    // Check for O/X count consistency.
    if( tmp_O_cnt - tmp_X_cnt == 1 || tmp_O_cnt == tmp_X_cnt ){
        TTT_press_cnt = tmp_O_cnt + tmp_X_cnt;
    }else{
        cerr << "The number of O and X on the board is impossible given O starts playing first." << endl;
        return false;
    }
    
    // Fill the current game with the given board configuration.
    for( unsigned int i = 0; i < 3; i++ ){
        for( unsigned int j = 0; j < 3; j++ ){
            this->TTT_board[i][j] = in_TTT_board[i][j];
        }
    }

    // Update the game state.
    this->updState();

    return success;

}

// ====================================================================== <<<<<



void tests::TikTakTok_test1(){

    gameEngine::TikTakTok myGame;
    myGame.printBoard();
    myGame.play( 0, 0 );    myGame.printBoard();
    myGame.play( 1, 1 );    myGame.printBoard();
    myGame.play( 0, 2 );    myGame.printBoard();
    myGame.play( 2, 0 );    myGame.printBoard();
    myGame.play( 0, 1 );    myGame.printBoard();
    myGame.play( 2, 2 );    myGame.printBoard();
    myGame.reset();         myGame.printBoard();

}

void tests::TikTakTok_test2(){
    
    gameEngine::TikTakTok myGame;

    unsigned int tmp_TTT_board[3][3] = {
        TikTakTok::X_val, TikTakTok::n_val, TikTakTok::n_val, 
        TikTakTok::n_val, TikTakTok::n_val, TikTakTok::n_val, 
        TikTakTok::n_val, TikTakTok::n_val, TikTakTok::O_val
    };

    myGame.setBoard( tmp_TTT_board );
    myGame.printBoard();

    myGame.play( 1, 1 );    myGame.printBoard();
    

}


void tests::TikTakTok_test3(){

    gameEngine::TikTakTok myGame;

    unsigned int tmp_TTT_board_A[3][3] = {
        TikTakTok::n_val, TikTakTok::n_val, TikTakTok::X_val, 
        TikTakTok::n_val, TikTakTok::X_val, TikTakTok::n_val, 
        TikTakTok::n_val, TikTakTok::O_val, TikTakTok::O_val
    };

    myGame.setBoard( tmp_TTT_board_A );
    myGame.printBoard();

    bool is_O_turn = remainder( myGame.getTTT_press_cnt(), 2 ) == 0;
    int score = myGame.minmax( true );
    cout << "When set to maxing, score = " << score << endl;
    score = myGame.minmax( false );
    cout << "When set to minimizing, score = " << score << endl;


    unsigned int tmp_TTT_board_B[3][3] = {
        TikTakTok::n_val, TikTakTok::n_val, TikTakTok::X_val, 
        TikTakTok::n_val, TikTakTok::n_val, TikTakTok::n_val, 
        TikTakTok::n_val, TikTakTok::O_val, TikTakTok::O_val
    };

}