#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QWidget>
#include "protocol.h"
namespace Ui {
class PrivateChat;
}

class PrivateChat : public QWidget
{
    Q_OBJECT

public:
    explicit PrivateChat(QWidget *parent = nullptr);
    ~PrivateChat();

    static PrivateChat &getInstance();

    //设置信息的发送者以及接收者
    void setChatName(QString name);

    //更新聊天对话框中的信息
    void updateMsg(const PDU *pdu);
private slots:
    void on_sendMsg_pb_clicked();

private:
    Ui::PrivateChat *ui;

    QString m_chatName;
    QString m_strLoginName;
};

#endif // PRIVATECHAT_H
