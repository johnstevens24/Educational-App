/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    MainWindow w(m);
    w.show();
    return a.exec();
}
