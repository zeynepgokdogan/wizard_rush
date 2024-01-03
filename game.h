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
    void keyPressEvent(QKeyEvent *event);
    void displayMainMenu(QString title, QString play);
    void displayPlayerSelection(QString title);
    void gameOver();
    QGraphicsScene * scene;
    QGraphicsScene * scene2;
    Player * player;
    Player * player2;
    Score * score;
    Health * health;
    Button *playButton;
    Button *quitButton;


    Button *player1Button;
    Button *player2Button;
    Button *player3Button;
    QTimer *timer;
    QTimer *timerP;

    bool isPlayer1, isPlayer2, isPlayer3, isPotioned;

private:
    QGraphicsTextItem* titleText_1;
    QGraphicsTextItem* titleText_2;
    QGraphicsTextItem* chooseCharacterText;
    QGraphicsPixmapItem* player1Image;
    QGraphicsPixmapItem* player2Image;
    QGraphicsPixmapItem* player3Image;


public slots:
    void startGame();
    void quitGame();
    void setPlayer1();
    void setPlayer2();
    void setPlayer3();

private slots:
    void handlePlayerSelection(int playerNumber);
};

#endif // GAME_H
