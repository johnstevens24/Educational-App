/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#ifndef CHEMICAL_H
#define CHEMICAL_H
#include <QLabel>

class chemical
{
public:
    chemical();
    chemical(QString, QString);
    QString name;
    QString chemValue;

};

#endif // CHEMICAL_H
