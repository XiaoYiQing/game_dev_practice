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
//      Chess Piece Class
// ====================================================================== >>>>>

    class chs_piece{

    public:

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

    };

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Chess Move Class
// ====================================================================== >>>>>

    /**
     * Specialized nested class for representing a chess move.
     * 
     * \warning This class does not check for validity of a move.
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

    chs_piece get_piece_at( unsigned int i, unsigned int j ) const;

    void set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce );

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
    

private:


};


};


#endif // CHESS_H