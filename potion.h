#ifndef POTION_H
#define POTION_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Potion: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Potion(QGraphicsItem * parent=0);
public slots:
    void movePotion();
};

#endif // POTION_H
