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

/**
 * My implementation of the chess game.
 * 
 * This basic implementation operates under the assumption that white starts at 
 * the lower side and black starts at the top side of the board.
 */
class chess{

public:

    // The dimensions of the chess board.
    static const unsigned int BOARDWIDTH = 8;
    static const unsigned int BOARDHEIGHT = 8;

    // Define the maximum number of consecutive moves without a pawn being moved
    // or a piece been captured.
    static const unsigned int DRAWMOVECOUNTMAX = 50;


// ====================================================================== >>>>>
//      Class Enum "CHS_PIECE_TYPE" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the possible chess pieces placed on the board.
     */
    enum class CHS_PIECE_TYPE{ NO_P, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

    // The number of enum entries in the enum "CHS_PIECE_TYPE" (Uses magic enum).
    const static int CHS_PIECE_TYPE_Count = (int) magic_enum::enum_count<CHS_PIECE_TYPE>();

    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHS_PIECE_TYPE The target CHS_PIECE_TYPE enum.
     * @return The string representation of the target CHS_PIECE_TYPE enum.
     */
    static string get_CHS_PIECE_TYPE_Str( CHS_PIECE_TYPE tar_CHS_PIECE_TYPE );
    /**
     * Obtain the CHS_PIECE_TYPE enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHS_PIECE_TYPE enum.
     * @return The matching CHS_PIECE_TYPE enum to the target index, if it exists.
     */
    static CHS_PIECE_TYPE get_CHS_PIECE_TYPE_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHS_PIECE_COLOR" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the possible chess pieces placed on the board.
     */
    enum class CHS_PIECE_COLOR{ NO_C, WHITE, BLACK };

    // The number of enum entries in the enum "CHS_PIECE_COLOR" (Uses magic enum).
    const static int CHS_PIECE_COLOR_Count = (int) magic_enum::enum_count<CHS_PIECE_COLOR>();

    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHS_PIECE_COLOR The target CHS_PIECE_COLOR enum.
     * @return The string representation of the target CHS_PIECE_COLOR enum.
     */
    static string get_CHS_PIECE_COLOR_Str( CHS_PIECE_COLOR tar_CHS_PIECE_COLOR );
    /**
     * Obtain the CHS_PIECE_COLOR enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHS_PIECE_COLOR enum.
     * @return The matching CHS_PIECE_COLOR enum to the target index, if it exists.
     */
    static CHS_PIECE_COLOR get_CHS_PIECE_COLOR_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHS_STATE" Help Functions
// ====================================================================== >>>>>
/*
Update the state of the game:
    > 0 = unfinished ---> game is still in progress.
    > 1 = White won: ---> game has ended with white being victorious.
    > 2 = Black won: -----> game has ended with black being victorious.
    > 3 = Draw: --------> game has ended with no one victorious.
*/

/**
 * Enum representing the states the game can be in.
 */
enum class CHS_STATE{ ONGOING, WWIN, RBIN, DRAW };

// The number of enum entries in the enum "CHS_STATE" (Uses magic enum).
const static int CHS_STATE_Count = (int) magic_enum::enum_count<CHS_STATE>();
/**
 * Obtain the string of the target enum case (Uses magic enum).
 * 
 * @param tar_CHS_STATE The target CHS_STATE enum.
 * @return The string representation of the target CHS_STATE enum.
 */
static string get_CHS_STATE_Str( CHS_STATE tar_CHS_STATE );
/**
 * Obtain the CHS_STATE enum whose native index matches the target index.
 * 
 * @param idx The target index for which we seek a matching CHS_STATE enum.
 * @return The matching CHS_STATE enum to the target index, if it exists.
 */
static CHS_STATE get_CHS_STATE_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Chess Piece Class
// ====================================================================== >>>>>

    class chs_piece{

    public:

        /**
         * Comparison operator overload.
         * 
         * \param other Target chs_piece to compare with.
         * \return Result of the comparison.
         */
        bool operator==(const chs_piece& other) const;

        // Base constructor.
        chs_piece();

        chs_piece( CHS_PIECE_TYPE type, CHS_PIECE_COLOR color );

        // Set the piece into an empty space equivalent.
        void set_as_empty();

        /**
         * \brief Print the piece using the designated symbol.
         * 
         * Prints only the symbol with no space or line breaks to delimit the symbol.
         * 
         * \note This is a debug tool and has no impact on actual game functionalities.
         */
        void printPiece() const;

        /**
         * The type of piece.
         */
        CHS_PIECE_TYPE type;

        /**
         * The color of the piece.
         */
        CHS_PIECE_COLOR color;

        /**
         * The boolean indicating whether this piece has not yet performed its forst 
         * move yet.
         */
        bool not_moved;

    };

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Chess Move Class
// ====================================================================== >>>>>

    /**
     * Specialized nested class for representing a chess move.
     * 
     * \warning This class does not check for validity of a move inherently. 
     *  However, it does define functions to do just so.
     */
    class chs_move{

