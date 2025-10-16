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

/**
 * An implementation of the base checkers' game functionalities.
 * 
 * Win/Lost conditions:
 * - Opponent/you lost all his/her pieces.
 * - Opponent/you cannot perform any move.
 * 
 * Draw conditions:
 * - When neither side can force a victory and continuous unproductive plays is recorded, draw.
 */
class checkers{




public:

    // The size of the checker board.
    static const unsigned int BOARD_SIZE = 8;
    // the unified size variable above.
    static const unsigned int BOARDWIDTH = 8;
    static const unsigned int BOARDHEIGHT = 8;

    // Define the maximum number of turns with no capture or promotion before a draw is declared.
    static const unsigned int DRAWTURNCOUNTMAX = 40;
    

    


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


// ====================================================================== >>>>>
//      Class Enum "CHK_DIREC" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the directions in which pieces can attack or move.
     */
    enum class CHK_DIREC{ NO_D, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

    // The number of enum entries in the enum "CHK_DIREC" (Uses magic enum).
    const static int CHK_DIREC_Count = (int) magic_enum::enum_count<CHK_DIREC>();
    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHK_DIREC The target CHK_DIREC enum.
     * @return The string representation of the target CHK_DIREC enum.
     */
    static string get_CHK_DIREC_Str( CHK_DIREC tar_CHK_DIREC );
    /**
     * Obtain the CHK_DIREC enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHK_DIREC enum.
     * @return The matching CHK_DIREC enum to the target index, if it exists.
     */
    static CHK_DIREC get_CHK_DIREC_AtIdx( int idx );

// ====================================================================== <<<<<

    

// ====================================================================== >>>>>
//      Class Enum "CHK_STATE" Help Functions
// ====================================================================== >>>>>
/*
Update the state of the game:
    > 0 = unfinished ---> game is still in progress.
    > 1 = locked -------> game is locked in an attack sequence by a certain piece.
    > 2 = Black won: ---> game has ended with black being victorious.
    > 3 = Red won: -----> game has ended with red being victorious.
    > 4 = Draw: --------> game has ended with no one victorious (20 turns with no capture or crowning).
*/

    /**
     * Enum representing the states the game can be in.
     */
    enum class CHK_STATE{ ONGOING, LOCKED, BWIN, RWIN, DRAW };

    // The number of enum entries in the enum "CHK_STATE" (Uses magic enum).
    const static int CHK_STATE_Count = (int) magic_enum::enum_count<CHK_STATE>();
    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHK_STATE The target CHK_STATE enum.
     * @return The string representation of the target CHK_STATE enum.
     */
    static string get_CHK_STATE_Str( CHK_STATE tar_CHK_STATE );
    /**
     * Obtain the CHK_STATE enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHK_STATE enum.
     * @return The matching CHK_STATE enum to the target index, if it exists.
     */
    static CHK_STATE get_CHK_STATE_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHK_AI_OPT" Help Functions
// ====================================================================== >>>>>
/**
 * Options with AI selection:
 * - [0 = standard minmax]
 * - [1 = multi-threaded standard minmax]
 * - [2 = minmax with AB-pruning]
 * - [3 = multi-threaded minmax with AB-pruning]
 */

    /**
     * Enum representing the AI options being used.
     */
    enum class CHK_AI_OPT{ STD_MM, MT_MM, STD_AB_MM, MT_AB_MM };
    // The number of enum entries in the enum "CHK_AI_OPT" (Uses magic enum).
    const static int CHK_AI_OPT_Count = (int) magic_enum::enum_count<CHK_AI_OPT>();
    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHK_AI_OPT The target CHK_AI_OPT enum.
     * @return The string representation of the target CHK_AI_OPT enum.
     */
    static string get_CHK_AI_OPT_Str( CHK_AI_OPT tar_CHK_AI_OPT );
    /**
     * Obtain the CHK_AI_OPT enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHK_AI_OPT enum.
     * @return The matching CHK_AI_OPT enum to the target index, if it exists.
     */
    static CHK_AI_OPT get_CHK_AI_OPT_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Specialized Nested Class for Moves
// ====================================================================== >>>>>

