#include "sharefile.h"
#include "TcpClient.h"

ShareFile::ShareFile(QWidget *parent)
    : QWidget{parent}
{
    m_pSelectAllPB = new QPushButton("全选");//全选
    m_pCancelSelectPB = new QPushButton("取消选择");//取消选择
    m_pOkSharePB = new QPushButton("确定");//确定分享
    m_pCancelSharePB = new QPushButton("取消分享");//取消分享

    m_pSA = new QScrollArea;//展示区域
    m_pFriendW = new QWidget;//要分享的好友

    m_pFriendWVBL = new QVBoxLayout(m_pFriendW); //保存垂直布局
    m_pButtonGroup = new QButtonGroup(m_pFriendW);//管理所有好友
    m_pButtonGroup->setExclusive(false);//保持多选

    //水平布局 合成全选 取消全选
    QHBoxLayout *pTopHBL = new QHBoxLayout;
    pTopHBL->addWidget(m_pSelectAllPB);
    pTopHBL->addStretch();
    pTopHBL->addWidget(m_pCancelSelectPB);

    //水平布局 合成确定 取消分享
    QHBoxLayout *pDownHBL = new QHBoxLayout;
    pDownHBL->addWidget(m_pOkSharePB);
    pDownHBL->addStretch();
    pDownHBL->addWidget(m_pCancelSharePB);

    //垂直布局
    QVBoxLayout *pMainVBL = new QVBoxLayout;
    pMainVBL->addLayout(pTopHBL);
    pMainVBL->addWidget(m_pSA);
    pMainVBL->addLayout(pDownHBL);
    setLayout(pMainVBL);

    connect(m_pSelectAllPB,SIGNAL(clicked(bool)),this,SLOT(selectAll()));
    connect(m_pCancelSelectPB,SIGNAL(clicked(bool)),this,SLOT(cancelSelect()));
    connect(m_pOkSharePB,SIGNAL(clicked(bool)),this,SLOT(okShare()));
    connect(m_pCancelSharePB,SIGNAL(clicked(bool)),this,SLOT(cancelShare()));
    //test();
}

void ShareFile::test()
{
    QVBoxLayout *p = new QVBoxLayout(m_pFriendW);
    QCheckBox *pCB = NULL;
    for(int i = 0; i < 15; i++){
        pCB = new QCheckBox("jack");
        p->addWidget(pCB);
        m_pButtonGroup->addButton(pCB);
    }
    m_pSA->setWidget(m_pFriendW);
}

ShareFile &ShareFile::getInstance()
{
    static ShareFile instance;
    return instance;
}

void ShareFile::updateFriend(QListWidget *friendListW)
{
    if(friendListW == NULL) return;
    //获取之前的好友列表
    QAbstractButton *tmp = NULL;
    QList<QAbstractButton*> preFriendList = m_pButtonGroup->buttons();
    qDebug() << "preFriendList:" << preFriendList.count();
    //清空之前的窗口信息
    for(int i = 0; i < preFriendList.count(); i++){
        qDebug() << i;
        tmp = preFriendList[i];
        m_pFriendWVBL->removeWidget(tmp);
        m_pButtonGroup->removeButton(tmp);
        //preFriendList.removeOne(tmp);
    }
    delete tmp;
    tmp = NULL;

    //更新窗口信息
    QCheckBox *pCB = NULL;
    for(int i = 0; i < friendListW->count(); i++){
        pCB = new QCheckBox(friendListW->item(i)->text());
        m_pFriendWVBL->addWidget(pCB);
        m_pButtonGroup->addButton(pCB);
    }
    m_pSA->setWidget(m_pFriendW);
}

void ShareFile::selectAll()
{
    QList<QAbstractButton*> cbList = m_pButtonGroup->buttons();
    for(int i = 0; i < cbList.size(); i++){
        cbList[i]->setChecked(true);
    }
}

void ShareFile::cancelSelect()
{
    QList<QAbstractButton*> cbList = m_pButtonGroup->buttons();
    for(int i = 0; i < cbList.size(); i++){
        cbList[i]->setChecked(false);
    }
}

void ShareFile::okShare()
{
    //获取文件的分享者以及当前路径 要分享的文件的名称
    QString strName = TcpClient::getInstance().getLoginName();
    QString strCurPath = TcpClient::getInstance().curPath();
    QString strShareFileName =OpeWidget::getInstance().getBook()->getShareFileName();

    QString strPath = strCurPath+"/"+strShareFileName;

    //从m_pFriendW中获取要被分享的人数
    int num = 0;
    QList<QAbstractButton*> cbList = m_pButtonGroup->buttons();
    for(int i = 0; i < cbList.size(); i++){
        if(cbList[i]->isChecked()){
            num++;
        }
    }

    //如果要分享的人数为0，直接返回
    if(num == 0) return;

    //cadata写入发送方，人数 csmsg写入要分享的人，路径
    PDU* pdu = mkPDU(num*32+strPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_REQUEST;
    sprintf(pdu->caData,"%s %d",strName.toStdString().c_str(),num);
    int j = 0;
    for(int i = 0; i < cbList.size(); i++){
        if(cbList[i]->isChecked()){
            memcpy((char*)(pdu->caMsg)+j*32,cbList[i]->text().toStdString().c_str(),cbList[i]->text().size());
            j++;
        }
    }

    memcpy((char*)(pdu->caMsg)+num*32,strPath.toStdString().c_str(),strPath.size());

    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;

    this->hide();
}

void ShareFile::cancelShare()
{
    this->hide();
}
