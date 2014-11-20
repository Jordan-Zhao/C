#include "mainwindow.h"
#include "centralwidget.h"

#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <qapplication.h>
#include <qfiledialog.h>

ABMainWindow::ABMainWindow()
    : QMainWindow(),
      filename( QString::null )
{
    setupMenuBar();
    setupStatusBar();
    setupCentralWidget();
}


ABMainWindow::~ABMainWindow()
{
}

void ABMainWindow::setupMenuBar()
{
    QPopupMenu *file = new QPopupMenu( this );
    menuBar()->insertItem( trUtf8("文件 &F"), file );
   
    file->insertItem( QPixmap( "fileopen.xpm" ), trUtf8("打开 &O"), this, SLOT( fileOpen() ),ALT+Key_O);

    file->insertSeparator();//分隔线

    file->insertItem( QPixmap( "filesave.xpm" ), trUtf8("保存 &D"), this, SLOT( fileSave() ), ALT+Key_D );
    file->insertItem( trUtf8("另存为 &A..."), this, SLOT( fileSaveAs() ), ALT+Key_A );

    file->insertSeparator();//分隔线

    file->insertItem( trUtf8("关闭 &C"), this, SLOT( close() ), ALT+Key_C );
    file->insertItem( trUtf8("退出 &Q"), qApp, SLOT( quit() ), ALT+Key_Q );
}

void ABMainWindow::setupStatusBar()
{
    statusBar()->message( trUtf8("就绪"), 2000 );
}

void ABMainWindow::setupCentralWidget()
{
    view = new ABCentralWidget( this );
    setCentralWidget( view );
}

void ABMainWindow::fileOpen()
{
    QString fn = QFileDialog::getOpenFileName( QString::null, QString::null, this );
    if ( !fn.isEmpty() ) {
        filename = fn;
        view->load( filename );
    }
}

void ABMainWindow::fileSave()
{
    if ( filename.isEmpty() ) {
        fileSaveAs();
        return;
    }

    view->save( filename );
}

void ABMainWindow::fileSaveAs()
{
    QString fn = QFileDialog::getSaveFileName( QString::null, QString::null, this );
    if ( !fn.isEmpty() ) {
        filename = fn;
        fileSave();
    }
}
