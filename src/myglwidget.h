// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void setXTranslate(int trans);
    void setYTranslate(int trans);

    void setGLScale(int _scale);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

    // Emit lorsque le zoom a changé
    void scaleChanged( int scale);

    void xTransChanged( int xtr );
    void yTransChanged( int ytr );

private:
    void draw();

    int xRot;
    int yRot;
    int zRot;

    // Facteur de zoom
    int scale;

    // Translation selon X
    int xTrans;
    // Translation selon Y
    int yTrans;

    QPoint lastPos;
};

#endif // MYGLWIDGET_H

