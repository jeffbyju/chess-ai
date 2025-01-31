#include "ChessLogic.h"
#include <cmath>
#include <algorithm>

static std::vector<std::pair<int,int>> rookDirections = {
    {1,0},{-1,0},{0,1},{0,-1}
};
static std::vector<std::pair<int,int>> bishopDirections = {
    {1,1},{1,-1},{-1,1},{-1,-1}
};
static std::vector<std::pair<int,int>> queenDirections = {
    {1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}
};

Board::Board(){
    clear();
}
Board::~Board(){
    for(int r=0; r<8; r++){
        for(int c=0; c<8; c++){
            if(squares[r][c]){
                delete squares[r][c];
                squares[r][c]=nullptr;
            }
        }
    }
}
void Board::clear(){
    for(int r=0; r<8; r++){
        for(int c=0; c<8; c++){
            squares[r][c]=nullptr;
        }
    }
    whiteCanCastleK=true;
    whiteCanCastleQ=true;
    blackCanCastleK=true;
    blackCanCastleQ=true;
    enPassantColumn=-1;
}

void Board::initializeStandard(){
    clear();
    // place pawns
    for(int c=0; c<8; c++){
        squares[6][c] = new Piece(PieceColor::White, PieceType::Pawn);
        squares[1][c] = new Piece(PieceColor::Black, PieceType::Pawn);
    }
    // rooks
    squares[7][0] = new Piece(PieceColor::White, PieceType::Rook);
    squares[7][7] = new Piece(PieceColor::White, PieceType::Rook);
    squares[0][0] = new Piece(PieceColor::Black, PieceType::Rook);
    squares[0][7] = new Piece(PieceColor::Black, PieceType::Rook);
    // knights
    squares[7][1] = new Piece(PieceColor::White, PieceType::Knight);
    squares[7][6] = new Piece(PieceColor::White, PieceType::Knight);
    squares[0][1] = new Piece(PieceColor::Black, PieceType::Knight);
    squares[0][6] = new Piece(PieceColor::Black, PieceType::Knight);
    // bishops
    squares[7][2] = new Piece(PieceColor::White, PieceType::Bishop);
    squares[7][5] = new Piece(PieceColor::White, PieceType::Bishop);
    squares[0][2] = new Piece(PieceColor::Black, PieceType::Bishop);
    squares[0][5] = new Piece(PieceColor::Black, PieceType::Bishop);
    // queens
    squares[7][3] = new Piece(PieceColor::White, PieceType::Queen);
    squares[0][3] = new Piece(PieceColor::Black, PieceType::Queen);
    // kings
    squares[7][4] = new Piece(PieceColor::White, PieceType::King);
    squares[0][4] = new Piece(PieceColor::Black, PieceType::King);
}

bool Board::isValidMove(const Move& mv, PieceColor currentPlayer){
    auto legal= generateLegalMoves(currentPlayer);
    for(auto& l : legal){
        if(l.startRow== mv.startRow &&
           l.startCol== mv.startCol &&
           l.endRow== mv.endRow &&
           l.endCol== mv.endCol &&
           l.isPromotion== mv.isPromotion &&
           l.promotionType== mv.promotionType){
            return true;
        }
    }
    return false;
}

