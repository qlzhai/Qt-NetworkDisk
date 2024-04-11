#include "opedb.h"
#include <QSet>

OpeDB::OpeDB(QObject *parent) : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");//采用qsqlite3数据库
}

OpeDB &OpeDB::getInstance()
{
    static OpeDB instance;
    return instance;//返回单例的引用
}

void OpeDB::init()
{
    m_db.setHostName("localhost");//连接本地数据库
    m_db.setDatabaseName("E:\\Qt_network_disk\\TcpServer\\cloud.db");
    if(m_db.open()){
        //如果数据库能够打开，查询数据库
        QSqlQuery query;
        query.exec("select * from usrInfo");
        while(query.next()){
            QString data = QString("%1,%2,%3").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString());
            qDebug()<<data;
        }
    }
    else{
        QMessageBox::critical(NULL,"打开数据库","打开数据库失败");
    }
}

OpeDB::~OpeDB()
{
    m_db.close();
}

bool OpeDB::handelRegist(const char *name, const char *pwd)
{
    if(name == NULL || pwd == NULL){
        qDebug() << "name or pwd is null!";
        return false;//存在空数据，无法注册
    }
    //注意存入的是字符串，要添加单引号
    QString data = QString("insert into usrInfo(name,pwd) values(\'%1\',\'%2\')").arg(name).arg(pwd);
    qDebug() << data;
    QSqlQuery query;
    return query.exec(data); //执行data语句，返回能否注册
}

bool OpeDB::handelLogin(const char *name, const char *pwd)
{
    if(name == NULL || pwd == NULL){
        qDebug() << "name or pwd is null!";
        return false;//存在空数据，无法注册
    }

    //拼接查询语句
    QString data = QString("select * from usrInfo where name = \'%1\' and pwd = \'%2\' and online = 0").arg(name).arg(pwd);
    qDebug() << data;
    QSqlQuery query;
    query.exec(data); //执行data语句
    if(query.next()){
        //执行data语句之后获得的数据
        //将登录状态改为1 已登录
        data = QString("update usrInfo set online = 1 where name = \'%1\' and pwd = \'%2\'").arg(name).arg(pwd);
        qDebug() << data;
        QSqlQuery query1;
        query1.exec(data); //执行data语句
        return true;
    }
    return false;
}

void OpeDB::handleOffline(const char *name)
{
    if(name == NULL){
        qDebug() << "name is null!";
        return ;//存在空数据，无法注册
    }

    QString data = QString("update usrInfo set online = 0 where name = \'%1\'").arg(name);
    qDebug() << data;
    QSqlQuery query;
    query.exec(data); //执行data语句
}

QStringList OpeDB::handleAllOnline()
{
    QString data = QString("select * from usrInfo where online = 1");

    QSqlQuery query;
    query.exec(data); //执行data语句
    QStringList result;
    result.clear();

    while(query.next()){
        result.append(query.value(1).toString());
    }

    return result;
}

int OpeDB::handleSearchUsr(const char *name)
{
    if(name == NULL) return -1;
    QString data = QString("select online from usrInfo where name = \'%1\'").arg(name);
    QSqlQuery query;
    query.exec(data); //执行data语句
    if(query.next()){
        int ret=query.value(0).toInt();
        if(ret==1){
            return 1;   //对方在线
        }
        else if(ret==0){
            return 0;   //对方离线
        }
    }
    //用户不存在，返回-1
    return -1;
}

/*
 * 处理添加好友请求，
 * 0是朋友，
 * 1不是朋友但是对方在线，
 * 2不是朋友但是对方不在线在线，
 * 3用户不存在，-1其他情况
 */
