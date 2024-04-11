#include "book.h"
#include "TcpClient.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <stdio.h>
#include "sharefile.h"

Book::Book(QWidget *parent)
    : QWidget{parent}
{
    this->m_strEnterDir.clear();

    m_pTimer = new QTimer;

    this->isDownloadFile = false;//初始时不是下载文件状态

    m_pBookListW = new QListWidget; //文件名字的列表
    m_pReturnPB = new QPushButton("返回");
    m_pCreateDirPB = new QPushButton("创建文件夹");
    m_pDeleteDirPB = new QPushButton("删除文件夹");
    m_pRenameFilePB = new QPushButton("重命名文件夹");
    m_pFlushDirPB = new QPushButton("刷新文件夹");

    //将文件夹操作垂直布局
    QVBoxLayout *pDirVBL = new QVBoxLayout;
    pDirVBL->addWidget(m_pReturnPB);
    pDirVBL->addWidget(m_pCreateDirPB);
    pDirVBL->addWidget(m_pDeleteDirPB);
    pDirVBL->addWidget(m_pRenameFilePB);
    pDirVBL->addWidget(m_pFlushDirPB);

    m_pUploadFilePB = new QPushButton("上传文件");
    m_pDownloadFilePB = new QPushButton("下载文件");
    m_pDeleteFilePB = new QPushButton("删除文件");
    m_pShareFilePB = new QPushButton("分享文件");
    m_pMoveFilePB = new QPushButton("移动文件");
    m_pSelectDestDirPB = new QPushButton("选择目标目录");
    m_pSelectDestDirPB->setEnabled(false);//默认不可选

    //将文件操作是垂直布局
    QVBoxLayout *pFileVBL = new QVBoxLayout;
    pFileVBL->addWidget(m_pUploadFilePB);
    pFileVBL->addWidget(m_pDownloadFilePB);
    pFileVBL->addWidget(m_pDeleteFilePB);
    pFileVBL->addWidget(m_pShareFilePB);
    pFileVBL->addWidget(m_pMoveFilePB);
    pFileVBL->addWidget(m_pSelectDestDirPB);

    //水平布局
    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addWidget(m_pBookListW);
    pMain->addLayout(pDirVBL);
    pMain->addLayout(pFileVBL);

    setLayout(pMain); //设置窗口总布局

    //连接 创建文件夹 槽函数
    connect(m_pCreateDirPB,SIGNAL(clicked(bool)),this,SLOT(createDir()));
    //连接 刷新文件夹 槽函数
    connect(m_pFlushDirPB,SIGNAL(clicked(bool)),this,SLOT(flushDir()));
    //连接 删除文件夹 槽函数
    connect(m_pDeleteDirPB,SIGNAL(clicked(bool)),this,SLOT(deleteDir()));
    //连接 重命名文件 槽函数
    connect(m_pRenameFilePB,SIGNAL(clicked(bool)),this,SLOT(renameFile()));
    //连接 进入文件夹 槽函数
    connect(m_pBookListW,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(enterDir(QModelIndex)));
    //连接 返回上一级 槽函数
    connect(m_pReturnPB,SIGNAL(clicked(bool)),this,SLOT(returnPre()));
    //连接 上传文件 槽函数
    connect(m_pUploadFilePB,SIGNAL(clicked(bool)),this,SLOT(uploadFile()));
    //连接 定时器与上传文件数据 槽函数
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(uploadFileData()));
    //连接 删除文件 槽函数
    connect(m_pDeleteFilePB,SIGNAL(clicked(bool)),this,SLOT(deleteFile()));
    //连接 下载文件 槽函数
    connect(m_pDownloadFilePB,SIGNAL(clicked(bool)),this,SLOT(downloadFile()));
    //连接 分享文件 槽函数
    connect(m_pShareFilePB,SIGNAL(clicked(bool)),this,SLOT(shareFile()));
    //连接 移动文件 槽函数
    connect(m_pMoveFilePB,SIGNAL(clicked(bool)),this,SLOT(moveFile()));
    //连接 选择目标目录 槽函数
    connect(m_pSelectDestDirPB,SIGNAL(clicked(bool)),this,SLOT(selectDestDir()));
}

void Book::flushFileList(const PDU *pdu)
{
    if(pdu==NULL) return;
    //每次刷新之前清空窗口内容
    m_pBookListW->clear();

    int fileCount = pdu->uiMsgLen/sizeof(FileInfo);
    FileInfo *pFileInfo = NULL;
    for(int i = 0; i < fileCount; i++){
        //按地址提取数据
        pFileInfo = (FileInfo*)pdu->caMsg+i;
        QString strFileName = pFileInfo->fileName;
        //qDebug() << strFileName;
        if(strFileName == "." || strFileName == "..") continue;
        QListWidgetItem *pItem = new QListWidgetItem;
        if(pFileInfo->fileType == 0){
            //文件夹
            pItem->setIcon(QIcon(QPixmap(":/map/folder.png")));
        }
        if(pFileInfo->fileType == 1){
            //常规文件
            pItem->setIcon(QIcon(QPixmap(":/map/document.png")));
        }
        pItem->setText(pFileInfo->fileName);
        m_pBookListW->addItem(pItem);
    }
}