    /*
    Simplest class for identifying a move, with minimal information.
    
    Whether it is an attack or just a displacement can be discerned by the board situation. 
    Whether this move is legal for the target piece is also checked on the board.
    */

    /**
     * Simplest class for identifying a move, with minimal information:
     * 
     * - Starting location + direction.
     * 
     * \note Whether it is an attack or just a displacement can be discerned by the board situation. 
     * \note Whether this move is legal for the target piece is also checked on the board.
     * 
     */
    class CHK_move{

        public:
        
        /**
         * Initialize a checkers' move with position (i,j) and direction k.
         * 
         * @param i The row index.
         * @param j The column index.
         * @param k The relative direction.
         */
        CHK_move( unsigned int i, unsigned int j, CHK_DIREC k );

        // Row index.
        unsigned int i;
        // Column index.
        unsigned int j;
        // Relative direction.
        CHK_DIREC k;

    };

    /**
     * Define an impossible move serving as reference for indicating failure to
     * attain a usable move.
     */
    static const CHK_move IMPOS_MOVE;

// ====================================================================== >>>>>

    

   

// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

    /**
     * Initialize a checkers game in a completely fresh state.
     */
    checkers();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

    /**
     * \brief Perform a play using the piece located at coordinate [i,j].
     * 
     * \param i Row of the target piece.
     * \param j Column of the target piece.
     * \param direction The direction for the piece to displace or attack towards.
     * \return Boolean indicating whether a play is successful.
     * 
     * A play can be made under the following conditions:
     * 
     * 1. All possible attack moves take priority. A simple displacement move is 
     *  invalid if there is even one other piece that can perform an attack. 
     * 
     * 2. The attack move is possible if your piece face the enemy piece in the 
     *  direct next diagonal space and there is a free space behind the enemy 
     *  piece on this same diagonal line.
     * 
     * 3. The attack move does not end the turn if the piece end up on a square 
     *  where another attack presents itself. In fact, it MUST continue attacking
     *  until the same piece can no longer attack.
     * 
     * 4. If an attacking piece has multiple avenue of attacks, it may choose which 
     *  attack to perform.
     * 
     * 5. If a piece arrives on the last row (closest to the opponent), it must be crowned 
     *  which gives it the ability to move and capture backward.
     *  If the piece was crowned whilst attacking, the attack MUST continue if possible 
     *  now that it can capture backward.
     */
    bool play( unsigned int i, unsigned int j, CHK_DIREC direction );

    /**
     * \brief Perform an attack using the piece at the target coordinate against the (supposed) 
     * piece at its immediate adjascent diagonal along the specified direction.
     * 
     * Strictly performs the attack after checking attack is possible and nothing else.
     * 
     * \param i Target attacking piece's row index.
     * \param j Target attacking piece's column index.
     * \param direction Target piece's attacking direction.
     * 
     * \return Coordinate of the target piece's final destination post-attack. 
     *  If attack failed, coordinate is empty.
     */
    vector<unsigned int> attack( unsigned int i, unsigned int j, CHK_DIREC direction );

    /**
     * \brief Perform a move using the piece at the target coordinate and displace it 
     * one diagonal unit in the specified direction.
     * 
     * Strickly performs the move after checking move is possible and nothing else.
     * 
     * \warning This function only ensures that a move is possible, but does not consider 
     * if a move is legal (attacks normally take precedence over moves).
     * 
     * \param i Target moving piece's row index.
     * \param j Target moving piece's column index.
     * \param direction Target piece's moving direction.
     * \return Coordinate of the target piece's final destination post-move. 
     *  If the move failed, coordinate is empty.
     */
    vector<unsigned int> move( unsigned int i, unsigned int j, CHK_DIREC direction );

    /**
     * \brief Perform the crowning action on the black piece at the specified column.
     * 
     * \param j Target column's index where a black piece promotion is performed.
     * \return Flag indicating whether a crowning was successfully performed.
     */
    bool crownBlkPiece( unsigned int j );
    /**
     * \brief Perform the crowning action on the red piece at the specified column.
     * 
     * \param j Target column's index where a red piece promotion is performed.
     * \return Flag indicating whether a crowning was successfully performed.
     */
    bool crownRedPiece( unsigned int j );
    
