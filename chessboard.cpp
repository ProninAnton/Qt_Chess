#include "chessboard.h"
#include "chessbox.h"
#include "game.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"
extern Game *game;

ChessBoard::ChessBoard()
{
    drawBlack();
    drawWhite();
}
void ChessBoard::drawBoxes(int x,int y)
{
    int dS = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box = new ChessBox();
            game->board[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+dS*j,y+dS*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);
            game->addToScene(box);
        }
    }
}

void ChessBoard::addFigure() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box =game->board[i][j];
            if(i < 2) {
                static int k;
                box->placeFigure(black[k]);
                game->aliveFigure.append(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > 5) {
                static int h;
                box->placeFigure(white[h]);
                game->aliveFigure.append(white[h]);
                game->addToScene(white[h++]);
            }
        }
    }
}

void ChessBoard::drawWhite()
{
    Figure *figure;
    for(int i = 0; i < 8; i++) {
        figure = new Pawn("WHITE","PAWN");
        white.append(figure);
    }
    figure = new Rook("WHITE","ROOK");
    white.append(figure);
    figure = new Knight("WHITE","KNIGHT");
    white.append(figure);
    figure = new Bishop("WHITE","BISHOP");
    white.append(figure);
    figure = new Queen("WHITE","QUEEN");
    white.append(figure);
    figure = new King("WHITE","KING");
    white.append(figure);
    figure = new Bishop("WHITE","BISHOP");
    white.append(figure);
    figure = new Knight("WHITE","KNIGHT");
    white.append(figure);
    figure = new Rook("WHITE","ROOK");
    white.append(figure);
}

void ChessBoard::drawBlack()
{
    Figure *figure;
    figure = new Rook("BLACK","ROOK");
    black.append(figure);
    figure = new Knight("BLACK","KNIGHT");
    black.append(figure);
    figure = new Bishop("BLACK","BISHOP");
    black.append(figure);
    figure = new Queen("BLACK","QUEEN");
    black.append(figure);
    figure = new King("BLACK","KING");
    black.append(figure);
    figure = new Bishop("BLACK","BISHOP");
    black.append(figure);
    figure = new Knight("BLACK","KNIGHT");
    black.append(figure);
    figure = new Rook("BLACK","ROOK");
    black.append(figure);
    for(int i = 0; i < 8; i++) {
        figure = new Pawn("BLACK","PAWN");
        black.append(figure);
    }
}
