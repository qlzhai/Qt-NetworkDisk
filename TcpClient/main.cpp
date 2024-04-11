#include "TcpClient.h"
#include <QApplication>

#include "book.h"
#include "sharefile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpClient::getInstance().show();

    //Book w;
    //w.show();

    //OpeWidget w;
    //w.show();

    //Online w;
    //w.show();

    //Friend w;
    //w.show();

    //ShareFile w;
    //w.show();
    return a.exec();
}
