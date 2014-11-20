#ifndef FTPMAINWINDOW_H
#define FTPMAINWINDOW_H

/*MyFtp-client所需头文件*/
#include <qmainwindow.h>
#include <qurloperator.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>

/*引入MyFtp-client所需的类*/
class FtpView;
class QSplitter;
class QVBox;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QNetworkOperation;
class QLabel;
class QProgressBar;

class FtpMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    FtpMainWindow();
  
    QSplitter *mainSplitter() const {
        return splitter;
    }

private:
    /*MyFtp-client私有函数定义*/
    void setupLeftSide();
    void setupRightSide();
    void setupCenterCommandBar();
    void setup();

private slots:
     /*MyFtp-client槽定义*/
    void slotLocalDirChanged( const QString &path );
    void slotLocalDirChanged( const QUrlInfo &info );
    void slotRemoteDirChanged( const QString &path );
    void slotRemoteDirChanged( const QUrlInfo &info );
    void slotConnect();
    void slotUpload();
    void slotDownload();
    void slotLocalStart( QNetworkOperation * );
    void slotLocalFinished( QNetworkOperation * );
    void slotRemoteStart( QNetworkOperation * );
    void slotRemoteFinished( QNetworkOperation * );
    void slotLocalDataTransferProgress( int, int, QNetworkOperation * );
    void slotRemoteDataTransferProgress( int, int, QNetworkOperation * );
    void slotLocalMkDir();
    void slotLocalRemove();
    void slotLocalAddressBook();
    void slotLocalPortScan();
    void slotRemoteMkDir();
    void slotRemoteRemove();
    void slotConnectionStateChanged( int, const QString &msg );
     
private:
     /*MyFtp-client所用到的类成员定义*/
    QSplitter *splitter;
    QVBox *mainWidget;
    FtpView *leftView, *rightView;
    QComboBox *localCombo, *remoteHostCombo, *remotePathCombo, *userCombo;
    QLineEdit *passLined;
    QSpinBox *portSpin;
    QUrlOperator localOperator, remoteOperator, oldLocal, oldRemote;
    QLabel *progressLabel1, *progressLabel2;
    QProgressBar *progressBar1, *progressBar2;

};
#endif