    /**
     * \brief Checks if the target piece can attack in the desired direction.
     * 
     * Beyond the base validities, a theoretical attack check is performed.
     * 
     * \param i Target attacking piece's row index.
     * \param j Target attacking piece's column index.
     * \param direction Target piece's attacking direction.
     * \return Flag indicating whether the specified attack is valid to perform.
     */
    bool validAtkCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const;
    
    /**
     * \brief Checks if the target piece can move in the desired direction.
     * 
     * Beyond the base validities, a theoretical move check is performed.
     * 
     * \param i Target moving piece's row index.
     * \param j Target moving piece's column index.
     * \param direction Target piece's move direction.
     * \return Flag indicating whether the specified move is valid to perform.
     */
    bool validMoveCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const;

    /**
     * \brief First set of checks on whether a piece can be played.
     * 
     * The conditions are:
     * 
     * - The coordinate is valid.
     * 
     * - There is a piece at the coordinate.
     * 
     * - The piece color matches the current turn order.
     * 
     * \param i Target piece's row index.
     * \param j Target piece's column index.
     * \param direction Target piece's action direction.
     * \return Flag indicating whether the piece meets minimum requirements to perform an action.
     */
    bool validBasicCheck( unsigned int i, unsigned int j, CHK_DIREC direction ) const;

    /**
     * \brief A theoretical attack check, assuming a piece of target color and rank initiates
     * the attack at the desired position along the desired direction.
     * 
     * The conditions checked are:
     * 
     * - The required attack direction matches the capability of the piece.
     * 
     * - If the attack is still within the limits of the board.
     * 
     * - If there is an enemy piece within the immediate next diagonal square along
     *      the specified path of attack.
     * 
     * - If there is an empty square behind above said enemy piece allowing your piece
     *      to land after the attack.
     * 
     * \param i Target attacking piece's row index.
     * \param j Target attacking piece's column index.
     * \param piece Target piece being verified, providing rank and color info of the piece.
     * \param direction Target piece's attacking direction.
     * \return Flag indicating whether the piece meets the requirements to perform an attack.
     */
    bool theoAtkCheck( unsigned int i, unsigned int j, CHK_PIECE piece, CHK_DIREC direction ) const;

    /**
     * \brief A theoretical move check, assuming a piece of target color and rank initiates
     *  the move at the desired position along the desired direction.
     * 
     * The conditions checked are:
     * 
     * - The required move direction matches the capability of the piece.
     * 
     * - If the move is still within the limits of the board.
     * 
     * - If the move is impeded by an existing piece.
     * 
     * \param i Target moving piece's row index.
     * \param j Target moving piece's column index.
     * \param piece Target piece being verified, providing rank and color info of the piece.
     * \param direction Target piece's move direction.
     * \return Flag indicating whether the piece meets the requirements to perform a move.
     */
    bool theoMoveCheck( unsigned int i, unsigned int j, CHK_PIECE piece, CHK_DIREC direction ) const;

    /**
     * \brief A theoretical attack check on all directions, assuming a piece of target color 
     *  and rank initiates the attack at the desired position.
     * 
     * \param i Target attacking piece's row index.
     * \param j Target attacking piece's column index.
     * \param piece Target piece being verified, providing rank and color info of the piece.
     * \return Vector of all directions the target piece can attack towards.
     */
    vector<CHK_DIREC> theoAtkCheckAll( unsigned int i, unsigned int j, CHK_PIECE piece ) const;

    /**
     * \brief A theoretical move check on all directions, assuming a piece of target color 
     *  and rank initiates the attack at the desired position.
     * 
     * \param i Target moving piece's row index.
     * \param j Target moving piece's column index.
     * \param piece Target piece being verified, providing rank and color info of the piece.
     * \return Vector of all directions the target piece can move towards.
     */
    vector<CHK_DIREC> theoMoveCheckAll( unsigned int i, unsigned int j, CHK_PIECE piece ) const;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

    /**
     * Obtain the current turn index representation.
     * 
     * \return Current turn index: [0 = black] [1 = red].
     */
    int getCurrTurn() const;

    /**
     * Determine if current turn is black turn.
     * 
     * \return Flag indicating if it is black's turn.
     */
    bool isBlackTurn() const;

