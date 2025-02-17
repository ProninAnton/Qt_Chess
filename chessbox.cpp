#include "chessbox.h"
#include "game.h"
#include <QDebug>
#include "king.h"
#include "exchangebuttons.h"

extern Game *game;
ChessBox::ChessBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasFigure(false);
    setFigureColor("NONE");
    currentFigure = NULL;
}

ChessBox::~ChessBox()
{
    delete this;
}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

        if(currentFigure == game->figureToMove && currentFigure){
            currentFigure->mousePressEvent(event);
            return;
        }

        if(game->figureToMove){
            if(this->getFigureColor() == game->figureToMove->getSide())
                return;

            QList <ChessBox *> movLoc = game->figureToMove->moveLocation();
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;
                }
            }

            if(check == 0)
                return;
            // проверка хода на шах
            ChessBox* box = game->board[game->startRow][game->startCol];
            removed = false;
                    if(this->getHasFigure()){
                        this->currentFigure->setIsPlaced(false);
                        this->currentFigure->setCurrentBox(NULL);
                        if(this->currentFigure->getSide() == "WHITE") {
                            game->whiteRemoved.append(this->currentFigure);
                        }
                            else
                            {
                                game->blackRemoved.append(this->currentFigure);
                            }
                        game->aliveFigure.removeAll(this->currentFigure);
                        removed = true;
                    }
                    changeBox(this, game->figureToMove);
                    checkedTeam ="";
                    revision();
                    changeBox(box,game->figureToMove);

                    if (removed == true)
                    {
                        riseFigure(this, game->figureToMove->side);
                    }
                    if (checkedTeam == game->figureToMove->side || checkedTeam == "BOTH")
                    {
                        game->figureToMove = NULL;
                            return;
                    }

                    if (game->figureToMove->figureType == "KING" && (this->rowLoc==0 || this->rowLoc==7) && this->colLoc==6 && box->colLoc==4 && (box->rowLoc==0 || box->rowLoc==7))
                    {
                        ChessBox* transit = game->board[game->startRow][game->startCol+1];
                        changeBox(transit, game->figureToMove);
                        checkedTeam ="";
                        revision();
                        changeBox(box,game->figureToMove);
                        if (checkedTeam == game->figureToMove->side || checkedTeam == "BOTH")
                        {
                            game->figureToMove=NULL;
                            return;
                    }
                    }
                    if (game->figureToMove->figureType == "KING" && (this->rowLoc==0 || this->rowLoc==7) && this->colLoc==2 && box->colLoc==4 && (box->rowLoc==0 || box->rowLoc==7))
                    {
                        ChessBox* transit = game->board[game->startRow][game->startCol-1];
                        changeBox(transit, game->figureToMove);
                        checkedTeam ="";
                        revision();
                        changeBox(box,game->figureToMove);
                        if (checkedTeam == game->figureToMove->side || checkedTeam == "BOTH")
                        {
                            game->figureToMove=NULL;
                            return;
                    }
                    }


            game->figureToMove->decolor();
            IsFirstMove = game->figureToMove->firstMove;
            game->figureToMove->firstMove = false;
            srubleno=false;
            //удаление срубленной фигуры
            if(this->getHasFigure()){
                this->currentFigure->setIsPlaced(false);
                this->currentFigure->setCurrentBox(NULL);
                game->removedFigures(this->currentFigure);
                srubleno=true;
            }

            //ход фигуры на новую клетку
            moveFrom = way();
            game->figureToMove->currentBox->resetOriginalColor();
            changeBox(this, game->figureToMove);
            moveTo = way();

            QSqlQuery logQuery;
            if (game->db.open()) {
            QSqlQuery qMax("select (MAX(id)+1) as max from log");
            qMax.next();
            int logMaxId = qMax.value(0).toInt();
            logQuery.prepare("INSERT INTO log (id, gameid, player, move_from, move_to, move_time, srub, first_move) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
            logQuery.addBindValue(logMaxId);
            logQuery.addBindValue(game->gameId);
            logQuery.addBindValue(game->figureToMove->getSide());
            logQuery.addBindValue(moveFrom);
            logQuery.addBindValue(moveTo);
            time = QTime::currentTime();
            logQuery.addBindValue(time);
            logQuery.addBindValue(srubleno);
            logQuery.addBindValue(IsFirstMove);
            if(!logQuery.exec()) { qDebug() << "fatal error";};
            game->logId.append(logMaxId);
            }
            players.append(game->figureToMove->getSide());
            movesFrom.append(moveFrom);
            movesTo.append(moveTo);
            timesToMove.append(time.toString());

            game->table->setRowCount(game->table->rowCount() + 1);
            addRowTable(game->figureToMove->getSide(),0);
            addRowTable(moveFrom,1);
            addRowTable(moveTo,2);
            addRowTable(time.toString(),3);
            game->movedFigure.append(game->figureToMove);
            animation(game->figureToMove);

            //Превращение пешки в другую фигуру
            if ((this->rowLoc==7 || this->rowLoc==0) && game->figureToMove->figureType=="PAWN")
            {
                game->startRow = this->rowLoc;
                game->startCol = this->colLoc;
                this->currentFigure->setIsPlaced(false);
                this->currentFigure->setCurrentBox(NULL);
                game->removedFigures(this->currentFigure);
                this->currentFigure->setVisible(false);

                for (int i=0; i<8;i++)
                {
                    for (int j=0; j<8; j++)
                    {
                         box = game->board[i][j];
                         box->setEnabled(false);
                    }
                }
                QList <Figure *> pList = game->aliveFigure;
                for(int i = 0; i < pList.length(); i++ )
                {
                    pList[i]->setEnabled(false);
                }
                game->text->setVisible(true);
                for (int i=0; i<game->exchange.length(); i++)
                {
                    game->exchange[i]->setVisible(true);
                    game->exchange[i]->setEnabled(true);
                    if (this->rowLoc==0)
                    {
                        game->exchange[i]->color="WHITE";
                    }
                    else
                         game->exchange[i]->color="BLACK";
                }
                if (this->rowLoc==0)
                {
                    game->exchange[0]->setPixmap(QPixmap(":/wN.png"));
                    game->exchange[1]->setPixmap(QPixmap(":/wR.png"));
                    game->exchange[2]->setPixmap(QPixmap(":/wQ.png"));
                    game->exchange[3]->setPixmap(QPixmap(":/wB.png"));
                }
                else
                {
                    game->exchange[0]->setPixmap(QPixmap(":/bN.png"));
                    game->exchange[1]->setPixmap(QPixmap(":/bR.png"));
                    game->exchange[2]->setPixmap(QPixmap(":/bQ.png"));
                    game->exchange[3]->setPixmap(QPixmap(":/bB.png"));
                }
                game->specialTurn.append(game->table->rowCount());
                game->specialMove.append("EXCHANGE");
                game->figureToMove=NULL;
                return;
            }

            //Рокировки
            if (game->figureToMove->figureType == "KING" && (this->rowLoc==0 || this->rowLoc==7) && this->colLoc==6 && box->colLoc==4 && (box->rowLoc==0 || box->rowLoc==7))
            {
                    ChessBox* rookFrom = game->board[box->rowLoc][box->colLoc+3];
                    ChessBox* rookTo = game->board[box->rowLoc][box->colLoc+1];
                    Figure* rook = rookFrom->currentFigure;
                    changeBox(rookTo,rook);
                    animation(rook);
                    game->specialTurn.append(game->table->rowCount());
                    game->specialMove.append("ROCK_RIGHT");
        }
            if (game->figureToMove->figureType == "KING" && (this->rowLoc==0 || this->rowLoc==7) && this->colLoc==2 && box->colLoc==4 && (box->rowLoc==0 || box->rowLoc==7))
            {
                    ChessBox* rookFrom = game->board[box->rowLoc][box->colLoc-4];
                    ChessBox* rookTo = game->board[box->rowLoc][box->colLoc-1];
                    Figure* rook = rookFrom->currentFigure;
                    changeBox(rookTo,rook);
                    animation(rook);
                    game->specialTurn.append(game->table->rowCount());
                    game->specialMove.append("ROCK_LEFT");
        }
            game->changeTurn();
            checkForCheck();
            if (game->check->isVisible()==true)
            {
                checkForMate(game->figureToMove->side);
            }
            else {
                checkForMate("NONE");
            }
            game->figureToMove = NULL;
        }
        else if(this->getHasFigure())
        {
            this->currentFigure->mousePressEvent(event);
        }
}

