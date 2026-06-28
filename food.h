#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsPixmapItem>
#include <QPainterPath>

class Food : public QGraphicsPixmapItem
{
public:
    Food();
    // Unique identifier for collision detection matrix
    enum { Type = UserType + 1 };
    int type() const override { return Type; }
protected:
    // Custom circular collision shape to match the pixel apple asset
    QPainterPath shape() const override;
};

#endif // FOOD_H
