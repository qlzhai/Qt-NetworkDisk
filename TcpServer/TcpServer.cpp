#include "TcpServer.h"
#include "ui_TcpServer.h"
#include "mytcpserver.h"

TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    resize(200,200);
    this->loadConfig();

    MyTcpServer::getInstance().listen(QHostAddress(this->m_strIp),this->m_usPort); //服务器监听端口
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::loadConfig()
{
    QFile file(":/server.config");
    if (file.open(QIODevice::ReadOnly)) {
        //只读方式打开
        QByteArray baData = file.readAll();//以字节数组形式读取
        QString strData = baData.toStdString().c_str();//类型转换
        qDebug() << strData;
        file.close();

        //数据处理
        strData.replace("\r\n", " "); //\r\n回车换行
        qDebug() << strData;

        QStringList strlist = strData.split(" ");
        for (int i = 0; i < strlist.size(); i++) {
            qDebug() << "--->" << strlist[i];
        }

        this->m_strIp = strlist[0];
        this->m_usPort = strlist[1].toUShort();
        qDebug() << "ip:" << this->m_strIp;
        qDebug() << "port:" << this->m_usPort;
    }
    else {
        QMessageBox::critical(this, "open config", "open config failed");
    }
}

