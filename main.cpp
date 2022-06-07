#include "mainwindow.h"

#include <QApplication>
#include <GameController.hpp>
#include <memory.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto gc = std::make_shared<GameController>();

    MainWindow w(gc);
    w.show();
    return a.exec();
}
