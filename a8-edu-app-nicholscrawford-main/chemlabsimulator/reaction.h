/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#ifndef REACTION_H
#define REACTION_H
#include <QLabel>
#include "chemical.h"

class reaction
{
public:
    reaction();
    reaction(QString, QString, std::vector<QString>);
    QString name;
    QString chemEquation;
    bool isComplete;
    std::vector<QString> reactants;
    std::vector<QString> chemicalsAddedToReaction;
    void addChemical(QString);
    void reset();
};

#endif // REACTION_H
