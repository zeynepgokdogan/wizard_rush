#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "button.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void displayMainMenu(QString title, QString play);
    QGraphicsTextItem *titleText;
    QGraphicsScene * scene;
    QGraphicsScene * scene2;
    Player * player;
    Score * score;
    Health * health;

    Button *playButton;
    Button *quitButton;

public slots:
    void startGame();
    void gameOver();
};

#endif // GAME_H
