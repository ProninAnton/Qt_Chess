#ifndef PAWN_H
#define PAWN_H

#include "figure.h"
#include "chessboard.h"
class Pawn:public Figure
{
public:
    Pawn(QString team,QString type,QGraphicsItem *parent = 0);
    void setImage() override;
    void moves() override;

};

#endif // PAWN_H
