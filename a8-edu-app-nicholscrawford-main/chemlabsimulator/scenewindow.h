/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class SceneWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SceneWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();
    void clearWorld();
    void addElement(QString imagePath, float scaleFactor, QPoint pos, bool WindowCoords);
    void replaceAllPictures(QString path);

private:
    b2World world;
    QVector<b2Body*> bodies;
    QTimer timer;
    QVector<QImage> images;

};

#endif // SCENEWINDOW_H
