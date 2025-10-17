#ifndef CHESS_H
#define CHESS_H



#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <mutex>
#include <stack>
#include <string>
#include <vector>


using namespace std;



namespace gameEngine{

class chess{

public:

    // The dimensions of the chess board.
    static const unsigned int BOARDWIDTH = 8;
    static const unsigned int BOARDHEIGHT = 8;

    // Define the maximum number of consecutive moves without a pawn being moved
    // or a piece been captured.
    static const unsigned int DRAWMOVECOUNTMAX = 50;


// ====================================================================== >>>>>
//      Class Enum "CHK_PIECE" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the possible pieces placed on the board.
     */
    enum class CHK_PIECE{ NO_P, RED_P, BLK_P, CRED_P, CBLK_P };

    // The number of enum entries in the enum "CHK_PIECE" (Uses magic enum).
    const static int CHK_PIECE_Count = (int) magic_enum::enum_count<CHK_PIECE>();

    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHK_PIECE The target CHK_PIECE enum.
     * @return The string representation of the target CHK_PIECE enum.
     */
    static string get_CHK_PIECE_Str( CHK_PIECE tar_CHK_PIECE );
    /**
     * Obtain the CHK_PIECE enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHK_PIECE enum.
     * @return The matching CHK_PIECE enum to the target index, if it exists.
     */
    static CHK_PIECE get_CHK_PIECE_AtIdx( int idx );

// ====================================================================== <<<<<

protected:


private:


};


};


#endif CHESS_H