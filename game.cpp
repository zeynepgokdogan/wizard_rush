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

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    player =NULL;
    player2 = NULL;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(player)
        player->keyPressEvent(event);
    else
        QGraphicsView::keyPressEvent(event);
}

void Game::startGame()
{
    // Remove previous instances of Health and Score
    if (health) {
        scene->removeItem(health);
        delete health;
        health = nullptr;
    }

    if (score) {
        scene->removeItem(score);
        delete score;
        score = nullptr;
    }

    // create new instances of Health and Score
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

    score = new Score();
    scene->addItem(score);

    // Reset the score to zero
    score->resetScore();

    // Reset the health to its initial value
    health->resetHealth();

    // Remove buttons
    scene->removeItem(playButton);
    scene->removeItem(quitButton);
    scene->removeItem(titleText);

    // Create the player
    player = new Player();
    player->setPos(80, 400); // TODO generalize to always be in the middle bottom of the screen

    // Make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Add the player to the scene
    scene->addItem(player);

    if (player2)
        player2->deleteLater();
    player2 = player;

    // Add enemies
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

    // Calculate button positions relative to the width of the screen
    int buttonWidth = 200; // Adjust this value based on your button size
    int buttonXPos = width() / 2 - buttonWidth / 2;
    int playButtonYPos = 300;
    int quitButtonYPos = 370;

    // Create Play Button
    playButton = new Button(play, titleText);
    playButton->setPos(buttonXPos, playButtonYPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playButton);
    playButton->setFlag(QGraphicsItem::ItemIsFocusable);
    playButton->setFocus();


    // Create Quit Button
    quitButton = new Button("Quit", titleText);
    quitButton->setPos(buttonXPos, quitButtonYPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
    quitButton->setFlag(QGraphicsItem::ItemIsFocusable);
    quitButton->setFocus();
}

void Game::gameOver() {
    qDebug() << "Game Over";

    if (player) {
        disconnect(player, SIGNAL(keyPressEvent(QKeyEvent*)), 0, 0);
        player->clearFocus(); // Clear the focus from the player
        scene->removeItem(player);
    }

    // Display the main menu
    displayMainMenu("Game Over!","Play Again");
}
