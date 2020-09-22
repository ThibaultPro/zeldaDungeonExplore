#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H
#include <QImage>
#include <QDebug>
#include <QList>

#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include <opencv4/opencv2/imgcodecs.hpp>

#include <iostream>
#include <sstream>

#include "gameview.h"
#include "levelscene.h"
#include "pixmapitem.h"

using namespace std;
using namespace cv;


class DungeonGenerator
{
public:
    DungeonGenerator();
    void generatePerlinNoise(int nOutputWidth, int nOutputHeight, float *fNoiseSeed2D, int nOctaveCount, float fScalingBias, float *fPerlinNoise2D);
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);
    void createLevel();
    int* generateDiffuseNoise(int R, int nWidth, int nHeight);
    void createTeleporter(int i, int nOutputWidth, LevelScene level);

    LevelScene* getCurrentScene() const { return levels.last(); }

private:
    View *view;
    QList<LevelScene*> levels;
};

#endif // DUNGEONGENERATOR_H
