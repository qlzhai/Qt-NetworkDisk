#ifndef SHAREFILE_H
#define SHAREFILE_H

#include <QWidget>
#include <QPushButton> //按钮
#include <QHBoxLayout> //水平布局
#include <QVBoxLayout> //垂直布局
#include <QButtonGroup> //选择统一管理
#include <QScrollArea> //区域选择
#include <QCheckBox> //处理打勾
#include <QListWidget>
#include <QAbstractButton>

class ShareFile : public QWidget
{
    Q_OBJECT
public:
    explicit ShareFile(QWidget *parent = nullptr);
    void test();//测试

    static ShareFile &getInstance();

    void updateFriend(QListWidget *friendListW);//更新共享文件窗口的好友列表信息

signals:

public slots:
    void selectAll();
    void cancelSelect();
    void okShare();
    void cancelShare();

private:
    QPushButton *m_pSelectAllPB;//全选
    QPushButton *m_pCancelSelectPB;//取消选择
    QPushButton *m_pOkSharePB;//确定分享
    QPushButton *m_pCancelSharePB;//取消分享

    QScrollArea *m_pSA;//展示区域
    QWidget *m_pFriendW;//要分享的好友

    QButtonGroup *m_pButtonGroup;//管理所有好友
    QVBoxLayout *m_pFriendWVBL; //保存垂直布局
};

#endif // SHAREFILE_H
