#include "player.h"
#include "sword.h"
#include "enemy.h"

// le header
#include <QGraphicsScene>
#include <QtEvents>
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

Player::Player() : PixmapItem(QString(":/Assets/walkR10.png"))
{
setFlag(QGraphicsItem::ItemIsFocusable);
setFocus();
setZValue(8);
setlargeur(10);
setlongueur(10);
setmovement(10);
//scene()->addItem(this);

};
void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        //if (pos().x() > 0)
        emit goLeft();
        changePix(":/Assets/walkL1.png");
        //setPos(x() - getmovement(), y());
    }
    if (event->key() == Qt::Key_Right){
        //if(pos().x() + getlongueur() < height)
        emit goRight();
        changePix(":/Assets/walkR1.png");
        //setPos(x() + getmovement(), y());
    }
    if (event->key() == Qt::Key_Up){
        //if(pos().y() - getlargeur() > -width)
        emit goUp();
        changePix(":/Assets/walkU1.png");
        //setPos(x() , y()- getmovement());
    }
    if (event->key() == Qt::Key_Down){
        //if(pos().y()<0)
        emit goDown();
        changePix(":/Assets/walkD1.png");
       // setPos(x(), y() + getmovement());
    }

    if (event->key() == Qt::Key_Z){

        //attack with sword
        sword * Psword = new sword();
   //     Psword->setRect(0,0,Psword->getlargeurEpee(),Psword->getlongeurEpee());
        Psword->setPos(x()+getlongueur()-Psword->getlargeurEpee(),y()-Psword->getlongeurEpee());//la pos de l'épée
        Psword->setPixmap(QPixmap(":/Assets/swordU.png"));
        scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_D){

        //attack with sword
        sword * Psword = new sword();
      //  Psword->setRect(0,0,Psword->getlongeurEpee(),Psword->getlargeurEpee());
          Psword->setPos(x()+getlongueur(),y()+getlargeur()-Psword->getlargeurEpee());//la pos de l'épée
          Psword->setPixmap(QPixmap(":/Assets/swordR.png"));
          scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_Q){

        //attack with sword
        sword * Psword = new sword();
   //     Psword->setRect(0,0,Psword->getlongeurEpee(),Psword->getlargeurEpee());
          Psword->setPos(x()-Psword->getlongeurEpee(),y());//la pos de l'épée
          Psword->setPixmap(QPixmap(":/Assets/swordL.png"));
          scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_S){

        //attack with sword
        sword * Psword = new sword();
     //   Psword->setRect(0,0,Psword->getlargeurEpee(),Psword->getlongeurEpee());
          Psword->setPos(x(),y()+getlargeur());//la pos de l'épée
          Psword->setPixmap(QPixmap(":/Assets/swordD.png"));
          scene()->addItem(Psword);
    }
}


