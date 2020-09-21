HEADERS += \
    controller.h \
    dungeongenerator.h \
    gameview.h \
    levelscene.h \
    pixmapitem.h \
    player.h

SOURCES += \
    controller.cpp \
    dungeongenerator.cpp \
    gameview.cpp \
    levelscene.cpp \
    main.cpp \
    pixmapitem.cpp \
    player.cpp

QT += \
    widgets \
    multimedia\
    core

RESOURCES += \
    res.qrc


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv4
