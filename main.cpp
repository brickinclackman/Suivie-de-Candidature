#include "fenprincipsc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenPrincipSC w;
    w.show();
    return a.exec();
}
