#ifndef ONLINE_H
#define ONLINE_H

#include <QWidget>
#include "protocol.h"

namespace Ui {
class Online;
}

class Online : public QWidget
{
    Q_OBJECT

public:
    explicit Online(QWidget *parent = nullptr);
    ~Online();

    //定义显示在线用户的ui
    void showUsr(PDU *pdu);
public slots:

private slots:
    void on_addFriend_pb_clicked();

private:
    Ui::Online *ui;
};

#endif // ONLINE_H
