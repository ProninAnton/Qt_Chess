#include "figure.h"
#include "game.h"
#include "king.h"


extern Game *game;

Figure::Figure(QString team, QString type, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
    figureType = type;
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Отмена выбора фигуры
    if(this == game->figureToMove){
        game->figureToMove->getCurrentBox()->resetOriginalColor();
        game->figureToMove->decolor();
        game->figureToMove = NULL;
       return;
    }

    if((!getIsPlaced() )|| ( (game->getTurn() != this->getSide())&& (!game->figureToMove)) )
        return;
    //выбор фигуры
    if(!game->figureToMove){
        game->figureToMove = this;
        game->figureToMove->getCurrentBox()->setColor(Qt::green);
        game->figureToMove->moves();
        game->startRow = this->currentBox->rowLoc;
        game->startCol = this->currentBox->colLoc;
    }


    else if(this->getSide() != game->figureToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }
}

void Figure::setCurrentBox(ChessBox *box)
{

    currentBox = box;
}

ChessBox *Figure::getCurrentBox()
{
    return currentBox;
}

QString Figure::getSide()
{
    return side;
}

void Figure::setSide( QString value)
{
    side = value;
}

bool Figure::getIsPlaced()
{
    return isPlaced;
}

void Figure::setIsPlaced(bool value)
{
    isPlaced = value;

}
QList<ChessBox *> Figure::moveLocation()
{
    return location;
}
void Figure::decolor()
{
    for(int i = 0; i < location.length();i++) {
         location[i]->resetOriginalColor();
    }
}

bool Figure::boxSetting(ChessBox *box)
{
    if(box->getHasFigure()) {
        King *k = dynamic_cast<King*>(location.last()->currentFigure);
        if(k){
            box->setColor(Qt::blue);
        }
        else
            box->setColor(Qt::red);
        return true;
    }
    else
        location.last()->setColor(Qt::red);
    return false;
}
