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

void Game::displayPlayerSelection(QString title)
{
    scene->removeItem(titleText_2);
    scene->removeItem(playButton);
    scene->removeItem(quitButton);

    // Declare titleText here
    titleText_1 = new QGraphicsTextItem(title);
    QFont titleFont("arial", 50);
    titleText_1->setFont(titleFont);
    titleText_1->setDefaultTextColor(Qt::red);
    int titleXPos = width() / 2 - titleText_1->boundingRect().width() / 2;
    int titleYPos = 150;
    titleText_1->setPos(titleXPos, titleYPos);
    scene->addItem(titleText_1);

    // second title
    chooseCharacterText = new QGraphicsTextItem("Choose A Character");
    QFont font("arial", 20);
    chooseCharacterText->setFont(font);
    int xPos = width() / 2 - chooseCharacterText->boundingRect().width() / 2;
    int yPos = 250;
    chooseCharacterText->setPos(xPos, yPos);
    scene->addItem(chooseCharacterText);

    // Create Buttons
    int spacing = 20;      // Adjust this value as needed

    player1Button = new Button("Player 1", titleText_1);
    player1Button->setPos(-80 , height() / 2);
    connect(player1Button, &Button::clicked, [=]() {
        startGame();
    });
    scene->addItem(player1Button);

    player2Button = new Button("Player 2", titleText_1);
    player2Button->setPos(120, height() / 2);
    connect(player2Button, &Button::clicked, [=]() {
        startGame();
    });
    scene->addItem(player2Button);

    player3Button = new Button("Player 3", titleText_1);
    player3Button->setPos(320, height() / 2);
    connect(player3Button, &Button::clicked, [=]() {
        startGame();
    });
    scene->addItem(player3Button);
}





void Game::displayMainMenu(QString title, QString play)
{
    // Remove Health and Score
    scene->removeItem(score);
    scene->removeItem(health);


    // Declare titleText here
    titleText_2 = new QGraphicsTextItem(title);
    QFont titleFont("arial", 30);
    titleText_2->setFont(titleFont);
    int xPos = width() / 2 - titleText_2->boundingRect().width() / 2;
    int yPos = 150;
    titleText_2->setPos(xPos, yPos);
    scene->addItem(titleText_2);

    // Create Buttons
    int buttonWidth = 150; // Adjust this value as needed
    int buttonHeight = 50; // Adjust this value as needed
    int spacing = 20;      // Adjust this value as needed

    // Create Play Button
    playButton = new Button(play, titleText_2);
    int pxPos = (xPos - 300 - 100)/2;
    int pyPos = height() / 2;
    playButton->setPos(pxPos, pyPos);
    connect(playButton, &Button::clicked, [=]() {
        displayPlayerSelection("WizarD RusH");
    });
    scene->addItem(playButton);

    // Create Quit Button
    quitButton = new Button("Quit", titleText_2);
    int qxPos = pxPos + 250;
    int qyPos = height() / 2;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, &Button::clicked, this, &Game::quitGame);
    scene->addItem(quitButton);
}


void Game::startGame()
{

    scene->removeItem(chooseCharacterText);
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
    scene->removeItem(titleText_1);


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
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    int randomSecond = rand() % 1500;
    timer->start(1500 + randomSecond);

    // Disconnect existing connections before creating new ones
    disconnect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    disconnect(this, SIGNAL(playerKeyPressed(QKeyEvent*)), player, SLOT(keyPressEvent(QKeyEvent*)));
    disconnect(player, SIGNAL(keyPressEvent(QKeyEvent*)), this, SIGNAL(playerKeyPressed(QKeyEvent*)));

    // Connect new signals
    connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    connect(this, SIGNAL(playerKeyPressed(QKeyEvent*)), player, SLOT(keyPressEvent(QKeyEvent*)));
    connect(player, SIGNAL(keyPressEvent(QKeyEvent*)), this, SIGNAL(playerKeyPressed(QKeyEvent*)));


    scene->removeItem(titleText_2);


}

void Game::quitGame()
{
    QApplication::quit();  // This will gracefully close the application
}

void Game::handlePlayerSelection(int value) {

}

void Game::gameOver() {
    if (player) {
        disconnect(this, SIGNAL(playerKeyPressed(QKeyEvent*)), player, SLOT(keyPressEvent(QKeyEvent*)));
        player->clearFocus(); // Clear the focus from the player
        player->setVisible(false);
    }
    disconnect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    // Display the main menu
    displayMainMenu("GAME OVER!","PLAY AGAİN");
}


