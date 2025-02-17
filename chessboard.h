#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "figure.h"
#include "pawn.h"
class ChessBoard
{
public:
    ChessBoard();

    void drawBoxes(int x, int y);

    void drawWhite();
    void drawBlack();

    QList <Figure *> white;
    QList <Figure *> black;

    void addFigure();
};

#endif // CHESSBOARD_H
