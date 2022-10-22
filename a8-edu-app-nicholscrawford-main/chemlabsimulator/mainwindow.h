/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QEventLoop>
#include <QMessageBox>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model& m, QWidget *parent = nullptr);
    ~MainWindow();
protected:
    QMovie *explosionAnimation;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void stopExplosionAnimation();
    //void paintEvent(QPaintEvent* aPainEvent);

public slots:
    void updateEquationLabel(QString equation);
    void updateReactionDescriptionLabel(QString description);
    //void addElement(QString s, QPoint pos);

private slots:
    void makingWaterSelected();
    void burningFuelSelected();
    void metalFlameTestSelected();
    void colorChangeSelected();
    void burnerSelected();
    void beakerSelected();
    void startFlame();
    void moveChemcial(QLabel* chemical, QPoint pos);
    void on_startBurnerButton_clicked();
    void flameColorChanged(int);
    void on_infoButton_clicked();

    void recieveAndShowInfo(QString Reaction, QString info);
    void playExplosionAnimation();

    void updateTutorialText(QString text);

    void on_startTutorialPushButton_clicked();

    void endTutorial();

signals:
    int updateCurrentReaction(QString reaction);
    void chemicalClicked(QPoint pos);
    void chemicalMoved(QPoint pos);
    void chemicalReleased(QPoint pos);
    void addChemicalLabel(QLabel* label);
    void getInfo();
    void selectBeaker();
    void selectBurner();
    void startTutorial();

private:
    Ui::MainWindow *ui;
    QImage backgroundImage;
    QVector<QVector<QImage>> flameImages;
    QTimer* flameTimer;
    QEventLoop flameLoop;
    bool flameOn;
    Model& model;
    int currentFlameIndex;
};
#endif // MAINWINDOW_H
