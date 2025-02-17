#include "game.h"
#include <QPixmap>
#include "king.h"
#include <QGraphicsProxyWidget>


Game::Game(QWidget *parent ):QGraphicsView(parent)
{

    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,900);
    setFixedSize(1400,900);
    setScene(gameScene);
    figureToMove = NULL;
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::black);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText(trUtf8("Ход белых"));

    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(1);
    check->setDefaultTextColor(Qt::blue);
    check->setFont(QFont("",18));
    check->setPlainText(trUtf8("Шах!"));
    check->setVisible(false);
    setTurn("WHITE");

    table = new QTableWidget();
    table->setColumnCount(4);
    table->setGeometry(1120,0,275,400);
    table->setColumnWidth(0,75);
    table->setColumnWidth(1,50);
    table->setColumnWidth(2,50);
    table->setColumnWidth(3,100);
    QGraphicsProxyWidget *proxy;
    proxy = gameScene->addWidget(table);
    proxy->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    proxy->setZValue(3);
    //gameScene->addItem(proxy);

    but = new Button(trUtf8("Отменить ход"));
    but->setZValue(2);
    addToScene(but);

    text = new QGraphicsTextItem();
    text->setPos(30,120);
    text->setZValue(2);
    text->setDefaultTextColor(Qt::blue);
    text->setFont(QFont("",13));
    text->setPlainText(trUtf8("Выберите фигуру!"));
    text->setVisible(false);

    QPointF pointKnight = QPointF(30,150);
    excKnight = new ExchangeButtons("KNIGHT", pointKnight);
    excKnight->setZValue(2);
    excKnight->setVisible(false);
    excKnight->setEnabled(false);
    exchange.append(excKnight);
    QPointF pointRook = QPointF(120,150);
    excRook = new ExchangeButtons("ROOK", pointRook);
    excRook->setZValue(2);
    excRook->setVisible(false);
    excRook->setEnabled(false);
    exchange.append(excRook);
    QPointF pointQueen = QPointF(30,250);
    excQueen = new ExchangeButtons("QUEEN", pointQueen);
    excQueen->setZValue(2);
    excQueen->setVisible(false);
    excQueen->setEnabled(false);
    exchange.append(excQueen);
    QPointF pointBishop = QPointF(120,250);
    excBishop = new ExchangeButtons("BISHOP", pointBishop);
    excBishop->setZValue(2);
    excBishop->setVisible(false);
    excBishop->setEnabled(false);
    exchange.append(excBishop);
}

void Game::drawChessBoard()
{
    chess = new ChessBoard();
    drawField(0,420);
    drawField(1120,420);
    chess->drawBoxes(width()/2-400,50);
}

void Game::removedFigures(Figure *figure)
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    QPointF point;
    if(figure->getSide() == "WHITE") {
        whiteRemoved.append(figure);
        for(int i = 0; i<whiteRemoved.size(); i++) {
        if(j == 4){
            k++;
            j = 0;
            }
         point = QPointF(20+SHIFT*j++, 420+SHIFT*2*k);
        }
         animation(whiteRemoved.last(),point);
    }
    else{
        blackRemoved.append(figure);
        for(int i = 0; i<blackRemoved.length(); i++) {
            if(j == 4){
                k++;
                j = 0;
            }
             point = QPointF(1120+SHIFT*j++, 420+SHIFT*2*k);
        }
        animation(blackRemoved.last(),point);
    }
    aliveFigure.removeAll(figure);
}

void Game::animation(Figure *figure, QPointF point)
{
    QTimeLine *timer = new QTimeLine(1000);
    timer->setFrameRange(0, 100);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(figure);
    animation->setTimeLine(timer);
    animation->setPosAt(1, point);
    timer->start();
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);
}

QString Game::getTurn()
{
    return turn;
}

void Game::setTurn(QString value)
{
    turn = value;
}

void Game::changeTurn()
{
    if(getTurn() == "WHITE")
    {
        setTurn("BLACK");
        turnDisplay->setPlainText(trUtf8("Ход черных"));
    }
    else
        {
        setTurn("WHITE");
        turnDisplay->setPlainText(trUtf8("Ход белых"));
    }
}

void Game::drawField(int x, int y)
{
    field = new QGraphicsRectItem(x,y,280,500);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    field->setZValue(0);
    field->setBrush(brush);
    addToScene(field);
}

void Game::start()
{
    drawChessBoard();
    time = QTime::currentTime();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./chess.db");
    if (!db.open()){
        QMessageBox* pmbx =
                        new QMessageBox(QMessageBox::Information,
                        trUtf8("Ошибка"),
                        trUtf8("сервер не подключен"),
                        QMessageBox::Ok
                        );
                        pmbx->exec();
                        delete pmbx;
                        return;
        }
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("CREATE TABLE game (ID INTEGER, game_t time)");
    QSqlQuery qMax("select (MAX(id)+1) as max from game");
    qMax.next();
    gameId = qMax.value(0).toInt();
    query->exec("INSERT INTO game VALUES ("+QString::number(gameId)+",'"+time.toString()+"')");
    query->exec("CREATE TABLE log "
                    "(id integer, "
                    "gameid integer, "
                    "player text, "
                    "move_from text, "
                    "move_to text, "
                    "move_time time, "
                    "srub integer, "
                    "first_move integer) ");
    addToScene(turnDisplay);
    addToScene(check);
    addToScene(text);
    for (int i=0; i<exchange.length();i++)
    {
        addToScene(exchange[i]);
    }
    chess->addFigure();
}


void Game::gameOver(QString winCol)
{
    QString winner;
    if (winCol == "WHITE")
        winner = trUtf8("белые ");
    else if (winCol == "BLACK")
        winner = trUtf8("черные ");
    if (winCol != "NONE")
    {
    QMessageBox* pmbx =
    new QMessageBox(QMessageBox::Information,
    trUtf8("Партия сыграна"), winner + trUtf8("выиграли"), QMessageBox::Ok );
    int n = pmbx->exec();
    delete pmbx;
    if (n == QMessageBox::Ok) {
        db.close();
           QWidget::close();
    }
    }
    else
    {
        QMessageBox* pmbx =
        new QMessageBox(QMessageBox::Information,
        trUtf8("ничья"), trUtf8("пат"), QMessageBox::Ok );
        int n = pmbx->exec();
        delete pmbx;
        if (n == QMessageBox::Ok) {
            db.close();
               QWidget::close();
        }
    }
}


