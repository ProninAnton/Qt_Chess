#include "queen.h"
#include "game.h"
extern Game *game;
Queen::Queen(QString team, QString type, QGraphicsItem *parent):Figure(team,type,parent)
{
    setImage();
}

void Queen::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/wQ.png"));
    else
        setPixmap(QPixmap(":/bQ.png"));
}


void Queen::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();


     for(int i = row-1,j = col; i >= 0 ; i--) {
       if(game->board[i][j]->getFigureColor() == team ) {
           break;
       }
       else
       {
           location.append(game->board[i][j]);
           if(boxSetting(location.last()))
               break;
        }
    }


      for(int i = row+1,j = col; i <= 7 ; i++) {
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


       for(int i = row,j = col-1; j >= 0 ; j--) {
         if(game->board[i][j]->getFigureColor() == team ) {
             break;
         }
         else
         {
             location.append(game->board[i][j]);
             if(boxSetting(location.last()))
                break;
         }
       }

        for(int i = row,j = col+1; j <= 7 ; j++)
        {
              if(game->board[i][j]->getFigureColor() == team ) {
                  break;
              }
              else
              {
                  location.append(game->board[i][j]);
                  if(boxSetting(location.last()))
                      break;
               }
       }


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
