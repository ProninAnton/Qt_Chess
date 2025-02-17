#include "knight.h"
#include "game.h"
extern Game *game;

Knight::Knight(QString team, QString type, QGraphicsItem *parent):Figure(team,type,parent)
{
    setImage();
}

void Knight::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/wN.png"));
    else
        setPixmap(QPixmap(":/bN.png"));
}



void Knight::moves()
{
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    int i ,j;
    QString team  = this->getSide();


    i = row - 2;
    j = col - 1;
    if(i >=0 && j>=0 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row - 2;
    j = col + 1;
    if(i >=0 && j<=7 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row + 2;
    j = col - 1;
    if(i <= 7 && j>=0 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row + 2;
    j = col + 1;
    if(i <=7 && j<=7 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row - 1;
    j = col - 2;
    if(i >=0 && j>=0 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row + 1;
    j = col - 2;
    if(i <=7 && j>=0 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row - 1;
    j = col + 2;
    if(i >=0 && j<=7 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }

    i = row + 1;
    j = col +  2;
    if(i <=7 && j<=7 && (game->board[i][j]->getFigureColor() != team))
    {
        location.append(game->board[i][j]);
            location.last()->setColor(Qt::red);
    }
}
