#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QBrush>
#include <QImage>
#include <QGraphicsView>

Game::Game(QWidget *parent): QGraphicsView(parent){
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)

    QImage backgroundImage(":/assets/blueBackground.jpg");
    setBackgroundBrush(QBrush(backgroundImage));

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // create the player
    player = new Player();
    player->setPos(80,400); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);
}

void Game::startGame()
{

    scene->removeItem(playButton);
    scene->removeItem(quitButton);
    scene->removeItem(titleText);

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    int randomSecond = rand() % 1500;
    timer->start(1500 + randomSecond);
}

void Game::displayMainMenu(QString title, QString play)
{
    // Create the title
    titleText = new QGraphicsTextItem(title);
    QFont titleFont("arial", 50);
    titleText->setFont(titleFont);
    int xPos = width() / 2 - titleText->boundingRect().width() / 2;
    int yPos = 150;
    titleText->setPos(xPos, yPos);
    scene->addItem(titleText);

    // Create Button
    playButton = new Button(play, titleText);
    int pxPos = 160;
    int pyPos = 160;
    playButton->setPos(pxPos, pyPos);

    connect(playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playButton);

    // Create Quit Button
    quitButton = new Button("Quit", titleText);
    int qxPos = 160;
    int qyPos = 230;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::gameOver(){
    displayMainMenu("Game Over!","Play Again");
    scene->removeItem(player);
    scene->removeItem(score);
    scene->removeItem(health);
}
