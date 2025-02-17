#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include "chessbox.h"
#include <QGraphicsSceneMouseEvent>
#include <QString>

class ChessBox;
class Figure:public QGraphicsPixmapItem
{
public:
    Figure(QString team = "", QString type="",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(ChessBox *box);
    ChessBox *getCurrentBox() ;

    QString getSide() ;
    void setSide( QString value);
    virtual void setImage() = 0;
    void decolor();

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <ChessBox *> moveLocation();
    virtual void moves() = 0;
    bool boxSetting(ChessBox *box);
    QString figureType;
    QString side;
    bool firstMove;
    ChessBox *currentBox;
    QList <ChessBox *> location;
protected:

    bool isPlaced;


};

#endif // FIGURE_H
