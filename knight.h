#ifndef KNIGHT_H
#define KNIGHT_H

#include "figure.h"
class Knight:public Figure
{
public:
    Knight(QString team,QString type,QGraphicsItem *parent = 0);
    void setImage() override;
    void moves() override;

};

#endif // KNIGHT_H
