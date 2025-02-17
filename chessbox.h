#ifndef CHESSBOX_H
#define CHESSBOX_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QTime>
#include <QList>
#include "figure.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class Figure;
class ChessBox:public QGraphicsRectItem
{
public:

    ChessBox(QGraphicsItem *parent=0);
    ~ChessBox();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void placeFigure(Figure *figure);
    QList <Figure *> whiteDead;
    QList <Figure *> blackDead;
    QString way();

    void setColor(QColor color);
    void resetOriginalColor();
    void setOriginalColor(QColor value);
    bool getHasFigure();
    void setHasFigure(bool value,Figure *figure = 0);
    void checkForCheck();
    void checkForMate(QString color);
    void setFigureColor(QString value);
    void animation(Figure* figure);
    void changeBox(ChessBox* box, Figure* figure);
    void riseFigure(ChessBox* box, QString side);
    QString getFigureColor() ;
    bool hasFigure;

    int rowLoc;
    int colLoc;

    Figure * currentFigure;

private:
    void revision();

    void addRowTable(QString rowText, int column);
    QBrush brush;
    QColor originalColor;

    QString checkedTeam;
    bool srubleno, IsFirstMove, removed;
    QString FigureColor;
    QTime time;
    QString id;
    QList<QString> players, movesFrom, movesTo, timesToMove;
    QString moveTo, moveFrom;

};

#endif // CHESSBOX_H