        public:

        // Base constructor.
        chs_move();
        /**
         * Direct coordinate (individual numeral format) input constructor.
         * 
         * \param i_a Starting coordinate row index.
         * \param j_a Starting coordinate column index.
         * \param i_b Ending coordinate row index.
         * \param j_b Ending coordinate column index.
         */
        chs_move( int i_a, int j_a, int i_b, int j_b );
        /**
         * Direct coordinate (pair format) input constructor.
         * \param pt_a Starting coordinate.
         * \param pt_b Ending coordinate.
         */
        chs_move( pair<int,int> pt_a, pair<int,int> pt_b );

        // Starting coordinates.
        pair<int,int> pt_a;
        // Ending coordinate.
        pair<int,int> pt_b;

        /**
         * Obtain the vector representation of the move.
         * 
         * \return A pair of integers, representing a 2D vector.
         */
        std::pair<int,int> get_vec();
        

    };

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

    chess();

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
     * \brief Set the piece at the target coordinate as the target piece.
     * 
     * \note Overwrites existing piece by default.
     * 
     * \param i The row index of the insertion point.
     * \param j The row index of the insertion point.
     * \param inPce The new piece to be inserted.
     * 
     * \warning Does not update the game state or turn count.
     */
    void set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce );

    /**
     * Reset the board to the state of a fresh new game.
     * 
     * \note This function serves as a game instance reset, though some class
     *  variables may not be affected.
     */
    void resetBoard();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

    /**
     * Perform a chess piece displacement with the piece at the target square 
     * towards the specificed destination square.
     */
    bool move( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft );
    
    
    bool is_move_valid( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft );

    
    
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>

    /**
     * \brief Print the state of the board onto the console terminal.
     * 
     * \note This is a debug tool and has no impact on actual game functionalities.
     */
    void printBoard() const;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Function
// ====================================================================== >>>>>
    
    /**
     * \brief Convert 2D indexing to 1D.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * For example:
     *  (0,0)=>0, (0,1)=>1, ... (0,7)=>7, (1,0)=>8, and so on.
     * 
     * \param i Row index.
     * \param j Column index.
     * \return The linear index equivalent.
     */
    static int sub2ind( int i, int j );
    /**
     * \brief Convert 2D indexing to 1D.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * For example:
     *  (0,0)=>0, (0,1)=>1, ... (0,7)=>7, (1,0)=>8, and so on.
     * 
     * \param subIdx The 2D coordinate pair (first = row index, second = column index).
     * \return The linear index equivalent.
     */
    static int sub2ind( pair<int,int> subIdx );

    /**
     * \brief Convert linear indexing to 2D indexing.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * \param linIdx The linear index.
     * \return The 2D coordinate pair equivalent (first = row index, second = column index).
     */
    static pair<int,int> ind2sub( int linIdx );

    /**
     * Obtain the chess piece at the target coordinate.
     * 
     * \param i The row index of the target piece.
     * \param j The column index of the target piece.
     * \return The target piece at the coordinate.
     */
    chs_piece get_piece_at( unsigned int i, unsigned int j ) const;
    
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
    void setTurn_cnt( const unsigned int turn_cnt );
    
    /**
     * \brief Get the current game state.
     * 
     * \return The current game state.
     */
    CHS_STATE getState() const;

    /**
     * \brief Set the current game state.
     * 
     * \param state The new state to be applied to the game instance.
     * 
     * \warning This function can completely break the game's logic flow.
     */
    void setState( const CHS_STATE state );

    /**
     * \return The number of consecutive turns where no significant changes has occurred.
     */
    unsigned int getNo_change_turn_cnt() const;
    /**
     * \param no_change_turn_cnt The number of consecutive turns where no significant
     *  changes has occurred to be directly applied to the current game instance.
     */
    void setNo_change_turn_cnt( const unsigned int no_change_turn_cnt );

// ====================================================================== <<<<<


protected:

    /**
     * \brief Array representing the chess board.
     * 
     * - First indexing represents the row indexing.
     * 
     * - Second indexing represents the column indexing.
     * 
     * \note Remember that the lower right corner is a white square in chess.
     */
    chs_piece CHS_board[BOARDHEIGHT][BOARDWIDTH];
    
    /**
     * Array of lists of white pieces attacking the square associated to the index
     * in the array.
     */
    std::vector<int> atk_list_by_W[BOARDHEIGHT*BOARDWIDTH];
    /**
     * Array of lists of black pieces attacking the square associated to the index
     * in the array.
     */
    std::vector<int> atk_list_by_B[BOARDHEIGHT*BOARDWIDTH];

    // The number of times a play has been made. White start at turn 0.
    unsigned int turn_cnt;

    // The number of consecutive turns where the draw by lack of progress conditions applies.
    unsigned int no_change_turn_cnt;

    // The state of the game.
    CHS_STATE state;
    

private:


};


};


#endif // CHESS_H