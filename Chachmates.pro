QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    figure.cpp \
    main.cpp \
    bishop.cpp \
    button.cpp \
    chessboard.cpp \
    chessbox.cpp \
    game.cpp \
    king.cpp \
    knight.cpp \
    pawn.cpp \
    queen.cpp \
    rook.cpp \
    exchangebuttons.cpp

HEADERS += \
    bishop.h \
    button.h \
    chessboard.h \
    chessbox.h \
    figure.h \
    game.h \
    king.h \
    knight.h \
    pawn.h \
    queen.h \
    rook.h \
    exchangebuttons.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images/Images.qrc
