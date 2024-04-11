#include "TcpClient.h"
#include "ui_TcpClient.h"
#include "privatechat.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    resize(500,400);

    this->loadConfig();

    //连接槽和服务器的信号  信号发送放、信号内容、接收方、处理函数
    connect(&m_tcpSocket, SIGNAL(connected()), this,SLOT(showConnect()));//信号的发送者、发送的是什么信号、信号的处理者，怎么处理
    connect(&m_tcpSocket, SIGNAL(readyRead()), this,SLOT(recvMsg())); //只要客户端收到消息，就会产生readyRead()信号

    this->m_tcpSocket.connectToHost(QHostAddress(m_strIp), m_usPort);
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()
{
    QFile file(":/client.config");
    if (file.open(QIODevice::ReadOnly)) {
        //只读方式打开
        QByteArray baData = file.readAll();//以字节方式读取
        QString strData = baData.toStdString().c_str();
        qDebug() << strData;
        file.close();
        strData.replace("\r\n", " "); //\r\n回车换行
        qDebug() << strData;

        QStringList strlist = strData.split(" ");
        for (int i = 0; i < strlist.size(); i++) {
            qDebug() << "--->" << strlist[i];
        }

        this->m_strIp = strlist[0];
        this->m_usPort = strlist[1].toUShort();
        qDebug() << "ip:" << this->m_strIp;
        qDebug() << "port:" << this->m_usPort;
    }
    else {
        QMessageBox::critical(this, "open config", "open config falsed");
    }
}

TcpClient &TcpClient::getInstance()
{
    static TcpClient instance;
    return instance;
}

QTcpSocket &TcpClient::getTcpSocket()
{
    return m_tcpSocket;
}

void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","连接服务器成功");
}

