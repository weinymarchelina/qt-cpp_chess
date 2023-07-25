QT       += core gui \
            multimedia \
            widgets \
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    board.cpp \
    gamewindow.cpp \
    king.cpp \
    knight.cpp \
    main.cpp \
    menuwindow.cpp \
    pawn.cpp \
    player.cpp \
    position.cpp \
    queen.cpp \
    resultwindow.cpp \
    rook.cpp

HEADERS += \
    bishop.h \
    board.h \
    gamewindow.h \
    king.h \
    knight.h \
    menuwindow.h \
    pawn.h \
    player.h \
    position.h \
    queen.h \
    resultwindow.h \
    rook.h

FORMS += \
    gamewindow.ui \
    menuwindow.ui \
    resultwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    sound/bgmusic_1.mp3 \
    sound/bgmusic_2.mp3 \
    sound/bgmusic_3.mp3
