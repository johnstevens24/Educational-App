/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <iostream>
#include <QPixmap>
#include <vector>
#include <QTimer>
#include <QIcon>
#include "scenewindow.h"

MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), model(model)
{
    ui->setupUi(this);

    //Hides the bunsen burner labels
    ui->flameLabel->setHidden(true);
    ui->burnerLabel->setHidden(true);

    //places the metals behind the flame during flame test
    ui->lithiumLabel->lower();
    ui->copperLabel->lower();
    ui->beakerLabel->raise();

    //load the explosion animation gif
    explosionAnimation = new QMovie(":/other/img/explosionGif.gif");

    // adding all images to the UI
    QImage flaskPicture(":/backgroundImage/img/beaker.png");
    QImage flaskPictureScaled = flaskPicture.scaled(ui->beakerLabel->width(), ui->beakerLabel->height(), Qt::KeepAspectRatio);
    ui->beakerLabel->setPixmap(QPixmap::fromImage(flaskPictureScaled));

    QImage calciumPicture(":/backgroundImage/img/calcium.png");
    QImage calciumPictureScaled = calciumPicture.scaled(ui->calciumLabel->width(), ui->calciumLabel->height(), Qt::KeepAspectRatio);
    ui->calciumLabel->setPixmap(QPixmap::fromImage(calciumPictureScaled));

    QImage lithiumPicture(":/backgroundImage/img/lithium.png");
    QImage lithiumPictureScaled = lithiumPicture.scaled(ui->lithiumLabel->width(), ui->lithiumLabel->height(), Qt::KeepAspectRatio);
    ui->lithiumLabel->setPixmap(QPixmap::fromImage(lithiumPictureScaled));

    QImage copperPicture(":/backgroundImage/img/copper.png");
    QImage copperPictureScaled = copperPicture.scaled(ui->copperLabel->width(), ui->copperLabel->height(), Qt::KeepAspectRatio);
    ui->copperLabel->setPixmap(QPixmap::fromImage(copperPictureScaled));

    QImage potassiumPicture(":/backgroundImage/img/potassium.png");
    QImage potassiumPictureScaled = potassiumPicture.scaled(ui->potassiumMetal->width(), ui->potassiumMetal->height(), Qt::KeepAspectRatio);
    ui->potassiumMetal->setPixmap(QPixmap::fromImage(potassiumPictureScaled));

    QImage sodiumPicture(":/backgroundImage/img/sodium.png");
    QImage sodiumPictureScaled = sodiumPicture.scaled(ui->sodiumMetal->width(), ui->sodiumMetal->height(), Qt::KeepAspectRatio);
    ui->sodiumMetal->setPixmap(QPixmap::fromImage(sodiumPictureScaled));

    QImage ferricChloridePicture(":/backgroundImage/img/ferric chloride.png");
    QImage ferricChloridePictureScaled = ferricChloridePicture.scaled(ui->ferricChloride->width(), ui->ferricChloride->height(), Qt::KeepAspectRatio);
    ui->ferricChloride->setPixmap(QPixmap::fromImage(ferricChloridePictureScaled));

    QImage hydrogenPicture(":/backgroundImage/img/hydrogen.png");
    QImage hydrogenPictureScaled = hydrogenPicture.scaled(ui->hydrogenGas->width(), ui->hydrogenGas->height(), Qt::KeepAspectRatio);
    ui->hydrogenGas->setPixmap(QPixmap::fromImage(hydrogenPictureScaled));

    QImage phenolPicture(":/backgroundImage/img/phenol.png");
    QImage phenolPictureScaled = phenolPicture.scaled(ui->phenol->width(), ui->phenol->height(), Qt::KeepAspectRatio);
    ui->phenol->setPixmap(QPixmap::fromImage(phenolPictureScaled));

    QImage waterPicture(":/backgroundImage/img/water.png");
    QImage waterPictureScaled = waterPicture.scaled(ui->water->width(), ui->water->height(), Qt::KeepAspectRatio);
    ui->water->setPixmap(QPixmap::fromImage(waterPictureScaled));

    QImage oxygenPicture(":/backgroundImage/img/oxygen.png");
    QImage oxygenPictureScaled = oxygenPicture.scaled(ui->oxygenGas->width(), ui->oxygenGas->height(), Qt::KeepAspectRatio);
    ui->oxygenGas->setPixmap(QPixmap::fromImage(oxygenPictureScaled));

    QImage energyPicture(":/backgroundImage/img/regularFlame.png");
    QImage energyPictureScaled = energyPicture.scaled(ui->energy->width(), ui->energy->height(), Qt::KeepAspectRatio);
    ui->energy->setPixmap(QPixmap::fromImage(energyPictureScaled));

    QImage propanePicture(":/backgroundImage/img/propane.png");
    QImage propanePictureScaled = propanePicture.scaled(ui->propane->width(), ui->propane->height(), Qt::KeepAspectRatio);
    ui->propane->setPixmap(QPixmap::fromImage(propanePictureScaled));



    // setting burner on connections
    ui->startBurnerButton->setVisible(false);
    connect(ui->startBurnerButton, &QPushButton::clicked, this, &MainWindow::startFlame);
    QImage orangeFlameOne(":/backgroundImage/img/orange_flame_001.png");
    QImage orangeFlameTwo(":/backgroundImage/img/orange_flame_002.png");
    QImage orangeFlameThree(":/backgroundImage/img/orange_flame_003.png");
    QImage orangeFlameFour(":/backgroundImage/img/orange_flame_004.png");
    QImage orangeFlameFive(":/backgroundImage/img/orange_flame_005.png");
    QImage orangeFlameSix(":/backgroundImage/img/orange_flame_006.png");
    QImage orangeFlameSeven(":/backgroundImage/img/orange_flame_007.png");
    QImage orangeFlameEight(":/backgroundImage/img/orange_flame_008.png");
    QVector<QImage> orangeFlameImages;
    orangeFlameImages.push_back(orangeFlameOne);
    orangeFlameImages.push_back(orangeFlameTwo);
    orangeFlameImages.push_back(orangeFlameThree);
    orangeFlameImages.push_back(orangeFlameFour);
    orangeFlameImages.push_back(orangeFlameFive);
    orangeFlameImages.push_back(orangeFlameSix);
    orangeFlameImages.push_back(orangeFlameSeven);
    orangeFlameImages.push_back(orangeFlameEight);
    flameImages.push_back(orangeFlameImages);

    QImage yellowFlameOne(":/backgroundImage/img/flame_001.png");
    QImage yellowFlameTwo(":/backgroundImage/img/flame_002.png");
    QImage yellowFlameThree(":/backgroundImage/img/flame_003.png");
    QImage yellowFlameFour(":/backgroundImage/img/flame_004.png");
    QImage yellowFlameFive(":/backgroundImage/img/flame_005.png");
    QImage yellowFlameSix(":/backgroundImage/img/flame_006.png");
    QImage yellowFlameSeven(":/backgroundImage/img/flame_007.png");
    QImage yellowFlameEight(":/backgroundImage/img/flame_008.png");
    QVector<QImage> yellowFlameImages;
    yellowFlameImages.push_back(yellowFlameOne);
    yellowFlameImages.push_back(yellowFlameTwo);
    yellowFlameImages.push_back(yellowFlameThree);
    yellowFlameImages.push_back(yellowFlameFour);
    yellowFlameImages.push_back(yellowFlameFive);
    yellowFlameImages.push_back(yellowFlameSix);
    yellowFlameImages.push_back(yellowFlameSeven);
    yellowFlameImages.push_back(yellowFlameEight);
    flameImages.push_back(yellowFlameImages);

    QImage redFlameOne(":/backgroundImage/img/red_flame_001.png");
    QImage redFlameTwo(":/backgroundImage/img/red_flame_002.png");
    QImage redFlameThree(":/backgroundImage/img/red_flame_003.png");
    QImage redFlameFour(":/backgroundImage/img/red_flame_004.png");
    QImage redFlameFive(":/backgroundImage/img/red_flame_005.png");
    QImage redFlameSix(":/backgroundImage/img/red_flame_006.png");
    QImage redFlameSeven(":/backgroundImage/img/red_flame_007.png");
    QImage redFlameEight(":/backgroundImage/img/red_flame_008.png");
    QVector<QImage> redFlameImages;
    redFlameImages.push_back(redFlameOne);
    redFlameImages.push_back(redFlameTwo);
    redFlameImages.push_back(redFlameThree);
    redFlameImages.push_back(redFlameFour);
    redFlameImages.push_back(redFlameFive);
    redFlameImages.push_back(redFlameSix);
    redFlameImages.push_back(redFlameSeven);
    redFlameImages.push_back(redFlameEight);
    flameImages.push_back(redFlameImages);

    QImage lilacFlameOne(":/backgroundImage/img/lilac_flame_001.png");
    QImage lilacFlameTwo(":/backgroundImage/img/lilac_flame_002.png");
    QImage lilacFlameThree(":/backgroundImage/img/lilac_flame_003.png");
    QImage lilacFlameFour(":/backgroundImage/img/lilac_flame_004.png");
    QImage lilacFlameFive(":/backgroundImage/img/lilac_flame_005.png");
    QImage lilacFlameSix(":/backgroundImage/img/lilac_flame_006.png");
    QImage lilacFlameSeven(":/backgroundImage/img/lilac_flame_007.png");
    QImage lilacFlameEight(":/backgroundImage/img/lilac_flame_008.png");
    QVector<QImage> lilacFlameImages;
    lilacFlameImages.push_back(lilacFlameOne);
    lilacFlameImages.push_back(lilacFlameTwo);
    lilacFlameImages.push_back(lilacFlameThree);
    lilacFlameImages.push_back(lilacFlameFour);
    lilacFlameImages.push_back(lilacFlameFive);
    lilacFlameImages.push_back(lilacFlameSix);
    lilacFlameImages.push_back(lilacFlameSeven);
    lilacFlameImages.push_back(lilacFlameEight);
    flameImages.push_back(lilacFlameImages);

    QImage blueFlameOne(":/backgroundImage/img/bluegreen_flame_001.png");
    QImage blueFlameTwo(":/backgroundImage/img/bluegreen_flame_002.png");
    QImage blueFlameThree(":/backgroundImage/img/bluegreen_flame_003.png");
    QImage blueFlameFour(":/backgroundImage/img/bluegreen_flame_004.png");
    QImage blueFlameFive(":/backgroundImage/img/bluegreen_flame_005.png");
    QImage blueFlameSix(":/backgroundImage/img/bluegreen_flame_006.png");
    QImage blueFlameSeven(":/backgroundImage/img/bluegreen_flame_007.png");
    QImage blueFlameEight(":/backgroundImage/img/bluegreen_flame_008.png");
    QVector<QImage> blueFlameImages;
    blueFlameImages.push_back(blueFlameOne);
    blueFlameImages.push_back(blueFlameTwo);
    blueFlameImages.push_back(blueFlameThree);
    blueFlameImages.push_back(blueFlameFour);
    blueFlameImages.push_back(blueFlameFive);
    blueFlameImages.push_back(blueFlameSix);
    blueFlameImages.push_back(blueFlameSeven);
    blueFlameImages.push_back(blueFlameEight);
    flameImages.push_back(blueFlameImages);

    QImage crimsonFlameOne(":/backgroundImage/img/crimson_flame_001.png");
    QImage crimsonFlameTwo(":/backgroundImage/img/crimson_flame_002.png");
    QImage crimsonFlameThree(":/backgroundImage/img/crimson_flame_003.png");
    QImage crimsonFlameFour(":/backgroundImage/img/crimson_flame_004.png");
    QImage crimsonFlameFive(":/backgroundImage/img/crimson_flame_005.png");
    QImage crimsonFlameSix(":/backgroundImage/img/crimson_flame_006.png");
    QImage crimsonFlameSeven(":/backgroundImage/img/crimson_flame_007.png");
    QImage crimsonFlameEight(":/backgroundImage/img/crimson_flame_001.png");
    QVector<QImage> crimsonFlameImages;
    crimsonFlameImages.push_back(crimsonFlameOne);
    crimsonFlameImages.push_back(crimsonFlameTwo);
    crimsonFlameImages.push_back(crimsonFlameThree);
    crimsonFlameImages.push_back(crimsonFlameFour);
    crimsonFlameImages.push_back(crimsonFlameFive);
    crimsonFlameImages.push_back(crimsonFlameSix);
    crimsonFlameImages.push_back(crimsonFlameSeven);
    crimsonFlameImages.push_back(crimsonFlameEight);
    flameImages.push_back(crimsonFlameImages);

    // flame timer and initializing default flame
    currentFlameIndex = 0;
    flameTimer = new QTimer(this);
    connect(flameTimer, SIGNAL(timeout()), &flameLoop, SLOT(quit()));
    flameOn = false;

    //connecting all the dropdown options with the model
    connect(ui->selectMakingWater, &QAction::triggered, this, &MainWindow::makingWaterSelected);
    connect(ui->selectBurningFuel, &QAction::triggered, this, &MainWindow::burningFuelSelected);
    connect(ui->selectMetalFlameTest, &QAction::triggered, this, &MainWindow::metalFlameTestSelected);
    connect(ui->selectColorChange, &QAction::triggered, this, &MainWindow::colorChangeSelected);
    connect(this, &MainWindow::updateCurrentReaction, &model, &Model::setReaction);

    // connecting flame image changing
    connect(&model, &Model::flameIndexChanged, this, &MainWindow::flameColorChanged);

    //connecting the update equation and reaction description labels
    connect(&model, &Model::updateReactionDescriptionLabel, this, &MainWindow::updateReactionDescriptionLabel);
    connect(&model, &Model::updateEquationLabel, this, &MainWindow::updateEquationLabel);

    connect(this, &MainWindow::addChemicalLabel, &model, &Model::addChemicalLabel);
    connect(this, &MainWindow::chemicalClicked, &model, &Model::chemicalClicked);
    connect(this, &MainWindow::chemicalMoved, &model, &Model::chemicalMoved);
    connect(this, &MainWindow::chemicalReleased, &model, &Model::chemicalReleased);
    connect(&model, &Model::moveChemcial, this, &MainWindow::moveChemcial);

    //List chemicals here:
    emit addChemicalLabel(ui->hydrogenGas);
    emit addChemicalLabel(ui->oxygenGas);
    emit addChemicalLabel(ui->propane);
    emit addChemicalLabel(ui->energy);
    emit addChemicalLabel(ui->water);
    emit addChemicalLabel(ui->sodiumMetal);
    emit addChemicalLabel(ui->potassiumMetal);
    emit addChemicalLabel(ui->ferricChloride);
    emit addChemicalLabel(ui->phenol);
    emit addChemicalLabel(ui->calciumLabel);
    emit addChemicalLabel(ui->copperLabel);
    emit addChemicalLabel(ui->lithiumLabel);

    // initializing model values
    model.windowWidth = ui->backgroundImageWidget->width();
    model.windowHeight = ui->centralwidget->height();
    model.sodiumWidth = ui->sodiumMetal->width();
    model.sodiumHeight = ui->sodiumMetal->height();
    model.potassiumWidth = ui->potassiumMetal->width();
    model.potassiumHeight = ui->potassiumMetal->height();
    model.copperWidth = ui->copperLabel->width();
    model.copperHeight = ui->copperLabel->height();
    model.lithiumWidth = ui->lithiumLabel->width();
    model.lithiumHeight = ui->lithiumLabel->height();
    model.calciumWidth = ui->calciumLabel->width();
    model.calciumHeight = ui->calciumLabel->height();
    model.burnerOn = false;
    model.fireTop = ui->flameLabel->pos().y();
    model.fireBottom = model.fireTop + ui->flameLabel->height() / 2;

    //hiding burner metals
    ui->copperLabel->setVisible(false);
    ui->lithiumLabel->setVisible(false);

    //connect the reset button
    connect(ui->resetButton, &QPushButton::pressed, &model, &Model::resetEquation);

    //connect getting the reaction info text
    connect(this, &MainWindow::getInfo, &model, &Model::gatherInfo);
    connect(&model, &Model::returnInfo, this, &MainWindow::recieveAndShowInfo);

    //connect selecting the correct setup per reaction
    connect(this, &MainWindow::selectBurner, this, &MainWindow::burnerSelected);
    connect(this, &MainWindow::selectBeaker, this, &MainWindow::beakerSelected);

    //connects for box2d
    connect(&model, &Model::addElement, ui->physicsScene, &SceneWindow::addElement);
    connect(&model, &Model::clearWorld, ui->physicsScene, &SceneWindow::clearWorld);
    connect(&model, &Model::replaceAllPictures, ui->physicsScene, &SceneWindow::replaceAllPictures);

    //connection for the explosion animation
    connect(&model, &Model::playExplosionAnimation, this, &MainWindow::playExplosionAnimation);

    //defaults the game to making water
    emit makingWaterSelected();

    //Hides the tutorial at the start
    ui->tutorialTextLabel->setVisible(false);

    //connects starting, ending and updating the tutorial
    connect(this, &MainWindow::startTutorial, &model, &Model::startTutorial);
    connect(&model, &Model::sendTutorialText, this, &MainWindow::updateTutorialText);
    connect(&model, &Model::endTheTutorial, this, &MainWindow::endTutorial);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::updateEquationLabel - Updates the chemical equation
 * @param equation - A QString with the contents that are being passed in to be displayed as the equation
 */
void MainWindow::updateEquationLabel(QString equation){
    ui->reactionEquationLabel->setText(equation);
}

/**
 * @brief MainWindow::updateReactionDescriptionLabel - Updates the chemical description
 * @param description - A QString with the contents that are being passed in to be displayed as the reaction
 */
void MainWindow::updateReactionDescriptionLabel(QString description){
    ui->reactionDescriptionLabel->setText(description);
}

void MainWindow::mousePressEvent(QMouseEvent *ev){
    emit chemicalClicked(ev->pos());
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev){
    emit chemicalMoved(ev->pos());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev){
    emit chemicalReleased(ev->pos());
}

/**
 * @brief MainWindow::makingWaterSelected - Tells the model to switch to the Making Water reaction
 */
void MainWindow::makingWaterSelected()
{
    emit updateCurrentReaction("MakingWater");
    emit selectBeaker();
}

/**
 * @brief MainWindow::burningFuelSelected - Tells the model to switch to the Burning Fuel reaction
 */
void MainWindow::burningFuelSelected()
{
    emit updateCurrentReaction("BurningFuel");
    emit selectBeaker();
}

/**
 * @brief MainWindow::metalFlameTestSelected - Tells the model to switch to the Metal Flame Test reaction
 */
void MainWindow::metalFlameTestSelected()
{
    emit updateCurrentReaction("MetalFlameTest");
    emit selectBurner();
}

/**
 * @brief MainWindow::colorChangeSelected - Tells the model to switch to the Color Change reaction
 */
void MainWindow::colorChangeSelected()
{
    emit updateCurrentReaction("ColorChange");
    emit selectBeaker();
}

/**
 * @brief MainWindow::burnerSelected - switches elements in the UI to show what's needed for the burner
 */
void MainWindow::burnerSelected(){
    // adding burner ekements
    ui->burnerLabel->setVisible(true);
    QImage burnerPicture(":/backgroundImage/img/bussinBurnerCrop.png");
    QImage burnerPictureScaled = burnerPicture.scaled(ui->burnerLabel->width(), ui->burnerLabel->height(), Qt::KeepAspectRatio);
    ui->burnerLabel->setPixmap(QPixmap::fromImage(burnerPictureScaled));
    ui->beakerLabel->setVisible(false);
    ui->startBurnerButton->setVisible(true);
    ui->startBurnerButton->setText("Start Flame");

    // removing not needed elements
    ui->energy->setVisible(false);
    ui->calciumLabel->setVisible(true);
    ui->copperLabel->setVisible(true);
    ui->lithiumLabel->setVisible(true);
    ui->ferricChloride->setVisible(false);
    ui->oxygenGas->setVisible(false);
    ui->phenol->setVisible(false);
    ui->water->setVisible(false);
    ui->hydrogenGas->setVisible(false);
    ui->propane->setVisible(false);

    // removing functionality of not needed elements
    ui->energy->setEnabled(false);
    ui->calciumLabel->setEnabled(true);
    ui->copperLabel->setEnabled(true);
    ui->lithiumLabel->setEnabled(true);
    ui->ferricChloride->setEnabled(false);
    ui->oxygenGas->setEnabled(false);
    ui->phenol->setEnabled(false);
    ui->water->setEnabled(false);
    ui->hydrogenGas->setEnabled(false);
    ui->propane->setEnabled(false);
    ui->resetButton->setVisible(false);
}

/**
 * @brief MainWindow::beakerSelected - Switches UI elements to back to standard experiment elements
 */
void MainWindow::beakerSelected(){
    // enabling UI elemetns
    ui->beakerLabel->setVisible(true);
    QImage beakerPicture(":/backgroundImage/img/beaker.png");
    QImage beakerPictureScaled = beakerPicture.scaled(ui->beakerLabel->width(), ui->beakerLabel->height(), Qt::KeepAspectRatio);
    ui->beakerLabel->setPixmap(QPixmap::fromImage(beakerPictureScaled));
    ui->burnerLabel->setVisible(false);
    ui->startBurnerButton->setVisible(false);
    flameOn = false;

    // setting standard reaction elements to visable and enables
    ui->energy->setVisible(true);
    ui->calciumLabel->setVisible(false);
    ui->copperLabel->setVisible(false);
    ui->lithiumLabel->setVisible(false);
    ui->ferricChloride->setVisible(true);
    ui->oxygenGas->setVisible(true);
    ui->phenol->setVisible(true);
    ui->water->setVisible(true);
    ui->hydrogenGas->setVisible(true);
    ui->propane->setVisible(true);

    ui->energy->setEnabled(true);
    ui->calciumLabel->setEnabled(false);
    ui->copperLabel->setEnabled(false);
    ui->lithiumLabel->setEnabled(false);
    ui->ferricChloride->setEnabled(true);
    ui->oxygenGas->setEnabled(true);
    ui->phenol->setEnabled(true);
    ui->water->setEnabled(true);
    ui->hydrogenGas->setEnabled(true);
    ui->propane->setEnabled(true);
    ui->resetButton->setVisible(true);
}

/**
 * @brief MainWindow::flameColorChanged - Slot for the model to tell the UI to switch flame color
 * @param newFlameIndex - flame index (color) of the newe flame
 */
void MainWindow::flameColorChanged(int newFlameIndex){
    currentFlameIndex = newFlameIndex;
}

/**
 * @brief MainWindow::startFlame - contains picture switching logic to display flame images in an animation with proper timing
 */
void MainWindow::startFlame(){
    ui->flameLabel->setHidden(false);
    // checks if the flame has not been switched on
    if(!flameOn){
        flameOn = true;
        ui->startBurnerButton->setText("Stop Flame");
        model.burnerOn = true;
    }
    else{
        flameOn = false;
        model.burnerOn = false;
        ui->startBurnerButton->setText("Start Flame");
    }
    while(flameOn){ // logic of switching flame image
        if(!QWidget::isVisible()){
            QCoreApplication::quit();
            break;
        }
        for(int i = 0; i < flameImages.at(0).size(); i++){ // loops through flame images
            if(!flameOn){
               break;
            }
            flameTimer->start(100);
            flameTimer->setSingleShot(true);
            QImage flamePictureScaled = flameImages.at(currentFlameIndex).at(i).scaled(ui->flameLabel->width(), ui->flameLabel->height(), Qt::KeepAspectRatio); // gets current color as told by model and displays all images
            ui->flameLabel->setPixmap(QPixmap::fromImage(flamePictureScaled));
            flameLoop.exec();
        }
    }
    ui->flameLabel->clear();
}

void MainWindow::moveChemcial(QLabel* label, QPoint pos)
{
    label->move(pos);
}

void MainWindow::on_startBurnerButton_clicked()
{
}

/**
 * @brief MainWindow::on_infoButton_clicked - Tells the model to get the detailed reaction info
 */
void MainWindow::on_infoButton_clicked()
{
    emit getInfo();
}

/**
 * @brief MainWindow::recieveAndShowInfo - Opens a new box titled the reaction name with the detailed reaction info
 * @param reactionName - name of the reaction which info is displayed
 * @param info - info/text about the reaction to be displayed
 */
void MainWindow::recieveAndShowInfo(QString reactionName, QString info)
{
    QWidget tempWidget;
    QMessageBox::information(&tempWidget, reactionName, info);
}

/**
 * @brief MainWindow::playExplosionAnimation - plays the explosion animation for the propane reaction one time
 */
void MainWindow::playExplosionAnimation()
{
    //resets the animaion every time
    ui->explosionLabel->setMovie(explosionAnimation);
    ui->explosionLabel->show();
    explosionAnimation->start();

    //stops the animation
    QTimer::singleShot(530, this, &MainWindow::stopExplosionAnimation);
}

/**
 * @brief MainWindow::stopExplosionAnimation - stops the explosion animation
 */
void MainWindow::stopExplosionAnimation()
{
    ui->explosionLabel->movie()->stop();
    ui->explosionLabel->hide();
}

/**
 * @brief MainWindow::updateTutorialText - Updates the tutorial's text
 * @param text - the new tutorial text
 */
void MainWindow::updateTutorialText(QString text)
{
    ui->tutorialTextLabel->setText(text);
}

/**
 * @brief MainWindow::on_startTutorialPushButton_clicked - Tells the model to start the tutorial
 */
void MainWindow::on_startTutorialPushButton_clicked()
{
    ui->tutorialTextLabel->setVisible(true);
    ui->startTutorialPushButton->setVisible(false);
    emit startTutorial();
}

/**
 * @brief MainWindow::endTutorial - Hides the tutorial text and shows the start tutorial button
 */
void MainWindow::endTutorial()
{
    ui->tutorialTextLabel->setVisible(false);
    ui->startTutorialPushButton->setVisible(true);
}
