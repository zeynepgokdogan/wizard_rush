#include <QApplication>
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

void Game::displayPlayerSelection(QString title, QString play)
{
    // Declare titleText here
    titleText_1 = new QGraphicsTextItem(title);
    QFont titleFont("arial", 30);
    titleText_1->setFont(titleFont);
    int xPos = 800 / 2 - titleText_1->boundingRect().width() / 2;
    int yPos = 150;
    titleText_1->setPos(xPos, yPos);
    scene->addItem(titleText_1);

    // Create Buttons
    player1Button = new Button("Player 1", titleText_1);
    int p1xPos = 800 / 4 - player1Button->boundingRect().width() / 2;
    int p1yPos = 600 / 2;
    player1Button->setPos(p1xPos, p1yPos);
    connect(player1Button, &Button::clicked, [=]() {
        displayMainMenu("Player 1 Selected", "Play");
    });
    scene->addItem(player1Button);

    player2Button = new Button("Player 2", titleText_1);
    int p2xPos = 800 / 2 - player2Button->boundingRect().width() / 2;
    int p2yPos = 600 / 2;
    player2Button->setPos(p2xPos, p2yPos);
    connect(player2Button, &Button::clicked, [=]() {
        displayMainMenu("Player 2 Selected", "Play");
    });
    scene->addItem(player2Button);

    player3Button = new Button("Player 3", titleText_1);
    int p3xPos = 800 * 3 / 4 - player3Button->boundingRect().width() / 2;
    int p3yPos = 600 / 2;
    player3Button->setPos(p3xPos, p3yPos);
    connect(player3Button, &Button::clicked, [=]() {
        displayMainMenu("Player 3 Selected", "Play");
    });
    scene->addItem(player3Button);

}

void Game::displayMainMenu(QString title, QString play)
{
    displayMainMenu("Main Menu", "Play");
    // Remove Health and Score
    scene->removeItem(score);
    scene->removeItem(health);

    // Declare titleText here
    titleText_2 = new QGraphicsTextItem(title);
    QFont titleFont("arial", 50);
    titleText_2->setFont(titleFont);
    int xPos = width() / 2 - titleText_2->boundingRect().width() / 2;
    int yPos = 150;
    titleText_2->setPos(xPos, yPos);
    scene->addItem(titleText_2);

    // Create Play Button
    playButton = new Button("play", titleText_2);
    int pxPos = width() / 2 - playButton->boundingRect().width() / 2;
    int pyPos = height() / 2;
    playButton->setPos(pxPos, pyPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playButton);

    // Create Quit Button
    quitButton = new Button("Quit", titleText_2);
    int qxPos = width() / 2 - quitButton->boundingRect().width() / 2;
    int qyPos = height() / 1.5;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, &Button::clicked, this, &Game::quitGame);
    scene->addItem(quitButton);
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
    scene->removeItem(titleText_2);


    // Create the player and Add the player to the scene
    player = new Player();
    player->setPos(80, 400);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    if (player2)
        player2->deleteLater();
    player2 = player;

    //Add enemies
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    int randomSecond = rand() % 1500;
    timer->start(1500 + randomSecond);

    // Connect player's keyPressEvent signal again
    connect(this, SIGNAL(playerKeyPressed(QKeyEvent*)), player, SLOT(keyPressEvent(QKeyEvent*)));
    connect(player, SIGNAL(keyPressEvent(QKeyEvent*)), this, SIGNAL(playerKeyPressed(QKeyEvent*)));
}

void Game::quitGame()
{
    QApplication::quit();  // This will gracefully close the application
}


void Game::gameOver() {
    qDebug() << "Game Over";

    if (player) {
        disconnect(this, SIGNAL(playerKeyPressed(QKeyEvent*)), player, SLOT(keyPressEvent(QKeyEvent*)));
        player->clearFocus(); // Clear the focus from the player
        scene->removeItem(player);
    }

    // Display the main menu
    displayMainMenu("Game Over!","Play Again");
}


