#include "GameWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>

static const int MAX_MOVES=200;

GameWindow::GameWindow(QWidget* parent)
: QMainWindow(parent),
  dqn(65,300,300,200,0.0001f),
  replay(50000),
  currentPlayer(::PieceColor::White),
  dragging(false),
  dragStartRow(-1),
  dragStartCol(-1),
  tileSize(80),
  gamma(0.99f),
  epsilon(0.3f),
  stepCount(0),
  targetUpdateFreq(20)
{
    setFixedSize(8*tileSize, 8*tileSize);

    board.initializeStandard();

    loadPieceImages();

    // link the replay to the DQN so addRewardToColor() modifies the same buffer
    dqn.setReplay(&replay);

    // load any saved model
    if (std::filesystem::exists("myOnlineNet.pt")) {
        dqn.load("myOnlineNet.pt");
    }

    srand(time(nullptr));
}

// A new helper to load each piece sprite into pieceImages:
void GameWindow::loadPieceImages()
{
    QString pathPrefix = QDir::currentPath() + "/resources/";
    qDebug() << "Current working directory: " << pathPrefix;

    QStringList pieceNames = {
        "white_pawn", "white_rook", "white_knight", "white_bishop",
        "white_queen", "white_king", "black_pawn", "black_rook",
        "black_knight", "black_bishop", "black_queen", "black_king"
    };

    for (const QString& name : pieceNames) {
        QString path = pathPrefix + name + ".png";
        pieceImages[name] = QPixmap(path);

        if (pieceImages[name].isNull()) {
            qDebug() << "Failed to load: " << path;
        } else {
            qDebug() << "Loaded successfully: " << path;
        }
    }
}
GameWindow::~GameWindow()
{
    // save model
    dqn.save("myOnlineNet.pt");
}

void GameWindow::initBoard()
{
    board.initializeStandard();
    currentPlayer= ::PieceColor::White;
    dragging=false;
}

void GameWindow::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    drawBoard(p);
    drawPieces(p);
}

void GameWindow::drawBoard(QPainter& p)
{
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
            bool dark= ((r+c)%2==1);
            QColor color= dark? QColor(150,150,150): QColor(255,255,255);
            p.fillRect(c*tileSize, r*tileSize, tileSize, tileSize, color);
        }
    }
}