    /**
     * Obtain the turn id of the target piece.
     * 
     * Possible outcomes:
     * 
     * - [-1 = no piece]
     * 
     * - [0 = black]
     * 
     * - [1 = red]
     * 
     * \return The turn index associated to the target piece.
     */
    int getTurnID( CHK_PIECE ) const;


    /**
     * Perform a check on the current state of the game and update the game state variable.
     * 
     * The possible states are:
     * 
     * - unfinished ---> game is still in progress.
     * - locked -------> game is locked in an attack sequence by a certain piece.
     * - Black won: ---> game has ended with black being victorious.
     * - Red won: -----> game has ended with red being victorious.
     * - Draw: --------> game has ended with no one victorious (a number of turns with no capture or crowning).
     * 
     */
    void upd_game_state();

    /**
     * \brief Update the list of possible attacking pieces.
     * 
     * Both the list of red and black pieces that can perform an attack
     * will be updated.
     */
    void upd_atk_posb();

    /**
     * \brief Update the list of possible displacements.
     * 
     * Both the list of red and black pieces that can perform a move
     * will be updated.
     */
    void upd_displ_posb();

    /*
    Print to terminal the state of the board.
    This is a debug tool, and may be deleted.
    */

    /**
     * \brief Print the state of the board onto the console terminal.
     * 
     * \note This is a debug tool and has no impact on actual game functionalities.
     */
    void printBoard() const;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

    /**
     * \brief Set the board as completely blank.
     * 
     * All pieces of the board adopt the "no piece" state.
     */
    void clearBoard();

    /**
     * \brief Place a new piece at the target coordinate on the board.
     * 
     * \note Overwrites existing piece by default.
     * 
     * \warning Does not update the game state or turn count.
     * 
     * \param i Target attacking piece's row index.
     * \param j Target attacking piece's column index.
     * \param piece Target piece being verified, providing rank and color info of the piece.
     * \return The boolean indicating whether the piece insertion was successful.
     */
    bool insertPiece( unsigned int i, unsigned int j, CHK_PIECE newPiece );

    /**
     * \brief Directly insert the desired board set to this game object.
     * 
     * \param in_CHK_board The given board that is copied by the class' board.
     * 
     * \warning Does not update game state or turn count.
     */
    void insertBoard( const CHK_PIECE in_CHK_board[BOARDHEIGHT][BOARDWIDTH] );

    /**
     * Reset the board to the state of a fresh new game.
     * 
     * \note This function serves as a game instance reset, though some class
     *  variables may not be affected.
     */
    void resetBoard();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      AI Related Functions
// ====================================================================== >>>>>

    /**
     * \brief Provide a numerical score to the current state of the game.
     * 
     * This function call automatically calls the upd_game_state() function.
     * 
     * \return The numerical value of the current state of the game.
     * 
     * \note A negative value is associated to red, a positive value is associated 
     *  to black, so a high positive value translates to a good board situation 
     *  for red and vice versa.
     */
    int gameStateEval();

    /**
     * Obtain all current valid moves (displacements).
     * 
     * Turn is based on the current checkers instance's turn count.
     * 
     * \note Attacks take precedence over displacements, so if a single piece
     *  can attack, no other piece of the same color can be displaced and this
     *  function would return an empty vector.
     */
    vector<CHK_move> get_valid_moves();

    /**
     * \brief The minmax function for helping the game A.I. to make the best 
     *  possible move. This function acts as both initialization and recursive 
     *  portions.
     * 
     * Max for black, min for red.
     * 
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     * \note This function does not determine the best move, but helps in 
     *  attributing numerical values to each possible move up to a specified 
     *  depth/turn into the future.
     */
    int minmax( bool isMaximizing, int depth );


    /**
     * \brief The multithread portion of the minmax function for helping the game 
     *  A.I. to make the best possible move with multi-threaded design to be able 
     *  to be run with multiple instances at the same time.
     * 
     * Max for black, min for red.
     * 
     *
     * \param tarGame The game for which the minmax value is to be calucalted at 
     *  its current state.
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     * \warning This function is designed to be ran with multiple instances on 
     *  different threads and should not be called out of a vacuum.
     *  Please use the designated multi-thread minmax run starting function
     *  minmax_split_init.
     * 
     * \note This function does not determine the best move, but helps in 
     *  attributing numerical values to each possible move up to a specified 
     *  depth/turn into the future.
     */
    static int minmax_split( checkers& tarGame, bool isMaximizing, int depth );
    
