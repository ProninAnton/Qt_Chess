#include "exchangebuttons.h"
#include "chessbox.h"
#include "game.h"
#include "figure.h"
extern Game *game;

ExchangeButtons::ExchangeButtons(QString name, QPointF point)
{
    setPos(point);
    str = name;
}

void ExchangeButtons::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ChessBox* box = game->board[game->startRow][game->startCol];
    Figure *figure;
    if (str == "KNIGHT")
    {
    figure = new Knight(color, str);
    }
    if (str == "QUEEN")
    {
    figure = new Queen(color, str);
    }
    if (str == "ROOK")
    {
    figure = new Rook(color, str);
    }
    if (str == "BISHOP")
    {
    figure = new Bishop(color, str);
    }
    box->placeFigure(figure);
    game->aliveFigure.append(figure);
    game->addToScene(figure);
    game->text->setVisible(false);
    for (int i=0; i<game->exchange.length(); i++)
    {
        game->exchange[i]->setVisible(false);
        game->exchange[i]->setEnabled(false);
    }
    for (int i=0; i<8;i++)
    {
        for (int j=0; j<8; j++)
        {
             box = game->board[i][j];
             box->setEnabled(true);
        }
    }
    QList <Figure *> pList = game->aliveFigure;
    for(int i = 0; i < pList.length(); i++ )
    {
        pList[i]->setEnabled(true);
    }
    box->checkForCheck();
    if (game->check->isVisible())
    {
        box->checkForMate(color);
    }
    game->changeTurn();
}
