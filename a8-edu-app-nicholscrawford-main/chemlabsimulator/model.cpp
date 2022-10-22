/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#include "model.h"
#include <iostream>

Model::Model(QObject *parent)
    : QObject{parent}
{
    canAddChemicals = false;
    resetEquation();

    //Creates/adds the reactions to the model
    reactions.insert("MakingWater", reaction("Synthesis of Water","Heat + 2H<sub>2</sub> + O<sub>2</sub> -> 2H<sub>2</sub>O", {"Heat", "2H<sub>2</sub>", "O<sub>2</sub>"}));
    reactions.insert("BurningFuel", reaction("Decomposition of Propane", "Heat + C<sub>6</sub>H<sub>8</sub> + 8O<sub>2</sub> -> 6CO<sub>2</sub> + 4H<sub>2</sub>O", {"Heat", "C<sub>6</sub>H<sub>8</sub>", "8O<sub>2</sub>"}));
    reactions.insert("MetalFlameTest", reaction("Metal Flame Test", "Hold a metal over the flame", {}));
    reactions.insert("ColorChange", reaction("Phenol and Ferric Chloride in Water", "3C<sub>6</sub>H<sub>5</sub>OH + FeCl<sub>3</sub> -> Fe(C<sub>6</sub>H<sub>5</sub>O)3 + 3HCl", {"3C<sub>6</sub>H<sub>5</sub>OH", "FeCl<sub>3</sub>"}));

    //Sets up a table that pairs the chemical names with their formulas
    nameAndChemPairs.insert("hydrogenGas","2H<sub>2</sub>");
    nameAndChemPairs.insert("water", "H<sub>2</sub>O");
    nameAndChemPairs.insert("oxygenGas","O<sub>2</sub>");
    nameAndChemPairs.insert("propane","C<sub>6</sub>H<sub>8</sub>");
    nameAndChemPairs.insert("ferricChloride","FeCl<sub>3</sub>");
    nameAndChemPairs.insert("phenol","3C<sub>6</sub>H<sub>5</sub>OH");
    nameAndChemPairs.insert("potassiumMetal","");
    nameAndChemPairs.insert("sodiumMetal","");
    nameAndChemPairs.insert("energy","Heat");

    //Sets up a map of pairs of reaction names with their detailed info .txt file
    reactionInfoFileNames.insert("Synthesis of Water", "://textInfo/water reaction info.txt");
    reactionInfoFileNames.insert("Decomposition of Propane", "://textInfo/combustion of propane info.txt");
    reactionInfoFileNames.insert("Metal Flame Test", "://textInfo/flame test info.txt");
    reactionInfoFileNames.insert("Phenol and Ferric Chloride in Water", "://textInfo/phenol fecl3 info.txt");

    //Sets up a map of pairs of tutorial steps and the info given to the user in said step
    tutorialTextMap.insert("Add Chemical","Hover over chemicals\nto see their name and\nchemical formula.\nClick and drag chemicals\nand items to add them\nto the beaker.");
    tutorialTextMap.insert("Added Correct Chemical","When an item is added\ncorrectly, it will turn\ngreen in the equation.\nWhen everything is\nadded correctly, the\nequation will turn green\nand the reaction will occur.");
    tutorialTextMap.insert("Incorrect Chemical Added","When something is incorrectly\nadded, the equation will turn\nred and you need to press the\nreset button to try again.");
    tutorialTextMap.insert("Finished Reaction","Select a reaction from the\ndropdown menu in the top\nleft to switch reactions");
    tutorialTextMap.insert("Selected New Reaction","Click the 'I' information\nbutton for more info on the\ncurrently selected reaction.");

    //Defaults the tutorial to being inactive
    tutorialActive = false;
}

/**
 * @brief Model::setReaction - sets the current reaction. This is a slot for a dropdown menu in the view.
 * @param reaction - the reaction that the model is switching to.
 */
void Model::setReaction(QString reaction)
{
    currentReaction = reactions[reaction];
    emit updateReactionDescriptionLabel(currentReaction.name);
    resetEquation();

    if(tutorialActive)
    {
        emit sendTutorialText(tutorialTextMap["Selected New Reaction"]);
        //Since it is usually the last step in the tutorial, sets it up to end the tutorial
        endOfTutorial = true;
    }
}

/**
 * @brief Model::chemicalClicked
 * @param pos
 */
void Model::chemicalClicked(QPoint pos)
{
    pos.setY(pos.y() - 20);
    for(QLabel* label : chemicalLabels)
    {
        bool insideY = pos.y() > label->frameGeometry().top() && pos.y() < (label->frameGeometry().top() + label->frameGeometry().height());
        bool insideX = pos.x() > label->frameGeometry().left() && pos.x() < (label->frameGeometry().left() + label->frameGeometry().width());
        if(insideX && insideY){
            currentSelectedChemical = label;
            currentSelectedChemicalOrigin = label->pos();
            currentChem = label->text();
            break;
        }

    }
}

/**
 * @brief Model::chemicalMoved Called when a chemical is being dragged around.
 * @param pos Current mouse position
 */
