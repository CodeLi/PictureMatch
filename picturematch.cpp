#include "picturematch.h"
#include<time.h>
#include<QLabel>
#include<QMouseEvent>

PictureMatch::PictureMatch(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
     setAcceptDrops(true);

     QPixmap* image = new QPixmap(":/image/1.png");
     m_imageWeith = image->width();
     m_imageWeith = image->height();
     qsrand(time(NULL));
     for(int i = 0; i < 3; i++)
     {
         for(int j = 0; j < 6; j++)
         {
             int count(50000);
             while(count--);
             m_Array[i][j] = rand()%7+1;
             m_Array[i+3][j] = m_Array[i][j];
         }
     }

     QString strPath = NULL;
     for(int i = 0; i < 6; i++)
         for(int j = 0; j < 6; j++)
         {
             strPath = QString(":/image/%1.png").arg(m_Array[i][j]);
             QLabel* label = new QLabel(this);
             label->setPixmap(QPixmap(strPath));
             label->move((2+m_imageWeith)*i, (2+m_imageWeith)*j);
             label->show();
             label->setAttribute(Qt::WA_DeleteOnClose);
         }
}

PictureMatch::~PictureMatch()
{
    
}

void PictureMatch::mousePressEvent(QMouseEvent * event)
{
    QLabel* myLabel = static_cast<QLabel*>(childAt(event->pos()));
    if(!myLabel)
        return;
    myLabel->setStyleSheet("color:red");
    myLabel->setFrameStyle(QFrame::Box|QFrame::Plain);
    myLabel->setLineWidth(5);
//    myLabel->deleteLater();
//    myLabel->hide();

}
