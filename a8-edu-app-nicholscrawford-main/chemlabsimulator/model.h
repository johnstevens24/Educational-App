/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "reaction.h"
#include "QFile"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    void addChemToReaction();
    int windowWidth;
    int windowHeight;
    int potassiumWidth;
    int potassiumHeight;
    int sodiumWidth;
    int sodiumHeight;
    int lithiumWidth;
    int lithiumHeight;
    int calciumWidth;
    int calciumHeight;
    int copperWidth;
    int copperHeight;
    bool burnerOn;
    int fireTop;
    int fireBottom;


private:
    bool canAddChemicals;
    reaction currentReaction;
    QMap<QString, reaction> reactions;
    QLabel* currentSelectedChemical = nullptr;
    QPoint currentSelectedChemicalOrigin;
    QVector<QLabel*> chemicalLabels;
    QString currentChem;
    QMap<QString, QString> nameAndChemPairs;
    QMap<QString, QString> reactionInfoFileNames;
    void addChemToPhysics(QPoint pos);
    void addWater();
    QMap<QString, QString> tutorialTextMap;
    bool tutorialActive;
    bool endOfTutorial;
    void getAddChemicalTutorialStep();


public slots:
    void setReaction(QString reaction);
    void chemicalClicked(QPoint pos);
    void chemicalMoved(QPoint pos);
    void chemicalReleased(QPoint pos);
    void addChemicalLabel(QLabel* label);
    void resetEquation();
    void gatherInfo();   
    void startTutorial();


signals:
    void updateReactionDescriptionLabel(QString description);
    void updateEquationLabel(QString equation);
    void moveChemcial(QLabel* chemical, QPoint pos);
    void returnInfo(QString reaction, QString info);
    void flameIndexChanged(int);
    void addElement(QString imagePath, float scaleFactor, QPoint pos, bool WindowCoords);
    void clearWorld();
    void replaceAllPictures(QString path);
    void playExplosionAnimation();
    void sendTutorialText(QString tip);
    void endTheTutorial();
};

#endif // MODEL_H