void Model::chemicalMoved(QPoint pos)
{
    if(currentSelectedChemical){
        pos.setX(pos.x() - currentSelectedChemical->width()/2);
        pos.setY(pos.y() - currentSelectedChemical->height()/2);
        emit moveChemcial(currentSelectedChemical, pos);

        // checking for chemical on top of flame to switch color. Emits to the mainwindow which color is now active
        if(currentSelectedChemical->objectName() == "sodiumMetal" && burnerOn){
            if(pos.x() > (((windowWidth)/2) - ((1.3) * sodiumWidth))  && pos.x() < ((windowWidth)/2) && pos.y() > fireTop && pos.y() < fireBottom + sodiumHeight){
                emit flameIndexChanged(1);
            }
            else{
                emit flameIndexChanged(0);
            }
        }
        else if(currentSelectedChemical->objectName() == "potassiumMetal" && burnerOn){
            if(pos.x() > ((windowWidth)/2) - (1.2) * potassiumWidth  && pos.x() < ((windowWidth)/2) && pos.y() > fireTop && pos.y() < fireBottom + potassiumHeight){
                // flame switch
                emit flameIndexChanged(3);
            }
            else {
                emit flameIndexChanged(0);
            }
        }
        else if(currentSelectedChemical->objectName() == "lithiumLabel" && burnerOn){
            if(pos.x() > ((windowWidth)/2) - (1.2) * lithiumWidth  && pos.x() < ((windowWidth)/2) && pos.y() > fireTop && pos.y() < fireBottom + lithiumHeight){
                // flame switch
                emit flameIndexChanged(5);
            }
            else {
                emit flameIndexChanged(0);
            }
        }
        else if(currentSelectedChemical->objectName() == "copperLabel" && burnerOn){
            if(pos.x() > ((windowWidth)/2) - (1.4) * copperWidth  && pos.x() < ((windowWidth)/2) && pos.y() > fireTop && pos.y() < fireBottom + copperHeight){
                // flame switch
                emit flameIndexChanged(4);
            }
            else {
                emit flameIndexChanged(0);
            }
        }
        else if(currentSelectedChemical->objectName() == "calciumLabel" && burnerOn){
            if(pos.x() > ((windowWidth)/2) - (1.3) * calciumWidth  && pos.x() < ((windowWidth)/2) && pos.y() > fireTop && pos.y() < fireBottom + calciumHeight){
                // flame switch
                emit flameIndexChanged(2);
            }
            else {
                emit flameIndexChanged(0);
            }
        }

        //saves the current chemical name to be used in the addChemToReaction method
        currentChem = currentSelectedChemical->objectName();
    }

}

/**
 * @brief Model::chemicalReleased Called when a chemical being dragged is let go
 * @param pos Mouse position where it's been let go
 */
void Model::chemicalReleased(QPoint pos)
{
    //checks to see if its in the "hitbox" of the beaker
    if(currentChem != "" && canAddChemicals == true && pos.x() > 308 && pos.x() < 513 && pos.y() > 169 && pos.y() < 417)
    {
        addChemToPhysics(pos);
        addChemToReaction();
    }

    if(currentSelectedChemical){
        emit moveChemcial(currentSelectedChemical, currentSelectedChemicalOrigin);
        currentSelectedChemical = nullptr;
    }

    currentChem = "";
    // when a chemical is let go, flame needs to go back to standard color
    emit flameIndexChanged(0);
}

void Model::addChemicalLabel(QLabel* label)
{
    chemicalLabels.append(label);
}

/**
 * @brief Model::addChemToReaction - Adds the currently selected chemical to the current reaction and updates the view.
 */
