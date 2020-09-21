#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>

class LevelScene : public QGraphicsScene
{
public:
    LevelScene(QImage backgroundBrush, int level, int nOutputWidth, int nOutputHeight, int **mapArr);
    void initializeObstacles();

    void surroundingsEquals(int x, int y, int R);
    bool createTeleporterBack(int x, int y, int R, bool tSet);
    bool createTeleporterOut(int x, int y, int R, bool tSet);

private:
    int currentLevel;
    int sceneWidth;
    int sceneHeight;
    int **mapA;
    QPoint teleporterOut;
    QPoint teleporterBack;


};

#endif // LEVELSCENE_H
