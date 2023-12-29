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
    void displayPlayerSelection(QString title, QString play);
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

private:
    QGraphicsTextItem* titleText_1;
    QGraphicsTextItem* titleText_2;
    QGraphicsTextItem* chooseCharacterText;

public slots:
    void startGame();
    void quitGame();

private slots:
    void handlePlayerSelection(int playerNumber);
};

#endif // GAME_H
