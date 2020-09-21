#include "player.h" // le header
#include <QGraphicsScene>
#include <QtEvents>
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

Player::Player() : PixmapItem(QString(":/Assets/walkR10.png"))
{
setFlag(QGraphicsItem::ItemIsFocusable);
setFocus();
setlargeur(10);
setlongueur(10);
setmovement(10);
};
void Player::keyPressEvent(QKeyEvent *event){

    const int width = QApplication::desktop()->width();
    const int height = QApplication::desktop()->height();

    if (event->key() == Qt::Key_Left){
        //if (pos().x() > 0)
        setPos(x()-getmovement(),y());
    }
    else if (event->key() == Qt::Key_Right){
        //if(pos().x() + getlongueur() < height)
        setPos(x()+getmovement(),y());
    }
    else if (event->key() == Qt::Key_Up){
        //if(pos().y() - getlargeur() > -width)
        setPos(x(),y()-getmovement());
    }
    else if (event->key() == Qt::Key_Down){
        //if(pos().y()<0)
        setPos(x(),y()+getmovement());
    }
    /**
    else if (event->key() == Qt::Key_Z){

        //attack with sword
        sword * Psword = new sword();
        Psword->setRect(0,0,Psword->getlargeurEpee(),Psword->getlongeurEpee());
        Psword->setPos(x()+getlongueur()-Psword->getlargeurEpee(),y()-Psword->getlongeurEpee());//la pos de l'épée
        scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_D){

        //attack with sword
        sword * Psword = new sword();
        Psword->setRect(0,0,Psword->getlongeurEpee(),Psword->getlargeurEpee());
        Psword->setPos(x()+getlongueur(),y()+getlargeur()-Psword->getlargeurEpee());//la pos de l'épée
        scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_Q){

        //attack with sword
        sword * Psword = new sword();
        Psword->setRect(0,0,Psword->getlongeurEpee(),Psword->getlargeurEpee());
        Psword->setPos(x()-Psword->getlongeurEpee(),y());//la pos de l'épée
        scene()->addItem(Psword);
    }
    else if (event->key() == Qt::Key_S){

        //attack with sword
        sword * Psword = new sword();
        Psword->setRect(0,0,Psword->getlargeurEpee(),Psword->getlongeurEpee());
        Psword->setPos(x(),y()+getlargeur());//la pos de l'épée
        scene()->addItem(Psword);
    }
    **/
}
