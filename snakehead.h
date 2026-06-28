#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QSoundEffect>

class SnakeHead : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SnakeHead();
    void move();
    QList<QGraphicsPixmapItem*> tails;
signals:
    void dead();
    void eaten();
protected:
    // Keyboard inputs for movement control
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void updaterotation();
    QString direction = "right";

    bool speedkey = false;
    short movecounter = 0;

    QSoundEffect *eatSound;
};

#endif // SNAKEHEAD_H
