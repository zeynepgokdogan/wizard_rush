#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Enemy.h"
#include "potion.h"
#include "game.h"
#include <QTimer>

extern Game *game;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set graphic
    isUp = false;
    isDown = false;
    isLeft = false;
    isRight = false;

    if((game -> isPlayer1) == true){
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
    }else if((game -> isPlayer2) == true){
        QPixmap imageOne (":/assets/flyingPotter.png");
        setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));

        timerUp = new QTimer(this);
        connect(timerUp, SIGNAL(timeout()),this,SLOT(up()));
        timerUp->start(10);
        timerUp->stop();

        timerDown = new QTimer(this);
        connect(timerDown, SIGNAL(timeout()),this,SLOT(down()));
        timerDown->start(10);
        timerDown->stop();

        timerRight = new QTimer(this);
        connect(timerRight, SIGNAL(timeout()),this,SLOT(right()));
        timerRight->start(10);
        timerRight->stop();

        timerLeft = new QTimer(this);
        connect(timerLeft, SIGNAL(timeout()),this,SLOT(left()));
        timerLeft->start(10);
        timerLeft->stop();
    }else if((game -> isPlayer3) == true){
        QPixmap imageOne (":/assets/hermonie.png");
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
}

void Player::jump(){
    if((game -> isPlayer1) == true){
        if(pos().y() >= 300){
            setPos(x(),y()-8);
        }else if(pos().y() < 300 && pos().y() >= 250){
            setPos(x(),y()-5);
        }else if(pos().y() < 250 && pos().y() >= 215){
            setPos(x(),y()-4);
        }else if(pos().y() < 215 && pos().y() >= 200){
            setPos(x(),y()-2);
        }
        else{
            timerOne->stop();
            QPixmap imageOne (":/assets/wizardE3.png");
            setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));
            timerTwo->start();

        }
    }
    else if((game -> isPlayer3) == true){
        if(pos().y() >= 300){
            setPos(x(),y()-8);
        }else if(pos().y() < 300 && pos().y() >= 250){
            setPos(x(),y()-5);
        }else if(pos().y() < 250 && pos().y() >= 215){
            setPos(x(),y()-4);
        }else if(pos().y() < 215 && pos().y() >= 200){
            setPos(x(),y()-2);
        }
        else{
            timerOne->stop();

            timerTwo->start();

        }
    }
}

void Player::fall(){
    if((game -> isPlayer1) == true){
        if(pos().y() < 215){
            timerOne->stop();
            setPos(x(),y()+3);
        }else if(pos().y() >= 215 && pos().y() < 250){
            setPos(x(),y()+6);
        }else if(pos().y() >= 250 && pos().y() < 300){
            setPos(x(),y()+7);
        }else if(pos().y() >= 300 && pos().y() < 400){
            setPos(x(),y()+10);
        }
        else{
            QPixmap imageOne (":/assets/wizardE.png");
            setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));
            timerTwo->stop();

        }
    }
    else if((game -> isPlayer3) == true){
        if(pos().y() < 215){
            timerOne->stop();
            setPos(x(),y()+3);
        }else if(pos().y() >= 215 && pos().y() < 250){
            setPos(x(),y()+6);
        }else if(pos().y() >= 250 && pos().y() < 300){
            setPos(x(),y()+7);
        }else if(pos().y() >= 300 && pos().y() < 400){
            setPos(x(),y()+10);
        }
        else{

            timerTwo->stop();

        }
    }
}

void Player::instaFall(){
    if((game -> isPlayer1) == true){
        if(pos().y() < 400){
            timerOne->stop();
            setPos(x(),y()+12);
        }
        else{
            QPixmap imageOne (":/assets/wizardE.png");
            setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));
            timerTwo->stop();
            timerThree->stop();
        }
    }else if((game -> isPlayer3) == true){
        if(pos().y() < 400){
            timerOne->stop();
            setPos(x(),y()+12);
        }
        else{

            timerTwo->stop();
            timerThree->stop();
        }
    }
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if((game -> isPlayer1) == true){
        if (event->key() == Qt::Key_Down){
            if (pos().y() + 210 < 600){
                QPixmap imageOne (":/assets/wizardE3.png");
                setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));
                timerThree->start();

            }
        }
        else if (event->key() == Qt::Key_Up){
            if (pos().y() > 0){
                QPixmap imageOne (":/assets/wizardE2.png");
                setPixmap(imageOne.scaled(120,120, Qt::KeepAspectRatio));
                timerOne->start();
            }
        }
    }
    if((game -> isPlayer2) == true){
        if(event->key() == Qt::Key_Down){
                isDown = true;

                if(isDown){
                    timerDown->start();
                }
        }
        else if(event->key() == Qt::Key_Up){
                isUp = true;
                if(isUp){
                    timerUp->start();
                }
        }        else if(event->key() == Qt::Key_Right){
            isRight = true;
            if(isRight){
                timerRight->start();
            }
        }        else if(event->key() == Qt::Key_Left){
            isLeft = true;
            if(isLeft){
                timerLeft->start();
            }
        }
    }
    if((game -> isPlayer3) == true){
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
}


void Player::keyReleaseEvent(QKeyEvent *event){
    if(game->isPlayer2){
    if(event -> key() == Qt::Key_Down){
        timerDown->stop();
        isDown = false;
    }else if(event -> key() == Qt::Key_Up){
        timerUp->stop();
        isUp = false;
    }else if(event -> key() == Qt::Key_Right){
        timerRight->stop();
        isRight = false;
    }else if(event -> key() == Qt::Key_Left){
        timerLeft->stop();
        isLeft = false;
    }
    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);


}

void Player::spawnP(){
    Potion * potion = new Potion();
    scene()->addItem(potion);
}

void Player::up(){
    if((game->isPlayer2) == true){
        setPos(x(),y()-5);
    }
}

void Player::down(){
    if((game->isPlayer2) == true){
        setPos(x(),y()+5);
    }
}

void Player::right(){
    if((game->isPlayer2) == true){
        setPos(x()+5,y());
    }
}

void Player::left(){
    if((game->isPlayer2) == true){
        setPos(x()-5,y());
    }
}


