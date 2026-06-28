#include "snakehead.h"
#include "food.h"
#include"snakebody.h"

#include <QGraphicsScene>
#include <QDebug>

SnakeHead::SnakeHead()
{
    setPixmap(QPixmap(":/models/models/head.png"));
    setTransformOriginPoint(10,10);

    // Initialize eat audio effect
    eatSound = new QSoundEffect(this);
    eatSound -> setSource(QUrl::fromLocalFile(":/models/models/pop - Kopya.wav"));
    eatSound -> setVolume(0.6);
}

void SnakeHead::updaterotation()
{
    if(direction == "right") setRotation(90);
    else if(direction =="left") setRotation(-90);
    else if(direction =="down") setRotation(180);
    else if(direction =="up") setRotation(0);

}

void SnakeHead::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left && direction != "right")  direction = "left";
    else if(event->key() == Qt::Key_Right && direction != "left")  direction = "right";
    else if(event->key() == Qt::Key_Up && direction != "down")  direction = "up";
    else if(event->key() == Qt::Key_Down && direction != "up")  direction = "down";

    // Manage continuous speed boost on key hold
    if(event->isAutoRepeat()) speedkey = true;
    else speedkey = false;


    QGraphicsPixmapItem::keyPressEvent(event);
}

void SnakeHead::keyReleaseEvent(QKeyEvent *event)
{
    // Reset to normal speed when directional key is released
    if(!event->isAutoRepeat()) speedkey = false;
}


void SnakeHead::move(){

    movecounter++;

    // Frame threshold switch for normal vs fast speed states
    short thereshold = speedkey ? 2 : 6;

    if(movecounter<thereshold) return;

    movecounter = 0;

    short prevx = x();
    short prevy = y();
    qreal prevrotation = rotation();

    if(direction == "left")  setPos(x() - 20, y());
    else if(direction == "right")  setPos(x() + 20, y());
    else if(direction == "up")  setPos(x(), y() - 20);
    else if(direction == "down")  setPos(x(), y() + 20);

    updaterotation();

    // Propagate position updates through the trailing tail segments
    if(!tails.isEmpty()){
        QGraphicsPixmapItem *last_part = tails.takeLast();
        last_part->setPos(prevx, prevy);

        if(rotation() != prevrotation){

            // Right body corner group
            if ((prevrotation == 0 && rotation() == 90) ||
                (prevrotation == 90 && rotation() == 180) ||
                (prevrotation == 180 && rotation() == -90) ||
                (prevrotation == -90 && rotation() == 0))
            {
                last_part->setPixmap(QPixmap(":/models/models/corner.png"));

                // giving rotation depends directon
                if (prevrotation == 0) last_part->setRotation(90);
                else if (prevrotation == -90) last_part->setRotation(0);
                else if (prevrotation == 180) last_part->setRotation(-90);
                else if (prevrotation == 90) last_part->setRotation(180);
            }
            // Left body corner group
            else
            {
                last_part->setPixmap(QPixmap(":/models/models/corner_mirror.png"));

                // giving rotation depends directon
                if (prevrotation == 0) last_part->setRotation(-90);
                else if (prevrotation == 90) last_part->setRotation(0);
                else if (prevrotation == 180) last_part->setRotation(90);
                else if (prevrotation == -90) last_part->setRotation(180);
            }
        } else {// Apply straight body sprite if path hasn't changed
            last_part->setPixmap(QPixmap(":/models/models/body.png"));
            last_part->setRotation(prevrotation);
        }

        tails.prepend(last_part);
        tails.last()->setPixmap(QPixmap(":/models/models/tail.png"));
    }

    // Boundary check for map limits
    if (x() < 0 || x() >= 600 || y() < 0 || y() >= 600) {
        emit dead();
        return;
    }

    QList<QGraphicsItem*> colliding_items = collidingItems(Qt::IntersectsItemShape);
    for(int i=0, n=colliding_items.size(); i<n; i++){

        if(colliding_items[i]->type() == Food::Type){
            eatSound->play();
            emit eaten();

            SnakeBody *part = new SnakeBody;
            part->setPos(prevx, prevy);
            scene()->addItem(part);
            tails.append(part);
            return;
        }
        else if(colliding_items[i]->type() == SnakeBody::Type){
            emit dead();
            return;
        }
    }
}
