#ifndef QUEEN_H
#define QUEEN_H

#include "figure.h"
class Queen:public Figure
{
public:
    Queen(QString team,QString type,QGraphicsItem *parent = 0);
    void setImage() override;
    void moves() override;

};

#endif // QUEEN_H
