#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QList>
#include "chessbox.h"



class Button:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
public:

    Button(QString name, QGraphicsItem * parent = NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    void returnFigure(ChessBox *rise);
    void deleteLogRow(ChessBox *box);
    Figure *figure;
    QGraphicsTextItem *text;
    QList<QString> players, movesFrom, movesTo, srubleno, IsFirstMove;
    int rowOpr(QString row);
    int colOpr(QString col);
    int rows, cols, rowT, colT, rowF, colF;
    QString play, from, to, srub, first, rowTo, colTo, rowFrom, colFrom;
};
#endif // BUTTON_H
