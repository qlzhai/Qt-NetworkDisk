#include "friend.h"
#include "protocol.h"
#include "TcpClient.h"
#include <QInputDialog>
#include "privatechat.h"

Friend::Friend(QWidget *parent)
    : QWidget{parent}
{
    m_pShowMsgTE=new QTextEdit;
    m_pFriendListWidget=new QListWidget;
    m_pInputMsgLE=new QLineEdit;

    m_pDelFriendPB=new QPushButton("删除好友");
    m_pFlushFriendPB=new QPushButton("刷新好友");
    m_pShowOnlineUsrPB=new QPushButton("显示在线用户");
    m_pSearchUsrPB=new QPushButton("查找用户");
    m_pMsgSendPB=new QPushButton("信息发送");
    m_pPrivateChatPB=new QPushButton("私聊");

    //垂直布局 除信息发送的按钮
    QVBoxLayout *pRightPBVBL = new QVBoxLayout;
    pRightPBVBL->addWidget(m_pDelFriendPB);
    pRightPBVBL->addWidget(m_pFlushFriendPB);
    pRightPBVBL->addWidget(m_pShowOnlineUsrPB);
    pRightPBVBL->addWidget(m_pSearchUsrPB);
    pRightPBVBL->addWidget(m_pPrivateChatPB);

    //水平布局1 信息显示/好友列表/其余按钮
    QHBoxLayout *pTopHBL=new QHBoxLayout;
    pTopHBL->addWidget(m_pShowMsgTE);
    pTopHBL->addWidget(m_pFriendListWidget);
    pTopHBL->addLayout(pRightPBVBL);

    //水平布局2 窗口(信息输入)/按钮(信息发送)
    QHBoxLayout *pMsgHBL=new QHBoxLayout;
    pMsgHBL->addWidget(m_pInputMsgLE);
    pMsgHBL->addWidget(m_pMsgSendPB);

    m_pOnline =new Online;  //在线用户界面

    //合成垂直布局
    QVBoxLayout *pMain=new QVBoxLayout;
    pMain->addLayout(pTopHBL);
    pMain->addLayout(pMsgHBL);
    pMain->addWidget(m_pOnline);
    m_pOnline->hide(); //online初始时不显示

    setLayout(pMain);

    //关联显示在线用户的信号槽
    connect(m_pShowOnlineUsrPB,SIGNAL(clicked(bool)),this,SLOT(showOnline()));
    //关联查找用户信息的信号槽
    connect(m_pSearchUsrPB,SIGNAL(clicked(bool)),this,SLOT(searchUsr()));
    //关联刷新好友列表的信号槽
    connect(m_pFlushFriendPB,SIGNAL(clicked(bool)),this,SLOT(flushFriList()));
    //关联删除好友的信号槽
    connect(m_pDelFriendPB,SIGNAL(clicked(bool)),this,SLOT(deleteFriend()));
    //关联私聊好友的信号槽
    connect(m_pPrivateChatPB,SIGNAL(clicked(bool)),this,SLOT(privateChatFriend()));
    //关联群聊的信号槽
    connect(m_pMsgSendPB,SIGNAL(clicked(bool)),this,SLOT(groupChat()));
}

void Friend::showALLOnlineUsr(PDU *pdu)
{
    if(pdu == NULL){
        return;
    }
    m_pOnline->showUsr(pdu);
}

void Friend::showFriendName(PDU *pdu)
{
    if(pdu == NULL) return;
    m_pFriendListWidget->clear();

    //数据提取
    uint uiSize = pdu->uiMsgLen/32;//uiSize表示有多少个好友，每个好友的姓名占32位
    char caTmp[32];//临时数组，用来存放姓名
    for(uint i = 0; i < uiSize; i++){
        memcpy(caTmp,(char*)pdu->caMsg+i*32,32);
        this->m_pFriendListWidget->addItem(caTmp);
    }
}

void Friend::showGroupMsg(PDU *pdu)
{
    if(pdu == NULL) return;
    char sendName[32] = {'\0'};
    strcpy(sendName,pdu->caData);
    QString msg = QString("\'%1\' says: \'%2\'").arg(sendName).arg((char*)pdu->caMsg);
    m_pShowMsgTE->append(msg);
}

QListWidget *Friend::getFriendListWidget()
{
    return m_pFriendListWidget;
}

void Friend::showOnline()
{
    if(m_pOnline->isHidden()){
        m_pOnline->show();

        //查看在线用户的协议数据单元
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINE_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
    else{
        m_pOnline->hide();
    }
}

void Friend::searchUsr()
{
    //根据用户名进行搜索
    m_strSearchName = QInputDialog::getText(this,"搜索","用户名:");//弹出一个窗口输入用户名
    if(!m_strSearchName.isEmpty()){
        qDebug() << m_strSearchName;
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_SEARCH_REQUEST;//向服务器端发送查找请求信号
        strncpy(pdu->caData,m_strSearchName.toStdString().c_str(),m_strSearchName.size());

        TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);//通过Tcp协议向服务器端发送数据
        free(pdu);
        pdu = NULL;
    }
}

void Friend::flushFriList()
{
    //获取本机登录的姓名
    QString m_strLoginName = TcpClient::getInstance().getLoginName();
    if(m_strLoginName.size() == 0) return;
    qDebug() << m_strLoginName;
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST;
    strncpy(pdu->caData,m_strLoginName.toStdString().c_str(),m_strLoginName.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);//通过Tcp协议向服务器端发送数据
    free(pdu);
    pdu = NULL;
}

void Friend::deleteFriend()
{
    //获取本机登录的姓名
    QString m_strLoginName = TcpClient::getInstance().getLoginName();
    if(m_strLoginName.size() == 0) return;
    //获取选择的Item的姓名
    QString m_strFriName = m_pFriendListWidget->currentItem()->text();
    PDU *pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST;
    memcpy(pdu->caData,m_strLoginName.toStdString().c_str(),m_strLoginName.size());
    memcpy(pdu->caData+32,m_strFriName.toStdString().c_str(),m_strFriName.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);//通过Tcp协议向服务器端发送数据
    free(pdu);
    pdu = NULL;
}

void Friend::privateChatFriend()
{
    if(m_pFriendListWidget->currentItem() == NULL) return;
    QString m_strFriname = m_pFriendListWidget->currentItem()->text();
    PrivateChat::getInstance().setChatName(m_strFriname);
    if(PrivateChat::getInstance().isHidden()){
        PrivateChat::getInstance().show();
    }
}

void Friend::groupChat()
{
    QString m_pMsg = m_pInputMsgLE->text();
    if(m_pMsg.size() == 0) return;
    QString m_sendName = TcpClient::getInstance().getLoginName();//获取信息的发送者
    PDU *pdu = mkPDU(m_pMsg.size());
    pdu->uiMsgType = ENUM_MSG_TYPE_GROUP_CHAT_REQUEST;
    memcpy(pdu->caData,m_sendName.toStdString().c_str(),m_sendName.size());
    memcpy((char*)pdu->caMsg,m_pMsg.toStdString().c_str(),m_pMsg.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}
