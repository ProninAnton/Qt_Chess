#include "king.h"
#include "game.h"
#include "pawn.h"
#include "rook.h"
extern Game *game;
extern Rook *rook;
King::King(QString team, QString type, QGraphicsItem *parent):Figure(team,type,parent)
{
    setImage();
}

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/wK.png"));
    else
        setPixmap(QPixmap(":/bK.png"));
}


void King::moves()
{

    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

        if(col > 0 && row > 0 && !(game->board[row-1][col-1]->getFigureColor() == team)) {
            location.append(game->board[row-1][col-1]);
            game->board[row-1][col-1]->setColor(Qt::red);

        }
        if(col < 7 && row > 0 && !(game->board[row-1][col+1]->getFigureColor() == team)) {
            location.append(game->board[row-1][col+1]);
            game->board[row-1][col+1]->setColor(Qt::red);

        }
        if(row>0 && !(game->board[row-1][col]->getFigureColor() == team)) {
            location.append(game->board[row-1][col]);
            game->board[row-1][col]->setColor(Qt::red);

        }
        if(row<7 && !(game->board[row+1][col]->getFigureColor() == team)) {
            location.append(game->board[row+1][col]);
            game->board[row+1][col]->setColor(Qt::red);

        }
        if(col>0 && !(game->board[row][col-1]->getFigureColor() == team)) {
            location.append(game->board[row][col-1]);
            game->board[row][col-1]->setColor(Qt::red);

        }
        if(col<7 && !(game->board[row][col+1]->getFigureColor() == team)) {
            location.append(game->board[row][col+1]);
            game->board[row][col+1]->setColor(Qt::red);

        }
        if(col > 0 && row < 7  && !(game->board[row+1][col-1]->getFigureColor() == team)) {
            location.append(game->board[row+1][col-1]);
            game->board[row+1][col-1]->setColor(Qt::red);

        }
        if(col < 7 && row < 7 && !(game->board[row+1][col+1]->getFigureColor() == team)) {
            location.append(game->board[row+1][col+1]);
            game->board[row+1][col+1]->setColor(Qt::red);
        }

        if (firstMove==true && game->board[row][col+1]->hasFigure == false && game->board[row][col+2]->hasFigure == false && game->board[row][col+3]->getFigureColor() == team && game->board[row][col+3]->currentFigure->firstMove==true)
        {
            location.append(game->board[row][col+2]);
            game->board[row][col+2]->setColor(Qt::red);
        }
        if (firstMove==true && game->board[row][col-1]->hasFigure == false && game->board[row][col-2]->hasFigure == false && game->board[row][col-3]->hasFigure == false && game->board[row][col-4]->getFigureColor() == team && game->board[row][col-4]->currentFigure->firstMove==true)
        {
            location.append(game->board[row][col-2]);
            game->board[row][col-2]->setColor(Qt::red);
        }
            findUnSafeLocation();
}



void King::findUnSafeLocation() {
    QList <Figure *> pList = game->aliveFigure;
    for(int i = 0; i < pList.length(); i++) {

        if(pList[i]->getSide() != this->getSide())
        {
            QList <ChessBox *> bList = pList[i]->moveLocation();

            for(int j = 0; j < bList.length(); j++) {
                Pawn *c = dynamic_cast<Pawn *> (pList[i]) ;
                if(c)
                    continue;
                for(size_t k = 0, n = location.size(); k < n; k++) {
                   if(bList[j] == location [k]) {
                       location[k]->setColor(Qt::blue);
                   }
                }
            }
        }
    }
}
