#ifndef BISHOP_H
#define BISHOP_H

#include "figure.h"
class Bishop:public Figure
{
public:
    Bishop(QString team, QString type, QGraphicsItem *parent = 0);
    void setImage() override;
    void moves() override;

};


#endif // BISHOP_H
