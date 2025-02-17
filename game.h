#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chessboard.h>
#include "figure.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTime>
#include <QTableWidget>
#include "exchangebuttons.h"
#include "button.h"
class Game:public QGraphicsView
{
    Q_OBJECT
public:

    Game(QWidget *parent = 0);

    void drawChessBoard();
    void removedFigures(Figure *figure);
    void gameOver(QString winCol);
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
    void setTurn( QString value);
    void changeTurn();
    Figure *figureToMove;
    QString getTurn() ;

    QSqlDatabase db;
    ChessBox *board[8][8];
    QGraphicsTextItem *check;
    QGraphicsTextItem *text;
    QTableWidget *table;
    QList <Figure *> aliveFigure;
    QList <Figure *> movedFigure;
    QList <Figure *> whiteRemoved;
    QList <Figure *> blackRemoved;
    QList <ChessBox *> specialBox;
    QList <int> logId;
    QString winCol;
    int otstup;
    int gameId;
    QGraphicsScene *gameScene;
    int startRow ,startCol;
    Button *but;
    QList <ExchangeButtons *> exchange;
    QList <QString> specialMove;
    QList <int> specialTurn;

public slots:
    void start();
private:
    ExchangeButtons * excKnight;
    ExchangeButtons * excRook;
    ExchangeButtons * excQueen;
    ExchangeButtons * excBishop;
    QGraphicsRectItem *field;
    QString turn;
    ChessBoard *chess;
    QGraphicsTextItem * turnDisplay;
    QTime time;
    void drawField(int x, int y);
    void animation(Figure *figure, QPointF point);
};

#endif // GAME_H
