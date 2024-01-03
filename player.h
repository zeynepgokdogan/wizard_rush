#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QTimer * timerOne;
    QTimer * timerTwo;
    QTimer * timerThree;
    QTimer * timerUp;
    QTimer * timerDown;
    QTimer * timerRight;
    QTimer * timerLeft;
    //QTimer * timerInvis;
    bool isUp, isDown, isLeft, isRight;
public slots:
    void spawn();
    void spawnP();
    void jump();
    void fall();
    void instaFall();
    void up();
    void down();
    void right();
    void left();
    //void invisible();
};

#endif // PLAYER_H
