#include "ftpmainwindow.h"
#include "ftpview.h"
#include <unistd.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qsplitter.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qprogressbar.h>
#include <qdir.h>
#include <qinputdialog.h>
#include <qapplication.h>
#include <qstatusbar.h>

FtpMainWindow::FtpMainWindow()
    : QMainWindow(),
      localOperator( "/" )
{
    setup();

     //连接本地的QUrlOperator信号----这个将使用到
     //在本地文件系统的相应操作(如查看目录等)和复制文件到本地文件系统(即下载)
    
    connect( &localOperator, SIGNAL( newChildren( const QValueList<QUrlInfo> &, QNetworkOperation * ) ),
             leftView, SLOT( slotInsertEntries( const QValueList<QUrlInfo> & ) ) );
    connect( &localOperator, SIGNAL( start( QNetworkOperation * ) ),
             this, SLOT( slotLocalStart( QNetworkOperation *) ) );
    connect( &localOperator, SIGNAL( finished( QNetworkOperation * ) ),
             this, SLOT( slotLocalFinished( QNetworkOperation *) ) );
    connect( leftView, SIGNAL( itemSelected( const QUrlInfo & ) ),
             this, SLOT( slotLocalDirChanged( const QUrlInfo & ) ) );
    connect( &localOperator, SIGNAL( dataTransferProgress( int, int, QNetworkOperation * ) ),
             this, SLOT( slotLocalDataTransferProgress( int, int, QNetworkOperation * ) ) );


     //连接远程端的QUrlOperator信号----这个将使用到
    //在远程端文件系统的相应操作(即在FTP服务器上)和复制文件到FTP服务器(即上传)

    connect( &remoteOperator, SIGNAL( newChildren( const QValueList<QUrlInfo> &, QNetworkOperation * ) ),
             rightView, SLOT( slotInsertEntries( const QValueList<QUrlInfo> & ) ) );
    connect( &remoteOperator, SIGNAL( start( QNetworkOperation * ) ),
             this, SLOT( slotRemoteStart( QNetworkOperation *) ) );
    connect( &remoteOperator, SIGNAL( finished( QNetworkOperation * ) ),
             this, SLOT( slotRemoteFinished( QNetworkOperation *) ) );
    connect( rightView, SIGNAL( itemSelected( const QUrlInfo & ) ),
             this, SLOT( slotRemoteDirChanged( const QUrlInfo & ) ) );
    connect( &remoteOperator, SIGNAL( dataTransferProgress( int, int, QNetworkOperation * ) ),
             this, SLOT( slotRemoteDataTransferProgress( int, int, QNetworkOperation * ) ) );
    connect( &remoteOperator, SIGNAL( connectionStateChanged( int, const QString & ) ),
             this, SLOT( slotConnectionStateChanged( int, const QString & ) ) );

    
     //在程序一开始运行时就读入本地文件系统
    localOperator.listChildren();

     //新建状态栏
    (void)statusBar();
}

void FtpMainWindow::setupLeftSide()
{

     //设置FtpClient程序左侧图形界面,这个部分是通过运用listview控件来罗列本地文件系统信息
    QVBox *layout = new QVBox( splitter );
    layout->setSpacing( 5 );
    layout->setMargin( 5 );

    QHBox *h = new QHBox( layout );
    h->setSpacing( 5 );
    QLabel *l = new QLabel( trUtf8( "本地路径:" ), h );
    l->setFixedWidth( l->sizeHint().width() );
    localCombo = new QComboBox( TRUE, h );
    localCombo->insertItem( "/" );

    connect( localCombo, SIGNAL( activated( const QString & ) ),
             this, SLOT( slotLocalDirChanged( const QString & ) ) );

    leftView = new FtpView( layout );

    QHBox *bottom = new QHBox( layout );
    bottom->setSpacing( 5 );
    QPushButton *bMkDir = new QPushButton( trUtf8( "新建目录" ), bottom );
    QPushButton *bRemove = new QPushButton( trUtf8( "删除" ), bottom );
     //1.地址簿模块切入点
    QPushButton *bAddressBook = new QPushButton( trUtf8( "地址簿" ), bottom );    
     //2.系统漏洞扫描模块切入点
    QPushButton *bPortScan = new QPushButton( trUtf8( "本地端口扫描" ), bottom );

    connect( bMkDir, SIGNAL( clicked() ),
             this, SLOT( slotLocalMkDir() ) );
    connect( bRemove, SIGNAL( clicked() ),
             this, SLOT( slotLocalRemove() ) );
     //1.信号连接
    connect( bAddressBook, SIGNAL( clicked() ),
             this, SLOT( slotLocalAddressBook() ) );
     //2.信号连接
    connect( bPortScan, SIGNAL( clicked() ),
             this, SLOT( slotLocalPortScan() ) );

    splitter->setResizeMode( layout, QSplitter::Stretch );
}

