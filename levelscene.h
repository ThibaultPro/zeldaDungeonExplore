#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

#include "player.h"
#include "pixmapitem.h"


class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LevelScene(QImage backgroundBrush, int level, int nOutputWidth, int nOutputHeight, int **mapArr);
    void initializeObstacles();

    void surroundingsEquals(int x, int y, int R);
    bool createTeleporterBack(int x, int y, int R, bool tSet);
    bool createTeleporterOut(int x, int y, int R, bool tSet);

public slots:
    void goUp();
    void goDown();
    void goLeft();
    void goRight();

private:
    int currentLevel;
    int sceneWidth;
    int sceneHeight;
    int **mapA;
    QPoint teleporterOut;
    QPoint teleporterBack;
    Player *player;
};

#endif // LEVELSCENE_H
