#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QString>
#include <qfile.h>
#include <qdebug.h>
#include <qbytearray.h>
#include <qmessagebox.h>
#include <QTcpSocket>
#include <QLineEdit>
#include <QHostAddress>
#include "protocol.h"
#include "opewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

    void loadConfig(); //配置文件加载，从client.config文件中找出ip和端口

    static TcpClient &getInstance();
    QTcpSocket &getTcpSocket();
//槽函数
public slots:
    void showConnect();
    void recvMsg();

    QString getLoginName();//通过公有函数获取私有的登录用户姓名
    QString curPath();//通过共有函数获取当前路径
    void updateCurPath(QString str_curPath);//更新当前路径
private slots:
    //void on_send_pb_clicked();

    void on_login_pb_clicked();

    void on_registe_pb_clicked();

    void on_cancel_pb_clicked();

private:
    Ui::TcpClient *ui;

    QString m_strIp; //ip地址
    quint16 m_usPort; //端口号

    QTcpSocket m_tcpSocket; //连接服务器，和服务器进行数据交互
    QString m_strLoginName; //记录本机所登录用户的姓名

    //定义路径
    QString m_strCurPath;
    QFile m_file;
};
#endif // TCPCLIENT_H
