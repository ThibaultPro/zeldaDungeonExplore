#include "gameview.h"
#include "gamescene.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QStyle>
#include <QWidget>
#include <QToolButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QtMath>
#include <QAbstractSlider>

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->angleDelta().y() > 0)
        view->zoomIn(6);
    else
        view->zoomOut(6);
}


View::View(const QString &name, QWidget *parent) : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);
    zoomSlider->hide();

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;

    zoomSliderLayout->addWidget(zoomSlider);

    QToolButton *rotateLeftIcon = new QToolButton;
    rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    rotateLeftIcon->setIconSize(iconSize);

    QToolButton *rotateRightIcon = new QToolButton;
    rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    rotateRightIcon->setIconSize(iconSize);
    rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(-360);
    rotateSlider->setMaximum(360);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);
    rotateSlider->hide();

    // Rotate slider layout
    QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    rotateSliderLayout->addWidget(rotateLeftIcon);
    rotateSliderLayout->addWidget(rotateSlider);
    rotateSliderLayout->addWidget(rotateRightIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    // Label layout
    // Label layout
    /**
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label = new QLabel(name);
    label2 = new QLabel(tr("Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);

    QButtonGroup *pointerModeGroup = new QButtonGroup(this);
    //pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);

    labelLayout->addWidget(label);
    labelLayout->addStretch();
    labelLayout->addWidget(label2);
    labelLayout->addWidget(selectModeButton);
    labelLayout->addWidget(dragModeButton);
    labelLayout->addStretch();
    **/

    QGridLayout *topLayout = new QGridLayout;
    //topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addLayout(rotateSliderLayout, 2, 0);
    topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    connect(resetButton, &QAbstractButton::clicked, this, &View::resetView);
    connect(zoomSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);
    connect(rotateSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);

    //connect(selectModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);
    //connect(dragModeButton, &QAbstractButton::toggled, this, &View::togglePointerMode);

    connect(rotateLeftIcon, &QAbstractButton::clicked, this, &View::rotateLeft);
    connect(rotateRightIcon, &QAbstractButton::clicked, this, &View::rotateRight);

    setupMatrix();
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    zoomSlider->setValue(250);
    rotateSlider->setValue(0);
    setupMatrix();
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QTransform matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotateSlider->value());

    graphicsView->setTransform(matrix);
    setResetButtonEnabled();
}

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::zoomIn(int level)
{
     zoomSlider->setValue(zoomSlider->value() + level);
     //qDebug()<<zoomSlider->value() + level;
}

void View::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
    //qDebug()<<zoomSlider->value() - level;
}

void View::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void View::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}
