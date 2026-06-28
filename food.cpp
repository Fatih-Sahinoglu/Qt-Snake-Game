#include "food.h"

#include <QPixmap>

Food::Food() {
    QPixmap applepix(":/models/models/apple.png");
    // Scale the apple sprite to fit the 20x20 grid
    setPixmap(applepix.scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));

}
QPainterPath Food::shape() const
{
    QPainterPath path;
   // Circular hitbox matching the round fruit design for precise collision
    path.addEllipse(2, 2, 16, 16);
    return path;
}
