#include "widget.h"
#include <QLabel>
#include <QtWidgets>

#include<time.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setAcceptDrops(true);
    m_frontPictureId = 0;


    QPixmap* image = new QPixmap(":/image/1.png");
    pictureWeith = image->width();
    pictureHeight = image->height();
    formMap();
}

Widget::~Widget()
{
    
}



void Widget::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int i(0), j(0);
    i = (y/pictureWeith);// + (x%pictureWeith?1:0);
    j = (x/pictureHeight);// + (y%pictureHeight?1:0);
    if(m_frontPictureId == 0)
    {
        m_frontPictureId = m_Array[i][j];
        m_frontX = x;
        m_frontY = y;
        QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
        if(child)
        {
            child->setLineWidth(5);
            child->setStyleSheet("color:red");
            child->setFrameStyle(QFrame::Box | QFrame::Plain);
          //  child->deleteLater();
        }
    }
    else
    {
        int pictureId = m_Array[i][j];
        if(m_frontPictureId == pictureId)
        {
            int iFront = (m_frontY/pictureWeith);
            int jFront = (m_frontX/pictureHeight);
            if( (iFront == i) && (jFront==j) )//两次选中同一张图片
                return ;
            QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
            if(child)
            {
              child->deleteLater();
              m_Array[i][j] = 0;
            }
            child = static_cast<QLabel*>(childAt(m_frontX, m_frontY));
            if(child)
            {

                child->deleteLater();
                m_Array[iFront][jFront] = 0;
            }
            m_frontPictureId = 0;
        }
    }
}


void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    formMap();
}

void Widget::formMap()
{
    QString strPath = NULL;
    qsrand(time(NULL));
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            Sleep(20);
            m_Array[i][j] = rand()%7+1;
            m_Array[3+i][j] = m_Array[i][j];
        }
    }
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {

            strPath = QString(":/image/%1.png").arg(m_Array[i][j]);
            QLabel* lable = new QLabel(this);
            lable->setPixmap(QPixmap(strPath));
            lable->move((2+pictureWeith)*j, (2+pictureHeight)*i);
            lable->show();
            lable->setAttribute(Qt::WA_DeleteOnClose);
        }
    }
}
