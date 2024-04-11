#include "mytcpserver.h"
#include <qdebug.h>

MyTcpServer::MyTcpServer()
{

}

MyTcpServer &MyTcpServer::getInstance()
{
    //后面凡是需要MyTcpServer的地方，调用getInstance
    static MyTcpServer instance;
    return instance;
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "new client connected";
    MyTcpSocket *pTcpSocket = new MyTcpSocket;
    pTcpSocket->setSocketDescriptor(socketDescriptor);
    m_tcpSocketList.append(pTcpSocket);

    connect(pTcpSocket,SIGNAL(offline(MyTcpSocket*)),this,SLOT(deleteSocket(MyTcpSocket*)));//信号的发送者、发送的是什么信号、信号的处理者，怎么处理
}

void MyTcpServer::resend(const char *friName, PDU *pdu)
{
    qDebug() << "resend(const char *friName, PDU *pdu)";
    if(friName == NULL || pdu == NULL) return;
    QString strname = friName;
    for(int i = 0;i<m_tcpSocketList.size();i++){
        if(m_tcpSocketList.at(i)->getName() == strname){
            m_tcpSocketList.at(i)->write((char*)pdu,pdu->uiPDULen);
            break;
        }
    }
}

void MyTcpServer::resendGroupMsg(QSet<QString> friendSet, PDU *pdu)
{
    qDebug() << "resend(const char *friName, PDU *pdu)";
    if(pdu == NULL) return;
    QString strname;
    pdu->uiMsgType = ENUM_MSG_TYPE_GROUP_CHAT_RESPOND;
    for(QSet<QString>::iterator it = friendSet.begin(); it != friendSet.end(); it++){
        strname = *it;
        for(int i = 0;i<m_tcpSocketList.size();i++){
            if(m_tcpSocketList.at(i)->getName() == strname){
                m_tcpSocketList.at(i)->write((char*)pdu,pdu->uiPDULen);
            }
        }
    }
}

void MyTcpServer::deleteSocket(MyTcpSocket *mysocket)
{
    QList<MyTcpSocket*>::iterator iter = m_tcpSocketList.begin();
    for(;iter != m_tcpSocketList.end();iter++){
        if(mysocket == *iter){
            delete *iter;
            *iter = NULL;
            m_tcpSocketList.erase(iter);
            break;
        }
    }

    for(int i = 0;i<m_tcpSocketList.size();i++){
        qDebug() << m_tcpSocketList.at(i)->getName();
    }
}
