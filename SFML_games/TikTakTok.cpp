#include "TikTakTok.h"



using namespace gameEngine;

TikTakTok::TikTakTok(){
    
    state = 0;
    
    TTT_press_cnt = 0;

}

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

void TikTakTok::updState(){
    this->state = checkState();
    return;
}

unsigned int TikTakTok::getState() const{
    return this->state;
}

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



unsigned int TikTakTok::getTTT_press_cnt() const{
    return TTT_press_cnt;
}



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
