#include "privatechat.h"
#include "ui_privatechat.h"
#include "TcpClient.h"

PrivateChat::PrivateChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivateChat)
{
    ui->setupUi(this);
}

PrivateChat::~PrivateChat()
{
    delete ui;
}

PrivateChat &PrivateChat::getInstance()
{
    static PrivateChat instance;
    return instance;
}

void PrivateChat::setChatName(QString name)
{
    m_chatName = name;
    m_strLoginName = TcpClient::getInstance().getLoginName();
}

void PrivateChat::updateMsg(const PDU *pdu)
{
    if(pdu == NULL) return;
    char sendName[32] = {'\0'};//信息的发送者
    strncpy(sendName,pdu->caData,32);
    QString str_msg = (char*)pdu->caMsg;
    QString msg = QString("\'%1\' sends: \'%2\'").arg(sendName).arg(str_msg);
    ui->ui_Msg_te->append(msg);
}

void PrivateChat::on_sendMsg_pb_clicked()
{
    QString str_msg = ui->ui_Msg_le->text();
    //输入的信息为空 返回
    if(str_msg.size() == 0) return;
    //输入的信息不为空
    PDU *pdu = mkPDU(str_msg.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST;
    memcpy(pdu->caData,m_strLoginName.toStdString().c_str(),m_strLoginName.size());
    memcpy(pdu->caData+32,m_chatName.toStdString().c_str(),m_chatName.size());
    strcpy((char*)(pdu->caMsg),str_msg.toStdString().c_str());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

