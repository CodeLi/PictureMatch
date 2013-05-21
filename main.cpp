#include "picturematch.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PictureMatch w;
    w.show();
    
    return a.exec();
}