void TcpClient::recvMsg()
{
    //qDebug() << m_tcpSocket.bytesAvailable(); // 服务器端发送过来的数据大小
    if(!OpeWidget::getInstance().getBook()->getDownloadStatus()){
    uint uiPDULen = 0;
    m_tcpSocket.read((char*)&uiPDULen,sizeof(uint));//先接受四个字节的大小的数据
    uint uiMsgLen = uiPDULen - sizeof(uiPDULen);
    PDU *pdu = mkPDU(uiMsgLen);
    m_tcpSocket.read((char*)pdu + sizeof(int), uiPDULen - sizeof(uint));

    switch(pdu->uiMsgType){
        //客户端接收到服务器端发送的注册回复信号
    case ENUM_MSG_TYPE_REGIST_RESPOND:
    {
        if(0 == strcmp(pdu->caData, REGIST_OK)){
            //strcmp比较字符串
            QMessageBox::information(this,"注册",REGIST_OK);
        }
        else{
            QMessageBox::warning(this,"注册",REGIST_FAILED);
        }
        break;
    }
        //客户端接收到服务器端发送的登录回复信号
    case ENUM_MSG_TYPE_LOGIN_RESPOND:
    {
        if(0 == strcmp(pdu->caData, LOGIN_OK)){
            //登录成功之后，更新当前路径
            m_strCurPath = QString("./%1").arg(m_strLoginName);
            QMessageBox::information(this,"登录",LOGIN_OK);
            //登录成功后，由操作界面的对象，切换到操作界面
            OpeWidget::getInstance().show();
            //隐藏登录界面
            this->hide();
        }
        else{
            QMessageBox::warning(this,"登录",LOGIN_FAILED);
        }
        break;
    }
        //客户端接收到服务器端发送的查看所有用户回复信号
    case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND:
    {
        OpeWidget::getInstance().getFriend()->showALLOnlineUsr(pdu);
        break;
        //这里目前存在bug，也就是会重复显示，lineEdit中保留了上一次的结果
    }
        //客户端接收到服务器端发送的查找用户回复信号
    case ENUM_MSG_TYPE_SEARCH_RESPOND:
    {
        //用户不存在
        if(strcmp(SEARCH_USR_NO,pdu->caData) == 0){
            QMessageBox::information(this,"搜索",QString("\'%1\' no exist!").arg(OpeWidget::getInstance().getFriend()->m_strSearchName));
        }
        //用户在线
        else if(strcmp(SEARCH_USR_ONLINE,pdu->caData) == 0){
            QMessageBox::information(this,"搜索",QString("\'%1\' online!").arg(OpeWidget::getInstance().getFriend()->m_strSearchName));
        }
        //用户不在线
        else if(strcmp(SEARCH_USR_OFFLINE,pdu->caData) == 0){
            QMessageBox::information(this,"搜索",QString("\'%1\' offline!").arg(OpeWidget::getInstance().getFriend()->m_strSearchName));
        }
        break;
    }
        //客户端接收到服务器端发送的添加好友响应
    case ENUM_MSG_TYPE_ADD_FRIEND_RESPOND:
    {
        //未知错误
        if(strcmp(UNKNOW_ERROR,pdu->caData) == 0){
            QMessageBox::critical(this,"添加好友",UNKNOW_ERROR);
        }
        //已经是好友了
        else if(strcmp(EXISTED_FRIEND,pdu->caData) == 0){
            QMessageBox::information(this,"添加好友",EXISTED_FRIEND);
        }
        //不是好友但是对方已经离线
        else if(strcmp(ADD_FRIEND_OFFLINE,pdu->caData) == 0){
            QMessageBox::information(this,"添加好友",ADD_FRIEND_OFFLINE);
        }
        //用户不存在
        else if(strcmp(ADD_FRIEND_NOEXIST,pdu->caData) == 0){
            qDebug() << "ADD_FRIEND_NOEXIST";
            QMessageBox::information(this,"添加好友",ADD_FRIEND_NOEXIST);
        }
        break;
    }
        //客户端收到添加好友请求 A请求添加B为好友
    case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:
    {
        char requestName[32] = {'\0'}; //A的姓名
        char friName[32] = {'\0'}; //B的姓名
        strncpy(requestName,pdu->caData,32);
        strncpy(friName,pdu->caData+32,32);
        qDebug() << "strncpy(requestName,pdu->caData,32)";
        int ret = QMessageBox::information(this,"添加好友",QString("%1 want to add you as friend, do you agree?").arg(requestName),
                                            QMessageBox::Yes, QMessageBox::No);
        PDU *respdu = mkPDU(0);
        if(ret == QMessageBox::Yes){
            //同意添加
            respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE;
        }
        else{
            //拒绝添加
            respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REFUSE;
        }
        //数据处理后发送给服务器
        memcpy(respdu->caData,requestName,32);
        memcpy(respdu->caData+32,friName,32);
        m_tcpSocket.write((char*)respdu,respdu->uiPDULen);
        free(respdu);
        respdu = NULL;
        break;
    }
        //收到同意添加为好友回复
    case ENUM_MSG_TYPE_ADD_FRIEND_AGREE:
    {
        char friName[32] = {'\0'}; //B的姓名
        strncpy(friName,pdu->caData,32);
        QMessageBox::information(this,"添加好友",QString("%1 agree to add you as friend!").arg(friName));
        break;
    }
        //收到拒绝添加为好友的回复
    case ENUM_MSG_TYPE_ADD_FRIEND_REFUSE:
    {
        char friName[32] = {'\0'}; //B的姓名
        strncpy(friName,pdu->caData,32);
        QMessageBox::information(this,"添加好友",QString("%1 refuse to add you as friend!").arg(friName));
        break;
    }
        //收到服务器的刷新好友列表回复
    case ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND:
    {
        OpeWidget::getInstance().getFriend()->showFriendName(pdu);
        break;
    }
        //收到服务器端的删除好友成功回复
    case ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND_TRUE:
    {
        char usrName[32] = {'\0'};
        char friName[32] = {'\0'};
        //从pdu中获取用户姓名以及要删除好友的姓名
        strncpy(usrName,pdu->caData,32);
        strncpy(friName,pdu->caData+32,32);
        QMessageBox::information(this,"删除好友",QString("\'%1\' is successfully deleted").arg(friName));
        break;
    }
        //收到服务器的删除好友失败回复
    case ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND_FAILED:
    {
        char usrName[32] = {'\0'};
        char friName[32] = {'\0'};
        //从pdu中获取用户姓名以及要删除好友的姓名
        strncpy(usrName,pdu->caData,32);
        strncpy(friName,pdu->caData+32,32);
        QMessageBox::warning(this,"删除好友",QString("fail to delete, \'%1\' may not be your friend").arg(friName));
        break;
    }
        //客户端收到转发的私聊请求
    case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST:
    {
        if(PrivateChat::getInstance().isHidden()){
            PrivateChat::getInstance().show();
        }
        char sendName[32] = {'\0'};//信息的发送者
        char receiveName[32] = {'\0'};//信息的接收者
        strncpy(sendName,pdu->caData,32);
        strncpy(receiveName,pdu->caData+32,32);
        QString msg = (char*)pdu->caMsg;
        //在弹出的窗口中显示信息
        PrivateChat::getInstance().setChatName(sendName);
        PrivateChat::getInstance().updateMsg(pdu);
        break;
    }
        //客户端接收到群聊响应
    case ENUM_MSG_TYPE_GROUP_CHAT_RESPOND:
    {
        OpeWidget::getInstance().getFriend()->showGroupMsg(pdu);
        break;
    }
        //客户端接受到创建文件响应
    case ENUM_MSG_TYPE_CREATE_DIR_RESPOND:
    {
        if(strcmp(pdu->caData,FILE_NAME_EXIST) == 0){
            QMessageBox::critical(this,"新建文件夹","文件夹名字重复");
        }
        if(strcmp(pdu->caData,DIR_NO_EXIST) == 0){
            QMessageBox::critical(this,"新建文件夹","路径不存在");
        }
        if(strcmp(pdu->caData,CREATE_DIR_OK) == 0){
            QMessageBox::information(this,"新建文件夹","创建成功");
        }
        break;
    }
        //客户端接收到刷新文件回复
    case ENUM_MSG_TYPE_FLUSH_DIR_RESPOND:
    {
        OpeWidget::getInstance().getBook()->flushFileList(pdu);
        QString strEnterDir = OpeWidget::getInstance().getBook()->getEnterDir();
        if(!strEnterDir.isEmpty()){
            //更新当前路径
            m_strCurPath = m_strCurPath + "/" + strEnterDir;
            qDebug() << "enter dir:" << m_strCurPath;
        }
        break;
    }
        //客户端接收到删除文件夹回复
    case ENUM_MSG_TYPE_DELETE_DIR_RESPOND:
    {
        qDebug() << "ENUM_MSG_TYPE_DELETE_DIR_RESPOND";
        if(strcmp(pdu->caData, DELETE_DIR_SUCCESSED) == 0){
            //删除成功
            QMessageBox::information(this,"删除文件夹","删除成功");
        }
        if(strcmp(pdu->caData, DELETE_DIR_FAILED) == 0){
            QMessageBox::critical(this,"删除文件夹","删除失败");
        }
        break;
    }
        //客户端接收到重命名回复
    case ENUM_MSG_TYPE_RENAME_FILE_RESPOND:
    {
        if(strcmp(pdu->caData,RENAME_FILE_FAILED) == 0){
            //重命名失败
            QMessageBox::critical(this,"重命名文件",RENAME_FILE_FAILED);
        }
        if(strcmp(pdu->caData,RENAME_FILE_SUCCESSED) == 0){
            //重命名成功
            QMessageBox::information(this,"重命名文件",RENAME_FILE_SUCCESSED);
        }
        break;
    }
        //客户端接收到进入文件夹失败的回复
    case ENUM_MSG_TYPE_ENTER_DIR_RESPOND:
    {
        //进入文件失败，清空进入文件夹的名称
        OpeWidget::getInstance().getBook()->clearEnterDir();
        QMessageBox::critical(this,"进入文件夹",ENTER_DIR_FAILED);
        break;
    }
        //客户端接收到上传文件回复
    case ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND:
    {
        qDebug() << "ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND:";
        if(strcmp(pdu->caData,UPLOAD_FILE_FAILED) == 0){
            //上传失败
            qDebug() << UPLOAD_FILE_FAILED;
            QMessageBox::critical(this,"上传文件",UPLOAD_FILE_FAILED);
        }
        if(strcmp(pdu->caData,UPLOAD_FILE_SUCCESSED) == 0){
            //上传成功 上传成功之后应该立即刷新当前目录
            qDebug() << UPLOAD_FILE_SUCCESSED;
            QMessageBox::information(this,"上传文件",UPLOAD_FILE_SUCCESSED);
            OpeWidget::getInstance().getBook()->flushDir();
        }
        break;
    }
        //客户端接收到删除文件回复
    case ENUM_MSG_TYPE_DELETE_FILE_RESPOND:
    {
        if(strcmp(pdu->caData, DELETE_FILE_SUCCESSED) == 0){
            //删除成功
            QMessageBox::information(this,"删除文件","删除成功");
            OpeWidget::getInstance().getBook()->flushDir();//删除成功之后立即刷新文件夹
        }
        if(strcmp(pdu->caData, DELETE_FILE_FAILED) == 0){
            QMessageBox::critical(this,"删除文件","删除失败");
        }
        break;
    }
        //客户端接收到下载文件回复
    case ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND:
    {
        //从pdu中解析出下载文件的名称，大小
        char curFileName[32] = {'\0'};
        //sscanf拆解字符串，对应sprintf，因为是输入？所以要取地址？
        sscanf(pdu->caData,"%s %lld",curFileName,&(OpeWidget::getInstance().getBook()->m_iTotal));
        qDebug() << "curFileName:"<<curFileName;
        qDebug() << "m_iTotal:"<<OpeWidget::getInstance().getBook()->m_iTotal;
        if(strlen(curFileName) > 0 && OpeWidget::getInstance().getBook()->m_iTotal > 0){//文件有效
            OpeWidget::getInstance().getBook()->m_iRecved = 0;
            OpeWidget::getInstance().getBook()->setDownloadStatus(true);
            m_file.setFileName(OpeWidget::getInstance().getBook()->getSaveFilePath());
            qDebug() << "OpeWidget::getInstance().getBook()->getSaveFilePath():"<<OpeWidget::getInstance().getBook()->getSaveFilePath();
            if(!m_file.open(QIODevice::WriteOnly)){
                QMessageBox::warning(this,"下载文件","获得下载的文件失败");
            }
        }
        break;
    }
        //客户端接收到分享文件回应
    case ENUM_MSG_TYPE_SHARE_FILE_RESPOND:
    {
        char strMsg[32] = {'\0'};
        strcpy(strMsg,pdu->caData);
        QMessageBox::information(this,"分享文件",strMsg);
        break;
    }
        //客户端接收到分享文件通知
    case ENUM_MSG_TYPE_SHARE_FILE_NOTE:
    {
        //从pdu中获取文件路径以及发送方
        char *strPath = new char[pdu->uiMsgLen];
        memcpy(strPath,pdu->caMsg,pdu->uiMsgLen);

        //从后往前找指定字符
        char *pos = strrchr(strPath, '/');
        if(pos != NULL){
            pos++;
            QString strNote = QString("%1 shares file %2 with you? Do you accept?").arg(pdu->caData).arg(pos);
            int ret = QMessageBox::question(this,"分享文件",strNote);
            if(ret == QMessageBox::Yes){//同意接收
                qDebug() << "ENUM_MSG_TYPE_SHARE_FILE_NOTE YES";
                //向服务器端发送接收回应 将路径放入caMsg
                PDU *respdu = mkPDU(pdu->uiMsgLen);
                respdu->uiMsgType = ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND;
                memcpy(respdu->caMsg,pdu->caMsg,pdu->uiMsgLen);

                //放入客户端的姓名
                QString strName = TcpClient::getInstance().getLoginName();
                qDebug() << (char*)respdu->caMsg;
                qDebug() << strName;

                strcpy(respdu->caData,strName.toStdString().c_str());
                m_tcpSocket.write((char*)respdu,respdu->uiPDULen);
                free(respdu);
                respdu = NULL;
                qDebug() << "我运行到了这里";
            }
        }
        delete []strPath;
        strPath=NULL;
        //delete []pos;
        //pos = NULL;
        break;
    }
        //客户端接收到移动文件回应
    case ENUM_MSG_TYPE_MOVE_FILE_RESPOND:
    {
        qDebug() << "ENUM_MSG_TYPE_MOVE_FILE_RESPOND";
        if(strcmp(pdu->caData,MOVE_FILE_OK) == 0){
            //重命名成功
            QMessageBox::information(this,"移动文件",MOVE_FILE_OK);
        }
        if(strcmp(pdu->caData,MOVE_FILE_FAILURED) == 0){
            QMessageBox::critical(this,"移动文件",MOVE_FILE_FAILURED);
        }
        if(strcmp(pdu->caData,COMMON_ERR) == 0){
            QMessageBox::critical(this,"移动文件",COMMON_ERR);
        }
    }
    default:
        break;
    }
    free(pdu); //发送完消息后释放空间
    pdu = NULL;
    }else{//下载文件
    QByteArray buffer = this->m_tcpSocket.readAll();//返回字节数组
    this->m_file.write(buffer);
    Book *pBook=OpeWidget::getInstance().getBook();
    pBook->m_iRecved+=buffer.size();
    if(pBook->m_iTotal==pBook->m_iRecved){  //下载完成
        m_file.close();
        pBook->m_iTotal=0;
        pBook->m_iRecved=0;
        pBook->setDownloadStatus(false);
        QMessageBox::information(this,"下载文件","下载文件成功");
    }
    else{  //收到的数据更大
        m_file.close();
        pBook->m_iTotal=0;
        pBook->m_iRecved=0;
        pBook->setDownloadStatus(false);
        QMessageBox::critical(this,"下载文件","下载文件失败");
    }
    }
}

