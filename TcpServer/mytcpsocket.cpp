#include "mytcpsocket.h"
#include "mytcpserver.h"
#include <QSet>
#include <QDir>
#include <QFileInfoList>
MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    this->m_isUploadFile = false;//初始化不是上传文件状态
    m_pTimer = new QTimer;
    connect(this,SIGNAL(readyRead()),this,SLOT(recvMsg()));
    connect(this,SIGNAL(disconnected()),this,SLOT(clientOffline()));//客户端断开连接之后，服务器端会接受到一个disconnected()信号
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(sendFileToClient()));
}

QString MyTcpSocket::getName()
{
    return str_name;
}

//服务器端接收到数据
void MyTcpSocket::recvMsg()
{
    qDebug() << this->bytesAvailable(); // 客户端发送过来的数据大小   
    if(!this->m_isUploadFile){//不是上传文件的状态，按pdu操作
        uint uiPDULen = 0;
        this->read((char*)&uiPDULen,sizeof(uint));//先接受四个字节的大小的数据
        uint uiMsgLen = uiPDULen - sizeof(uiPDULen);
        PDU *pdu = mkPDU(uiMsgLen);
        this->read((char*)pdu + sizeof(int), uiPDULen - sizeof(uint));

        switch(pdu->uiMsgType){
            //服务器接收到客户端的注册请求
        case ENUM_MSG_TYPE_REGIST_REQUEST:
        {
            char caName[32] = {'\0'};
            char caPwd[32] = {'\0'};
            strncpy(caName,pdu->caData,32);
            strncpy(caPwd,pdu->caData+32,32);
            qDebug() << caName << caPwd <<pdu->uiMsgType;
            bool ret = OpeDB::getInstance().handelRegist(caName,caPwd);//数据库处理
            //产生回复的PDU
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_REGIST_RESPOND;//设置消息类型为注册回复
            if(ret){
                strcpy(respdu->caData,REGIST_OK);
                //注册成功的时候，创建一个以用户名字命名的文件夹，服务器debug目录中创建
                QDir dir;
                QString path = QString("./%1").arg(caName);
                dir.mkdir(path);
            }
            else{
                strcpy(respdu->caData,REGIST_FAILED);
            }
            write((char*)respdu,respdu->uiPDULen); //将消息发送给客户端
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //服务器接收到客户端的登录请求
        case ENUM_MSG_TYPE_LOGIN_REQUEST:
        {
            char caName[32] = {'\0'};
            char caPwd[32] = {'\0'};
            strncpy(caName,pdu->caData,32);
            strncpy(caPwd,pdu->caData+32,32);
            qDebug() << caName << caPwd <<pdu->uiMsgType;
            bool ret = OpeDB::getInstance().handelLogin(caName,caPwd);//数据库处理
            //产生回复的PDU
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_RESPOND;//设置消息类型为注册回复
            if(ret){
                strcpy(respdu->caData,LOGIN_OK);
                this->str_name = caName;
            }
            else{
                strcpy(respdu->caData,LOGIN_FAILED);
            }
            write((char*)respdu,respdu->uiPDULen); //将消息发送给客户端
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //服务器接收到客户端的可查看所有在线用户请求
        case ENUM_MSG_TYPE_ALL_ONLINE_REQUEST:
        {
            QStringList ret = OpeDB::getInstance().handleAllOnline();
            //产生回复的PDU
            uint resuiMsgLen = ret.size() * 32;//每一个姓名占32位字节
            PDU *respdu = mkPDU(resuiMsgLen);
            respdu->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINE_RESPOND;//设置消息类型为查看所有在线用户回复
            //将ret中的姓名拷贝到respdu
            for(int i = 0;i<ret.size();i++){
                //pdu中位置，数据，数据长度
                memcpy((char*)respdu->caMsg+i*32,
                       ret.at(i).toStdString().c_str(),
                       ret.at(i).size());
            }
            write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //服务器端接收到客户端发送的查找用户请求
        case ENUM_MSG_TYPE_SEARCH_REQUEST:
        {
            int ret = OpeDB::getInstance().handleSearchUsr(pdu->caData);
            qDebug() << "111" << pdu->caData;
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_SEARCH_RESPOND;
            if(ret == -1){
                strcpy(respdu->caData,SEARCH_USR_NO);
            }
            else if(ret == 1){
                strcpy(respdu->caData,SEARCH_USR_ONLINE);
            }else if(ret == 0){
                strcpy(respdu->caData,SEARCH_USR_OFFLINE);
            }
            write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //添加好友请求
        case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:
        {
            qDebug() << "ENUM_MSG_TYPE_ADD_FRIEND_REQUEST";
            char caName[32] = {'\0'};
            char caFriName[32] = {'\0'};
            strncpy(caName,pdu->caData,32);
            strncpy(caFriName,pdu->caData+32,32);
            int ret = OpeDB::getInstance().handleAddFriendRequest(caName,caFriName);
            if(ret == 0){
                //已经是好友
                PDU *respdu = mkPDU(0);
                respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPOND;
                strcpy(respdu->caData,EXISTED_FRIEND);
                write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
                free(respdu); //发送完消息后释放空间
                respdu = NULL;
            }
            else if(ret == 1){
                //在线,可向其申请添加好友 向客户端发送添加好友请求
                MyTcpServer::getInstance().resend(caFriName,pdu);
            }
            else if(ret == 2){
                //对方已离线
                PDU *respdu = mkPDU(0);
                respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPOND;
                strcpy(respdu->caData,ADD_FRIEND_OFFLINE);
                write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
                free(respdu); //发送完消息后释放空间
                respdu = NULL;
            }
            else if(ret == 3){
                //用户不存在
                PDU *respdu = mkPDU(0);
                respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPOND;
                strcpy(respdu->caData,ADD_FRIEND_NOEXIST);
                write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
                free(respdu); //发送完消息后释放空间
                respdu = NULL;
            }
            else{
                PDU *respdu = mkPDU(0);
                respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPOND;
                strcpy(respdu->caData,UNKNOW_ERROR);
                write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
                free(respdu); //发送完消息后释放空间
                respdu = NULL;
            }
            break;
        }
        //服务器端收到客户端发送的“同意添加对方为好友”的请求
        case ENUM_MSG_TYPE_ADD_FRIEND_AGREE:
        {
            char caName[32] = {'\0'};
            char caFriName[32] = {'\0'};
            strncpy(caName,pdu->caData,32);
            strncpy(caFriName,pdu->caData+32,32);
            OpeDB::getInstance().handleAddFriendAgree(caName,caFriName);
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE;
            QString friname = caFriName;
            qDebug() << "friname: " << friname;
            memcpy(respdu->caData,friname.toStdString().c_str(),friname.size());
            write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //服务器端收到客户端发送的“拒绝添加对方为好友”的请求
        case ENUM_MSG_TYPE_ADD_FRIEND_REFUSE:
        {
            char caName[32] = {'\0'};
            char caFriName[32] = {'\0'};
            strncpy(caName,pdu->caData,32);
            strncpy(caFriName,pdu->caData+32,32);
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REFUSE;
            QString friname = caFriName;
            qDebug() << "friname: " << friname;
            memcpy(respdu->caData,friname.toStdString().c_str(),friname.size());
            write((char*)respdu,respdu->uiPDULen);//利用Tcp协议发送数据
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //服务器端接收到客户端的刷新好友列表请求
        case ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST:
        {
            char caName[32] = {'\0'};
            strncpy(caName,pdu->caData,32);
            qDebug() << caName;
            QSet<QString> friendName = OpeDB::getInstance().handleFlushFriendList(caName);
            //产生回复的pdu
            uint resuiMsgLen = friendName.size()*32;
            PDU *respdu = mkPDU(resuiMsgLen);
            respdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND;
            //将friendName中的数据拷贝到respdu中
            int i = 0;
            for(const QString& name : friendName){
                //pdu中位置、数据、数据长度
                memcpy((char*)respdu->caMsg+i*32,
                       name.toStdString().c_str(),
                       name.size());
                qDebug() << "ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST: " << name;
                i++;
            }
            write((char*)respdu,respdu->uiPDULen);
            free(respdu); //发送完消息后释放空间
            respdu = NULL;
            break;
        }
        //服务器端接收到客户端发送的删除好友请求
        case ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST:
        {
            char usrName[32] = {'\0'};
            char friName[32] = {'\0'};
            //从pdu中获取用户姓名以及要删除好友的姓名
            strncpy(usrName,pdu->caData,32);
            strncpy(friName,pdu->caData+32,32);
            bool ret = OpeDB::getInstance().handleDeleteFriend(usrName,friName);
            PDU *respdu = mkPDU(0);
            //将用户姓名以及被删除的好友的姓名拷贝到respdu中
            strncpy(respdu->caData,usrName,32);
            strncpy(respdu->caData+32,friName,32);
            if(ret){
                //删除好友成功
                respdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND_TRUE;
            }
            else{
                //删除好友失败
                respdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND_FAILED;
            }
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu = NULL;
        }
        //服务器收到客户端的私聊请求,将聊天信息转发给chatName客户端
        case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST:
        {
            char chatName[32] = {'\0'};
            //从pdu中获取用户姓名以及要聊天好友的姓名
            strncpy(chatName,pdu->caData+32,32);
            //将聊天请求以及信息转发给chatName客户端
            MyTcpServer::getInstance().resend(chatName,pdu);
            break;
        }
        //服务器接收到客户端的群聊请求，将群聊信息转发给所有好友
        case ENUM_MSG_TYPE_GROUP_CHAT_REQUEST:
        {
            char sendName[32] = {'\0'};
            strcpy(sendName,pdu->caData);
            //获取好友列表
            QSet<QString> friendSet = OpeDB::getInstance().handleFlushFriendList(sendName);
            MyTcpServer::getInstance().resendGroupMsg(friendSet,pdu);
            break;
        }
        //服务器端接收到客户端发送的创建文件夹请求
        case ENUM_MSG_TYPE_CREATE_DIR_REQUEST:
        {
            QDir dir;
            char newDirName[32] = {'\0'};
            memcpy(newDirName,pdu->caData+32,32);//获取新建文件夹的名称
            QString curPath = (char*)pdu->caMsg;//从pdu中获取当前路径
            //判断当前路径是否存在
            bool ret = dir.exists(curPath);
            //生成回复的pdu
            if(ret){
                //当前路径存在，判断新建文件夹的名字是否已经存在
                QString newPath = curPath+"/"+newDirName;
                bool ret1 = dir.exists(newPath);
                if(ret1){
                    //文件夹名字重复
                    qDebug() << FILE_NAME_EXIST;
                    PDU *respdu = mkPDU(0);
                    respdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_RESPOND;
                    strcpy(respdu->caData,FILE_NAME_EXIST);
                    write((char*)respdu,respdu->uiPDULen);
                    free(respdu);
                    respdu=NULL;
                }else{
                    //文件夹名字不重复，可以创建
                    qDebug() << CREATE_DIR_OK;
                    PDU *respdu = mkPDU(0);
                    respdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_RESPOND;
                    dir.mkdir(newPath);
                    strcpy(respdu->caData,CREATE_DIR_OK);
                    write((char*)respdu,respdu->uiPDULen);
                    free(respdu);
                    respdu=NULL;
                }
            }else{
                //当前路径不存在
                qDebug() << DIR_NO_EXIST;
                PDU *respdu = mkPDU(0);
                respdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_RESPOND;
                strcpy(respdu->caData,DIR_NO_EXIST);
                write((char*)respdu,respdu->uiPDULen);
                free(respdu);
                respdu=NULL;
            }
            break;
        }
        //服务器端接收到刷新文件请求
        case ENUM_MSG_TYPE_FLUSH_DIR_REQUEST:
        {
            qDebug() << "ENUM_MSG_TYPE_FLUSH_DIR_REQUEST";
            char *curPath = new char[pdu->uiMsgLen];
            //从pdu中获取路径信息
            memcpy(curPath,pdu->caMsg,pdu->uiMsgLen);
            QDir dir(curPath);//进入路径
            //获取文件列表
            QFileInfoList fileInfoList = dir.entryInfoList();
            int iFileCount = fileInfoList.size();//文件个数
            //生成回复的PDU，用FileInfo结构体存储文件信息，结构的大小*文件个数就是回复消息的大小
            PDU* respdu = mkPDU(sizeof(FileInfo)*iFileCount);
            respdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_DIR_RESPOND;
            FileInfo *fileInfo = NULL;
            QString fileName = "";
            for(int i = 0; i < iFileCount;i++){
                //由地址指针填充数据
                fileInfo = (FileInfo*)(respdu->caMsg)+i;//fileInfo指向的地址
                fileName = fileInfoList[i].fileName();
                memcpy(fileInfo->fileName,fileName.toStdString().c_str(),fileName.size());
                if(fileInfoList[i].isDir()){
                    fileInfo->fileType = 0;//0表示文件夹
                }
                if(fileInfoList[i].isFile()){
                    fileInfo->fileType = 1;//1表示文件
                }
                qDebug() << fileInfoList[i].fileName()
                         << fileInfoList[i].size()
                         << "文件夹：" << fileInfoList[i].isDir()
                         << "常规文件：" << fileInfoList[i].isFile();
            }
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu=NULL;
            delete []curPath;
            curPath = NULL;
            break;
        }
        //服务器接收到客户端发送的删除文件夹请求
        case ENUM_MSG_TYPE_DELETE_DIR_REQUEST:
        {
            char delName[32] = {'\0'};
            strcpy(delName,pdu->caData);
            char *curPath = new char[pdu->uiMsgLen];
            strcpy(curPath,(char*)pdu->caMsg);
            QString path = QString("%1/%2").arg(curPath).arg(delName);//要删除文件夹的路径
            //获取path的文件信息
            QFileInfo fileInfo(path);
            bool ret = false;
            if(fileInfo.isDir()){
                //是文件夹
                ret = true;
                QDir dir;
                dir.setPath(path);
                dir.removeRecursively();//删除文件夹以及文件夹中的所有内容
            }else if(fileInfo.isFile()){
                ret = false;
            }
            //生成回复的PDU
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_DELETE_DIR_RESPOND;
            if(ret){
                //删除成功
                strcpy(respdu->caData,DELETE_DIR_SUCCESSED);
            }else{
                //删除失败
                strcpy(respdu->caData,DELETE_DIR_FAILED);
            }
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu=NULL;
            delete []curPath;
            curPath = NULL;
            break;
        }
        //服务器接收到客户端发送的重命名文件请求
        case ENUM_MSG_TYPE_RENAME_FILE_REQUEST:{
            char oldName[32] = {'\0'};
            char newName[32] = {'\0'};
            memcpy(oldName,pdu->caData,32);
            memcpy(newName,pdu->caData+32,32);
            char *curPath = new char[pdu->uiMsgLen];
            memcpy(curPath,(char*)pdu->caMsg,pdu->uiMsgLen);
            QString oldPath = QString("%1/%2").arg(curPath).arg(oldName);
            QString newPath = QString("%1/%2").arg(curPath).arg(newName);
            PDU* respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_RENAME_FILE_RESPOND;
            //判断新路径是否已经存在
            QDir dir;
            if(dir.exists(newPath)){
                //新路径存在 重命名失败
                strcpy(respdu->caData,RENAME_FILE_FAILED);
            }else{
                //新路径不存在 可以重命名
                strcpy(respdu->caData,RENAME_FILE_SUCCESSED);
                dir.rename(oldPath,newPath);//重命名操作
            }
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu = NULL;
            delete []curPath;
            curPath = NULL;
            break;
        }
        //服务器接收到客户端发送的进入文件夹请求
        case ENUM_MSG_TYPE_ENTER_DIR_REQUEST:
        {
            char selectName[32] = {'\0'};
            char *curPath = new char[pdu->uiMsgLen];
            strncpy(selectName,pdu->caData,32);
            memcpy(curPath,(char*)pdu->caMsg,pdu->uiMsgLen);
            QString path = QString("%1/%2").arg(curPath).arg(selectName);//合并路径
            QFileInfo qFileinfo(path);
            if(qFileinfo.isDir()){
                //是文件夹 可进入
                QDir dir(path);
                QFileInfoList fileInfoList = dir.entryInfoList();//获取文件列表
                int iFileCount = fileInfoList.size();//文件个数
                //生成回复的pdu，用FileInfo结构体存储文件信息
                PDU* respdu = mkPDU(sizeof(FileInfo)*iFileCount);
                respdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_DIR_RESPOND;
                FileInfo *fileInfo = NULL;
                QString fileName = "";
                for(int i = 0; i < iFileCount; i++){
                    //由地址指针填充数据
                    fileInfo = (FileInfo*)respdu->caMsg+i;
                    fileName = fileInfoList[i].fileName();
                    memcpy(fileInfo->fileName,fileName.toStdString().c_str(),fileName.size());
                    if(fileInfoList[i].isDir()){
                        fileInfo->fileType = 0;//0表示文件夹
                    }
                    if(fileInfoList[i].isFile()){
                        fileInfo->fileType = 1;//1表示文件
                    }
                }
                write((char*)respdu,respdu->uiPDULen);
                free(respdu);
                respdu = NULL;
            }
            if(qFileinfo.isFile()){
                //是文件，返回错误信息
                PDU* respdu = mkPDU(0);
                respdu->uiMsgType = ENUM_MSG_TYPE_ENTER_DIR_RESPOND;
                strcpy(respdu->caData,ENTER_DIR_FAILED);
                write((char*)respdu,respdu->uiPDULen);
                free(respdu);
                respdu = NULL;
            }
            delete []curPath;
            curPath = NULL;
            break;
        }
        //服务器端接收到客户端的上传文件请求
        case ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST:
        {
            qDebug() << "ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST:";
            //从pdu中解析出上传文件的名称，大小以及路径
            char *strCurPath = new char[pdu->uiMsgLen];
            memcpy(strCurPath,(char*)pdu->caMsg,pdu->uiMsgLen);
            qint64 fileSize = 0;
            char curFileName[32] = {'\0'};
            //sscanf拆解字符串，对应sprintf
            sscanf(pdu->caData,"%s %lld",curFileName,&fileSize);
            qDebug() << "curFileName: " << curFileName;
            QString strPath = QString("%1/%2").arg(strCurPath).arg(curFileName);//拼接路径
            qDebug() << strPath;
            delete []strCurPath;
            strCurPath = NULL;

            this->m_file.setFileName(strPath);
            //以只写的方式打开文件，若文件不存在，则会自动创建文件
            if(m_file.open(QIODevice::WriteOnly)){//设置上传文件状态
                this->m_isUploadFile = true;
                this->m_iTotal = fileSize;
                this->m_iRecved = 0;
            }
            break;
        }
        //服务器接收到客户端的删除文件请求
        case ENUM_MSG_TYPE_DELETE_FILE_REQUEST:
        {

            char delName[32] = {'\0'};
            strcpy(delName,pdu->caData);
            char *curPath = new char[pdu->uiMsgLen];
            strcpy(curPath,(char*)pdu->caMsg);
            QString path = QString("%1/%2").arg(curPath).arg(delName);//要删除文件夹的路径
            qDebug() << path;
            //获取path的文件信息
            QFileInfo fileInfo(path);
            bool ret = false;
            if(fileInfo.isDir()){
                //是文件夹
                ret = false;
            }else if(fileInfo.isFile()){
                ret = true;
                QDir dir;
                dir.remove(path);//删除文件夹以及文件夹中的所有内容
            }
            //生成回复的PDU
            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FILE_RESPOND;
            if(ret){
                //删除成功
                strcpy(respdu->caData,DELETE_FILE_SUCCESSED);
            }else{
                //删除失败
                strcpy(respdu->caData,DELETE_FILE_FAILED);
            }
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu=NULL;
            delete []curPath;
            curPath = NULL;
            break;
        }
        //服务器接收到客户端的下载文件请求
        case ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST:
        {
            //从pdu中获取文件名称以及当前路径并生成文件路径
            char strFileName[32] = {'\0'};
            char *strCurPath = new char[pdu->uiMsgLen];
            strcpy(strFileName,pdu->caData);
            memcpy(strCurPath,(char*)pdu->caMsg,pdu->uiMsgLen);
            QString path = QString("%1/%2").arg(strCurPath).arg(strFileName);
            qDebug() << path;
            delete []strCurPath;
            strCurPath = NULL;

            //获取文件大小
            QFileInfo fileInfo(path);
            qint64 fileSize = fileInfo.size();

            //生成回复的pdu，将文件名，文件大小传递给客户端
            PDU* respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND;
            sprintf(respdu->caData,"%s %lld",strFileName,fileSize);
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu = NULL;

            m_file.setFileName(path);
            m_file.open(QIODevice::ReadOnly);

            m_pTimer->start(1000);
            break;
        }
        //服务器接收到客户端的分享文件请求
        case ENUM_MSG_TYPE_SHARE_FILE_REQUEST:
        {
            //从pdu中获取数据 cadata中存放的是发送方以及认数
            char strSendName[32] = {'\0'};
            int num = 0;
            sscanf(pdu->caData,"%s %d",strSendName,&num);
            qDebug() << "strSendName: " << strSendName;
            qDebug() << "num: " << num;

            //解析出要分享的人 以及 文件路径信息
            int size = num * 32;
            char *strFilePath = new char[pdu->uiMsgLen-size];
            memcpy(strFilePath,(char*)pdu->caMsg+num*32,pdu->uiMsgLen-size);
            qDebug() << "strFilePath: " << strFilePath;
            char caRecvName[32] = {'\0'};

            //生成回复的pdu，将分享请求转发给要分享的人
            PDU* respdu = mkPDU(pdu->uiMsgLen-size);
            respdu->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_NOTE;
            strcpy(respdu->caData,strSendName);
            memcpy((char*)respdu->caMsg,strFilePath,pdu->uiMsgLen-size);

            delete []strFilePath;
            strFilePath = NULL;

            //根据姓名转发给不同的用户
            for(int i = 0;i < num; i++){
                memcpy(caRecvName,(char*)pdu->caMsg+i*32,32);
                qDebug() << "caRecvName: " << caRecvName;
                MyTcpServer::getInstance().resend(caRecvName,respdu);
            }
            free(respdu);
            respdu=NULL;

            //向发送方回复分享回应
            PDU* respdu2 = mkPDU(0);
            respdu2->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_RESPOND;
            strcpy(respdu2->caData,"share file successed");
            write((char*)respdu2,respdu2->uiPDULen);
            free(respdu2);
            respdu2=NULL;
            break;
        }
            //服务器接收到客户端的分享通知回应
        case ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND:
        {
            qDebug() << "ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND: ";
            char strLoginName[32] = {'\0'};
            strcpy(strLoginName,pdu->caData);
            char *pPath = new char[pdu->uiMsgLen];
            memcpy(pPath,(char*)pdu->caMsg,pdu->uiMsgLen);

            qDebug() << "strLoginName: " << strLoginName;
            qDebug() << "pPath: " << pPath;

            //要分享的文件的位置
            QString strShareFilePath = QString("%1").arg(pPath);
            //默认保存路径 保存在根目录
            //QString strDefaultPath = QString("./%1").arg(strLoginName)+'/'+"download";
            QString strDefaultPath = QString("./%1").arg(strLoginName);

            int index = strShareFilePath.lastIndexOf('/');
            QString strFileName = strShareFilePath.right(strShareFilePath.size()-index-1);
            QString strRecvFilePath = strDefaultPath+"/"+strFileName;

            qDebug() << "strShareFilePath: " << strShareFilePath;
            qDebug() << "strRecvFilePath: " << strRecvFilePath;

            //判断是文件还是文件夹
            QFileInfo fileInfo(strShareFilePath);
            if(fileInfo.isFile()){//文件，直接拷贝
                qDebug() << "文件，直接拷贝";
                QFile::copy(strShareFilePath,strRecvFilePath);
            }
            if(fileInfo.isDir()){//文件夹
                this->copyDir(strShareFilePath,strRecvFilePath);
            }

            delete []pPath;
            pPath = NULL;
            break;
        }
            //服务器接收到客户端的移动文件请求
        case ENUM_MSG_TYPE_MOVE_FILE_REQUEST:
        {
            char caFileName[32] = {'\0'};
            int srcLen = 0;
            int destLen = 0;
            sscanf(pdu->caData,"%d %d %s",&srcLen,&destLen,caFileName);

            qDebug() << "caFileName:" << caFileName;
            //获取路径信息
            char *pSrcPath = new char[srcLen+1];
            char *destPath = new char[destLen+1+32];
            memset(pSrcPath,'\0',srcLen+1);
            memset(destPath,'\0',destLen+1+32);

            memcpy(pSrcPath,pdu->caMsg,srcLen);
            memcpy(destPath,(char*)pdu->caMsg+srcLen+1,destLen);

            PDU *respdu = mkPDU(0);
            respdu->uiMsgType = ENUM_MSG_TYPE_MOVE_FILE_RESPOND;
            QFileInfo fileInfo(destPath);
            if(fileInfo.isDir()){//目标路径是文件夹
                strcat(destPath,"/");
                strcat(destPath,caFileName);
                qDebug() << "pSrcPath:" <<pSrcPath;
                qDebug() << "destPath:" <<destPath;
                bool ret = QFile::rename(pSrcPath,destPath);
                if(ret){//移动成功
                    strcpy(respdu->caData,MOVE_FILE_OK);
                }else{//移动失败
                    strcpy(respdu->caData,COMMON_ERR);
                }
            }else if(fileInfo.isFile()){//目标路径是文件
                strcpy(respdu->caData,MOVE_FILE_FAILURED);
            }

            delete []pSrcPath;
            pSrcPath = NULL;

            delete []destPath;
            destPath = NULL;

            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu = NULL;

            break;
        }
        default:
            break;
        }
        free(pdu); //发送完消息后释放空间
        pdu = NULL;
    }else{//上传文件状态
        //以二进制的形式接收收据
        qDebug() << "上传文件";
        QByteArray buff = readAll();//返回字节数组
        this->m_file.write(buff);
        m_iRecved+=buff.size();
        PDU* respdu = mkPDU(0);
        respdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND;
        if(m_iRecved == m_iTotal){//上传文件成功
            qDebug() << "上传文件成功";
            strcpy(respdu->caData,UPLOAD_FILE_SUCCESSED);
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu = NULL;
        }else{//上传失败
            qDebug() << "上传文件失败";
            strcpy(respdu->caData,UPLOAD_FILE_FAILED);
            write((char*)respdu,respdu->uiPDULen);
            free(respdu);
            respdu = NULL;
        }
        this->m_file.close();
        this->m_isUploadFile = false;
    }
}

void MyTcpSocket::clientOffline()
{
    OpeDB::getInstance().handleOffline(str_name.toStdString().c_str());
    emit offline(this);//发送下线信号 this指针保存的就是MyTcpSocket地址
}

void MyTcpSocket::sendFileToClient()
{
    m_pTimer->stop();
    char* pBuffer = new char[4096];
    qint64 ret = 0;
    while(true){
        ret = m_file.read(pBuffer,4096);
        if(ret > 0 && ret <= 4096){
            //向客户端发送数据
            write(pBuffer,ret);
        }else if(ret == 0){//读取完毕
            m_file.close();
            break;
        }else{//读取失败
            m_file.close();
            break;
        }
    }
    delete []pBuffer;
    pBuffer = NULL;
}

void MyTcpSocket::copyDir(QString strSrcDir, QString strDesDir)
{
    QDir dir;
    dir.mkdir(strDesDir);

    dir.setPath(strSrcDir);
    QFileInfoList fileInfoList = dir.entryInfoList();

    QString srcTmp;
    QString desTmp;
    for(int i = 0; i < fileInfoList.size(); i++){
        if(fileInfoList[i].isFile()){
            //文件，直接拷贝
            srcTmp=strSrcDir+"/"+fileInfoList[i].fileName();
            desTmp=strDesDir+"/"+fileInfoList[i].fileName();
            QFile::copy(srcTmp,desTmp);
        }else if(fileInfoList[i].isDir()){
            if(QString(".")==fileInfoList[i].fileName() || QString("..")==fileInfoList[i].fileName()){
                continue;
            }
            srcTmp=strSrcDir+"/"+fileInfoList[i].fileName();
            desTmp=strDesDir+"/"+fileInfoList[i].fileName();
            copyDir(srcTmp,desTmp);
        }
    }
}