QString Book::getEnterDir()
{
    return this->m_strEnterDir;
}

void Book::clearEnterDir()
{
    m_strEnterDir.clear();
}

QString Book::getSaveFilePath()
{
    return this->m_strSaveFilePath;
}

void Book::setDownloadStatus(bool status)
{
    this->isDownloadFile = status;
}

bool Book::getDownloadStatus()
{
    return this->isDownloadFile;
}

QString Book::getShareFileName()
{
    return this->m_strShareFileName;
}

void Book::createDir()
{
    //弹出一个输入框来提示新建文件夹的名字
    QString newDirName = QInputDialog::getText(this,"新建文件夹","新建文件夹的名称");
    //获取用户名
    QString loginName = TcpClient::getInstance().getLoginName();
    if(newDirName.isEmpty()){
        //文件夹名字为空，弹出提示框
        QMessageBox::warning(this,"新建文件夹","文件夹名字不能为空");
        return;
    }
    //获取当前路径
    QString curPath = TcpClient::getInstance().curPath();
    //生成pdu
    PDU* pdu = mkPDU(curPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_REQUEST;
    //caData的前32位放loginName，后32位放newDirName
    if(newDirName.size()>32){
        QMessageBox::warning(this,"新建文件夹","文件夹名字太长，请重新输入!");
    }else{
        memcpy(pdu->caData,loginName.toStdString().c_str(),loginName.size());
        memcpy(pdu->caData+32,newDirName.toStdString().c_str(),newDirName.size());
        memcpy((char*)pdu->caMsg,curPath.toStdString().c_str(),curPath.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu=NULL;
    }
}

void Book::flushDir()
{
    QString strCurPath = TcpClient::getInstance().curPath();
    PDU *pdu = mkPDU(strCurPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_DIR_REQUEST;
    strncpy((char*)pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::deleteDir()
{
    //从m_pBookListW中获取要删除的文件夹名称
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;
    QString delDirName = pItem->text();//要删除的文件夹名称
    QString curPath = TcpClient::getInstance().curPath();//当前路径
    PDU* pdu = mkPDU(curPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_DIR_REQUEST;
    memcpy(pdu->caData,delDirName.toStdString().c_str(),delDirName.size());
    memcpy((char*)pdu->caMsg,curPath.toStdString().c_str(),curPath.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::renameFile()
{
    //从m_pBookListW中获取要重命名的文件名称
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;

    QString oldDirName = pItem->text();//要重命名的文件夹名称
    QString curPath = TcpClient::getInstance().curPath();//当前路径
    QString newDirName = QInputDialog::getText(this,"重命名文件","请输入新的文件名");
    if(newDirName.size() > 32){
        QMessageBox::critical(this,"重命名文件","文件名字太长");
    }
    PDU* pdu = mkPDU(curPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_RENAME_FILE_REQUEST;
    memcpy(pdu->caData,oldDirName.toStdString().c_str(),oldDirName.size());
    memcpy(pdu->caData+32,newDirName.toStdString().c_str(),newDirName.size());
    memcpy((char*)pdu->caMsg,curPath.toStdString().c_str(),curPath.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::enterDir(const QModelIndex &index)
{
    //获取文件名以及当前路径
    QString selectName = index.data().toString();
    m_strEnterDir = selectName;
    QString curPath = TcpClient::getInstance().curPath();
    PDU* pdu = mkPDU(curPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_ENTER_DIR_REQUEST;
    strncpy(pdu->caData,selectName.toStdString().c_str(),selectName.size());
    strncpy((char*)pdu->caMsg,curPath.toStdString().c_str(),curPath.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

void Book::returnPre()
{
    //获取当前路径
    QString strCurPath = TcpClient::getInstance().curPath();
    //获取跟路径
    QString strRootPath = QString("./%1").arg(TcpClient::getInstance().getLoginName());
    //判断当前路径是否是根路径
    if(strCurPath == strRootPath){  //当前目录是根目录
        QMessageBox::warning(this,"返回上一级目录","当前目录为根目录，无返返回上一级目录！");
        return;
    }
    //当前目录不是根目录 生成上一级目录路径
    int index = strCurPath.lastIndexOf('/');//找到最后一个/出现的位置
    strCurPath.remove(index,strCurPath.size() - index);
    //更新当前路径
    TcpClient::getInstance().updateCurPath(strCurPath);

    //清空当前进入的文件夹路径
    clearEnterDir();

    //向服务器发送更新文件夹请求
    flushDir();
}

void Book::uploadFile()
{
    //获取当前目录的路径
    QString strCurPath = TcpClient::getInstance().curPath();
    //弹出打开文件的窗口，并获取所要上传文件的路径，获取的是绝对路径
    this->m_strUploadFilePath = QFileDialog::getOpenFileName();
    if(this->m_strUploadFilePath.isEmpty()) return;
    //获取最后一个/符号的索引
    int index = this->m_strUploadFilePath.lastIndexOf('/');
    //获取文件的名称
    QString strFileName = this->m_strUploadFilePath.right(this->m_strUploadFilePath.size() - index - 1);
    qDebug() << "strFileName: " << strFileName;
    QFile file(this->m_strUploadFilePath);//打开m_strUploadFilePath路径的文件
    qint64 fileSize = file.size();//获取文件大小

    //生成上传文件请求的pdu
    PDU *pdu = mkPDU(strCurPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST;
    memcpy((char*)pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());
    sprintf(pdu->caData,"%s %lld",strFileName.toStdString().c_str(),fileSize);//字符串拼接函数将文件名以及文件大小拷贝到pdu->caData
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
    this->m_pTimer->start(1000);//给1000ms时间向服务器发送上传文件请求
}

void Book::uploadFileData()
{
    qDebug() << "uploadFileData()";
    this->m_pTimer->stop();//停止计时
    QFile file(this->m_strUploadFilePath);
    //尝试打开指定路径的问价按
    if(!file.open(QIODevice::ReadOnly)){//打开文件失败
        QMessageBox::warning(this,"打开文件","打开文件失败");
        return;
    }
    char *pBuffer = new char[4096]; //4096字节读取，速率较快
    qint64 ret = 0;//标志位，判断是否读取完
    while(true){
        ret = file.read(pBuffer,4096);//ret记录每次读取的字节数
        if(ret > 0 && ret <= 4096){
            //向服务器端发送读取的数据
            TcpClient::getInstance().getTcpSocket().write(pBuffer,ret);
        }else if(ret == 0){//读取完毕
            break;
        }else{//读取失败
            QMessageBox::critical(this,"上传文件","上传失败");
        }
    }
    file.close();
    delete []pBuffer;
    pBuffer = NULL;
}

void Book::deleteFile()
{
    //从m_pBookListW中获取要删除的文件的名称
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;
    QString delFileName = pItem->text();
    QString curPath = TcpClient::getInstance().curPath();
    PDU* pdu = mkPDU(curPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FILE_REQUEST;
    memcpy(pdu->caData,delFileName.toStdString().c_str(),delFileName.size());
    memcpy((char*)pdu->caMsg,curPath.toStdString().c_str(),curPath.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::downloadFile()
{
    //从m_pBookListW中获取要下载的文件的名称
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;
    //获取要保存的路径
    QString strSaveFilePath = QFileDialog::getSaveFileName();
    if(strSaveFilePath.isEmpty()){
        QMessageBox::warning(this,"下载文件","请选择要保存的路径");
        m_strSaveFilePath.clear();
        return;
    }
    m_strSaveFilePath = strSaveFilePath;
    //向客户端发送要下载的文件名称以及当前路径
    QString strCurPath = TcpClient::getInstance().curPath();
    QString strFileName = pItem->text();
    PDU *pdu=mkPDU(strCurPath.size()+1);
    pdu->uiMsgType=ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST;
    strcpy(pdu->caData,strFileName.toStdString().c_str());
    memcpy(pdu->caMsg,strCurPath.toStdString().c_str(),strCurPath.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

void Book::shareFile()
{
    //从m_pBookListW中获取要分享的文件的名称
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;
    QListWidget *friendListW = OpeWidget::getInstance().getFriend()->getFriendListWidget();//好友列表信息
    //获取要分享的文件名
    this->m_strShareFileName = pItem->text();
    ShareFile::getInstance().updateFriend(friendListW);
    if(ShareFile::getInstance().isHidden()){
        ShareFile::getInstance().show();
    }
}

void Book::moveFile()
{
    //选择要移动的文件
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;
    m_strMoveFileName = pItem->text();
    QString curPath = TcpClient::getInstance().curPath();
    m_strMoveFilePath = curPath+"/"+m_strMoveFileName;
    m_pSelectDestDirPB->setEnabled(true);
}

void Book::selectDestDir()
{
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL) return;
    QString strDestDir = pItem->text();
    QString strCurPath = TcpClient::getInstance().curPath();
    m_strDestPath = strCurPath+"/"+strDestDir;

    int srcLen = m_strMoveFilePath.size();
    int destLen = m_strDestPath.size();
    PDU *pdu = mkPDU(srcLen+destLen+2);
    pdu->uiMsgType = ENUM_MSG_TYPE_MOVE_FILE_REQUEST;
    //cadata中存放 源路径长度、目标路径长度、要移动的文件的名称
    sprintf(pdu->caData,"%d %d %s",srcLen,destLen,this->m_strMoveFileName.toStdString().c_str());
    //camsg中存放 源路径、目标路径
    memcpy(pdu->caMsg,m_strMoveFilePath.toStdString().c_str(),m_strMoveFilePath.size());
    memcpy((char*)pdu->caMsg+srcLen+1,m_strDestPath.toStdString().c_str(),m_strDestPath.size());

    TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;

    m_pSelectDestDirPB->setEnabled(false);
}
