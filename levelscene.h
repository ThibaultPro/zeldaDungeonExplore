#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <iostream>
#include <vector>

#include "player.h"
#include "pixmapitem.h"

using namespace std;
class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LevelScene(QImage backgroundBrush, int level, int nOutputWidth, int nOutputHeight, vector<vector<int>> mapArr);
    void initializeObstacles();

    void surroundingsEquals(int x, int y, int R);
    bool createTeleporterBack(int x, int y, int R, bool tSet);
    bool createTeleporterOut(int x, int y, int R, bool tSet);


public slots:
    void spawn();

signals:
    void reachedOut();

public slots:
    void goUp();
    void goDown();
    void goLeft();
    void goRight();

private:
    int *currentLevel;
    int sceneWidth;
    int sceneHeight;
    vector<vector<int>> mapA;
    QPoint teleporterOut;
    QPoint teleporterBack;
    Player *player;
};

#endif // LEVELSCENE_H
