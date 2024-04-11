#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdlib.h>
#include <string>
#include <unistd.h>

typedef unsigned int uint;

#define REGIST_OK "regtist ok"
#define REGIST_FAILED "regist failed : name existed"

#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed : name failed or password failed or relogin"

#define SEARCH_USR_NO "no such people"
#define SEARCH_USR_ONLINE "online"
#define SEARCH_USR_OFFLINE "offline"

#define UNKNOW_ERROR "unknow error"
#define EXISTED_FRIEND "friend exist"
#define ADD_FRIEND_OFFLINE "usr offline"
#define ADD_FRIEND_NOEXIST "usr not exit"

#define ADD_FRIEND_AGREE "add friend agree"
#define ADD_FRIEND_REFUSE "add friend refuse"

#define DELETE_FRIEND_TRUE "delete friend true"
#define DELETE_FRIEND_FAILED "delete friend failed"

#define DIR_NO_EXIST "dir not exit"
#define FILE_NAME_EXIST "file name exit"
#define CREATE_DIR_OK "dir ok"

#define DELETE_DIR_SUCCESSED "delete dir successed"
#define DELETE_DIR_FAILED "delete dir failed: no dir"

#define RENAME_FILE_FAILED "rename file failed: file name exists"
#define RENAME_FILE_SUCCESSED "rename file successed"

#define ENTER_DIR_FAILED "enter dir failed: is reguler file"

#define UPLOAD_FILE_FAILED "upload file failed"
#define UPLOAD_FILE_SUCCESSED "upload file successed"

#define DELETE_FILE_SUCCESSED "delete file successed"
#define DELETE_FILE_FAILED "delete file failed: no file"

#define MOVE_FILE_OK "move file ok"
#define MOVE_FILE_FAILURED "move file failured:is reguler file"

#define COMMON_ERR "operate failed: system is busy"

//实际消息类型
enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN = 0,

    ENUM_MSG_TYPE_REGIST_REQUEST, //注册请求
    ENUM_MSG_TYPE_REGIST_RESPOND, //注册回复

    ENUM_MSG_TYPE_LOGIN_REQUEST, //登录请求
    ENUM_MSG_TYPE_LOGIN_RESPOND, //登录回复

    ENUM_MSG_TYPE_ALL_ONLINE_REQUEST, //查看在线用户请求
    ENUM_MSG_TYPE_ALL_ONLINE_RESPOND, //查看在线用户回复

    ENUM_MSG_TYPE_SEARCH_REQUEST, //搜索用户请求
    ENUM_MSG_TYPE_SEARCH_RESPOND, //搜索用户回复

    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST, //添加好友请求
    ENUM_MSG_TYPE_ADD_FRIEND_RESPOND, //添加好友回复

    ENUM_MSG_TYPE_ADD_FRIEND_AGREE, //同意添加对方为好友
    ENUM_MSG_TYPE_ADD_FRIEND_REFUSE, //拒绝添加对方为好友

    ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST, //刷新好友列表请求
    ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND, //刷新好友列表响应

    ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST, //删除好友请求
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND_TRUE, //删除好友成功
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND_FAILED, //删除好友失败

    ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST, //私聊请求
    ENUM_MSG_TYPE_PRIVATE_CHAT_RESPOND, //私聊回应

    ENUM_MSG_TYPE_GROUP_CHAT_REQUEST, //群聊请求
    ENUM_MSG_TYPE_GROUP_CHAT_RESPOND, //群聊回应

    ENUM_MSG_TYPE_CREATE_DIR_REQUEST, //创建文件夹请求
    ENUM_MSG_TYPE_CREATE_DIR_RESPOND, //创建文件夹回应

    ENUM_MSG_TYPE_FLUSH_DIR_REQUEST, //刷新文件夹请求
    ENUM_MSG_TYPE_FLUSH_DIR_RESPOND, //刷新文件夹回应

    ENUM_MSG_TYPE_DELETE_DIR_REQUEST, //删除文件夹请求
    ENUM_MSG_TYPE_DELETE_DIR_RESPOND, //删除文件夹回应

    ENUM_MSG_TYPE_RENAME_FILE_REQUEST, //重命名文件请求
    ENUM_MSG_TYPE_RENAME_FILE_RESPOND, //重命名文件回应

    ENUM_MSG_TYPE_ENTER_DIR_REQUEST, //进入文件夹请求
    ENUM_MSG_TYPE_ENTER_DIR_RESPOND, //进入文件夹回应

    ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST, //上传文件请求
    ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND, //上传文件回应

    ENUM_MSG_TYPE_DELETE_FILE_REQUEST, //删除文件请求
    ENUM_MSG_TYPE_DELETE_FILE_RESPOND, //删除文件回应

    ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST, //下载文件请求
    ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND, //下载文件回应

    ENUM_MSG_TYPE_SHARE_FILE_REQUEST, //分享文件请求
    ENUM_MSG_TYPE_SHARE_FILE_RESPOND, //分享文件回应
    ENUM_MSG_TYPE_SHARE_FILE_NOTE, //分享文件通知
    ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND, //分享文件通知响应

    ENUM_MSG_TYPE_MOVE_FILE_REQUEST, //移动文件请求
    ENUM_MSG_TYPE_MOVE_FILE_RESPOND, //移动文件回应

    ENUM_MSG_TYPE_MAX = 0X00ffffff
};

//文件信息
struct FileInfo{
    char fileName[32];//文件名称
    int fileType;//文件类型
};

//协议数据单元
typedef struct PDU{
    uint uiPDULen; //总的协议数据单元的大小
    uint uiMsgType; //消息类型
    char caData[64];
    uint uiMsgLen; //实际消息长度
    int caMsg[]; //实际消息
} PDU;

PDU *mkPDU(uint uiMsgLen); //协议数据单元动态空间申请

#endif // PROTOCOL_H
