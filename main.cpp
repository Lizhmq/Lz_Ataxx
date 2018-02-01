#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.Easy = 1;
    window.setWindowTitle("Ataxx");
    window.show();
    return a.exec();
}