void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void ChessBox::placeFigure(Figure *figure)
{
    figure->setPos(x()+50- figure->pixmap().width()/2  ,y()+50-figure->pixmap().width()/2);
    figure->setCurrentBox(this);
    setHasFigure(true,figure);
    currentFigure = figure;
}

QString ChessBox::way()
{
    QString move;
    int rT, cT;
    QString row, col;
                rT = game->figureToMove->getCurrentBox()->rowLoc;
                cT = game->figureToMove->getCurrentBox()->colLoc;

                while (row==NULL)
                {
                    if (rT ==0){row="1";break;}
                    if (rT ==1){row="2";break;}
                    if (rT ==2){row="3";break;}
                    if (rT ==3){row="4";break;}
                    if (rT ==4){row="5";break;}
                    if (rT ==5){row="6";break;}
                    if (rT ==6){row="7";break;}
                    if (rT ==7){row="8";break;}
                }
                while (col==NULL)
                {
                    if (cT ==0){col="a";break;}
                    if (cT ==1){col="b";break;}
                    if (cT ==2){col="c";break;}
                    if (cT ==3){col="d";break;}
                    if (cT ==4){col="e";break;}
                    if (cT ==5){col="f";break;}
                    if (cT ==6){col="g";break;}
                    if (cT ==7){col="h";break;}
                }
                move = col + row;
                return move;
}


