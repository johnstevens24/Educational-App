/* @Authors: Aric Potter, Andrew Nichols Taylor-Crawford, Emma Kerr, Charly Bueno, and John Stevens
 * CS 3505 Spring 2022
 * Prof. Johnson
 */

#include "scenewindow.h"
#include <random>
#include <QPainter>
#include <Box2D/Box2D.h>
#include <iostream>

SceneWindow::SceneWindow(QWidget *parent)
    : QWidget{parent},
      world(b2Vec2(0.0f, 30.0f)),
      timer(this)
      //image(":/backgroundImage/img/oxygen.png") // Make a resource file - mac executables are in a hidden folder
  {
      //image = image.scaled(image.width()/15, image.height()/15);



      // Define the ground body.
      b2BodyDef groundBodyDef;
      groundBodyDef.position.Set(0.0f, 20.0f);
      // Call the body factory which allocates memory for the ground body
      // from a pool and creates the ground box shape (also from a pool).
      // The body is also added to the world.
      b2Body* groundBody = world.CreateBody(&groundBodyDef);

      // Define the ground box shape.
      b2PolygonShape groundBox;

      // The extents are the half-widths of the box.
      groundBox.SetAsBox(50.0f, 10.0f);

      // Add the ground fixture to the ground body.
      groundBody->CreateFixture(&groundBox, 0.0f);

      b2BodyDef leftWallBodyDef;
      leftWallBodyDef.position.Set(0.0f, 20.0f);
      b2Body* leftWallBody = world.CreateBody(&leftWallBodyDef);
      b2PolygonShape leftWallBox;
      leftWallBox.SetAsBox(1.0f, 50.0f);
      leftWallBody->CreateFixture(&leftWallBox, 0.0f);

      b2BodyDef rightWallBodyDef;
      rightWallBodyDef.position.Set(10.0f, 20.0f);
      b2Body* rightWallBody = world.CreateBody(&rightWallBodyDef);
      b2PolygonShape rightWallBox;
      rightWallBox.SetAsBox(1.0f, 50.0f);
      rightWallBody->CreateFixture(&rightWallBox, 0.0f);


      //std::default_random_engine generator;
      //std::uniform_real_distribution<float> distribution(6.4, 6.6);
      //std::uniform_int_distribution<int> distribution(1,6);

      /**
      for(int i = 0; i< 100; i++){
          // Define the dynamic body. We set its position and call the body factory.
          b2BodyDef bodyDef;
          bodyDef.type = b2_dynamicBody;
          bodyDef.position.Set(distribution(generator),4.0);
          //bodies[i] = world.CreateBody(&bodyDef);
          bodies.append(world.CreateBody(&bodyDef));
          images.append(QImage(":/backgroundImage/img/oxygen.png"));
          // Define another box shape for our dynamic body.
          b2PolygonShape dynamicBox;
          dynamicBox.SetAsBox(0.5f, 0.5f);
          // Define the dynamic body fixture.
          b2FixtureDef fixtureDef;
          fixtureDef.shape = &dynamicBox;
          // Set the box density to be non-zero, so it will be dynamic.
          fixtureDef.density = 1.0f;
          // Override the default friction.
          fixtureDef.friction = 0.3f;
          fixtureDef.restitution = 0.9;
          // Add the shape to the body.
          bodies[i]->CreateFixture(&fixtureDef);
          printf("Init world\n");

      }
      **/

      connect(&timer, &QTimer::timeout, this, &SceneWindow::updateWorld);
      timer.start(50);
}

void SceneWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    for(int i = 0; i<bodies.length(); i++){
        b2Vec2 position = bodies[i]->GetPosition();
        //float angle = bodies[i]->GetAngle();

        //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        painter.drawImage((int)(position.x*20), (int)(position.y*20), images[i]);
    }
    //painter.drawImage(200, 200, image);
    //qDebug() << image;
    painter.end();
}

void SceneWindow::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);

    update();
}

void SceneWindow::clearWorld() {
    for(b2Body* b : bodies){
        world.DestroyBody(b);
    }
    bodies.clear();
    images.clear();

}

void SceneWindow::replaceAllPictures(QString path)
{
    /**for(QImage im : images)
    {
        im = QImage(path);
    }**/
    int len = images.length();
    images.clear();

    for(int i = 0 ; i< len; i++)
    {
        QImage im = QImage(path);
        images.append(im.scaled(im.width()/4.0, im.height()/4.0));
    }
}

void SceneWindow::addElement(QString imagePath, float scaleFactor, QPoint pos, bool WindowCoords)

{

    if(WindowCoords){
        //Adjust point, point is in main window frame, must be in current window and scaled to box2d
        //std::cout<<"Released position: "<<pos.x()<<" "<<pos.y()<<std::endl;
        //std::cout<<"Window position: "<<this->pos().x()<<" "<<this->pos().y()<<std::endl;

        pos = pos - this->pos();

        //std::cout<<"Corrected position: "<<pos.x()<<" "<<pos.y()<<std::endl;
        pos = pos /20;
        //std::cout<<"Scaled position: "<<pos.x()<<" "<<pos.y()<<std::endl;
    }

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x(), pos.y());
    //bodies[i] = world.CreateBody(&bodyDef);
    bodies.append(world.CreateBody(&bodyDef));
    //images.append(QImage(":/backgroundImage/img/oxygen.png"));
    QImage imge(imagePath);
    imge = imge.scaled(imge.width()/scaleFactor, imge.height()/scaleFactor);
    images.append(imge);
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    bodies.back()->CreateFixture(&fixtureDef);
}
