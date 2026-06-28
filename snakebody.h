#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <QGraphicsPixmapItem>

class SnakeBody : public QGraphicsPixmapItem {
public:
    SnakeBody();
    // Unique identifier for collision detection matrix
    enum { Type = UserType + 2 };
    int type() const override { return Type; }
protected:
    // Custom bounding shape for collision handling
    QPainterPath shape() const override;
};

#endif // SNAKEBODY_H