void Board::makeMove(const Move& mv, PieceColor currentPlayer){
    Piece* p= squares[mv.startRow][mv.startCol];
    squares[mv.startRow][mv.startCol]=nullptr;

    // en passant
    if(p && p->type==PieceType::Pawn && enPassantColumn>=0){
        int direction= (p->color==PieceColor::White? -1:1);
        if(mv.endCol== enPassantColumn){
            int capturedRow= mv.endRow - direction;
            if(capturedRow>=0&&capturedRow<8){
                Piece* maybePawn= squares[capturedRow][mv.endCol];
                if(maybePawn && maybePawn->type==PieceType::Pawn && maybePawn->color!= p->color){
                    delete squares[capturedRow][mv.endCol];
                    squares[capturedRow][mv.endCol]=nullptr;
                }
            }
        }
    }

    // place piece
    squares[mv.endRow][mv.endCol]= p;

    // reset enPassant
    enPassantColumn=-1;

    // if Pawn moves 2 squares => set enPassant
    if(p && p->type==PieceType::Pawn){
        if(std::abs(mv.endRow - mv.startRow)==2){
            enPassantColumn= mv.startCol;
        }
    }

    // castling
    if(p && p->type==PieceType::King && mv.startCol==4){
        if(p->color== PieceColor::White && mv.startRow==7){
            // short
            if(mv.endCol==6){
                Piece* rook= squares[7][7];
                squares[7][7]=nullptr;
                squares[7][5]= rook;
                whiteCanCastleK=false; whiteCanCastleQ=false;
            } else if(mv.endCol==2){
                Piece* rook= squares[7][0];
                squares[7][0]=nullptr;
                squares[7][3]= rook;
                whiteCanCastleK=false; whiteCanCastleQ=false;
            }
        }
        else if(p->color== PieceColor::Black && mv.startRow==0){
            // short
            if(mv.endCol==6){
                Piece* rook= squares[0][7];
                squares[0][7]=nullptr;
                squares[0][5]=rook;
                blackCanCastleK=false; blackCanCastleQ=false;
            }
            else if(mv.endCol==2){
                Piece* rook= squares[0][0];
                squares[0][0]=nullptr;
                squares[0][3]=rook;
                blackCanCastleK=false; blackCanCastleQ=false;
            }
        }
    }

    // if king or rook moves => remove castling rights
    if(p && p->type==PieceType::King){
        if(p->color== PieceColor::White){
            whiteCanCastleK=false; whiteCanCastleQ=false;
        } else {
            blackCanCastleK=false; blackCanCastleQ=false;
        }
    }
    else if(p && p->type==PieceType::Rook){
        if(p->color== PieceColor::White){
            if(mv.startRow==7 && mv.startCol==0) whiteCanCastleQ=false;
            if(mv.startRow==7 && mv.startCol==7) whiteCanCastleK=false;
        } else {
            if(mv.startRow==0 && mv.startCol==0) blackCanCastleQ=false;
            if(mv.startRow==0 && mv.startCol==7) blackCanCastleK=false;
        }
    }

    // promotion
    if(p && p->type==PieceType::Pawn && mv.isPromotion){
        delete squares[mv.endRow][mv.endCol];
        squares[mv.endRow][mv.endCol] = new Piece(p->color, mv.promotionType);
    }
}

bool Board::isGameOver(PieceColor currentPlayer){
    auto legal= generateLegalMoves(currentPlayer);
    if(legal.empty()) return true;
    return false;
}

bool Board::isInCheck(PieceColor color){
    // find king
    int kr=-1, kc=-1;
    for(int r=0; r<8; r++){
        for(int c=0; c<8; c++){
            Piece* pc= squares[r][c];
            if(pc && pc->type==PieceType::King && pc->color==color){
                kr=r; kc=c; break;
            }
        }
    }
    if(kr<0) return false; // no king found?

    // see if any enemy pseudo-legal move captures that square
    PieceColor opp= (color==PieceColor::White? PieceColor::Black: PieceColor::White);
    auto pseudo= generateAllPseudoMoves(opp);
    for(auto& mv : pseudo){
        if(mv.endRow==kr && mv.endCol==kc){
            return true;
        }
    }
    return false;
}

std::vector<Move> Board::generateLegalMoves(PieceColor color){
    auto pseudo= generateAllPseudoMoves(color);
    std::vector<Move> legal;
    for(auto& mv: pseudo){
        Board* cl= clone();
        cl->makeMove(mv, color);
        if(!cl->isInCheck(color)){
            legal.push_back(mv);
        }
        delete cl;
    }
    return legal;
}

