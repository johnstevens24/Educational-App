/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#include "reaction.h"

/**
 * @brief reaction::reaction - Default constructor for the reaction class
 */
reaction::reaction()
{
}

/**
 * @brief reaction::reaction - The reaction class constructor that takes arguments
 * @param name - the name of the reaction
 * @param equation - the chemical equation of the reaction
 * @param reactants - a list of all the reactants in the reaction
 */
reaction::reaction(QString name, QString equation, std::vector<QString> reactants)
{
    this->name = name;
    this->chemEquation = equation;
    this->reactants = reactants;
}

/**
 * @brief reaction::addChemical - this method adds a chemical to the list of added chemicals iff it hasn't already been added
 * @param newChem - the name of the chemical being added
 */
void reaction::addChemical(QString newChem)
{
    bool wasFound = false;
    for(QString chem : chemicalsAddedToReaction)
    {
        //if the newChem equals any of the already added chemicals, wasFound = true
        if(chem.compare(newChem) == 0)
        {
            wasFound = true;
            break;
        }
    }

    //if it wasn't found in the list of already added chemicals, add it to the list
    if(wasFound == false)
    {
       chemicalsAddedToReaction.push_back(newChem);
    }

    //if they contain the same number of items, the reaction must be complete
    if(reactants.size() == chemicalsAddedToReaction.size())
    {
        isComplete = true;
    }

}

/**
 * @brief reaction::reset - resets the reaction
 */
void reaction::reset(){
    chemicalsAddedToReaction.clear();
    isComplete = false;
}
