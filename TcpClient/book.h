#ifndef BOOK_H
#define BOOK_H

#include <QWidget>
#include <QListWidget>//操作文件
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <protocol.h>
#include <QTimer>

class Book : public QWidget
{
    Q_OBJECT
public:
    explicit Book(QWidget *parent = nullptr);

    //更新列表
    void flushFileList(const PDU* pdu);
    //获取进入文件夹后的路径
    QString getEnterDir();
    void clearEnterDir();

    //获取下载文件时保存的路径
    QString getSaveFilePath();
    //设置下载文件状态
    void setDownloadStatus(bool status);
    //获取下载文件标志位
    bool getDownloadStatus();

    //通过共有函数获取要分享的文件名
    QString getShareFileName();

    //总文件大小
    qint64 m_iTotal;
    //已接收到多少
    qint64 m_iRecved;
signals:

    //槽连接
public slots:
    //创建文件夹槽函数
    void createDir();
    //刷新文件槽函数
    void flushDir();
    //删除文件夹槽函数
    void deleteDir();
    //重命名文件槽函数
    void renameFile();
    //进入文件夹槽函数
    void enterDir(const QModelIndex &index);
    //返回上一级槽函数
    void returnPre();
    //上传文件槽函数
    void uploadFile();
    //上传文件数据槽函数
    void uploadFileData();
    //删除文件槽函数
    void deleteFile();
    //下载文件槽函数
    void downloadFile();
    //分享文件槽函数
    void shareFile();
    //移动文件槽函数
    void moveFile();
    //选择目标目录槽函数
    void selectDestDir();
private:
    QListWidget *m_pBookListW; //文件名字的列表
    QPushButton *m_pReturnPB;
    QPushButton *m_pCreateDirPB;
    QPushButton *m_pDeleteDirPB;
    QPushButton *m_pRenameFilePB;
    QPushButton *m_pFlushDirPB;
    QPushButton *m_pUploadFilePB;
    QPushButton *m_pDownloadFilePB;
    QPushButton *m_pDeleteFilePB;
    QPushButton *m_pShareFilePB;
    QPushButton *m_pMoveFilePB;
    QPushButton *m_pSelectDestDirPB;

    //进入后的路径
    QString m_strEnterDir;
    //上传文件时所上传文件的路径
    QString m_strUploadFilePath;

    //定时器
    QTimer *m_pTimer;

    //下载文件时要保存的路径
    QString m_strSaveFilePath;
    //下载文件表示位
    bool isDownloadFile;

    //要分享的文件的名
    QString m_strShareFileName;

    //要移动的文件名
    QString m_strMoveFileName;
    QString m_strMoveFilePath;
    QString m_strDestPath;
};

#endif // BOOK_H