QString TcpClient::getLoginName()
{
    return this->m_strLoginName;
}

QString TcpClient::curPath()
{
    return m_strCurPath;
}

void TcpClient::updateCurPath(QString str_curPath)
{
    m_strCurPath = str_curPath;
}

#if 0
void TcpClient::on_send_pb_clicked()
{
    QString strMsg = ui->lineEdit->text();
    if(!strMsg.isEmpty())
    {
        PDU *pdu = mkPDU(strMsg.size());
        pdu->uiMsgType = 8888;
        memcpy(pdu->caMsg,strMsg.toStdString().c_str(),strMsg.size());//将消息拷贝给pdu->caData
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen); //发送消息
        free(pdu); //发送完消息后释放空间
        pdu = NULL;
    }
    else{
        QMessageBox::warning(this,"信息发送","发送的信息不能为空");
    }
}
#endif

//登录槽函数
void TcpClient::on_login_pb_clicked()
{
    QString strName = ui->usName_le->text();
    QString strPwd = ui->usPwd_le->text();

    if(!strName.isEmpty() && !strPwd.isEmpty()){
        this->m_strLoginName = strName;
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_REQUEST;//将消息类型设置为登录请求
        //pdu->caData的前32位放用户名，后32位放密码
        strncpy(pdu->caData,strName.toStdString().c_str(),32);
        strncpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen); //将消息发送给服务器端
        free(pdu); //发送完消息后释放空间
        pdu = NULL;
    }
    else{
        QMessageBox::critical(this,"登录","登录失败：用户名或密码为空！");
    }
}

//注册槽函数
void TcpClient::on_registe_pb_clicked()
{
    QString strName = ui->usName_le->text();
    QString strPwd = ui->usPwd_le->text();

    if(!strName.isEmpty() && !strPwd.isEmpty()){
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;//将消息类型设置为注册请求
        //pdu->caData的前32位放用户名，后32位放密码
        strncpy(pdu->caData,strName.toStdString().c_str(),32);
        strncpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen); //将消息发送给服务器端
        free(pdu); //发送完消息后释放空间
        pdu = NULL;
    }
    else{
        QMessageBox::critical(this,"注册","注册失败：用户名或密码为空！");
    }
}

//注销槽函数
void TcpClient::on_cancel_pb_clicked()
{

}

