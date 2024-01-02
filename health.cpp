#include "Health.h"
#include <QApplication>
#include <QFont>
#include "game.h"

extern Game *game;

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    health = 3;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("Algerian", 16, QFont::Bold));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2

    // if health is 0 then the player must die. I temporarily made it to close the game but
    // this part is going to be pop-up the restart screen
    if(health == 0){
        game->gameOver();
    }
}

int Health::getHealth(){
    return health;
}

void Health::resetHealth()
{
    health = 3;
    setPlainText(QString("Health: ") + QString::number(health));
}
