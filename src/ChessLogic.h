#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H

#include <vector>

enum class PieceColor { White, Black };
enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

struct Piece {
    PieceColor color;
    PieceType  type;
    Piece(PieceColor c, PieceType t) : color(c), type(t) {}
};

struct Move {
    int startRow, startCol;
    int endRow, endCol;
    bool isPromotion;
    PieceType promotionType;

    Move()
    : startRow(0),startCol(0),
      endRow(0),endCol(0),
      isPromotion(false),
      promotionType(PieceType::Queen) {}
};

class Board {
public:
    Piece* squares[8][8];

    bool whiteCanCastleK;
    bool whiteCanCastleQ;
    bool blackCanCastleK;
    bool blackCanCastleQ;
    int  enPassantColumn; // -1 if none

    Board();
    ~Board();

    void clear();
    void initializeStandard();

    bool isValidMove(const Move& mv, PieceColor currentPlayer);
    void makeMove(const Move& mv, PieceColor currentPlayer);
    bool isGameOver(PieceColor currentPlayer);
    bool isInCheck(PieceColor color);

    // returns all fully legal moves
    std::vector<Move> generateLegalMoves(PieceColor color);

    // check if draw by insufficient material
    bool isInsufficientMaterial() const;

    Board* clone() const;

private:
    std::vector<Move> generateAllPseudoMoves(PieceColor color);
    std::vector<Move> getPieceMoves(int row, int col, Piece* p);

    void addPawnMoves(std::vector<Move>& moves, int row, int col, Piece* p);
    void addKnightMoves(std::vector<Move>& moves, int row, int col, Piece* p);
    void addSlidingMoves(std::vector<Move>& moves, int row, int col, Piece* p, const std::vector<std::pair<int,int>>& directions);
    void addKingMoves(std::vector<Move>& moves, int row, int col, Piece* p);

    bool inBounds(int r, int c) const { return (r>=0 && r<8 && c>=0 && c<8); }
};

#endif
