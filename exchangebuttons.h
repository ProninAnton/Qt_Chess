#ifndef EXCHANGEBUTTONS_H
#define EXCHANGEBUTTONS_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
#include <QGraphicsPixmapItem>
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"

class ExchangeButtons:public QGraphicsPixmapItem
{
public:
    ExchangeButtons(QString name, QPointF point);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString color;
private:
    QGraphicsTextItem *text;
    QString str;
};

#endif // EXCHANGEBUTTONS_H
