#include <QtGui/QApplication>
#include "se_terminal.h"
#include <QTextCodec>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QPoint>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

    se_terminal w;
    w.resize(720,1280);
    w.show();

    return a.exec();
}


