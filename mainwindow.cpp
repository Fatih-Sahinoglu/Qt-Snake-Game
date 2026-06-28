#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "snakebody.h"
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(650,650);
    this->setCentralWidget(ui->stackedWidget);

    // Configure main game view boundaries and scroll settings
    ui->graphicsView->setGeometry(20,20,600,600);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setLineWidth(0);
    ui->graphicsView->setContentsMargins(0, 0, 0, 0);

    // Initialize core gameplay scene matrix
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,600,600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(600,600);

    // Initialize interactive main menu scene
    menuscene = new QGraphicsScene(this);
    ui->menu_graphicsview->setScene(menuscene);
    ui->menu_graphicsview->setAlignment(Qt::AlignRight);

    // Activate mouse tracking across widgets for interactive elements
    ui->Start_btn->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    ui->Start_btn->setMouseTracking(true);
    ui->Exit_btn->setMouseTracking(true);
    ui->Start_btn->installEventFilter(this);
    ui->Exit_btn->installEventFilter(this);

    ui->stackedWidget->setMouseTracking(true);
    ui->page_1->setMouseTracking(true);
    ui->stackedWidget->installEventFilter(this);

    ui->menu_graphicsview->viewport()->installEventFilter(this);
    ui->centralwidget->installEventFilter(this);
    ui->centralwidget->setMouseTracking(true);
    ui->menu_graphicsview->setMouseTracking(true);

    // Set up responsive character menu mascot and pupils
    bighead = new QGraphicsPixmapItem(QPixmap(":/models/models/big_head.png"));
    bighead->setPos(60, menuscene->height()/2);
    bighead->setZValue(1);
    menuscene->addItem(bighead);

    leftpupil = new QGraphicsEllipseItem(0, 0, 25, 3);
    leftpupil->setBrush(Qt::black);
    leftpupil->setZValue(2);
    menuscene->addItem(leftpupil);

    rightpupil = new QGraphicsEllipseItem(0, 0, 25, 3);
    rightpupil->setBrush(Qt::black);
    rightpupil->setZValue(2);
    menuscene->addItem(rightpupil);

    lefteyecenter = QPointF(195, 35);
    righteyecenter = QPointF(195, 185);
    leftpupil->setPos(lefteyecenter.x()-6, lefteyecenter.y()-6);
    rightpupil->setPos(righteyecenter.x()-6, righteyecenter.y()-6);

    timer = new QTimer(this);

    // Initialize sound effects
    hoverSound = new QSoundEffect(this);
    gameOverSound = new QSoundEffect(this);

    hoverSound -> setSource(QUrl::fromLocalFile(":/models/models/rattle.wav"));
    gameOverSound -> setSource(QUrl::fromLocalFile(":/models/models/hiss.wav"));

    hoverSound -> setVolume(0.6);
    gameOverSound -> setVolume(0.6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameover()
{
    gameOverSound->play();
    timer->stop(); //Game stopped
    isdead = true;


    // Remi-transparent dark loss overlay mask
    QGraphicsRectItem *overlay = new QGraphicsRectItem(0, 0, 600, 600);
    overlay->setBrush(QBrush(QColor(0, 0, 0, 180)));
    overlay->setZValue(10);
    scene->addItem(overlay);

    // Score ve Message
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text->setPlainText("GAME OVER\nScore: " + QString::number(head->tails.size()-1) +"\n\nR to Restart");
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("Segoe UI", 30, QFont::Bold));
    text->setPos(180, 200);
    text->setZValue(11);
    scene->addItem(text);
}

void MainWindow::drawbackground()
{
    for (int i = 0; i < 600; i += 20) {
        for (int j = 0; j < 600; j += 20) {
            QGraphicsRectItem *rect = new QGraphicsRectItem(i, j, 20, 20);
            if ((i + j) / 20 % 2 == 0) {
                rect->setBrush(QBrush(QColor(30, 30, 30))); //Dark Gray
            } else {
                rect->setBrush(QBrush(QColor(40, 40, 40))); //Light Gray
            }
            rect->setPen(Qt::NoPen);
            rect->setZValue(-1);
            scene->addItem(rect);
        }
    }
}

void MainWindow::gamesetup()
{
    timer->stop();
    timer->disconnect();

    head = new SnakeHead();
    head->setPos(300,300);
    head->setRotation(90);

    scene->addItem(head);
    head->setFlag(QGraphicsItem::ItemIsFocusable);
    head->setFocus();

    SnakeBody *part = new SnakeBody;
    part->setPos(280, 300);
    part->setRotation(90);
    part->setPixmap(QPixmap(":/models/models/tail.png"));
    scene->addItem(part);
    head->tails.append(part);


    connect(head, &SnakeHead::dead, this, &MainWindow::gameover);
    connect(timer, &QTimer::timeout, head, &SnakeHead::move);
    connect(head, &SnakeHead::eaten, this, &MainWindow::foodspawn);

    srand(time(0));
    apple = new Food();
    foodspawn();
    scene->addItem(apple);
}

