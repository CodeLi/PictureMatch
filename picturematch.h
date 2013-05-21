#ifndef PICTUREMATCH_H
#define PICTUREMATCH_H

#include <QWidget>

class PictureMatch : public QWidget
{
    Q_OBJECT
    
public:
    PictureMatch(QWidget *parent = 0);
    ~PictureMatch();
    void mousePressEvent(QMouseEvent * event);
private:
    int m_imageWeith;
    int m_imageHeight;
    int m_Array[6][6];
};

#endif // PICTUREMATCH_H
