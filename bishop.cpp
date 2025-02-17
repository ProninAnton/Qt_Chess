#include "bishop.h"
#include <QDebug>
#include "game.h"
extern Game *game;

Bishop::Bishop(QString team, QString type, QGraphicsItem *parent):Figure(team,type,parent)
{
    setImage();
}

void Bishop::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/wB.png"));
    else
        setPixmap(QPixmap(":/bB.png"));
}


void Bishop::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

     for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
       if(game->board[i][j]->getFigureColor() == team ) {
           break;

       }
       else
       {
           location.append(game->board[i][j]);
           if(boxSetting(location.last()) ){
               break;
           }
       }
    }

      for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->board[i][j]->getFigureColor() == team ) {
            break;

        }
        else
        {
            location.append(game->board[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

       for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
         if(game->board[i][j]->getFigureColor() == team ) {
             break;

         }
         else
         {
             location.append(game->board[i][j]);
             if(boxSetting(location.last())){
                 break;
             }
         }
      }

        for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
          if(game->board[i][j]->getFigureColor() == team ) {
              break;

          }
          else
          {
              location.append(game->board[i][j]);
              if(boxSetting(location.last())){
                  break;
              }

          }
       }

}
