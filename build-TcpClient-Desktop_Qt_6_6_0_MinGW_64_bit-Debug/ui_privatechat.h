/********************************************************************************
** Form generated from reading UI file 'privatechat.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATECHAT_H
#define UI_PRIVATECHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrivateChat
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTextEdit *ui_Msg_te;
    QHBoxLayout *horizontalLayout;
    QLineEdit *ui_Msg_le;
    QPushButton *sendMsg_pb;

    void setupUi(QWidget *PrivateChat)
    {
        if (PrivateChat->objectName().isEmpty())
            PrivateChat->setObjectName("PrivateChat");
        PrivateChat->resize(400, 300);
        gridLayout = new QGridLayout(PrivateChat);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        ui_Msg_te = new QTextEdit(PrivateChat);
        ui_Msg_te->setObjectName("ui_Msg_te");
        QFont font;
        font.setPointSize(20);
        ui_Msg_te->setFont(font);
        ui_Msg_te->setReadOnly(true);

        verticalLayout->addWidget(ui_Msg_te);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ui_Msg_le = new QLineEdit(PrivateChat);
        ui_Msg_le->setObjectName("ui_Msg_le");
        ui_Msg_le->setFont(font);

        horizontalLayout->addWidget(ui_Msg_le);

        sendMsg_pb = new QPushButton(PrivateChat);
        sendMsg_pb->setObjectName("sendMsg_pb");
        sendMsg_pb->setFont(font);

        horizontalLayout->addWidget(sendMsg_pb);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(PrivateChat);

        QMetaObject::connectSlotsByName(PrivateChat);
    } // setupUi

    void retranslateUi(QWidget *PrivateChat)
    {
        PrivateChat->setWindowTitle(QCoreApplication::translate("PrivateChat", "Form", nullptr));
        sendMsg_pb->setText(QCoreApplication::translate("PrivateChat", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrivateChat: public Ui_PrivateChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATECHAT_H
