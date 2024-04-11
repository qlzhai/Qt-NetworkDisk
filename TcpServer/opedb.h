#ifndef OPEDB_H
#define OPEDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>   //字符串列表

class OpeDB : public QObject
{
    Q_OBJECT
public:
    explicit OpeDB(QObject *parent = nullptr);

    static OpeDB& getInstance(); //创建数据库的单例模式，构造OpeDB
    void init();//初始化数据库连接,失败则报错
    ~OpeDB();//关闭数据库

    bool handelRegist(const char* name,const char *pwd);//处理注册请求
    bool handelLogin(const char* name,const char *pwd);//处理登录请求
    void handleOffline(const char* name);//处理客户端下线
    QStringList handleAllOnline();//处理查看所有在线用户,以链表形式返回所有在线用户的name
    int handleSearchUsr(const char* name);//查找用户信息，-1用户不存在，1存在且在线，0存在但不在线
    //处理添加好友请求，0是朋友，1不是朋友但是对方在线，2不是朋友但是对方不在线在线，3用户不存在，-1其他情况
    int handleAddFriendRequest(const char* usrName,const char* friName);
    //处理同意添加对方为好友
    bool handleAddFriendAgree(const char* usrName,const char* friName);
    //数据库处理刷新好友列表请求
    QSet<QString> handleFlushFriendList(const char* usrName);
    //数据库处理删除好友请求 true删除成功 false删除失败，可能是因为已经删除了，但是好友列表还显示了，需要重新刷新好友列表
    bool handleDeleteFriend(const char* usrName,const char* friName);
signals:

private:
    QSqlDatabase m_db; //用来连接数据库
};

#endif // OPEDB_H
