#ifndef ROOK_H
#define ROOK_H

#include "figure.h"
class Rook:public Figure
{
public:
    Rook(QString team, QString type, QGraphicsItem *parent = 0);
    void setImage() override;
    void moves() override;

};

#endif // ROOK_H