void FtpMainWindow::setupRightSide()
{

     //设置FtpClient程序右侧图形界面,这个部分是通过运用listview控件来罗列
     //远程连接端文件系统信息(即FTP服务器端),同时还创建了Ftp登录项,如用户名和密码框等
    QVBox *layout = new QVBox( splitter );
    layout->setSpacing( 5 );
    layout->setMargin( 5 );

    QHBox *h = new QHBox( layout );
    h->setSpacing( 5 );
    QLabel *l = new QLabel( trUtf8( "远程主机:" ), h );
    l->setFixedWidth( l->sizeHint().width() );
    remoteHostCombo = new QComboBox( TRUE, h );

    l = new QLabel( trUtf8( "端口号:" ), h );
    l->setFixedWidth( l->sizeHint().width() );
    portSpin = new QSpinBox( 0, 32767, 1, h );
    portSpin->setValue( 21 );
    portSpin->setFixedWidth( portSpin->sizeHint().width() );
    remoteOperator.setPort( portSpin->value() );

    h = new QHBox( layout );
    h->setSpacing( 5 );
    l = new QLabel( trUtf8( "远程路径:" ), h );
    l->setFixedWidth( l->sizeHint().width() );
    remotePathCombo = new QComboBox( TRUE, h );

    h = new QHBox( layout );
    h->setSpacing( 5 );
    l = new QLabel( trUtf8( "用户名:" ), h );
    l->setFixedWidth( l->sizeHint().width() );
    userCombo = new QComboBox( TRUE, h );

    l = new QLabel( trUtf8( "口令:" ), h );
    l->setFixedWidth( l->sizeHint().width() );
    passLined = new QLineEdit( h );
    passLined->setEchoMode( QLineEdit::Password );

    rightView = new FtpView( layout );

    QHBox *bottom = new QHBox( layout );
    bottom->setSpacing( 5 );
    QPushButton *bMkDir = new QPushButton( trUtf8( "新建目录" ), bottom );
    QPushButton *bRemove = new QPushButton( trUtf8( "删除" ), bottom );
    connect( bMkDir, SIGNAL( clicked() ),
             this, SLOT( slotRemoteMkDir() ) );
    connect( bRemove, SIGNAL( clicked() ),
             this, SLOT( slotRemoteRemove() ) );

    splitter->setResizeMode( layout, QSplitter::Stretch );

    connect( remotePathCombo, SIGNAL( activated( const QString & ) ),
             this, SLOT( slotRemoteDirChanged( const QString & ) ) );
}

void FtpMainWindow::setupCenterCommandBar()
{
    
     //在左、右两个视图框中间设置一个命令栏,由Connect、Upload、Download三个按钮组成;
    QVBox *w = new QVBox( splitter );
    splitter->setResizeMode( w, QSplitter::FollowSizeHint );
    w->setSpacing( 5 );
    w->setMargin( 5 );

    QPushButton *bConnect = new QPushButton( trUtf8( "连接" ), w );
    (void)new QWidget( w );
    QPushButton *bUpload = new QPushButton( trUtf8( "==上传==>" ), w );
    QPushButton *bDownload = new QPushButton( trUtf8( "<==下载==" ), w );
    (void)new QWidget( w );

    connect( bConnect, SIGNAL( clicked() ),
             this, SLOT( slotConnect() ) );
    connect( bUpload, SIGNAL( clicked() ),
             this, SLOT( slotUpload() ) );
    connect( bDownload, SIGNAL( clicked() ),
             this, SLOT( slotDownload() ) );
}

void FtpMainWindow::setup()
{
    // 设置图形界面

    mainWidget = new QVBox( this );
    splitter = new QSplitter( mainWidget );
    setupLeftSide();
    setupCenterCommandBar();
    setupRightSide();

    progressLabel1 = new QLabel( trUtf8( "无操作进程" ), mainWidget );
    progressBar1 = new QProgressBar( mainWidget );
    progressLabel2 = new QLabel( trUtf8( "无操作进程" ), mainWidget );
    progressBar2 = new QProgressBar( mainWidget );

    progressLabel1->hide();
    progressBar1->hide();
    progressLabel2->hide();
    progressBar2->hide();

    setCentralWidget( mainWidget );
}
//当用户更改左侧目录时,显示对应目录信息
void FtpMainWindow::slotLocalDirChanged( const QString &path )
{
    
     //用户在左侧更改路径所能看到的信息
    oldLocal = localOperator;
    localOperator.setPath( path );
    localOperator.listChildren();
}

