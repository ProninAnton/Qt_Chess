#ifndef KING_H
#define KING_H

#include "figure.h"
class King:public Figure
{
public:
    King(QString team,QString type,QGraphicsItem *parent = 0);
    QString rock;
    void setImage() override;
    void findUnSafeLocation();
    void moves() override;
};

#endif // KING_H
