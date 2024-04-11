/********************************************************************************
** Form generated from reading UI file 'TcpClient.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *usName_le;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *usPwd_le;
    QSpacerItem *verticalSpacer_4;
    QPushButton *login_pb;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *registe_pb;
    QPushButton *cancel_pb;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName("TcpClient");
        TcpClient->resize(633, 492);
        gridLayout = new QGridLayout(TcpClient);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(TcpClient);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        verticalLayout->addWidget(label);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        label_2 = new QLabel(TcpClient);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        usName_le = new QLineEdit(TcpClient);
        usName_le->setObjectName("usName_le");
        usName_le->setFont(font);

        verticalLayout_2->addWidget(usName_le);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        usPwd_le = new QLineEdit(TcpClient);
        usPwd_le->setObjectName("usPwd_le");
        usPwd_le->setFont(font);
        usPwd_le->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(usPwd_le);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        login_pb = new QPushButton(TcpClient);
        login_pb->setObjectName("login_pb");
        QFont font1;
        font1.setPointSize(18);
        login_pb->setFont(font1);

        verticalLayout_3->addWidget(login_pb);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        registe_pb = new QPushButton(TcpClient);
        registe_pb->setObjectName("registe_pb");
        QFont font2;
        font2.setPointSize(12);
        registe_pb->setFont(font2);

        horizontalLayout_2->addWidget(registe_pb);

        cancel_pb = new QPushButton(TcpClient);
        cancel_pb->setObjectName("cancel_pb");
        cancel_pb->setFont(font2);

        horizontalLayout_2->addWidget(cancel_pb);


        verticalLayout_4->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QWidget *TcpClient)
    {
        TcpClient->setWindowTitle(QCoreApplication::translate("TcpClient", "TcpClient", nullptr));
        label->setText(QCoreApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("TcpClient", "\345\257\206   \347\240\201\357\274\232", nullptr));
        login_pb->setText(QCoreApplication::translate("TcpClient", "\347\231\273\345\275\225", nullptr));
        registe_pb->setText(QCoreApplication::translate("TcpClient", "\346\263\250\345\206\214", nullptr));
        cancel_pb->setText(QCoreApplication::translate("TcpClient", "\346\263\250\351\224\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