void GameWindow::drawPieces(QPainter& p)
{
    for(int row=0; row<8; row++){
        for(int col=0; col<8; col++){
            Piece* piece = board.squares[row][col];
            if(piece){
                QString colorStr = (piece->color == ::PieceColor::White) ? "white_" : "black_";
                QString typeStr;
                switch(piece->type){
                    case PieceType::Pawn:   typeStr="pawn"; break;
                    case PieceType::Rook:   typeStr="rook"; break;
                    case PieceType::Knight: typeStr="knight"; break;
                    case PieceType::Bishop: typeStr="bishop"; break;
                    case PieceType::Queen:  typeStr="queen"; break;
                    case PieceType::King:   typeStr="king"; break;
                }
                QString key = colorStr + typeStr;

                // retrieve the pixmap from our map
                QPixmap pix = pieceImages[key];
                if(!pix.isNull()){
                    // draw the piece image scaled to tileSize
                    // x = col*tileSize, y = row*tileSize
                    p.drawPixmap(col*tileSize, row*tileSize, tileSize/2, tileSize/2, pix);
                } else {
                    // fallback, just draw text if image isn't found
                    p.setPen(Qt::red);
                    p.drawText(col*tileSize + tileSize/2 - 5,
                               row*tileSize + tileSize/2 + 5,
                               "??");
                }
            }
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton){
        dragging=true;
        dragStartCol= event->x()/tileSize;
        dragStartRow= event->y()/tileSize;
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton && dragging){
        int endCol= event->x()/tileSize;
        int endRow= event->y()/tileSize;

        Move mv;
        mv.startRow= dragStartRow;
        mv.startCol= dragStartCol;
        mv.endRow= endRow;
        mv.endCol= endCol;
        mv.isPromotion=false;

        if(board.isValidMove(mv, currentPlayer)){
            Piece* movingPiece = board.squares[mv.startRow][mv.startCol];
            if (movingPiece && movingPiece->type == PieceType::Pawn) {
                bool whitePromoting = (movingPiece->color == PieceColor::White && endRow == 0);
                bool blackPromoting = (movingPiece->color == PieceColor::Black && endRow == 7);
                if (whitePromoting || blackPromoting) {
                    // show the dialog
                    mv.isPromotion = true;
                    mv.promotionType = showPromotionDialog();
                }
            }
            // state before
            auto before= boardToInput(board, currentPlayer);

            float reward=0.f;
            Piece* captured= board.squares[mv.endRow][mv.endCol];
            if(captured && captured->color!= currentPlayer){
                reward+= pieceValue(captured->type);
                dqn.addRewardToColor(captured->color,-pieceValue(captured->type));
            }

            board.makeMove(mv, currentPlayer);

            // check promotion
            Piece* moved= board.squares[mv.endRow][mv.endCol];
            if(moved && moved->type==PieceType::Pawn){
                if((moved->color==::PieceColor::White && mv.endRow==0)||
                   (moved->color==::PieceColor::Black && mv.endRow==7)){
                    reward+=2.f; // small bonus
                }
            }

            bool done= board.isGameOver(currentPlayer);
            bool insuff= board.isInsufficientMaterial();
            if(done||insuff){
                bool inCheck= board.isInCheck(currentPlayer);
                if(inCheck) reward+=100.f; // checkmate
                else reward+=10.f;        // stalemate/insufficient
            }

            auto after= boardToInput(board, (currentPlayer==::PieceColor::White? ::PieceColor::Black: ::PieceColor::White));
            storeTransition(before, currentPlayer, mv, reward, after, (done||insuff));

            if(done||insuff){
                addRewardToLosingSide(currentPlayer, -100.f);
                trainFromReplay();

                QMessageBox::information(this,"Game Over","Checkmate/stalemate/insufficient!");
                initBoard();
            } else {
                currentPlayer= (currentPlayer==::PieceColor::White? ::PieceColor::Black: ::PieceColor::White);
                trainFromReplay();

                if(currentPlayer==::PieceColor::Black){
                    doAIMove();
                }
            }
        }
        dragging=false;
    }
    update();
}

void GameWindow::doAIMove()
{
    auto legal= board.generateLegalMoves(currentPlayer);
    if(legal.empty()){
        // check if it's checkmate or stalemate
        bool inCheck = board.isInCheck(currentPlayer);
        if(inCheck) {
            // That means the currentPlayer (the AI) is checkmated
            // so the other side is the winner
            QMessageBox::information(this, "Game Over", "AI is checkmated!");
            // reward logic: 
            // currentPlayer is the loser => -100
            addRewardToLosingSide(currentPlayer, -100.f);
            // or you can give +100 to the other side if you like
            PieceColor opponent = (currentPlayer == PieceColor::White) ? PieceColor::Black : PieceColor::White;
            addRewardToLosingSide(opponent, +100);
        } else {
            // That’s a stalemate => a draw
            QMessageBox::information(this, "Game Over", "Stalemate / draw!");
            // If you like, give both sides a small positive or zero
            // For example:
            addRewardToLosingSide(PieceColor::White, +10);
            addRewardToLosingSide(PieceColor::Black, +10);
            // or no negative
        }
        // do a final train if you want:
        trainFromReplay();

        // either reset board or exit
        // e.g.:
        // initBoard();
        // or
        dqn.save("myOnlineNet.pt");
        QApplication::quit();
        return;
    }

    auto before= boardToInput(board, currentPlayer);

    auto qT= dqn.predict(before);
    float* data= qT.data_ptr<float>();

    bool doRand= (((double)rand()/RAND_MAX) < epsilon);
    Move best= legal[0];
    float bestQ=-99999.f;
    if(doRand){
        int idx= rand()% legal.size();
        best= legal[idx];
    } else {
        for(auto& mv: legal){
            int idx= moveToIndex(mv);
            if(data[idx]> bestQ){
                bestQ= data[idx];
                best= mv;
            }
        }
    }

    float reward=0.f;
    Piece* captured= board.squares[best.endRow][best.endCol];
    if(captured && captured->color!= currentPlayer){
        reward+= pieceValue(captured->type);
        dqn.addRewardToColor(captured->color,-pieceValue(captured->type));
    }

    board.makeMove(best, currentPlayer);

    bool done= board.isGameOver(currentPlayer);
    bool insuff= board.isInsufficientMaterial();
    if(done||insuff){
        bool inCheck= board.isInCheck(currentPlayer);
        if(inCheck) reward+=100.f;
        else reward+=10.f;
    }

    auto after= boardToInput(board, (currentPlayer==::PieceColor::White? ::PieceColor::Black: ::PieceColor::White));
    storeTransition(before, currentPlayer, best, reward, after, (done||insuff));

    if(done||insuff){
        addRewardToLosingSide(currentPlayer, -100.f);
        trainFromReplay();
        QMessageBox::information(this,"Game Over","AI checkmate/stalemate/insufficient!");
        initBoard();
    } else {
        currentPlayer= (currentPlayer==::PieceColor::White? ::PieceColor::Black: ::PieceColor::White);
        trainFromReplay();
    }
    update();
}

PieceType GameWindow::showPromotionDialog()
{
    // We'll present a simple list of piece types to choose from
    std::cout<<"showed the promotion dialog box"<<std::endl;
    QStringList items;
    items << "Queen" << "Rook" << "Bishop" << "Knight";

    bool ok = false;
    QString choice = QInputDialog::getItem(
        this, 
        "Promote Pawn", 
        "Choose piece to promote to:",
        items, 
        /*currentIndex=*/0, 
        /*editable=*/false,
        &ok
    );
    if (!ok) {
        // user canceled or closed => default to Queen
        return PieceType::Queen;
    }
    if (choice == "Rook")   return PieceType::Rook;
    if (choice == "Bishop") return PieceType::Bishop;
    if (choice == "Knight") return PieceType::Knight;
    // fallback
    return PieceType::Queen;
}

void GameWindow::trainFromReplay()
{
    if(replay.size()<16) return;
    std::vector<Transition> batch;
    for(int i=0;i<16;i++){
        batch.push_back(replay.sample());
    }
    dqn.trainBatch(batch, gamma);

    stepCount++;
    if(stepCount>= targetUpdateFreq){
        dqn.updateTarget();
        stepCount=0;
    }
}

std::vector<float> GameWindow::boardToInput(const Board& b, ::PieceColor c)
{
    std::vector<float> input(65,0.f);
    for(int r=0;r<8;r++){
        for(int col=0; col<8; col++){
            auto pc= b.squares[r][col];
            int idx= r*8 + col;
            if(pc){
                float val=0.f;
                switch(pc->type){
                    case PieceType::Pawn: val=1.f; break;
                    case PieceType::Knight: val=3.f; break;
                    case PieceType::Bishop: val=3.25f; break;
                    case PieceType::Rook: val=5.f; break;
                    case PieceType::Queen: val=9.f; break;
                    case PieceType::King: val=100.f; break;
                }
                if(pc->color==::PieceColor::Black) val= -val;
                input[idx]= val;
            } else {
                input[idx]=0.f;
            }
        }
    }
    input[64]= (c==::PieceColor::White? 1.f: 0.f);
    return input;
}

// naive hashing
int GameWindow::moveToIndex(const Move& mv)
{
    int val= (mv.startRow<<9) ^ (mv.startCol<<6) ^ (mv.endRow<<3) ^ (mv.endCol);
    if(mv.isPromotion){
        val ^= ((int)mv.promotionType + 999);
    }
    if(val<0) val=-val;
    return val % MAX_MOVES;
}

float GameWindow::pieceValue(PieceType pt)
{
    switch(pt){
        case PieceType::Pawn: return 1.f;
        case PieceType::Knight:
        case PieceType::Bishop: return 3.f;
        case PieceType::Rook: return 5.f;
        case PieceType::Queen: return 9.f;
        case PieceType::King: return 100.f;
    }
    return 0.f;
}

void GameWindow::storeTransition(const std::vector<float>& before, ::PieceColor color,
                                 const Move& mv, float reward,
                                 const std::vector<float>& after, bool done)
{
    int actIdx= moveToIndex(mv);
    Transition t;
    t.state= before;
    t.action= actIdx;
    t.reward= reward;
    t.nextState= after;
    t.done= done;
    t.moveColor= toPieceColor(color);

    replay.add(t);
}

// We call DQN's addRewardToColor now:
void GameWindow::addRewardToLosingSide(::PieceColor loser, float negativeReward)
{
    dqn.addRewardToColor(toPieceColor(loser), negativeReward);
}
