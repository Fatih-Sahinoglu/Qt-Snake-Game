#include "snakebody.h"
#include <QBrush>

SnakeBody::SnakeBody() {
    setPixmap(QPixmap(":/models/models/body.png"));
    // Set pivot point to center for smooth custom turn rotations
    setTransformOriginPoint(10,10);
    setZValue(1);
}

QPainterPath SnakeBody::shape() const
{
    QPainterPath path;
    // Rectangular hitbox slightly smaller than the 20x20 sprite to prevent ghost collisions
    path.addRect(2, 2, 16, 16);
    return path;
}