void FtpMainWindow::slotLocalDirChanged( const QUrlInfo &info )
{
     //用户在左侧更改路径所能看到的信息

    oldLocal = localOperator;
    localOperator.addPath( info.name() );
    localOperator.listChildren();
    localCombo->insertItem( localOperator.path(), 0 );
    localCombo->setCurrentItem( 0 );
}
//当用户更改右侧目录时,显示对应目录信息
void FtpMainWindow::slotRemoteDirChanged( const QString &path )
{
    //用户在右侧更改路径所能看到的信息

    if ( !remoteOperator.isValid() )
        return;
    oldRemote = remoteOperator;
    remoteOperator.setPath( path );
    remoteOperator.listChildren();
}

void FtpMainWindow::slotRemoteDirChanged( const QUrlInfo &info )
{
    //用户在右侧更改路径所能看到的信息

    oldRemote = remoteOperator;
    remoteOperator.addPath( info.name() );
    remoteOperator.listChildren();
    remotePathCombo->insertItem( remoteOperator.path(), 0 );
    remotePathCombo->setCurrentItem( 0 );
}

void FtpMainWindow::slotConnect()
{

     //用户通过点击connect按钮,来连接FTP服务器端
     //此外,我们还需要设置些必要的信息(如主机名,路径等),这些都是要求用户在进入右侧远程端进行
     //操作之前,进行适当配置

    // 协议 + 主机名(或路径)
    QString s = "ftp://" + remoteHostCombo->currentText();
    oldRemote = remoteOperator;
    remoteOperator = s;

    // 服务器端路径
    if ( !remotePathCombo->currentText().isEmpty() )
        remoteOperator.setPath( remotePathCombo->currentText() );
    else
        remoteOperator.setPath( "/" );


     //如果用户名为“空”、“ftp”或“anonymous”就可以不用输入,程序内部已经绑定
     //除非是匿名用户(anonymous),其他私有用户必需输入用户名和密码
    if ( !userCombo->currentText().isEmpty() &&
         userCombo->currentText().lower() != "anonymous" &&
         userCombo->currentText().lower() != "ftp" ) {
        remoteOperator.setUser( userCombo->currentText() );
        remoteOperator.setPassword( passLined->text() );
    }

    // 设置端口
    remoteOperator.setPort( portSpin->value() );

    
     //在FTP服务器端能够最终读到的目录
    remoteOperator.listChildren();
}

void FtpMainWindow::slotUpload()
{
    // 如果已经在左侧(本地文件系统)选定了文件,用户就通过点击“Upload”按钮,进行上传

    QValueList<QUrlInfo> files = leftView->selectedItems();
    if ( files.isEmpty() )
        return;

     //创建上传URL列表副本
    QStringList lst;
    QValueList<QUrlInfo>::Iterator it = files.begin();
    for ( ; it != files.end(); ++it )
        lst << QUrl( localOperator, ( *it ).name() );


     //将选中的文件清单复制到远程端(即FTP服务器)的上传目录中
    remoteOperator.copy( lst, remoteOperator, TRUE );
}

void FtpMainWindow::slotDownload()
{
 
     //如果在右侧(远程文件系统)中选定了文件,用户则可通过点击“Download”按钮,进行下载文件
    QValueList<QUrlInfo> files = rightView->selectedItems();
    if ( files.isEmpty() )
        return;

    //创建下载URL列表副本
    QStringList lst;
    QValueList<QUrlInfo>::Iterator it = files.begin();
    for ( ; it != files.end(); ++it )
        lst << QUrl( remoteOperator, ( *it ).name() );


     //将选中的文件清单复制到本地计算机的下载目录中
    localOperator.copy( lst, localOperator, FALSE );
}

void FtpMainWindow::slotLocalStart( QNetworkOperation *op )
{

     //若本地QUrlOperator开始,这个槽总是会被调用,来查看一个目录或是下载文件的相关信息

    if ( !op )
        return;

    if ( op->operation() == QNetworkProtocol::OpListChildren ) {
        
          //在开始查看目录时,清空左侧视图
        leftView->clear();
    } else if ( op->operation() == QNetworkProtocol::OpGet ) {
        
          //当开始下载文件时,重置进度栏
        progressBar1->setTotalSteps( 0 );
        progressBar1->reset();
    }
}

