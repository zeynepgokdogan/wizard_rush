#include "Potion.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"
#include <iostream>
#include <QDebug>


extern Game * game;


Potion::Potion(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){


    if(game->isPlayer3){
        setPos(650,420);
        // drew the rect
        QPixmap imageSecond (":/assets/potion.png");
        setPixmap(imageSecond.scaled(100,100, Qt::KeepAspectRatio));
        //setPixmap(QPixmap(":new/src/Resource/Images/cactus.png"));
        setTransformOriginPoint(50,50);
        //setRotation(180);

        // make/connect a timer to move() the enemy every so often
        QTimer * timerP = new QTimer(this);
        connect(timerP,SIGNAL(timeout()),this,SLOT(movePotion()));

        // start the timer
        int randomSpeed = (rand() % 100) + 15;
        timerP->start(10 + randomSpeed);
    }
}
    void Potion::movePotion(){

        // move enemy down
        int randSpeed = (rand() % 9) + 5;
        setPos(x()-randSpeed,y());

        // get a list of all the items currently colliding with this bullet
        QList<QGraphicsItem *> colliding_items = collidingItems();

        // if one of the colliding items is the Player, destroy the enemy
        for (int i = 0, n = colliding_items.size(); i < n; ++i){


            if (typeid(*(colliding_items[i])) == typeid(Player)){
                //increase the health
                game->health->increase();
                // remove them from the scene (still on the heap)
                //scene()->removeItem(colliding_items[i]);


                // delete them from the heap to save memory
                //delete colliding_items[i];
                delete this;

                // return (all code below refers to a non existint bullet)
                return;
            }

        }

        // destroy enemy when it goes out of the screen
        if (pos().x() + 80 < 0){

            // increase the score
            //game->score->increase();
            scene()->removeItem(this);
            delete this;
        }
    }

