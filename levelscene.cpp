#include "levelscene.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QImage>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QPainter>
#include <iostream>
#include <sstream>

#include "player.h"

LevelScene::LevelScene(QImage backgroundBrush, int level, int nOutputWidth, int nOutputHeight, int **mapArr): QGraphicsScene()
{
    setSceneRect(0,0,3840,2168);
    setBackgroundBrush(QBrush(backgroundBrush));
    sceneWidth = nOutputWidth;
    sceneHeight = nOutputHeight;
    mapA = mapArr;
    initializeObstacles();
    currentLevel = level;
}

void LevelScene::initializeObstacles()
{
    qDebug()<<"hey!";
    bool tOutSet = false;
    bool tBackSet = false;

    if (!tBackSet and !tOutSet)
    {
        for (int y=0; y<sceneHeight; ++y)
        {
            for(int x=0; x<sceneWidth; ++x)
            {
                if (mapA[x][y]!=0 and mapA[x][y]!=6)
                {
                    tBackSet =createTeleporterBack(x, y, 3500, tBackSet);
                    tOutSet = createTeleporterOut(x, y, 7000, tOutSet);
                }
            }
        }
    }
    if(!tBackSet)
    {
        for (int y=0; y<sceneHeight; ++y)
        {
            for(int x=0; x<sceneWidth; ++x)
            {
                if (mapA[x][y]!=0 and mapA[x][y]!=6)
                {
                    tBackSet =createTeleporterBack(x, y, 3500, tBackSet);
                }
            }
        }
    }
    if(!tOutSet)
    {
        for (int y=0; y<sceneHeight; ++y)
        {
            for(int x=0; x<sceneWidth; ++x)
            {
                if (mapA[x][y]!=0 and mapA[x][y]!=6)
                {
                    tOutSet = createTeleporterOut(x, y, 7000, tOutSet);
                }
            }
        }
    }

    QImage *rocher = new QImage;
    rocher->load(":/Assets/rocher.png");

    QImage *buisson = new QImage;
    buisson->load(":/Assets/buisson.png");

    QImage *mont = new QImage;
    mont->load(":/Assets/mont20.png");

    for (int y=0; y<sceneHeight; ++y)
    {
        for(int x=0; x<sceneWidth; ++x)
        {
            if(mapA[x][y]== 3)
            {
                QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*rocher));
                obstacle->setPos(x*32, y*32);
                obstacle->setPixmap(QPixmap::fromImage(*rocher));
                this->addItem(obstacle);
            }
            else if(mapA[x][y]==4)
            {
                QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*buisson));
                obstacle->setPos(x*32, y*32);
                addItem(obstacle);

            }
            else if (mapA[x][y]==6)
            {
                QGraphicsPixmapItem *obstacle = new QGraphicsPixmapItem(QPixmap::fromImage(*mont));
                obstacle->setPos(x*32, y*32);
                addItem(obstacle);
            }
            else if (mapA[x][y]==7)
            {
                std::string temp0;
                std::ostringstream temp1;

                temp1 <<"N :"<<(int)(currentLevel);
                temp0 = temp1.str();

                QImage *telBack = new QImage;
                telBack->load(":/Assets/teleporterBack.png");
                QPainter *p = new QPainter(telBack);
                QString strDisplay = QString::fromUtf8(temp0.c_str());
                p->setPen(QPen(Qt::white));
                p->setFont(QFont("Times", 10, QFont::Bold));
                p->drawText(telBack->rect(), Qt::AlignCenter, strDisplay);

                QGraphicsPixmapItem *teleporter = new QGraphicsPixmapItem(QPixmap::fromImage(*telBack));
                teleporter->setPos((x-1)*32, (y-1)*32);
                addItem(teleporter);

                Player *player = new Player();
                player->setPos((x-1)*32, (y-1)*32);

                addItem(player);
                player->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
                player->setFocus();
            }
            else if (mapA[x][y]==8)
            {
                std::string temp0;
                std::ostringstream temp1;

                temp1 <<"N :"<<(int)(currentLevel + 1);
                temp0 = temp1.str();

                QImage *telOut = new QImage;
                telOut->load(":/Assets/teleporterOut.png");

                QPainter *p = new QPainter(telOut);
                QString strDisplay = QString::fromUtf8(temp0.c_str());
                p->setPen(QPen(Qt::white));
                p->setFont(QFont("Times", 10, QFont::Bold));
                p->drawText(telOut->rect(), Qt::AlignCenter, strDisplay);

                QGraphicsPixmapItem *teleporter = new QGraphicsPixmapItem(QPixmap::fromImage(*telOut));
                teleporter->setPos((x-1)*32, (y-1)*32);
                addItem(teleporter);
            }
        }
    }
}

void LevelScene::surroundingsEquals(int x, int y, int R)
{
    mapA[x][y]=R;

    mapA[x+1][y]=0;
    mapA[x+1][y-1]=0;
    mapA[x+1][y+1]=0;
    mapA[x][y-1]=0;

    mapA[x][y+1]=0;
    mapA[x-1][y]=0;
    mapA[x-1][y-1]=0;
    mapA[x-1][y+1]=0;
}


bool LevelScene::createTeleporterBack(int x, int y, int threshold, bool tSet)
{
    int i = x*y;
    if (!tSet and i>=threshold and x<(sceneWidth/2) and x>3 and y>3 and y<sceneWidth-3 and y<sceneHeight-3)
    {
        teleporterBack = QPoint(x, y);
        surroundingsEquals(x, y, 7);
        tSet = true;
    }
    else if(!tSet and x>3 and y>3 and x<sceneWidth-3 and x<sceneHeight-3)
    {
        if (rand()%1001==1000 and x<(sceneWidth/2))
        {
            teleporterBack = QPoint(x, y);
            surroundingsEquals(x, y, 7);
            tSet = true;
        }
    }
    return tSet;
}

bool LevelScene::createTeleporterOut(int x, int y, int threshold, bool tSet)
{
    int i=x*y;

    if (!tSet and i>=threshold and x>(sceneWidth/2) and x>3 and y>3 and x<sceneWidth-3 and y<sceneHeight-3)
    {
        teleporterOut = QPoint(x, y);
        surroundingsEquals(x, y, 8);
        tSet = true;
    }
    else if(!tSet)
    {
        if (rand()%1001==1000 and x>(sceneWidth/2) and x>3 and y>3 and x<sceneWidth-3 and y<sceneHeight-3)
        {
            teleporterOut = QPoint(x, y);
            surroundingsEquals(x, y, 8);
            tSet = true;
        }
    }
    return tSet;
}
