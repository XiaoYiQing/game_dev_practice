#ifndef CHECKERS_H
#define CHECKERS_H

#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <stack>
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
//      Specialized Nested Class for Moves
// ====================================================================== >>>>>

    /*
    Simplest class for identifying a move, with minimal information.
    Starting location + direction.
    Whether it is an attack or just a displacement can be discerned by the board situation. 
    Whether this move is legal for the target piece is also checked on the board.
    */
    class CHK_move{

        public:
        
        CHK_move( unsigned int i, unsigned int j, CHK_DIREC k );

        unsigned int i;
        unsigned int j;
        CHK_DIREC k;

    };

    /*
    Define an impossible move serving as reference for indicating failure to
    attain a usable move.
    */
    static const CHK_move IMPOS_MOVE;

// ====================================================================== >>>>>

    

   

// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>
    checkers();
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
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

    // Return true if current game instance is at black's turn.
    bool isBlackTurn() const;

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
    Update the list of possible displacements.
    */
    void upd_displ_posb();

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
    Does not update game state or turn count.
    */
    bool insertPiece( unsigned int i, unsigned int j, CHK_PIECE newPiece );

    /*
    Directly insert the desired board set to this game object.
    The given board is copied by the class' board.
    Does not update game state or turn count.
    */
    void insertBoard( CHK_PIECE in_CHK_board[BOARD_SIZE][BOARD_SIZE] );

    /*
    Reset the board to the state of a fresh new game.
    This function serves as a game instance reset, though some class variables
    may not be affected.
    */
    void resetBoard();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      AI Related Functions
// ====================================================================== >>>>>

    /*
    Provide a numerical score to the current state of the game.
    Calling this function automatically calls the upd_game_state();
    */
    int gameStateEval();

    /*
    Obtain all currently valid moves.
    Turn is based on the current checkers instance's turn count.
    NOTE: Attacks take precedence over displacement, so if a single piece
    can attack, no other piece of the same color can be displaced.
    */
    vector<CHK_move> get_valid_moves();

    /*
    minmax function for helping the game A.I. to make the best possible move.
    This function does not determine the best move, but helps in attributing numerical
    values to each possible move up to a specified depth/turn into the future.
    NOTE: maximizing when black, minimizing when red.
    */
    int minmax( bool isMaximizing, int depth );

    /*
    minmax function for helping the game A.I. to make the best possible move.
    This function does not determine the best move, but helps in attributing numerical
    values to each possible move up to a specified depth/turn into the future.
    NOTE: maximizing when black, minimizing when red.
    NOTE: debug version prints every step on the console.
    */
    int minmax_debug( bool isMaximizing, int depth );
    /*
    The actual recursive portion of the debug minmax function.
    */
    int minmax_debug_loop( bool isMaximizing, int depth, int max_depth );

    /*
    The minmax function with AB-pruning.
    The process and results are basically the same as the standard minmax function,
    but branches of the search may be skipped depending on best results found in
    the immediate higher node of the search tree.
    */
    int minmaxAB( bool isMaximizing, int depth );
    /*
    The actual recursive portion of the minmax AB-pruning algorithm.
    */
    int minmaxAB_loop( bool isMaximizing, int alpha, int beta, int depth );

    /*
    Minmax with AP-pruning, with additional specified set of moves to perform the 
    minmax process on.
    This function is meant to be used with its own thread.
    */
    static int minmaxAB_split( checkers& tarGame, bool isMaximizing, int depth );

    /*
    The starting point of the split.
    */
    static int minmaxAB_split_init( checkers& tarGame, bool isMaximizing, int depth );



    /*
    Determine the best move to make in the current turn at the current board state.
    */
    CHK_move bestMove();
    /*
    Determine the best move to make in the current turn at the current board state
    using the minmax algorithm.
    NOTE: depth directly specified.
    */
    CHK_move bestMove( int depth );

    /*
    Determine the best move to make in the current turn at the current board state
    using the minmax AB-pruning algorithm.
    */
    CHK_move bestMove_ABP();
    /*
    Determine the best move to make in the current turn at the current board state
    using the minmax AB-pruning algorithm.
    NOTE: depth directly specified.
    */
    CHK_move bestMove_ABP( int depth );


    /*
    Let the AI perform the next move.
    If move fails, a move object with no direction (CHK_DIREC::NO_D) is returned.
    */
    static CHK_move AI_play( checkers& tarGame );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Variables Access Functions
// ====================================================================== >>>>>

    vector<CHK_move> getR_atk_list() const;
    vector<CHK_move> getB_atk_list() const;

    vector<CHK_move> getR_displ_list() const;
    vector<CHK_move> getB_displ_list() const;

    unsigned int getTurn_cnt() const;
    void setTurn_cnt( unsigned int );

    int getMinmax_depth() const;
    void setMinmax_depth( int in_minmax_depth );

    void enabledAI();
    void disableAI();
    void toggle_AI();
    bool is_AI_enabled() const;

    // Turn off the AI process flag. This will turn off the thread running the AI
    // at the earliest convenience.
    void disableAI_proc();
    // Turn off the AI process flag. 
    void enableAI_proc();


    bool is_AI_first() const;
    void set_AI_first();
    void set_AI_not_first();
    void toggle_AI_first();

// ====================================================================== <<<<<
    

protected:


// ====================================================================== >>>>>
//      AI Related Functions (Protected)
// ====================================================================== >>>>>

    /*
    The depth of the minmax function used by this game instance.
    */
    int minmax_depth = 6;

    /*
    Flag indicating if this game allows use of AI.
    */
    bool vsAI = true;
    
    /*
    Flag indicating if the AI plays first over a versus AI game.
    */
    bool AI_first = false;

    /*
    Flag used for separate thread running the AI process.
    This flag is normally turned on when the AI process starts to run.
    If this flag is turned off during an AI process run, the AI process 
    is to stop at the earliest convenience.
    */
    bool AI_proc_flag;

    /*
    Mutex for the purpose of synchronizing use of the shared list.
    */
    static std::mutex mtx_shared_move_list;

    /*
    This is a shared list of moves.
    This list serves as a shared pool of moves to be dipped by multiple threads
    at the same time.
    As such, you need to use mutex to ensure synchronization. 
    */
    static stack<checkers::CHK_move> shared_move_stk;

// ====================================================================== <<<<<

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
    vector<CHK_move> R_atk_list;
    // The list of black pieces that can attack.
    vector<CHK_move> B_atk_list;

    // The list of red piece's displacement possibilities.
    vector<CHK_move> R_displ_list;
    // The list of black piece's displacement possibilities.
    vector<CHK_move> B_displ_list;

    

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

    /*
    Check if the board state value evaluation works.
    */
    void checkers_test5();

    /*
    Check the valid moves function.
    */
    void checkers_test6();

    /*
    Check the minmax function.
    */
    void checkers_test7();

    /*
    Check the bestMove function.
    */
    void checkers_test8( int tar_scenario_id = 0 );

    /*
    Check the AI_play() function.
    */
    void checkers_test9( int tar_scenario_id = 0 );

    /*
    Check multi-thread minmax AB-pruning function.
    */
    void checkers_test10( int tar_scenario_id = 0 );

}

#endif  // CHECKERS