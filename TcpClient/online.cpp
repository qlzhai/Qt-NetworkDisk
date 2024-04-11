#include "online.h"
#include "ui_online.h"
#include "TcpClient.h"
#include <qmessagebox.h>

Online::Online(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Online)
{
    ui->setupUi(this);
}

Online::~Online()
{
    delete ui;
}

void Online::showUsr(PDU *pdu)
{
    if(pdu == NULL){
        return;
    }

    //数据提取
    uint uiSize = pdu->uiMsgLen / 32;
    char caTmp[32];//临时数组，存储pdu中的消息数据
    for(uint i = 0;i<uiSize;i++){
        memcpy(caTmp,(char*)pdu->caMsg+i*32,32);
        qDebug() << caTmp;
        ui->online_lw->addItem(caTmp);
    }
}

//添加好友槽函数
void Online::on_addFriend_pb_clicked()
{
    qDebug() << "on_addFriend_pb_clicked()";
    QListWidgetItem *pItem = ui->online_lw->currentItem(); //获取选择的Item
    QString usrName = TcpClient::getInstance().getLoginName();//用户姓名
    QString addFriName = pItem->text();//要添加朋友的姓名

    //自己不能添加自己为好友
    if(usrName == addFriName){
        QMessageBox::warning(this,"添加好友","自己不能添加自己为好友，请选择其他用户！");
        return;
    }

    //qDebug() << pItem->text();
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REQUEST;//设置消息类型为添加朋友请求
    memcpy(pdu->caData,usrName.toStdString().c_str(),usrName.size());
    memcpy(pdu->caData+32,addFriName.toStdString().c_str(),addFriName.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    qDebug() << "on_addFriend_pb_clicked()";
    free(pdu);
    pdu = NULL;
}