void FtpMainWindow::slotLocalFinished( QNetworkOperation *op )
{

     //若本地QUrlOperator操作结束时,这个槽总是会被调用
    if ( !op )
        return;

    if ( op && op->state() == QNetworkProtocol::StFailed ) {
        // 当有错误发生时, 能让用户知道
        QMessageBox::critical( this, trUtf8( "错误" ), op->protocolDetail() );

          //所出现的错误是由什么原因导致的
        int ecode = op->errorCode();
        if ( ecode == QNetworkProtocol::ErrListChildren || ecode == QNetworkProtocol::ErrParse ||
             ecode == QNetworkProtocol::ErrUnknownProtocol || ecode == QNetworkProtocol::ErrLoginIncorrect ||
             ecode == QNetworkProtocol::ErrValid || ecode == QNetworkProtocol::ErrHostNotFound ||
             ecode == QNetworkProtocol::ErrFileNotExisting ) {
            localOperator = oldLocal;
            localCombo->setEditText( localOperator.path() );
            localOperator.listChildren();
        }
    } else if ( op->operation() == QNetworkProtocol::OpPut ) {

          //当下载文件保存结束后,重读目录和隐藏进度栏
        localOperator.listChildren();
        progressLabel1->hide();
        progressBar1->hide();
    } else if ( op->operation() == QNetworkProtocol::OpGet ) {

          //在ftp服务器端文件结束是,重置进度栏
        progressBar1->setTotalSteps( 0 );
        progressBar1->reset();
    }

}

void FtpMainWindow::slotRemoteStart( QNetworkOperation *op )
{

     //若远程端QUrlOperator开始,这个槽总是会被调用,来查看一个目录或是上传文件的相关信息
    if ( !op )
        return;

    if ( op->operation() == QNetworkProtocol::OpListChildren ) {

          //在开始查看目录时,清空右侧视图
        rightView->clear();
    } else if ( op->operation() == QNetworkProtocol::OpGet ) {
 
          //当开始下载文件时,重置进度栏
        progressBar2->setTotalSteps( 0 );
        progressBar2->reset();
    }
}

void FtpMainWindow::slotRemoteFinished( QNetworkOperation *op )
{

     //若远程端QUrlOperator操作结束时,这个槽总是会被调用
    if ( !op )
        return;

    if ( op && op->state() == QNetworkProtocol::StFailed ) {
        
          //当有错误发生时,让用户知道
        QMessageBox::critical( this, trUtf8( "错误" ), op->protocolDetail() );

          //所出现的错误是由什么原因导致的
        int ecode = op->errorCode();
        if ( ecode == QNetworkProtocol::ErrListChildren || ecode == QNetworkProtocol::ErrParse ||
             ecode == QNetworkProtocol::ErrUnknownProtocol || ecode == QNetworkProtocol::ErrLoginIncorrect ||
             ecode == QNetworkProtocol::ErrValid || ecode == QNetworkProtocol::ErrHostNotFound ||
             ecode == QNetworkProtocol::ErrFileNotExisting ) {
            remoteOperator = oldRemote;
            remoteHostCombo->setEditText( remoteOperator.host() );
            remotePathCombo->setEditText( remoteOperator.path() );
            passLined->setText( remoteOperator.password() );
            userCombo->setEditText( remoteOperator.user() );
            portSpin->setValue( remoteOperator.port() );
            remoteOperator.listChildren();
        }
    } else if ( op->operation() == QNetworkProtocol::OpListChildren ) {

          //当目录读取完毕后,设置与右侧视图相适应的路径
        remotePathCombo->setEditText( remoteOperator.path() );
    } else if ( op->operation() == QNetworkProtocol::OpPut ) {

          //当下载文件保存完毕后,重读目录并隐藏进度栏
        remoteOperator.listChildren();
        progressLabel2->hide();
        progressBar2->hide();
    } else if ( op->operation() == QNetworkProtocol::OpGet ) {

          //当从本地文件系统中读完一个文件时,重置进度栏
        progressBar2->setTotalSteps( 0 );
        progressBar2->reset();
    }
}

