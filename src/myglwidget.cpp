// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include<iostream>

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    scale = 16;		// default object scale

    xTrans = 0;		// default object translation
    yTrans = 0;
}

MyGLWidget::~MyGLWidget()
{

}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

static void qNormalizeTanslate(int &trans)
{
    while (trans < 0)
        trans += 360 * 16;
    while (trans > 360)
        trans -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot)
    {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot)
    {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setXTranslate(int trans)
{
    //qNormalizeTanslate(trans);
    if( trans != xTrans )
    {
        xTrans = trans;
        emit xTransChanged(trans);
        updateGL();
    }
}
void MyGLWidget::setYTranslate(int trans)
{
    //qNormalizeTanslate(trans);
    if( trans != yTrans )
    {
        yTrans = trans;
        emit yTransChanged(trans);
        updateGL();
    }
}

void MyGLWidget::setGLScale(int _scale)
{
    if( _scale != scale )
    {
        scale = _scale;
        emit scaleChanged(scale);
        updateGL();
    }
}
void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::white);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    //glTranslatef(0.0, 0.0, -10.0);
    glTranslatef( xTrans/16.0, yTrans/16.0, -10.0 );
    glScalef( scale/16.0, scale/16.0, scale/16.0 );


    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    draw();


    //绘制坐标轴
    glEnable(GL_LINES);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-12.0f, 0*1.0);
    glVertex2f(12.0f, 0);

    glVertex2f(0.0f,-2.0);
    glVertex2f(0.0, 62.0);
    glEnd();
    glDisable(GL_LINES);
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-10, +10, -2, +120, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        //setXRotation(xRot + 8 * dy);
        //setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        //setXRotation(xRot + 8 * dy);
        //setZRotation(zRot + 8 * dx);

        setXTranslate(xTrans+dx);
        setYTranslate(yTrans-dy);

    }
    else if (event->buttons() & Qt::MidButton)
    {
        if( dy>=0 )
            setGLScale(scale - powf(0.88,(float)dy));
        else
            setGLScale(scale + powf(0.88,(float)dy));
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{
    /*
    qglColor(Qt::red);


    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glVertex3f(-1,-1,0);
    glVertex3f(-1,1,0);
    glVertex3f(1,1,0);
    glVertex3f(1,-1,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,-1,0.707);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1,0, 0.707);
    glVertex3f(1,-1,0);
    glVertex3f(1,1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0,1,0.707);
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,0,0.707);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(0,0,1.2);
    glEnd();
    */

    //----------------------------------------//
    glColor3f(0.0, 1.0, 0.0);
    renderText( 0,  9 , 0, "Map Demo", QFont("Ubuntu", 30, 10, false));



    glEnable(GL_LINES);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    //glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex2f(0,0);
    glVertex2f(2,50);
    glEnd();

    //glFlush ();
}
