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
    m_frontX = 0;
    m_frontY = 0;

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
    i = (y/pictureWeith) + 1;// + (x%pictureWeith?1:0);
    j = (x/pictureHeight) + 1;// + (y%pictureHeight?1:0);
    int iFront = (m_frontY/pictureWeith) + 1;
    int jFront = (m_frontX/pictureHeight) + 1;
    if( (iFront == i) && (jFront==j) )//两次选中同一张图片
        return ;
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
            if (isMatch(iFront, jFront, i, j) == 0)
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
    for(int i = 1; i < 4; i++)
    {
        for(int j = 1; j < 7; j++)
        {
            Sleep(20);
            m_Array[i][j] = rand()%7+1;
            m_Array[3+i][j] = m_Array[i][j];
        }
    }
    for(int i = 1; i < 7; i++)
    {
        for(int j = 1; j < 7; j++)
        {

            strPath = QString(":/image/%1.png").arg(m_Array[i][j]);
            QLabel* lable = new QLabel(this);
            lable->setPixmap(QPixmap(strPath));
            lable->move((2+pictureWeith)*(j-1), (2+pictureHeight)*(i-1));
            lable->show();
            lable->setAttribute(Qt::WA_DeleteOnClose);
        }
    }
}

//----------------------------
//判断两张图片是否符合消去规则
//返回值： 1 符合
//        0 不符合
//----------------------------
int Widget::isMatch(int iFront, int jFront, int iNow, int jNow)
{
    m_Array[iFront][jFront] = -1;
    QList<QPoint> pointList;//已搜到,但还未从其开始搜索的点
    QPoint pTemp(iNow, jNow);
    int searchFlag[8][8] = {0};
    pointList.push_back(pTemp);
    for(int i = 0; i < 4; i++)
    {
        if(searchPoint(pointList, searchFlag))
            return 1;
    }
    return 0;


}

int Widget::searchPoint(QList<QPoint> &pointList, int searchFlag[8][8])
{
    QList<QPoint> tempList;
    QPoint pTemp;
    while( !pointList.isEmpty())
    {
        QPoint pointNow = pointList.front();
        pointList.pop_front();
        int iNow = pointNow.ry();
        int jNow = pointNow.rx();
        //沿Y轴向两边找
        for(int i = iNow-1; i>-1; i--)
        {
            if(m_Array[i][jNow] == -1)
            {
                return 1;
            }
            else if(m_Array[i][jNow] == 0)
            {
                pTemp.setX(i);
                pTemp.setY(jNow);
                if(searchFlag[i][jNow] == 0)
                {
                    tempList.push_back(pTemp);
                    searchFlag[i][jNow] = 1;
                }
            }
            else
                break;
        }
        for(int i = iNow+1; i < 8; i++)
        {
            if(m_Array[i][jNow] == -1)
            {
                return 1;
            }
            else if(m_Array[i][jNow] == 0)
            {
                pTemp.setX(i);
                pTemp.setY(jNow);
                if(searchFlag[i][jNow] == 0)
                {
                    tempList.push_back(pTemp);
                    searchFlag[i][jNow] = 1;
                }
            }
            else
                break;
        }
        //沿x轴向两边找
        for(int j = jNow-1; j > -1; j--)
        {
            if(m_Array[iNow][j] == -1)
            {
                return 1;
            }
            else if(m_Array[iNow][j] == 0)
            {
                pTemp.setX(iNow);
                pTemp.setY(j);
                if(searchFlag[iNow][j] == 0)
                {
                    tempList.push_back(pTemp);
                    searchFlag[iNow][j] = 1;
                }
            }
            else
                break;
        }
        for(int j = jNow+1; j < 8; j++)
        {
            if(m_Array[iNow][j] == -1)
            {
                return 1;
            }
            else if(m_Array[iNow][j] == 0)
            {
                pTemp.setX(iNow);
                pTemp.setY(j);
                if(searchFlag[iNow][j] == 0)
                {
                    tempList.push_back(pTemp);
                    searchFlag[iNow][j] = 1;
                }
            }
            else
                break;
        }
    }
    pointList = tempList;
    return 0;
}
