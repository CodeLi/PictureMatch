#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    int m_Array[6][6];
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    int pictureWeith, pictureHeight;
    int m_frontPictureId;
    int m_frontX, m_frontY;
    void formMap();
    ~Widget();
};

#endif // WIDGET_H