    /**
     * \brief The initialization portion of the minmax function for helping the 
     *  game A.I. to make the best possible move with multi-threaded design to 
     *  be able to be run with multiple instances at the same time.
     * 
     * The starting point of the multi-threaded minmax_split run.
     * 
     * Like the normal minmax function version, this function generates a score for
     * helping the game A.I. to make the best possible move.
     * 
     * \param tarGame The game for which the minmax value is to be calucalted at 
     *  its current state.
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     */
    static int minmax_split_init( checkers& tarGame, bool isMaximizing, int depth );

    /*
    minmax function for helping the game A.I. to make the best possible move.
    This function does not determine the best move, but helps in attributing numerical
    values to each possible move up to a specified depth/turn into the future.
    NOTE: maximizing when black, minimizing when red.
    NOTE: debug version prints every step on the console.

    NOTE: If this is still here in the official version ... feel free to delete.
    */
    int minmax_debug( bool isMaximizing, int depth );
    /*
    The actual recursive portion of the debug minmax function.

    NOTE: If this is still here in the official version ... feel free to delete.
    */
    int minmax_debug_loop( bool isMaximizing, int depth, int max_depth );


    /**
     * \brief The initialization portion of the minmax function with AB-pruning 
     *  capability for helping the game A.I. to make the best possible move. 
     * 
     * Max for black, min for red.
     * 
     * The process and results are basically the same as the standard minmax 
     * function, but branches of the search may be skipped depending on best 
     * results found in the immediate higher node of the search tree.
     * 
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     * \note This function does not determine the best move, but helps in 
     *  attributing numerical values to each possible move up to a specified 
     *  depth/turn into the future.
     */
    int minmaxAB_init( bool isMaximizing, int depth );

    /**
     * \brief The recursive portion of the minmax function with AB-pruning 
     *  capability for helping the game A.I. to make the best possible move. 
     * 
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param alpha The best max score reference for the next turn score calculation.
     * \param beta The best min score reference for the next turn score calculation.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     * \warning This is the recursive portion for the minmaxAB full function and 
     *  should not be called out of a vacuum. Please use the intended starting 
     *  point function minmaxAB.
     */
    int minmaxAB_loop( bool isMaximizing, int alpha, int beta, int depth );


    /**
     * \brief The multithreaded portion of the minmax function with AB-pruning 
     *  capability with multi-threaded design.
     * 
     * Max for black, min for red.
     * 
     * The process and results are basically the same as the standard minmax 
     * function, but branches of the search may be skipped depending on best 
     * results found in the immediate higher node of the search tree.
     * 
     * \param tarGame The game for which the minmax value is to be calucalted at 
     *  its current state.
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     * \note This function does not determine the best move, but helps in 
     *  attributing numerical values to each possible move up to a specified 
     *  depth/turn into the future.
     * 
     * \warning This function is designed to be ran with multiple instances on 
     *  different threads and should not be called out of a vacuum.
     *  Please use the designated multi-thread minmaxAB run starting function 
     *  minmaxAB_split_init.
     * 
     */
    static int minmaxAB_split( checkers& tarGame, bool isMaximizing, int depth );


    /**
     * \brief The initialization portion of the minmax function with AB-pruning 
     *  capability with multi-threaded design.
     * 
     * \param tarGame The game for which the minmax value is to be calucalted at 
     *  its current state.
     * \param isMaximizing flag for indicating whether the minmax function is 
     *  aiming to maximize or not. If not, then it aims to minimize.
     * \param depth The number of moves (including opponent's) into the future to scan.
     * \return The computed minmax score.
     * 
     * \note This function does not determine the best move, but helps in 
     *  attributing numerical values to each possible move up to a specified 
     *  depth/turn into the future.
     */
    static int minmaxAB_split_init( checkers& tarGame, bool isMaximizing, int depth );

