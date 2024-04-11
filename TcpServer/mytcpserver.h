#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <qlist.h>
#include <mytcpsocket.h>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT //有了这个宏，才能加载信号槽
public:
    MyTcpServer();

    static MyTcpServer &getInstance();//单例模式

    //重载 只要有客户端连接到服务器，自动调用incomingConnection函数不断收集信号
    void incomingConnection(qintptr socketDescriptor);

    //向usrName客户端发送添加好友请求
    void resend(const char* friName, PDU* pdu);

    //向所有好友发送群聊信息
    void resendGroupMsg(QSet<QString> friendSet, PDU* pdu);
public slots:
    //接收MyTcpSocket的下线信号，删除此Socket
    void deleteSocket(MyTcpSocket* mysocket);

private:
    QList<MyTcpSocket*> m_tcpSocketList;
};

#endif // MYTCPSERVER_H
