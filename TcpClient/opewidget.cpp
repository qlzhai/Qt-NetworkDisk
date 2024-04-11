#include "opewidget.h"

OpeWidget::OpeWidget(QWidget *parent)
    : QWidget{parent}
{
    m_pListW = new QListWidget(this);
    m_pListW->addItem("好友");
    m_pListW->addItem("图书");

    m_pFriend = new Friend;
    m_pBook = new Book;

    //将m_pFriend与m_pBook放入堆栈窗口
    m_pSW = new QStackedWidget;
    m_pSW->addWidget(m_pFriend);
    m_pSW->addWidget(m_pBook);

    //水平布局
    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addWidget(m_pListW);
    pMain->addWidget(m_pSW);
    setLayout(pMain);

    //连接，pList发送信号，堆栈窗口处理信号
    connect(m_pListW,SIGNAL(currentRowChanged(int)),m_pSW,SLOT(setCurrentIndex(int)));
}

OpeWidget &OpeWidget::getInstance()
{
    static OpeWidget instance;
    return instance;
}

Friend *OpeWidget::getFriend()
{
    return m_pFriend;
}

Book *OpeWidget::getBook()
{
    return m_pBook;
}
