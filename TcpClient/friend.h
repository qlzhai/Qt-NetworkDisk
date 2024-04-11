#ifndef FRIEND_H
#define FRIEND_H

#include <QWidget>
#include <QTextEdit> //信息显示
#include <QListWidget>
#include <QLineEdit> //信息输入
#include <QPushButton> //按钮
#include <QVBoxLayout> //垂直布局
#include <QHBoxLayout> //水平布局
#include "online.h"

class Friend : public QWidget
{
    Q_OBJECT
public:
    explicit Friend(QWidget *parent = nullptr);
    //显示在线用户
    void showALLOnlineUsr(PDU *pdu);
    //显示好友列表
    void showFriendName(PDU *pdu);
    //显示群聊信息
    void showGroupMsg(PDU* pdu);
    QString m_strSearchName;

    //获取好友列表窗口
    QListWidget* getFriendListWidget();
signals:

public slots:
    //槽连接
    //显示在线用户
    void showOnline();
    //查找用户
    void searchUsr();
    //刷新好友列表
    void flushFriList();
    //删除好友操作
    void deleteFriend();
    //私聊好友操作
    void privateChatFriend();
    //群聊操作
    void groupChat();
private:
    //窗口(显示信息)
    QTextEdit *m_pShowMsgTE;
    //列表（好友列表）
    QListWidget *m_pFriendListWidget;
    //窗口(输入信息)
    QLineEdit *m_pInputMsgLE;

    //按钮(删除好友)
    QPushButton *m_pDelFriendPB;
    //按钮(刷新好友列表)
    QPushButton *m_pFlushFriendPB;
    //按钮(搜索在线用户)
    QPushButton *m_pShowOnlineUsrPB;
    //按钮(查看用户)
    QPushButton *m_pSearchUsrPB;
    //按钮(信息发送)
    QPushButton *m_pMsgSendPB;
    //按钮(私聊)
    QPushButton *m_pPrivateChatPB;

    //产生online的对象
    Online *m_pOnline;
};

#endif // FRIEND_H
