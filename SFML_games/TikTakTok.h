#ifndef TIKTAKTOK_H
#define TIKTAKTOK_H

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

namespace gameEngine{

/*
Game engine for the game of Tik-Tak-Toc (TTT).
*/
class TikTakTok{

public:

    TikTakTok();

    /* 
    Play at the specified square coordinate.
    A play can be made only when the game is unfinished.
    A play can only be made on a square that has not been played before.
    Return value meaning: [0 = failed], [1 = O played], [2 = X played].
    */
    unsigned int play( unsigned int row_id, unsigned int col_id );

    /*
    Update the state of the game: [0 = unfinished], [1 = O won], [2 = X won], [3 = draw].
    */
    void updState();

    /*
    Obtain the current state of the game.
    Possible states: [0 = unfinished], [1 = O won], [2 = X won], [3 = draw].
    */
    unsigned int getState() const;

    /*
    Reset the state of the game to a fresh start.
    */
    void reset();

    /*
    Print to terminal the state of the board.
    This is a debug tool, and may be deleted.
    */
    void printBoard() const;

    unsigned int getTTT_press_cnt() const;

protected:

    // The value of the unpressed square on the TTT board.
    static const unsigned int n_val = 0;
    /* 
    The value of the O square on the TTT board.
    WARNING: MUST RESPECT THE DIFFERENCE [3*O_val < X_val] OR [O_val > 3*X_val]
    */
    static const unsigned int O_val = 1;
    /* 
    The value of the X square on the TTT board.
    WARNING: MUST RESPECT THE DIFFERENCE [3*O_val < X_val] OR [O_val > 3*X_val]
    */
    static const unsigned int X_val = 10;

    // The state of the game: [0 = unfinished], [1 = O won], [2 = X won], [3 = draw].
    unsigned int state;

    // The number of times a square has been pressed.
    unsigned int TTT_press_cnt;

    // The numerical table representing the TTT playing board.
    unsigned int TTT_board[3][3] = {n_val, n_val, n_val, n_val, n_val, n_val, n_val, n_val, n_val};

    /*
    Check the current state of the game.
    The answers: [0 = unfinished], [1 = O won], [2 = X won], [3 = draw].
    */
    unsigned int checkState();

};

}


namespace tests{

    void TikTakTok_test1();

}


#endif  // TIKTAKTOK_H