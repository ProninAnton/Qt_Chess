#include "button.h"
#include <QGraphicsTextItem>
#include "game.h"
#include <QBrush>
#include <QDebug>

extern Game *game;
Button::Button(QString name, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    setRect(30,30,200,60);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);

    text = new QGraphicsTextItem(name,this);
    int xPos = text->boundingRect().width()/1.75;
    int yPos = text->boundingRect().height()*1.75;
    text->setPos(xPos,yPos);
    text->setFont(QFont("", 14));
    text->setDefaultTextColor(Qt::green);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (game->table->rowCount()!=0)
    {
    QSqlQuery sql;
    sql.prepare("SELECT player, move_from, move_to, srub, first_move FROM log where gameid = ?");
    sql.addBindValue(game->gameId);
    sql.exec();
    while(sql.next())
    {
    players.append(sql.value(0).toString());
    movesFrom.append(sql.value(1).toString());
    movesTo.append(sql.value(2).toString());
    srubleno.append(sql.value(3).toString());
    IsFirstMove.append(sql.value(4).toString());
    }

    play = players.last();
    from = movesFrom.last();
    to = movesTo.last();
    srub = srubleno.last();
    first = IsFirstMove.last();
    rowTo = to[1];
      colTo = to[0];

      rowT = rowOpr(rowTo);
      colT = colOpr(colTo);

      rowFrom = from[1];
      colFrom = from[0];

      rowF = rowOpr(rowFrom);
      colF = colOpr(colFrom);

             ChessBox *box =game->board[rowF][colF];
             ChessBox *rise = game->board[rowT][colT];
             if (game->specialTurn.count()>0 && game->specialTurn.last()==game->table->rowCount())
             {
                 if (game->specialMove.last() == "EXCHANGE")
                 {
                     rise->currentFigure->setCurrentBox(NULL);
                     game->removeFromScene(rise->currentFigure);
                     game->aliveFigure.removeAll(rise->currentFigure);
                     figure = game->movedFigure.last();
                     QString col = figure->getSide();
                     figure->setVisible(true);
                     figure = game->movedFigure.last();
                     figure->setCurrentBox(rise);
                     figure->getCurrentBox()->setHasFigure(false);
                     figure->setCurrentBox(box);
                     figure->getCurrentBox()->setHasFigure(true,figure);
                     figure->getCurrentBox()->currentFigure = figure;
                     figure->setIsPlaced(true);
                     box->animation(figure);

                     if (srub == "1")
                     {
                        returnFigure(rise);
                     }
                     game->specialTurn.removeLast();
                     game->specialMove.removeLast();
                     game->changeTurn();
                     deleteLogRow(rise);
                     return;
                  }
                 if (game->specialMove.last() == "ROCK_RIGHT")
                 {
                     ChessBox* rookFrom = game->board[box->rowLoc][box->colLoc+1];
                     ChessBox* rookTo = game->board[box->rowLoc][box->colLoc+3];
                     Figure* rook = rookFrom->currentFigure;
                     rookTo->changeBox(rookTo, rook);
                     rookTo->animation(rook);
                 }
                 if (game->specialMove.last() == "ROCK_LEFT")
                 {
                     ChessBox* rookFrom = game->board[box->rowLoc][box->colLoc-1];
                     ChessBox* rookTo = game->board[box->rowLoc][box->colLoc-4];
                     Figure* rook = rookFrom->currentFigure;
                     rookTo->changeBox(rookTo,rook);
                     rookTo->animation(rook);
                 }
                 game->specialTurn.removeLast();
                 game->specialMove.removeLast();
             }
             figure = game->movedFigure.last();
             box->changeBox(box,figure);
             figure->setIsPlaced(true);
             box->animation(figure);


             if (first == "1")
             {
                 figure->firstMove =true;
             }

             if (srub == "1")
             {
                returnFigure(rise);
             }
             deleteLogRow(box);
             game->changeTurn();
    }
}

void Button::returnFigure(ChessBox *rise)
{
    QString col = figure->getSide();
    Figure *returned;
    if (figure->getSide()== "WHITE")
    {
    returned = game->blackRemoved.last();
    }
    else
    {
    returned = game->whiteRemoved.last();
    }
    rise->riseFigure(rise, col);
    rise->animation(returned);
}

void Button::deleteLogRow(ChessBox *box)
{
    QSqlQuery query;
    query.prepare("DELETE FROM log where id = ?");
    query.addBindValue(game->logId.last());
    query.exec();
    game->logId.removeLast();
    game->movedFigure.removeLast();
    int roll = game->table->rowCount();
    game->table->removeRow(roll-1);
    box->checkForCheck();
}

int Button::rowOpr(QString row)
{
    return row.toInt() - 1;
}

int Button::colOpr(QString col)
{
    if (col =="a") return 0;
    if (col =="b") return 1;
    if (col =="c") return 2;
    if (col =="d") return 3;
    if (col =="e") return 4;
    if (col =="f") return 5;
    if (col =="g") return 6;
    //if (col =="h")
        return 7;
}



