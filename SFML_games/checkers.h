#ifndef CHECKERS_H
#define CHECKERS_H

#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <string>
#include <vector>


using namespace std;


namespace gameEngine{

class checkers{


/*
Win/Lost conditions:
> Opponent/you lost all his/her pieces.
> Opponent/you cannot perform any move.
Draw conditions:
> When neither side can force a victory and repetitive play is recorded, draw.
*/

public:

    /*
    The size of the board.
    */
    static const unsigned int BOARD_SIZE = 8;
    static const unsigned int BOARDWIDTH = 8;
    static const unsigned int BOARDHEIGHT = 8;

    // Define the maximum number of turns with no capture or promotion before a draw is declared.
    static const unsigned int DRAWTURNCOUNTMAX = 40;
    
// ====================================================================== >>>>>
//      Class Enum "CHK_PIECE" Help Functions
// ====================================================================== >>>>>
    /*
    Enum representing the possible pieces placed on the board.
    */
    enum class CHK_PIECE{ NO_P, RED_P, BLK_P, CRED_P, CBLK_P };

    // The number of enum entries in the enum "CHK_PIECE" (Uses magic enum).
    const static int CHK_PIECE_Count = (int) magic_enum::enum_count<CHK_PIECE>();

    // Obtain the string of the target enum case (Uses magic enum).
    static string get_CHK_PIECE_Str( CHK_PIECE tar_CHK_PIECE );
    // Obtain the enum matching the enum integer index.
    static CHK_PIECE get_CHK_PIECE_AtIdx( int idx );
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHK_DIREC" Help Functions
// ====================================================================== >>>>>
    /*
    Enum representing the directions in which pieces can attack or move.
    */
    enum class CHK_DIREC{ NO_D, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

    // The number of enum entries in the enum "CHK_DIREC" (Uses magic enum).
    const static int CHK_DIREC_Count = (int) magic_enum::enum_count<CHK_DIREC>();
    // Obtain the string of the target enum case (Uses magic enum).
    static string get_CHK_DIREC_Str( CHK_DIREC tar_CHK_DIREC );
    // Obtain the enum matching the enum integer index.
    static CHK_DIREC get_CHK_DIREC_AtIdx( int idx );
// ====================================================================== <<<<<

    
/*
Update the state of the game:
    > 0 = unfinished ---> game is still in progress.
    > 1 = locked -------> game is locked in an attack sequence by a certain piece.
    > 2 = Black won: ---> game has ended with black being victorious.
    > 3 = Red won: -----> game has ended with red being victorious.
    > 4 = Draw: --------> game has ended with no one victorious (20 turns with no capture or crowning).
*/
// ====================================================================== >>>>>
//      Class Enum "CHK_STATE" Help Functions
// ====================================================================== >>>>>
    /*
    Enum representing the states the game can be in.
    */
    enum class CHK_STATE{ ONGOING, LOCKED, BWIN, RWIN, DRAW };

    // The number of enum entries in the enum "CHK_STATE" (Uses magic enum).
    const static int CHK_STATE_Count = (int) magic_enum::enum_count<CHK_STATE>();
    // Obtain the string of the target enum case (Uses magic enum).
    static string get_CHK_STATE_Str( CHK_STATE tar_CHK_STATE );
    // Obtain the enum matching the enum integer index.
    static CHK_STATE get_CHK_STATE_AtIdx( int idx );
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>
    checkers();
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gampleplay Functions
// ====================================================================== >>>>>

    /*
    Perform a play using the piece located at coordinate [i,j].
    A play can be made under the following conditions:
    > The piece chosen must have the color matching the current turn color.
    > A move is valid. A valid move is defined following the rules:
        1- All possible attack moves take priority. A simple displacement move is invalid
            if there is even one other piece that can perform an attack.
        2- The attack move is possible if your piece face the enemy piece in the 
            direct next diagonal space and there is a free space behind the enemy 
            piece on this same diagonal line.
        3- The attack move does not end the turn if the piece end up on a square
            where another attack presents itself. In fact, it MUST continue attacking
            until the same piece can no longer attack.
        4- If an attacking piece has multiple avenue of attacks, it may choose which
            attack to perform.
        5- If a piece arrives on the last row (closest to the opponent), it must be crowned
            which gives it the ability to move and capture backward.
            If the piece was crowned whilst attacking, the attack MUST continue if possible 
            now that it can capture backward.
    */
    bool play( unsigned int i, unsigned int j, CHK_DIREC direction );

    /*
    Perform an attack using the piece at the target coordinate against the (supposed)
    piece at its immediate adjascent diagonal along the specified direction.
    Strictly performs the attack after checking attack is possible and nothing else.
    */
    vector<unsigned int> attack( unsigned int i, unsigned int j, CHK_DIREC direction );

    /*
    Perform a move using the piece at the target coordinate and displace it
    one diagonal unit in the specified direction.
    This function only ensures that a move is possible, but does not consider 
    if a move is legal (attacks normally take precedence over moves).
    Strickly performs the move after checking move is possible and nothing else.
    */
    vector<unsigned int> move( unsigned int i, unsigned int j, CHK_DIREC direction );

    /*
    Perform the crowning action on the black piece at specified column.
    */
    bool crownBlkPiece( unsigned int j );
    /*
    Perform the crowning action on the red piece at specified column.
    */
    bool crownRedPiece( unsigned int j );
    
    /*
    Checks if the target piece can attack in the desired direction.
    Beyond the base validities, a theoretical attack check is performed.
    */
    bool validAtkCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const;
    
