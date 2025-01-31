#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#undef slots   // <--- This kills the macro
#include "ChessLogic.h"
#include "DQN.h"
#include "ReplayBuffer.h"



// bridging enumerations
inline PieceColor toPieceColor(::PieceColor c){
    return (c==::PieceColor::White? PieceColor::White: PieceColor::Black);
}
inline ::PieceColor fromPieceColor(PieceColor c){
    return (c==PieceColor::White? ::PieceColor::White : ::PieceColor::Black);
}

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget* parent=nullptr);
    PieceType showPromotionDialog(); 
    ~GameWindow();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Board board;
    DQN   dqn;
    ReplayBuffer replay;

    ::PieceColor currentPlayer;
    bool dragging;
    int dragStartRow, dragStartCol;
    int tileSize;

    float gamma;
    float epsilon;
    int stepCount;
    int targetUpdateFreq;

    std::map<QString, QPixmap> pieceImages;

    void initBoard();
    void doAIMove();
    void loadPieceImages();  
    void trainFromReplay();
    std::vector<float> boardToInput(const Board& b, ::PieceColor c);
    int moveToIndex(const Move& mv);
    float pieceValue(PieceType pt);

    void storeTransition(const std::vector<float>& before, ::PieceColor color,
                         const Move& mv, float reward,
                         const std::vector<float>& after, bool done);

    void addRewardToLosingSide(::PieceColor loser, float negativeReward);

    void drawBoard(QPainter& p);
    void drawPieces(QPainter& p);
};

#endif
