#ifndef LINK_H
#define LINK_H
#include "pixmapitem.h"

#include <QObject>
#include <QGraphicsRectItem> // les objets de la scene
class Player: public PixmapItem{
    Q_OBJECT
public:
    Player();
    void keyPressEvent(QKeyEvent * event);

    int getmovement() const { return this->movement; } // définition au sein de la classe
    void setmovement(int value);

    int getlongueur() const { return this->longueur; } // définition au sein de la classe
    void setlongueur(int longueur);

    int getlargeur() const { return this->largeur; } // définition au sein de la classe
    void setlargeur(int largeur);
public slots:
private:
    int movement ;
    int largeur ;
    int longueur ;

};

inline void Player::setmovement(int movement) // définition au sein de la classe (inline)
{
    this->movement = movement;
}
inline void Player::setlongueur(int longueur) // définition au sein de la classe (inline)
{
    this->longueur = longueur;
}
inline void Player::setlargeur(int largeur) // définition au sein de la classe (inline)
{
    this->largeur = largeur;
}


#endif // LINK_H