void FtpMainWindow::slotLocalDataTransferProgress( int bytesDone, int bytesTotal,QNetworkOperation *op )
{

     //当本地QUrlOperator在读写数据时,在此显示进度
    if ( !op )
        return;

    if ( !progressBar1->isVisible() ) {
        if ( bytesDone < bytesTotal) {
            progressLabel1->show();
            progressBar1->show();
            progressBar1->setTotalSteps( bytesTotal );
            progressBar1->setProgress( 0 );
            progressBar1->reset();
        } else
            return;
    }

    if ( progressBar1->totalSteps() == bytesTotal )
        progressBar1->setTotalSteps( bytesTotal );

    if ( op->operation() == QNetworkProtocol::OpGet )
        progressLabel1->setText( trUtf8( "读: %1" ).arg( op->arg( 0 ) ) );
    else if ( op->operation() == QNetworkProtocol::OpPut )
        progressLabel1->setText( trUtf8( "写: %1" ).arg( op->arg( 0 ) ) );
    else
        return;

    progressBar1->setProgress( bytesDone );
}

void FtpMainWindow::slotRemoteDataTransferProgress( int bytesDone, int bytesTotal,QNetworkOperation *op )
{

     //当远程端QUrlOperator在读写数据时,在此显示进度
    if ( !op )
        return;

    if ( !progressBar2->isVisible() ) {
        if ( bytesDone < bytesTotal) {
            progressLabel2->show();
            progressBar2->show();
            progressBar2->setTotalSteps( bytesTotal );
            progressBar2->setProgress( 0 );
            progressBar2->reset();
        } else
            return;
    }

    if ( progressBar2->totalSteps() != bytesTotal )
        progressBar2->setTotalSteps( bytesTotal );

    if ( op->operation() == QNetworkProtocol::OpGet )
        progressLabel2->setText( trUtf8( "读: %1" ).arg( op->arg( 0 ) ) );
    else if ( op->operation() == QNetworkProtocol::OpPut )
        progressLabel2->setText( trUtf8( "写: %1" ).arg( op->arg( 0 ) ) );
    else
        return;

    progressBar2->setProgress( bytesDone );
}

void FtpMainWindow::slotLocalMkDir()
{

     //在本地文件系统中创建一个目录
    bool ok = FALSE;
    QString name = QInputDialog::getText( trUtf8( "Ftp客户端新建目录:" ), trUtf8("请输入<big><u><i>新建目录名</i></u></big>:"), QLineEdit::Normal, QString::null, &ok, this );

    if ( !name.isEmpty() && ok )
        localOperator.mkdir( name );
}

void FtpMainWindow::slotLocalRemove()
{
     //在本地文件系统中删除选定的目录
  bool ok = FALSE;
    QString name = QInputDialog::getText( trUtf8( "Ftp客户端删除:" ), trUtf8("请输入 <big><u><i>要删除目标名</i></u></big>:"), QLineEdit::Normal, QString::null, &ok, this );

    if ( !name.isEmpty() && ok )
        localOperator.remove( name );
}

void FtpMainWindow::slotLocalAddressBook()
{
     //地址簿功能实现代码
     //QMessageBox::warning(this,trUtf8("提示:"),trUtf8("<h2>调用地址簿</h2>"));
     switch(fork())
	{
	case -1:
		exit(1);
	case 0:
		execl("../addressbook/addressbook",NULL,NULL);
	exit(1);
	}
}

void FtpMainWindow::slotLocalPortScan()
{
     //端口扫描实现代码
     //QMessageBox::warning(this,trUtf8("提示:"),trUtf8("<h2>调用本地端口扫描</h2>"));
     switch(fork())
	{
	case -1:
		exit(1);
	case 0:
		execl("../port_scan/bin/portscan",NULL,NULL);
	exit(1);
	}
     
}

void FtpMainWindow::slotRemoteMkDir()
{

     //在远程端(FTP服务器)的文件系统中创建一个目录
    bool ok = FALSE;
    QString name = QInputDialog::getText( trUtf8( "Ftp服务端新建目录:" ), trUtf8("请输入<big><u><i>新建目录名</i></u></big>:"), QLineEdit::Normal, QString::null, &ok, this );

    if ( !name.isEmpty() && ok )
        remoteOperator.mkdir( name );
}

void FtpMainWindow::slotRemoteRemove()
{
     //在远程端(FTP服务器)的文件系统中删除选定的目录
bool ok = FALSE;
    QString name = QInputDialog::getText( trUtf8( "Ftp服务端删除:" ), trUtf8("请输入 <big><u><i>要删除目标名</i></u></big>: "), QLineEdit::Normal, QString::null, &ok, this );

    if ( !name.isEmpty() && ok )
        remoteOperator.remove( name );
}

void FtpMainWindow::slotConnectionStateChanged( int, const QString &msg )
{
    statusBar()->message( msg );
}
