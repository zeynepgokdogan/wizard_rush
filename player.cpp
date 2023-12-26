#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Enemy.h"
#include <QTimer>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set graphic
    QPixmap imageOne (":/assets/wizardE.png");
    setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));

    timerOne = new QTimer(this);
    timerTwo = new QTimer(this);
    timerThree = new QTimer(this);
    connect(timerTwo,SIGNAL(timeout()),this,SLOT(fall()));
    timerTwo->start(17);
    timerTwo->stop();
    connect(timerOne,SIGNAL(timeout()),this,SLOT(jump()));
    timerOne->start(10);
    timerOne->stop();
    connect(timerThree,SIGNAL(timeout()),this,SLOT(instaFall()));
    timerThree->start(10);
    timerThree->stop();
}

void Player::jump(){
    if(pos().y() > 200){
        setPos(x(),y()-5);
    }
    else{
        timerOne->stop();
        timerTwo->start();
    }
}

void Player::fall(){
    if(pos().y() < 400){
        timerOne->stop();
        setPos(x(),y()+2);
    }
    else{
        timerTwo->stop();
    }
}

void Player::instaFall(){
    if(pos().y() < 400){
        timerOne->stop();
        setPos(x(),y()+12);
    }
    else{
        timerTwo->stop();
        timerThree->stop();
    }
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Down){
        if (pos().y() + 210 < 600){
            timerThree->start();
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 0){
            timerOne->start();
        }
    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