void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}

void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

bool ChessBox::getHasFigure()
{
    return hasFigure;
}

void ChessBox::setHasFigure(bool value, Figure *figure)
{
    hasFigure = value;
    if(value)
        setFigureColor(figure->getSide());
    else
        setFigureColor("NONE");
}

void ChessBox::checkForCheck()
{
    int c = 0;
    QList <Figure *> pList = game->aliveFigure;
    for(int i = 0; i < pList.length(); i++ ) {
        King * p = dynamic_cast<King *> (pList[i]);
        if(p){
            continue;
        }
        pList[i]->moves();
        pList[i]->decolor();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(int j = 0; j < bList.length(); j ++) {
            King * p = dynamic_cast<King *> (bList[j]->currentFigure);
            if(p) {
                if(p->getSide() == pList[i]->getSide())
                    continue;
                bList[j]->setColor(Qt::blue);
                pList[i]->getCurrentBox()->setColor(Qt::red);
                if(!game->check->isVisible())
                    game->check->setVisible(true);
                c++;
            }
        }
    }
    if(!c){
        game->check->setVisible(false);
        for(size_t i = 0,n=pList.size(); i < n; i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }
}

void ChessBox::checkForMate(QString color)
{
    int c = 0;
    QList <Figure *> pList = game->aliveFigure;
    for (int i=0; i<pList.length();i++)
        {
         if (pList[i]->side != game->figureToMove->side)
        {
        pList[i]->location.clear();
        pList[i]->moves();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(int j = 0 ; j < bList.size(); j ++)
        {
            ChessBox* boxFrom = pList[i]->currentBox;
            ChessBox* boxTo = bList[j];
            removed = false;
            if(boxTo->getHasFigure()){
                boxTo->currentFigure->setIsPlaced(false);
                boxTo->currentFigure->setCurrentBox(NULL);
                if(boxTo->currentFigure->getSide() == "WHITE") {
                    game->whiteRemoved.append(boxTo->currentFigure);
                }
                    else
                    {
                        game->blackRemoved.append(boxTo->currentFigure);
                    }
                game->aliveFigure.removeAll(boxTo->currentFigure);
                removed = true;
            }
            changeBox(boxTo,pList[i]);
            checkedTeam ="";
            revision();

            if (checkedTeam == "" || checkedTeam == game->figureToMove->side)
            {
               c++;
            }
            changeBox(boxFrom,pList[i]);

            if (removed == true)
            {
                riseFigure(boxTo, pList[i]->side);
             }
             if (c>0)
                 break;
        }
        }
        if (c>0)
            break;
    }
    if (c==0)
        game->gameOver(color);
}

void ChessBox::revision()
{
    int c = 0;
    Figure* kingBlack;
    Figure* kingWhite;
    QList <Figure *> pList = game->aliveFigure;
    for (int i=0; i<pList.length();i++)
    {
        pList[i]->decolor();
        pList[i]->location.clear();
        pList[i]->moves();
    }
    for (int i=0; i< pList.length(); i++)
    {
        if (pList[i]->figureType == "KING")
      {
            kingBlack = pList[i];
            break;
      }
    }

    for (int i=pList.length()-1; i> 0; i--)
    {
        if (pList[i]->figureType == "KING")
      {
            kingWhite = pList[i];
            break;
      }
    }
    for(int i = 0; i < pList.size(); i++ ) {
        pList[i]->moves();
        pList[i]->decolor();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(int j = 0 ; j < bList.size(); j ++) {
        if (kingBlack->currentBox == bList[j] && kingBlack->side != pList[i]->side)
                {
                bList[j]->setColor(Qt::blue);
                pList[i]->getCurrentBox()->setColor(Qt::red);
                checkedTeam = kingBlack->getSide();
                c++;
            }
        }
    }
    if(!c){
        checkedTeam="";
        for(int i = 0; i < pList.length(); i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }
    for(int i = 0; i < pList.size(); i++ ) {
        pList[i]->moves();
        pList[i]->decolor();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(int j = 0 ; j < bList.size(); j ++) {
        if (kingWhite->currentBox == bList[j] && kingWhite->side != pList[i]->side)
                {
                bList[j]->setColor(Qt::blue);
                pList[i]->getCurrentBox()->setColor(Qt::red);
                if (checkedTeam != "BLACK")
                checkedTeam = kingWhite->getSide();
                else checkedTeam = "BOTH";
                c++;
            }
        }
    }
    if(!c){
        checkedTeam="";
        for(int i = 0; i < pList.length(); i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }
}

void ChessBox::animation(Figure *figure)
{
    QTimeLine *timer = new QTimeLine(1000);
    timer->setFrameRange(0, 100);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(figure);
    animation->setTimeLine(timer);
    animation->setPosAt(1, QPointF(310+100*figure->currentBox->colLoc  ,60+100*figure->currentBox->rowLoc));
    timer->start();
}

void ChessBox::changeBox(ChessBox *box, Figure *figure)
{
    figure->getCurrentBox()->setHasFigure(false);
    figure->getCurrentBox()->currentFigure = NULL;
    figure->setCurrentBox(box);
    figure->getCurrentBox()->setHasFigure(true,figure);
    figure->getCurrentBox()->currentFigure = figure;
}

void ChessBox::riseFigure(ChessBox *box, QString side)
{
    if(side == "WHITE")
    {
        Figure *black = game->blackRemoved.last();
        box->setHasFigure(true, black);
        black->setIsPlaced(true);
        black->setCurrentBox(box);
        box->currentFigure = black;
        game->blackRemoved.removeLast();
        game->aliveFigure.append(black);
    }
    else
    {
        Figure *white = game->whiteRemoved.last();
        box->setHasFigure(true, white);
        white->setIsPlaced(true);
        white->setCurrentBox(box);
        box->currentFigure = white;
        game->whiteRemoved.removeLast();
        game->aliveFigure.append(white);
    }
}

QString ChessBox::getFigureColor()
{
    return FigureColor;
}

void ChessBox::addRowTable(QString rowText, int column)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(rowText);
    game->table->setItem(game->table->rowCount()-1,column,item);
}

void ChessBox::setFigureColor(QString value)
{
    FigureColor = value;
}
