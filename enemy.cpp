#include "enemy.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h>
#include <QObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include "sword.h"

enemy::enemy(): QObject(),QGraphicsPixmapItem(){

    setlargeurE(10);
    setlongueurE(10);


    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    //set Random nb
    int random_nbW = rand() % (width-100);
    int random_nbH = rand() % (height-100);
    setPos(random_nbH,random_nbW);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void enemy::move(){
    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();
    //set Random nb
    int dir = rand() % 8;
    int dis = rand() % 5;

    QPixmap pixL = QPixmap(":/Assets/cyclopeL1.png");
    QPixmap pixU = QPixmap(":/Assets/cyclopeUp.png");
    QPixmap pixR = QPixmap(":/Assets/cyclopeR1.png");
    QPixmap pixD = QPixmap(":/Assets/cyclopeDOWN.png");
    switch(dir) {
      case 1:
        if(pos().y()<0){
            setPos(x(),y()+dis);
            setPixmap(pixL);
        }
        break;
      case 2:
        if(pos().y() - getlargeurE() > -width){
            setPos(x(),y()-dis);
            setPixmap(pixL);
        }
        break;
      case 3:
        if(pos().y()<0 && pos().x() + getlongueurE() < height){
          setPos(x()+dis,y()+dis);
          setPixmap(pixL);
        }
      break;
      case 4:
       if(pos().y() - getlargeurE() > -width && pos().x() + getlongueurE() < height){
           setPos(x()+dis,y()-dis);
           setPixmap(pixD);
       }
      break;
      case 5:
        if(pos().y() <0 && pos().x()>0){
            setPos(x()-dis,y()+dis);
            setPixmap(pixD);
        }
      break;
      case 6:
        if(pos().y()  - getlargeurE() > -width && pos().x()>0){
            setPos(x()-dis,y()-dis);
            setPixmap(pixD);
        }
      break;
      case 7:
        if(pos().x()+ getlongueurE() < height){
            setPos(x()+dis,y());
            setPixmap(pixD);
        }
      break;
      case 8:
        if(pos().x()>0){
            setPos(x()-dis,y());
            setPixmap(pixU);
        }
      break;
      default:
         setPos(x(),y());
        setPixmap(pixU);
    }

    //si l'enemy touche
    QList<QGraphicsItem *>  colliding_items = collidingItems();
    for (int i = 0, n=colliding_items.size(); i<n; ++i){
        if (typeid (*(colliding_items[i]))== typeid (sword))
        {//on detruit 1pv et l'enemie
            //NbVie->perdreVie();
            delete colliding_items[i];
            delete this;
            qDebug() << "-1pv";
            return;

        }
    }
}
