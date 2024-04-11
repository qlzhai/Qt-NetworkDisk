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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClientClass
{
public:

    void setupUi(QWidget *TcpClientClass)
    {
        if (TcpClientClass->objectName().isEmpty())
            TcpClientClass->setObjectName("TcpClientClass");
        TcpClientClass->resize(600, 400);

        retranslateUi(TcpClientClass);

        QMetaObject::connectSlotsByName(TcpClientClass);
    } // setupUi

    void retranslateUi(QWidget *TcpClientClass)
    {
        TcpClientClass->setWindowTitle(QCoreApplication::translate("TcpClientClass", "TcpClient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpClientClass: public Ui_TcpClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
