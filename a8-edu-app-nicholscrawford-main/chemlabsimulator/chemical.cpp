/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#include "chemical.h"

/**
 * @brief chemical::chemical - Default constructor of the chemical class
 */
chemical::chemical()
{

}

/**
 * @brief chemical::chemical - The chemical class constructor that takes in arguments
 * @param name - the name of the chemical
 * @param chemValue - the chemical value/formula of the chemical
 */
chemical::chemical(QString name, QString chemValue)
{
    this->name = name;
    this->chemValue = chemValue;
}
