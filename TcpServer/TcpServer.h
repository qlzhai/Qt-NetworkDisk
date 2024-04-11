#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QString>
#include <qfile.h>
#include <qdebug.h>
#include <qbytearray.h>
#include <qmessagebox.h>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

    void loadConfig();
private:
    Ui::TcpServer *ui;

    QString m_strIp; //ip地址
    quint16 m_usPort; //端口号
};
#endif // TCPSERVER_H