// check if we have K+B vs K or K+N vs K or just kings
bool Board::isInsufficientMaterial() const
{
    int pieceCount=0;
    int whiteCount=0;
    int blackCount=0;
    bool whiteBishopOrKnight=false;
    bool blackBishopOrKnight=false;

    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            auto p= squares[r][c];
            if(p){
                pieceCount++;
                if(p->color==PieceColor::White) whiteCount++;
                else blackCount++;

                if(p->type!=PieceType::King){
                    // if anything bigger than bishop/knight => not insufficient
                    // but we do further checks
                    if(p->type==PieceType::Bishop || p->type==PieceType::Knight){
                        if(p->color==PieceColor::White) whiteBishopOrKnight=true;
                        else blackBishopOrKnight=true;
                    }
                    else {
                        // if it's a rook or queen or pawn => not insufficient
                        return false;
                    }
                }
            }
        }
    }

    // if only 2 pieces => K vs K
    if(pieceCount==2) return true;

    // K+N vs K or K+B vs K
    if(pieceCount==3){
        // e.g. white has K+N or K+B
        // or black has K+N or K+B
        // check exactly
        // we see if there's exactly one minor piece
        int wMinor=0, bMinor=0;
        for(int r=0;r<8;r++){
            for(int c=0;c<8;c++){
                auto pc= squares[r][c];
                if(pc && pc->type!=PieceType::King){
                    if((pc->type==PieceType::Bishop||pc->type==PieceType::Knight)){
                        // OK
                    } else {
                        return false;
                    }
                }
            }
        }
        return true; 
    }

    // if K+B vs K+B with same color bishop => also insufficient in real chess
    // we'll skip advanced cases. We'll just do a base approach.

    // fallback
    return false;
}

Board* Board::clone() const
{
    Board* b2= new Board();
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            if(squares[r][c]){
                b2->squares[r][c] = new Piece(squares[r][c]->color, squares[r][c]->type);
            }
        }
    }
    b2->whiteCanCastleK= whiteCanCastleK;
    b2->whiteCanCastleQ= whiteCanCastleQ;
    b2->blackCanCastleK= blackCanCastleK;
    b2->blackCanCastleQ= blackCanCastleQ;
    b2->enPassantColumn= enPassantColumn;
    return b2;
}

// Private: generate all pseudo moves
static std::vector<std::pair<int,int>> kingDirs = {
    {1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}
};

std::vector<Move> Board::generateAllPseudoMoves(PieceColor color)
{
    std::vector<Move> out;
    for(int r=0; r<8; r++){
        for(int c=0; c<8; c++){
            Piece* piece= squares[r][c];
            if(piece && piece->color==color){
                auto these= getPieceMoves(r,c,piece);
                out.insert(out.end(), these.begin(), these.end());
            }
        }
    }
    return out;
}

std::vector<Move> Board::getPieceMoves(int row, int col, Piece* p)
{
    std::vector<Move> moves;
    switch(p->type){
        case PieceType::Pawn:   addPawnMoves(moves, row,col,p); break;
        case PieceType::Knight: addKnightMoves(moves, row,col,p); break;
        case PieceType::Bishop: addSlidingMoves(moves, row,col,p, bishopDirections); break;
        case PieceType::Rook:   addSlidingMoves(moves, row,col,p, rookDirections);   break;
        case PieceType::Queen:  addSlidingMoves(moves, row,col,p, queenDirections);  break;
        case PieceType::King:   addKingMoves(moves, row,col,p);   break;
    }
    return moves;
}

void Board::addPawnMoves(std::vector<Move>& moves, int row, int col, Piece* p)
{
    int dir= (p->color==PieceColor::White? -1: 1);
    int startRow= (p->color==PieceColor::White? 6:1);

    // forward 1
    int frow= row+ dir;
    if(inBounds(frow,col) && !squares[frow][col]){
        // check promotion
        if((frow==0 && p->color==PieceColor::White)||
           (frow==7 && p->color==PieceColor::Black)){
            Move m;
            m.startRow = row; 
            m.startCol = col;
            m.endRow   = frow;
            m.endCol   = col;
            // no isPromotion in the board's list
            moves.push_back(m);
        } else {
            Move m;
            m.startRow=row; m.startCol=col; m.endRow=frow; m.endCol=col;
            moves.push_back(m);
        }
        // forward 2
        if(row==startRow){
            int f2= row+2*dir;
            if(inBounds(f2,col) && !squares[f2][col]){
                Move m;
                m.startRow=row; m.startCol=col;
                m.endRow=f2;    m.endCol=col;
                moves.push_back(m);
            }
        }
    }

    // captures
    for(int dc=-1; dc<=1; dc+=2){
        int cc= col+dc;
        int rr= row+ dir;
        if(!inBounds(rr,cc)) continue;
        Piece* t= squares[rr][cc];
        if(t && t->color!= p->color){
            // capture
            if((rr==0 && p->color==PieceColor::White)||
               (rr==7 && p->color==PieceColor::Black)){
                // promotions
                Move mm;
                mm.startRow=row; mm.startCol=col;
                mm.endRow= rr;   mm.endCol= cc;
                moves.push_back(mm);
            } else {
                Move mm;
                mm.startRow=row; mm.startCol=col;
                mm.endRow= rr;   mm.endCol= cc;
                moves.push_back(mm);
            }
        } else {
            // en passant
            if(enPassantColumn== cc){
                if((p->color==PieceColor::White && row==3)||
                   (p->color==PieceColor::Black && row==4)){
                    Move mm;
                    mm.startRow=row; mm.startCol=col;
                    mm.endRow= rr;   mm.endCol= cc;
                    moves.push_back(mm);
                }
            }
        }
    }
}