void MainWindow::restart()
{
    scene->clear();
    drawbackground();
    gamesetup();
    timer->start(30);
}

void MainWindow::foodspawn()
{
    short xpos;
    short ypos;
    bool collision;

    // Relocate food entity ensuring it avoids snake body boundaries
    do{
        collision = false;
        xpos = (rand()%30)*20;
        ypos = (rand()%30)*20;

        QList<QGraphicsItem*> items_atpos = scene->items(QPointF(xpos +10,ypos +10));
        for(QGraphicsItem * item : items_atpos){

            if(item->zValue() == -1) continue;

            if(item->type() == SnakeHead::Type || item->type() == SnakeBody::Type){
                collision = true;
                break;
            }
        }

    }while(collision);

    apple->setPos(xpos,ypos);
}

void MainWindow::updateeyes(QPointF mousepos)
{
    QPointF globalpos = QCursor::pos();
    QPointF scene_mousepos = ui->menu_graphicsview->mapToScene(ui->menu_graphicsview->mapFromGlobal(globalpos.toPoint()));

    auto movePupil = [&](QGraphicsEllipseItem* pupil, QPointF center) {
        QLineF line(center, scene_mousepos);
        if (line.length() > 10) {
            line.setLength(10);
        }

        pupil->setPos(line.p2().x() - 6, line.p2().y() - 6);
    };

    movePupil(leftpupil, lefteyecenter);
    movePupil(rightpupil, righteyecenter);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Filter and handle interface sound triggers and eye animation steps
    if(event->type() == QEvent::HoverEnter){
        if(obj == ui->Start_btn || obj == ui->pushButton_2 || obj == ui->Exit_btn){
            hoverSound->play();
        }
    }
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        updateeyes(mouseEvent->pos());
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R){
        restart();
    }
    if(event->key() == Qt::Key_F) {
        if(!timer->isActive() || isdead) {
            on_pushButton_2_clicked();
            this->activateWindow();
            this->setFocus();
        }
    }
    if(event->key() == Qt::Key_Escape){
        if(timer->isActive()){
            timer->stop(); //Game paussed


            pause_overlay = new QGraphicsRectItem(0, 0, 600, 600);
            pause_overlay->setBrush(QBrush(QColor(0, 0, 0, 180)));
            pause_overlay->setZValue(10);
            scene->addItem(pause_overlay);


            pause_text = new QGraphicsTextItem();
            pause_text->setPlainText("Game Stopped\nPress ESC to continue\nScore: " + QString::number(head->tails.size()-1) + "\nF to Respect");
            pause_text->setDefaultTextColor(Qt::white);
            pause_text->setFont(QFont("Segoe UI", 30, QFont::Bold));
            pause_text->setPos(50, 120);
            pause_text->setZValue(11);
            scene->addItem(pause_text);

        }else{
            if(pause_text){
                scene->removeItem(pause_text);
                scene->removeItem(pause_overlay);
                delete pause_text;
                delete pause_overlay;
                pause_text = nullptr;
                pause_overlay = nullptr;
            }
            if(!isdead){
                timer->start(30);
                head->setFocus();}
        }
    }
}



void MainWindow::on_Start_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    scene->clear();

    drawbackground();
    gamesetup();
    timer->start(30);
}


void MainWindow::on_Exit_btn_clicked()
{
    qApp->quit();
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox cred(this);

    cred.setWindowTitle("Credits");
    cred.setStyleSheet("QMessageBox { background-color: #1e1e1e; } "
                       "QLabel { color: white; font-size: 14px; } "
                       "QPushButton { background-color: #4CAF50; color: white; border-radius: 5px; padding: 5px 15px; font-weight: bold; }");

    cred.setText("<h3>Qt Snake Game v1.0</h3>"
                 "<p><b>Developer:</b> Fatih Şahinoğlu</p>"
                 "<p>This project was developed as part of the C++ and Qt framework learning process.</p>"
                 "<p>Check out my projects on "
                 "<a href='https://github.com/Fatih-Sahinoglu'>GitHub</a> | "
                 "<a href='https://www.linkedin.com/in/fatih-şahinoğlu/'>Linkedin</a></p>"
                 "<hr>"
                 "<p><b>Geliştirici:</b> Fatih Şahinoğlu</p>"
                 "<p>Bu proje, C++ ve Qt framework öğrenim sürecinin bir parçası olarak geliştirilmiştir.</p>"
                 "<p>Diğer Projelerimi görmek için  "
                 "<a href='https://github.com/Fatih-Sahinoglu'>GitHub</a> | "
                 "<a href='https://www.linkedin.com/in/fatih-şahinoğlu/'>Linkedin</a></p>"
                 "<hr>");

    cred.setIcon(QMessageBox::Information);

    cred.exec();
}

