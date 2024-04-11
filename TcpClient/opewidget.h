#ifndef OPEWIDGET_H
#define OPEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include "friend.h"
#include "online.h"
#include "book.h"

#include <QStackedWidget> //堆栈窗口 每次只显示一个
class OpeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpeWidget(QWidget *parent = nullptr);
    static OpeWidget &getInstance();//单例模式
    Friend *getFriend();//通过单例函数访问私有成员
    Book *getBook();
signals:

private:
    QListWidget *m_pListW;

    Friend *m_pFriend;
    Book *m_pBook;

    QStackedWidget *m_pSW;//堆栈窗口
};

#endif // OPEWIDGET_H
