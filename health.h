#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    void increase();
    int getHealth();
private:
    int health;

public slots:
    void resetHealth();
};

#endif // HEALTH_H
