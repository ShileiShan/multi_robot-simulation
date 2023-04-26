#include "mainwindow.h"
#include <QApplication>
#include<QProcess>
#include <memory>
using namespace std;
int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    std::shared_ptr<QProcess> p1(new QProcess);
    MainWindow w(argc,argv,p1);
    w.setWindowTitle("Multi-Robot Simulation");
    w.show();
    return a.exec();
}