    /*
    Checks if the target piece can move in the desired direction.
    Beyond the base validities, a theoretical move check is performed.
    */
    bool validMoveCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const;

    /*
    First set of checks on whether a piece can be played:
    > The coordinate is valid.
    > There is a piece at the coordinate.
    > The piece color matches the current turn order.
    */
    bool validBasicCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const;

    /*
    A theoretical attack check, assuming a piece of target color and rank initiates
    the attack at the desired position along the desired direction.
    What is checked:
    > The required attack direction matches the capability of the piece.
    > If the attack is still within the limits of the board.
    > If there is an enemy piece within the immediate next diagonal square along
        the specified path of attack.
    > If there is an empty square behind above said enemy piece allowing your piece
        to land after the attack.
    */
    bool theoAtkCheck( unsigned int i, unsigned int j, CHK_PIECE piece, CHK_DIREC direction ) const;

    /*
    A theoretical move check, assuming a piece of target color and rank initiates
    the move at the desired position along the desired direction.
    What is checked:
    > The required move direction matches the capability of the piece.
    > If the move is still within the limits of the board.
    > If the move is impeded by an existing piece.
    */
    bool theoMoveCheck( unsigned int i, unsigned int j, CHK_PIECE piece, CHK_DIREC direction ) const;

    /*
    A theoretical attack check on all directions, assuming a piece of target color 
    and rank initiates the attack at the desired position.
    */
    vector<CHK_DIREC> theoAtkCheckAll( unsigned int i, unsigned int j, CHK_PIECE piece ) const;

    /*
    A theoretical move check on all directions, assuming a piece of target color
    and rank initiates the move at the desired position.
    */
    vector<CHK_DIREC> theoMoveCheckAll( unsigned int i, unsigned int j, CHK_PIECE piece ) const;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

    /*
    Obtain the current turn of the game.
        [0 = black]
        [1 = red]
    */
    int getCurrTurn() const;

    /*
    Obtain the turn id of the target piece.
    [-1 = no piece]
    [0 = black]
    [1 = red]
    */
    int getTurnID( CHK_PIECE ) const;

    /*
    Update the state of the game:
        > 0 = unfinished ---> game is still in progress.
        > 1 = locked -------> game is locked in an attack sequence by a certain piece.
        > 2 = Black won: ---> game has ended with black being victorious.
        > 3 = Red won: -----> game has ended with red being victorious.
        > 4 = Draw: --------> game has ended with no one victorious (20 turns with no capture or crowning).
    */
    void upd_game_state();

    /*
    Update the list of possible attacking pieces.
    */
    void upd_atk_posb();

    /*
    Print to terminal the state of the board.
    This is a debug tool, and may be deleted.
    */
    void printBoard() const;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

    // Set all pieces of the board to "no piece" state.
    void clearBoard();

    /*
    Place a new piece at the target coordinate on the board.
    Overwrites existing piece by default.
    */
    bool insertPiece( unsigned int i, unsigned int j, CHK_PIECE newPiece );

    /*
    Reset the board to the state of a fresh new game.
    */
    void resetBoard();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Variables Access Functions
// ====================================================================== >>>>>

    vector<unsigned int> getB_atk_i_list() const;
    vector<unsigned int> getB_atk_j_list() const;
    vector<unsigned int> getR_atk_i_list() const;
    vector<unsigned int> getR_atk_j_list() const;

// ====================================================================== <<<<<
    
protected:


    // The number of times a play has been made. Black start at turn 0.
    unsigned int turn_cnt;

    // The number of consecutive turns where no piece has been taken or promoted.
    unsigned int no_change_turn_cnt;

    /*
    Integer vector holding the count of pieces currently on the board. The vector 
    has 4 entries, in the following order:
        0 - # of red pieces.
        1 - # of black pieces.
        2 - # of crowned red pieces.
        3 - # of crowed black pieces.
    NOTE: this counter vector only updates with the function "upd_game_state()".
    */
    vector<unsigned int> pieceCounter;

    // TODO: Please find a way to allocate memory premptively for this array.
    /*
    Numerical table representing the checker board.
    The board orientation works in the manner as follow:
        CHK_board[0][0] => black piece
        CHK_board[BOARD_SIZE-1][BOARD_SIZE-1] => red piece
    */
    CHK_PIECE CHK_board[BOARD_SIZE][BOARD_SIZE];

    // The list of red pieces that can attack.
    vector<unsigned int> R_atk_i_list;
    vector<unsigned int> R_atk_j_list;
    // The list of black pieces that can attack.
    vector<unsigned int> B_atk_i_list;
    vector<unsigned int> B_atk_j_list;


    // The state of the game.
    CHK_STATE state;

    /*
    The coordinate variable which keeps track of the location of the piece which
    is causing a lock through an attack sequence.
    */
    vector<unsigned int> lock_tar;

};

}

namespace tests{

    /*
    Simple scenario tests to see if the base functionalities of the game have
    been implemented: move validity check, attack validity check.
    */
    void checkers_test1();

    /*
    Check if the base game play functionality works.
    A sequence of moves is executed on a custom game scenario to see if the expected
    behaviors occur.
    */
    void checkers_test2();

    /*
    Check if the attack locking sequence functionality works.
    */
    void checkers_test3();

    /*
    Check if the crowning functionality works. Also checks if crowned pieces
    can move backward.
    */
    void checkers_test4();

}

#endif  // CHECKERS