void Board::addKnightMoves(std::vector<Move>& moves, int row, int col, Piece* p)
{
    int offsets[8][2]= {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    for(int i=0; i<8; i++){
        int nr= row+ offsets[i][0];
        int nc= col+ offsets[i][1];
        if(inBounds(nr,nc)){
            Piece* t= squares[nr][nc];
            if(!t || t->color!= p->color){
                Move mm; 
                mm.startRow=row; mm.startCol=col;
                mm.endRow=nr;    mm.endCol=nc;
                moves.push_back(mm);
            }
        }
    }
}

void Board::addSlidingMoves(std::vector<Move>& moves, int row, int col, Piece* p, const std::vector<std::pair<int,int>>& directions)
{
    for(auto& d: directions){
        int rr=row; 
        int cc=col;
        while(true){
            rr += d.first;
            cc += d.second;
            if(!inBounds(rr,cc)) break;
            Piece* t= squares[rr][cc];
            if(!t){
                Move mm;
                mm.startRow=row; mm.startCol=col;
                mm.endRow= rr;   mm.endCol= cc;
                moves.push_back(mm);
            } else {
                // if color differs => we can capture
                if(t->color!= p->color){
                    Move mm;
                    mm.startRow=row; mm.startCol=col;
                    mm.endRow= rr;   mm.endCol= cc;
                    moves.push_back(mm);
                }
                break; 
            }
        }
    }
}

void Board::addKingMoves(std::vector<Move>& moves, int row, int col, Piece* p)
{
    for(int dr=-1; dr<=1; dr++){
        for(int dc=-1; dc<=1; dc++){
            if(dr==0 && dc==0) continue;
            int nr= row+ dr; 
            int nc= col+ dc;
            if(inBounds(nr,nc)){
                Piece* t= squares[nr][nc];
                if(!t || t->color!= p->color){
                    Move mm; mm.startRow=row; mm.startCol=col;
                    mm.endRow=nr; mm.endCol=nc;
                    moves.push_back(mm);
                }
            }
        }
    }
    // castling
    if(p->color==PieceColor::White && row==7 && col==4){
        // short
        if(whiteCanCastleK && !squares[7][5] && !squares[7][6]){
            Piece* rook= squares[7][7];
            if(rook && rook->type==PieceType::Rook && rook->color==PieceColor::White){
                Move mm; mm.startRow=7; mm.startCol=4; mm.endRow=7; mm.endCol=6;
                moves.push_back(mm);
            }
        }
        // long
        if(whiteCanCastleQ && !squares[7][1] && !squares[7][2] && !squares[7][3]){
            Piece* rook= squares[7][0];
            if(rook && rook->type==PieceType::Rook && rook->color==PieceColor::White){
                Move mm; mm.startRow=7; mm.startCol=4; mm.endRow=7; mm.endCol=2;
                moves.push_back(mm);
            }
        }
    }
    else if(p->color==PieceColor::Black && row==0 && col==4){
        // short
        if(blackCanCastleK && !squares[0][5] && !squares[0][6]){
            Piece* rook= squares[0][7];
            if(rook && rook->type==PieceType::Rook && rook->color==PieceColor::Black){
                Move mm; mm.startRow=0; mm.startCol=4; mm.endRow=0; mm.endCol=6;
                moves.push_back(mm);
            }
        }
        // long
        if(blackCanCastleQ && !squares[0][1] && !squares[0][2] && !squares[0][3]){
            Piece* rook= squares[0][0];
            if(rook && rook->type==PieceType::Rook && rook->color==PieceColor::Black){
                Move mm; mm.startRow=0; mm.startCol=4; mm.endRow=0; mm.endCol=2;
                moves.push_back(mm);
            }
        }
    }
}