    /**
     * Determine the best move to make in the current turn at the current board state
     * using the standard minmax computation.
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove();

    /**
     * Determine the best move to make in the current turn at the current board state 
     * with a minmax score computed up to the specified number of moves in the future.
     * 
     * \param depth The number of moves (including opponent's) into the future to scan.
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove( int depth );

    /**
     * Determine the best move to make in the current turn at the current board state 
     * using the minmax algorithm with multi-thread capability.
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove_split();
    /**
     * Determine the best move to make in the current turn at the current board state 
     * using the minmax algorithm with multi-thread capability with a specified max depth.
     * 
     * \param depth The number of moves (including opponent's) into the future to scan.
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove_split( int depth );


    /**
     * Determine the best move to make in the current turn at the current board state
     * using the minmax with AB-pruning score.
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove_ABP();
    /**
     * Determine the best move to make in the current turn at the current board state
     * using the minmax with AB-pruning score with set recursion depth limit.
     * 
     * \param depth The number of moves (including opponent's) into the future to scan. 
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove_ABP( int depth );


    /**
     * Determine the best move to make in the current turn at the current board state 
     * using the AB-pruning minmax algorithm with multi-thread capability.
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove_ABP_split();


    /**
     * Determine the best move to make in the current turn at the current board state 
     * using the multi-threaded AB-pruning minmax algorithm with set recursion 
     * depth limit.
     * 
     * \param depth The number of moves (including opponent's) into the future to scan. 
     * 
     * \return The best move to perform at the current board's state.
     */
    CHK_move bestMove_ABP_split( int depth );

    /**
     * Let the AI perform the next move in the target checkers game.
     * 
     * \param tarGame The target checkers game in which the next move is to be 
     *  made by the AI.
     * 
     * \return The checkers move made (IMPOS_MOVE if no move is made).
     * 
     * \note The move is made in game automatically during function call. 
     *  The return value is just additional info.
     */
    static CHK_move AI_play( checkers& tarGame );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Variables Access Functions
// ====================================================================== >>>>>

    /**
     * Return the list of possible attacks by red pieces at the current board state.
     * 
     * \return The vector of possible red attack moves.
     */
    vector<CHK_move> getR_atk_list() const;
    /**
     * Return the list of possible attacks by black pieces at the current board state.
     * 
     * \return The vector of possible black attack moves.
     */
    vector<CHK_move> getB_atk_list() const;

    /**
     * Return the list of possible displacement by red pieces at the current board state.
     * 
     * \return The vector of possible red piece displacement.
     */
    vector<CHK_move> getR_displ_list() const;
    /**
     * Return the list of possible displacement by black pieces at the current board state.
     * 
     * \return The vector of possible black piece displacement.
     */
    vector<CHK_move> getB_displ_list() const;

    /**
     * \return Current game state turn count.
     */
    unsigned int getTurn_cnt() const;
    /**
     * \brief Forcibly set the game's current turn count.
     * 
     * \param turn_cnt The number of turns to set the game to 
     *  (disregarding current state).
     */
    void setTurn_cnt( unsigned int turn_cnt );

    /**
     * \return The current game's AI options:
     *  
     * - [0 = standard minmax]
     * 
     * - [1 = multi-threaded standard minmax]
     * 
     * - [2 = minmax with AB-pruning]
     * 
     * - [3 = multi-threaded minmax with AB-pruning]
     */
    CHK_AI_OPT getAI_opt() const;

    /**
     * Set the AI option
     * 
     * \param opt The new AI option to adopt.
     *
     * - [0 = standard minmax]
     * 
     * - [1 = multi-threaded standard minmax]
     * 
     * - [2 = minmax with AB-pruning]
     * 
     * - [3 = multi-threaded minmax with AB-pruning]
     */
    void setAI_opt( CHK_AI_OPT opt );

    //TODO: Check argument.
    /**
     * \return The minmax depth currently adopted by this checkers game instance.
     */
    unsigned int getMinmax_depth() const;
    /**
     * Assign a new minmax depth to this checkers game instance.
     * 
     * \param in_minmax_depth New minmax depth to adopt.
     */
    void setMinmax_depth( unsigned int in_minmax_depth );

    /**
     * Set use AI flag to true.
     */
    void enabledAI();
    /**
     * Set use AI flag to false.
     */
    void disableAI();
    /**
     * Switch the AI use flag.
     */
    void toggle_AI();
    /**
     * \return The AI use flag.
     */
    bool is_AI_enabled() const;

