#include "pawn.h"
#include "game.h"
#include <typeinfo>
#include "queen.h"
extern Game * game;
Pawn::Pawn(QString team, QString type,QGraphicsItem *parent):Figure(team,type,parent)
{
    setImage();
    firstMove = true;
}

void Pawn::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/wP.png"));
    else
        setPixmap(QPixmap(":/bP.png"));
}



void Pawn::moves()
{
    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;



    if(this->getSide() == "WHITE")  {

        if(col > 0 && row > 0 && game->board[row-1][col-1]->getFigureColor() == "BLACK") {
            location.append(game->board[row-1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row > 0 && game->board[row-1][col+1]->getFigureColor() == "BLACK") {
            location.append(game->board[row-1][col+1]);
            boxSetting(location.last());
        }
        if(row>0 && (!game->board[row-1][col]->getHasFigure())) {
            location.append(game->board[row-1][col]);
            boxSetting(location.last());
            if(firstMove && !game->board[row-2][col]->getHasFigure()){
                location.append(game->board[row-2][col]);
                boxSetting(location.last());
            }
        }

        }


     if(this->getSide() == "BLACK")  {
        if(col > 0 && row < 7 && game->board[row+1][col-1]->getFigureColor() == "WHITE") {
            location.append(game->board[row+1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row <  7 && game->board[row+1][col+1]->getFigureColor() == "WHITE") {
            location.append(game->board[row+1][col+1]);
            boxSetting(location.last());
        }
        if(row<7 && (!game->board[row+1][col]->getHasFigure())) {
            location.append(game->board[row+1][col]);
            boxSetting(location.last());
            if(firstMove && !game->board[row+2][col]->getHasFigure()){
                location.append(game->board[row+2][col]);
                boxSetting(location.last());
            }

        }

    }

}
