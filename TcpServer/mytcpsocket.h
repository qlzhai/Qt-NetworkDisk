#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include <qdebug.h>
#include "protocol.h"
#include "opedb.h"
#include <QDir>//操作文件夹
#include <QTimer>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    QString getName();
signals:
    void offline(MyTcpSocket *mysocket);//客户端下线信号

public slots:
    void recvMsg();
    void clientOffline();//用来处理客户端下线
    void sendFileToClient();
private:
    QString str_name;    //用来记录登录用户的姓名
    //处理接收的文件
    QFile m_file;
    //文件大小
    qint64 m_iTotal;
    //已接收文件的大小
    qint64 m_iRecved;
    //是否处于上传文件状态
    bool m_isUploadFile;
    QTimer *m_pTimer;
    void copyDir(QString strSrcDir, QString strDesDir);
};

#endif // MYTCPSOCKET_H