    /**
     * \brief Turn off the AI process flag.
     * 
     * This will turn off the AI running threads at the earliest convenience.
     */
    void disableAI_proc();
    /**
     * \brief Turn on the AI process flag.
     */
    void enableAI_proc();

    /**
     * \return AI play first flag.
     */
    bool is_AI_first() const;
    /**
     * \brief Turn on AI play first flag.
     */
    void set_AI_first();
    /**
     * \brief Turn off AI play first flag.
     */
    void set_AI_not_first();
    /**
     * \brief Switch AI play first flag.
     */
    void toggle_AI_first();

    /**
     * Get the number of threads this game engine attempts to use if AI is enabled.
     * 
     * \return the number of threads used by this game's AI, if available.
     */
    unsigned int get_thread_to_use() const;

    /**
     * Set the number of threads this checkers instance use by its AI.
     * 
     * \param new_thr_cnt New number of threads to use for the game AI.
     *
     * \note If value exceeds current hardware thread count limit, the limit is 
     *  adopted. If value is 0, it will turn to 1.
     */
    void set_thread_to_use( const unsigned int new_thr_cnt );

// ====================================================================== <<<<<
    

protected:


// ====================================================================== >>>>>
//      AI Related Functions (Protected)
// ====================================================================== >>>>>

    /**
     * Options with AI selection:
     * - [0 = standard minmax]
     * - [1 = multi-threaded standard minmax]
     * - [2 = minmax with AB-pruning]
     * - [3 = multi-threaded minmax with AB-pruning]
     */
    CHK_AI_OPT AI_opt;

    /**
     * The depth of the minmax function used by this game instance.
     */
    unsigned int minmax_depth;

    /**
     * Flag indicating if this game enables AI to play as opponent.
     */
    bool vsAI = true;
    
    /**
     * Flag indicating if the AI plays first over a versus AI game.
     */
    bool AI_first = false;

    /**
     * \brief Flag used for separate thread running the AI process.
     * 
     * This flag is normally turned on when the AI process starts to run.
     * If this flag is turned off during an AI process run, the AI process 
     * is to stop at the earliest convenience.
     */
    bool AI_proc_flag;

    /**
     * The number of threads that this game seek to use if multithread AI usage 
     * is enabled.
     * 
     * \note Won't try to use more than available number of threads given local
     *  hardware limits.
     */
    unsigned int thread_to_use;

    /**
     * Class static mutex for the purpose of synchronizing use of shared variables.
     */
    static std::mutex mtx_shared_move_list;

    /**
     * Class static shared list of moves.
     * 
     * This list serves as a shared pool of moves to be dipped by multiple threads 
     * at the same time. To prevent the same move from being analysed by more than 
     * one thread, you need to use mutex to ensure synchronization. 
     */
    static stack<checkers::CHK_move> shared_move_stk;

    /**
     * Class static shared stack of minmax operation results.
     * 
     * This stack serves as the deposit point of results from running minmax
     * over several threads at the same time.
     */
    static stack<int> shared_minmax_res;

// ====================================================================== <<<<<

    // The number of times a play has been made. Black start at turn 0.
    unsigned int turn_cnt;

    // The number of consecutive turns where no piece has been taken or promoted.
    unsigned int no_change_turn_cnt;


    /**
     * Integer vector holding the count of pieces currently on the board. The vector 
     * has 4 entries, in the following order:
     * 
     *  0- number of red pieces.
     *  1- number of black pieces.
     *  2- number of crowned red pieces.
     *  3- number of crowed black pieces.
     * 
     * This counter vector only updates with the function "upd_game_state()".
     */
    vector<unsigned int> pieceCounter;

    // TODO: Please find a way to allocate memory premptively for this array.
    /**
     * Numerical table representing the checker board.
     * The board orientation works in the manner as follow:
     *  - CHK_board[0][0] => black piece
     *  - CHK_board[BOARDHEIGHT-1][BOARDWIDTH-1] => red piece
     */
    CHK_PIECE CHK_board[BOARDHEIGHT][BOARDWIDTH];

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

    /**
     * The coordinate variable which keeps track of the location of the piece which 
     * is causing a lock through an attack sequence.
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