void Model::addChemToReaction()
{
    //If the last tutorial step has already been sent, ends the tutorial
    if(endOfTutorial)
    {
        emit endTheTutorial();
        tutorialActive = false;
    }

    if(nameAndChemPairs.contains(currentChem) && currentReaction.name != "Metal Flame Test")
    {
        //gets the chemical formula of the current chem ex: hydrogenGas will return 2H2
        QString chemicalFormula = nameAndChemPairs.value(currentChem);

        //adds an 8 in front for the burning fuel equation
        if(currentReaction.name == "Decomposition of Propane" && chemicalFormula == "O<sub>2</sub>")
        {
            chemicalFormula = "8O<sub>2</sub>";
        }

        bool contains = false;

        //checks to see if it is one of the reactants of the current reaction
        for(QString t : currentReaction.reactants)
        {
            if(t.compare(chemicalFormula) == 0)
                contains = true;
        }

        //if it is one of the reactants, it proceeds
        if(contains == true)
        {
            //Gives the next tutorial step if the tutorial is active
            if(tutorialActive)
            {
                emit sendTutorialText(tutorialTextMap["Added Correct Chemical"]);
            }

            //adds the current chemical to the reaction
            currentReaction.addChemical(chemicalFormula);

            //get the current chemical equation from the view
            QString chemicalEquationString = currentReaction.chemEquation;
            int endOfReactantsIndex = chemicalEquationString.indexOf("-");

            //separate the reactant side of the equation
            QString reactants = chemicalEquationString.mid(0, endOfReactantsIndex);

            //goes through each of the chemicals that were added to the current reaction and makes them green
            for(QString tempChem : currentReaction.chemicalsAddedToReaction)
            {
                if(reactants.contains(tempChem))
                {
                    QString tempString = "<font color='green'>";
                    tempString += tempChem;
                    tempString += "</font>";
                    reactants.replace(tempChem, tempString);

                }
             }

            //puts the pieces of the reaction string back together
            reactants += chemicalEquationString.mid(endOfReactantsIndex, chemicalEquationString.length()-1);
            emit updateEquationLabel(reactants);

            //check to see if the reaction is complete
            if(currentReaction.isComplete == true)
            {
                canAddChemicals = false;

                //Gives the next tutorial step if the tutorial is active
                if(tutorialActive)
                {
                    emit sendTutorialText(tutorialTextMap["Finished Reaction"]);
                }

                //makes the whole equation green
                QString chemicalEquationString = currentReaction.chemEquation;
                chemicalEquationString = "<font color='green'>" + chemicalEquationString + "</font>";
                emit updateEquationLabel(chemicalEquationString);  

                //Adjust the physics scene to the finished experiment
                if(currentReaction.name == "Synthesis of Water")
                {
                    //Udate the physics scene for the finished reaction
                    emit clearWorld();
                    addWater();
                }
                if(currentReaction.name == "Phenol and Ferric Chloride in Water")
                {
                    //Changes all of the water in the scene to purple
                    emit replaceAllPictures(":/backgroundImage/img/purpleWater.png");

                }
                if(currentReaction.name == "Decomposition of Propane")
                {
                   emit clearWorld();
                   emit playExplosionAnimation();
                }

            }

        }
        else
        {
            //update the view to show that you added something wrong to the reaction
            QString chemicalEquationString = currentReaction.chemEquation;
            chemicalEquationString = "<font color='red'>" + chemicalEquationString + "</font>";
            emit updateEquationLabel(chemicalEquationString);
            canAddChemicals = false;

            //Gives the next tutorial step if the tutorial is active in response to user error
            if(tutorialActive)
            {
                emit sendTutorialText(tutorialTextMap["Incorrect Chemical Added"]);
            }
        }


    }
}

/**
 * @brief Model::resetEquation - resets everything in the model.
 */
void Model::resetEquation()
{
    currentReaction.reset();
    canAddChemicals = true;

    //Gives the first step of the tutorial as the reaction is restarted
    if(tutorialActive){
        getAddChemicalTutorialStep();
    }

    //Clears any changes to the physics scene.
    emit clearWorld();
    emit updateEquationLabel(currentReaction.chemEquation);

    //the Phenol/Ferric Chloride reaction happens in water so it needs to be added
    if(currentReaction.name == "Phenol and Ferric Chloride in Water")
    {
        addWater();
    }
}

/**
 * @brief Model::gatherInfo - Gathers and sends the view the detailed, text description of a reaction with its name
 */
void Model::gatherInfo()
{
    QString reactionName = currentReaction.name;
    QString info;

    //Gets the text stored in the .txt file
    QString fileName(reactionInfoFileNames[reactionName]);
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {
        info = file.readAll();
    }
    file.close();

    emit returnInfo(reactionName, info);
}

/**
 * @brief Model::addChemToPhysics Add the current selected chemical
 * @param pos Mouse position to be translated to position within the physics scene
 */
void Model::addChemToPhysics(QPoint pos)
{
    if(currentSelectedChemical){
        //std::cout<<"CurrentReaction: "<<currentReaction.name.toStdString()<<std::endl;
        if(currentReaction.name == "Synthesis of Water")
        {
            if(currentSelectedChemical->objectName() == "oxygenGas")
            {
                emit addElement(":/backgroundImage/img/oxygen.png",10, pos, true);
            }

            if(currentSelectedChemical->objectName() == "hydrogenGas")
            {
                emit addElement(":/backgroundImage/img/hydrogen.png",10, pos, true);
            }
        }
        if(currentReaction.name == "Decomposition of Propane")
        {
            if(currentSelectedChemical->objectName() == "oxygenGas")
            {
                emit addElement(":/backgroundImage/img/oxygen.png",10, pos, true);
            }

            if(currentSelectedChemical->objectName() == "propane")
            {
                emit addElement(":/backgroundImage/img/propane.png",10, pos, true);
            }
        }
    }
}

/**
 * @brief Model::addWater Reusable method to fill the scene with water
 */
void Model::addWater()
{
    for(int i = 0; i < 40; i++)
        emit addElement(":/backgroundImage/img/water.png",4,  QPoint(5, 2), false);

}
/**
 * @brief Model::getAddChemicalTutorialStep - Gives the first step of the tutorial to the view
 */
void Model::getAddChemicalTutorialStep()
{
    QString tip = tutorialTextMap["Add Chemical"];
    emit sendTutorialText(tip);
}

/**
 * @brief Model::startTutorial - Activates the tutorial calls a getAddChemicalTutorialStep to send the first step
 */
void Model::startTutorial()
{
    tutorialActive = true;
    endOfTutorial = false;
    getAddChemicalTutorialStep();
}