int OpeDB::handleAddFriendRequest(const char *usrName, const char *friName)
{
    qDebug() << "handleAddFriendRequest";
    if(usrName == NULL || friName == NULL){
        return -1;
    }

    //首先判断friName是否存在
    QString data = QString("select * from usrInfo where name = \'%1\'").arg(friName);
    QSqlQuery query;
    query.exec(data); //执行data语句
    if(query.next()){
        //用户存在
        //判断双方是否是朋友
        QString data1 = QString("select * from friend where (id=(select id from usrInfo where name = \'%1\') and friendId=(select id from usrInfo where name = \'%2\')) or (id=(select id from usrInfo where name = \'%3\') and friendId=(select id from usrInfo where name = \'%4\'))").arg(usrName).arg(friName).arg(friName).arg(usrName);
        QSqlQuery query1;
        query1.exec(data1); //执行data语句
        if(query1.next()){
            //双方是朋友
            return 0;
        }
        else{
            //双方不是朋友
            //判断对方是否在线
            QString data3 = QString("select online from usrInfo where name = \'%1\'").arg(friName);
            QSqlQuery query3;
            query3.exec(data3); //执行data语句
            if(query3.next()){
                int ret=query3.value(0).toInt();
                if(ret==1){
                    return 1;   //对方在线
                }
                else if(ret==0){
                    return 2;   //对方离线
                }
            }
        }
    }
    else{
        //用户不存在
        qDebug() << "usr no exist";
        return 3;
    }
    return -1;
}

bool OpeDB::handleAddFriendAgree(const char *usrName, const char *friName)
{
    if(usrName == NULL || friName == NULL){
        return false;
    }

    //插入好友关系的数据 对方 请求者
    QString data = QString("insert into friend(id, friendId) values((select id from usrInfo where name=\'%1\'), (select id from usrInfo where name=\'%2\'))").arg(usrName).arg(friName);
    qDebug()<<data;
    QSqlQuery query;
    return query.exec(data);
}

QSet<QString> OpeDB::handleFlushFriendList(const char *usrName)
{
    QSet<QString> result;
    result.clear();
    if(usrName == NULL){
        return result;
    }
    //这里id in...不能用id = ...，因为=只能匹配第一条数据
    QString data = QString("select friendId from friend where id = (select id from usrInfo where name=\'%1\')")
                           .arg(usrName);

    QSqlQuery query;
    query.exec(data);

    //query.next();
    //qDebug() << "handleFlushFriendList: " << query.value(0).toInt();

    while(query.next()){
        int id = query.value(0).toInt();
        data = QString("select * from usrInfo where id = %1").arg(id);
        QSqlQuery query1;
        query1.exec(data);
        query1.next();
        result.insert(query1.value(1).toString());
        qDebug() << query1.value(1).toString();
    }

    data = QString("select id from friend where friendId = (select id from usrInfo where name=\'%1\')")
               .arg(usrName);

    query.exec(data);
    while(query.next()){
        int id = query.value(0).toInt();
        data = QString("select * from usrInfo where id = %1").arg(id);
        QSqlQuery query1;
        query1.exec(data);
        query1.next();
        result.insert(query1.value(1).toString());
        qDebug() << query1.value(1).toString();
    }

    return result;
}

bool OpeDB::handleDeleteFriend(const char *usrName, const char *friName)
{
    if(usrName == NULL || friName == NULL){
        return false;
    }

    //判断双方是否是朋友
    QString data = QString("select * from friend where (id=(select id from usrInfo where name = \'%1\') and friendId=(select id from usrInfo where name = \'%2\')) "
                           "or (id=(select id from usrInfo where name = \'%3\') and friendId=(select id from usrInfo where name = \'%4\'))")
                       .arg(usrName).arg(friName).arg(friName).arg(usrName);
    QSqlQuery query;
    query.exec(data);
    if(query.next()){
        //双方是朋友 删除
        data = QString("delete from friend where ((id=(select id from usrInfo where name=\'%1\') and friendId=(select id from usrInfo where name=\'%2\')) "
                               "or (id=(select id from usrInfo where name=\'%3\') and friendId=(select id from usrInfo where name=\'%4\')))")
                           .arg(usrName).arg(friName).arg(friName).arg(usrName);
        return query.exec(data);
    }
    //双方不是朋友
    return false;
}
