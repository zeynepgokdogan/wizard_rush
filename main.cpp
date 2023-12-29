#include <QApplication>
#include "Game.h"

Game* game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    game = new Game();

    game->show();
    game->displayPlayerSelection("WizarD RusH", "PLAY");

    return a.exec();
}
