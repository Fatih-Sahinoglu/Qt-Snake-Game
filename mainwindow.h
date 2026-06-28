#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snakehead.h"
#include "food.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void gameover();
    void drawbackground();
    void gamesetup();
    void restart();
    void foodspawn();
    void updateeyes(QPointF mousepos);

    // Event filter for handling menu button hover effects
    bool eventFilter(QObject *watch, QEvent *event) override;
protected:

    // System level key shortcuts
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_Start_btn_clicked();

    void on_Exit_btn_clicked();

    void on_pushButton_2_clicked(); // Triggers credits screen

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *menuscene;

    QGraphicsPixmapItem *bighead;
    QGraphicsEllipseItem *leftpupil;
    QGraphicsEllipseItem *rightpupil;

    QTimer *timer;
    SnakeHead *head;
    Food *apple;

    QGraphicsRectItem *pause_overlay = nullptr;
    QGraphicsTextItem *pause_text = nullptr;

    QPointF lefteyecenter;
    QPointF righteyecenter;

    bool isdead = false;

    QSoundEffect *hoverSound;
    QSoundEffect *gameOverSound;
};
#endif // MAINWINDOW_H
