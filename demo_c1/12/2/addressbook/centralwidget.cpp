#include "centralwidget.h"

#include <qtabwidget.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qfile.h>
#include <qtextstream.h>

ABCentralWidget::ABCentralWidget( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
    mainGrid = new QGridLayout( this, 2, 1, 5, 5 );

    setupTabWidget();
    setupListView();

    mainGrid->setRowStretch( 0, 0 );
    mainGrid->setRowStretch( 1, 1 );
}

void ABCentralWidget::save( const QString &filename )
{
    if ( !listView->firstChild() )
        return;

    QFile f( filename );
    if ( !f.open( IO_WriteOnly ) )
        return;

    QTextStream t( &f );

    QListViewItemIterator it( listView );

    for ( ; it.current(); ++it )
        for ( unsigned int i = 0; i < 4; i++ )
            t << it.current()->text( i ) << "\n";

    f.close();
}

void ABCentralWidget::load( const QString &filename )
{
    listView->clear();

    QFile f( filename );
    if ( !f.open( IO_ReadOnly ) )
        return;

    QTextStream t( &f );

    while ( !t.atEnd() ) {
        QListViewItem *item = new QListViewItem( listView );
        for ( unsigned int i = 0; i < 4; i++ )
            item->setText( i, t.readLine() );
    }

    f.close();
}

void ABCentralWidget::setupTabWidget()
{
    tabWidget = new QTabWidget( this );

    QWidget *input = new QWidget( tabWidget );
    QGridLayout *grid1 = new QGridLayout( input, 2, 5, 5, 5 );

    QLabel *liTitle = new QLabel( trUtf8("标签 &t"), input );
    liTitle->resize( liTitle->sizeHint() );
    grid1->addWidget( liTitle, 0, 0 );

    QLabel *liPackageName = new QLabel( trUtf8("文件名 &p"), input );
    liPackageName->resize( liPackageName->sizeHint() );
    grid1->addWidget( liPackageName, 0, 1 );

    QLabel *liSize = new QLabel( trUtf8("大小 &z"), input );
    liSize->resize( liSize->sizeHint() );
    grid1->addWidget( liSize, 0, 2 );

    QLabel *liFtpSite = new QLabel( trUtf8("Ftp站点 &e"), input );
    liFtpSite->resize( liFtpSite->sizeHint() );
    grid1->addWidget( liFtpSite, 0, 3 );

    add = new QPushButton( trUtf8("添加 &d"), input );
    add->resize( add->sizeHint() );
    grid1->addWidget( add, 0, 4 );
    connect( add, SIGNAL( clicked() ), this, SLOT( addEntry() ) );

    iTitle = new QLineEdit( input );
    iTitle->resize( iTitle->sizeHint() );
    grid1->addWidget( iTitle, 1, 0 );
    liTitle->setBuddy( iTitle );

    iPackageName = new QLineEdit( input );
    iPackageName->resize( iPackageName->sizeHint() );
    grid1->addWidget( iPackageName, 1, 1 );
    liPackageName->setBuddy( iPackageName );

    iSize = new QLineEdit( input );
    iSize->resize( iSize->sizeHint() );
    grid1->addWidget( iSize, 1, 2 );
    liSize->setBuddy( iSize );

    iFtpSite = new QLineEdit( input );
    iFtpSite->resize( iFtpSite->sizeHint() );
    grid1->addWidget( iFtpSite, 1, 3 );
    liFtpSite->setBuddy( iFtpSite );

    change = new QPushButton( trUtf8("更改 &c"), input );
    change->resize( change->sizeHint() );
    grid1->addWidget( change, 1, 4 );
    connect( change, SIGNAL( clicked() ), this, SLOT( changeEntry() ) );

    tabWidget->addTab( input, trUtf8("添加与更改 &a") );

    // --------------------------------------

    QWidget *search = new QWidget( this );
    QGridLayout *grid2 = new QGridLayout( search, 2, 5, 5, 5 );

    cTitle = new QCheckBox( trUtf8("标签 &t"), search );
    cTitle->resize( cTitle->sizeHint() );
    grid2->addWidget( cTitle, 0, 0 );
    connect( cTitle, SIGNAL( clicked() ), this, SLOT( toggleTitle() ) );

    cPackageName = new QCheckBox(  trUtf8("文件名 &p"), search );
    cPackageName->resize( cPackageName->sizeHint() );
    grid2->addWidget( cPackageName, 0, 1 );
    connect( cPackageName, SIGNAL( clicked() ), this, SLOT( togglePackageName() ) );

    cSize = new QCheckBox(trUtf8("大小 &z"), search );
    cSize->resize( cSize->sizeHint() );
    grid2->addWidget( cSize, 0, 2 );
    connect( cSize, SIGNAL( clicked() ), this, SLOT( toggleSize() ) );

    cFtpSite = new QCheckBox( trUtf8("Ftp站点 &e"), search );
    cFtpSite->resize( cFtpSite->sizeHint() );
    grid2->addWidget( cFtpSite, 0, 3 );
    connect( cFtpSite, SIGNAL( clicked() ), this, SLOT( toggleFtpSite() ) );

    sTitle = new QLineEdit( search );
    sTitle->resize( sTitle->sizeHint() );
    grid2->addWidget( sTitle, 1, 0 );

    sPackageName = new QLineEdit( search );
    sPackageName->resize( sPackageName->sizeHint() );
    grid2->addWidget( sPackageName, 1, 1 );

    sSize = new QLineEdit( search );
    sSize->resize( sSize->sizeHint() );
    grid2->addWidget( sSize, 1, 2 );

    sFtpSite = new QLineEdit( search );
    sFtpSite->resize( sFtpSite->sizeHint() );
    grid2->addWidget( sFtpSite, 1, 3 );

    find = new QPushButton( trUtf8("查找 &i"), search );
    find->resize( find->sizeHint() );
    grid2->addWidget( find, 1, 4 );
    connect( find, SIGNAL( clicked() ), this, SLOT( findEntries() ) );

    cTitle->setChecked( TRUE );
    sTitle->setEnabled( TRUE );
    sPackageName->setEnabled( FALSE );
    sSize->setEnabled( FALSE );
    sFtpSite->setEnabled( FALSE );

    tabWidget->addTab( search, trUtf8("搜索 &s") );

    mainGrid->addWidget( tabWidget, 0, 0 );
}

void ABCentralWidget::setupListView()
{
    listView = new QListView( this );
    listView->addColumn( trUtf8("标签") );
    listView->addColumn( trUtf8("文件名") );
    listView->addColumn( trUtf8("大小") );
    listView->addColumn( trUtf8("Ftp站点") );

    listView->setSelectionMode( QListView::Single );

    connect( listView, SIGNAL( clicked( QListViewItem* ) ), this, SLOT( itemSelected( QListViewItem* ) ) );

    mainGrid->addWidget( listView, 1, 0 );
    listView->setAllColumnsShowFocus( TRUE );
}

void ABCentralWidget::addEntry()
{
    if ( !iTitle->text().isEmpty() || !iPackageName->text().isEmpty() ||
         !iSize->text().isEmpty() || !iFtpSite->text().isEmpty() ) {
        QListViewItem *item = new QListViewItem( listView );
        item->setText( 0, iTitle->text() );
        item->setText( 1, iPackageName->text() );
        item->setText( 2, iSize->text() );
        item->setText( 3, iFtpSite->text() );
    }

    iTitle->setText( "" );
    iPackageName->setText( "" );
    iSize->setText( "" );
    iFtpSite->setText( "" );
}

void ABCentralWidget::changeEntry()
{
    QListViewItem *item = listView->currentItem();

    if ( item &&
         ( !iTitle->text().isEmpty() || !iPackageName->text().isEmpty() ||
           !iSize->text().isEmpty() || !iFtpSite->text().isEmpty() ) ) {
        item->setText( 0, iTitle->text() );
        item->setText( 1, iPackageName->text() );
        item->setText( 2, iSize->text() );
        item->setText( 3, iFtpSite->text() );
    }
}

void ABCentralWidget::selectionChanged()
{
    iTitle->setText( "" );
    iPackageName->setText( "" );
    iSize->setText( "" );
    iFtpSite->setText( "" );
}

void ABCentralWidget::itemSelected( QListViewItem *item )
{
    if ( !item )
        return;
    item->setSelected( TRUE );
    item->repaint();

    iTitle->setText( item->text( 0 ) );
    iPackageName->setText( item->text( 1 ) );
    iSize->setText( item->text( 2 ) );
    iFtpSite->setText( item->text( 3 ) );
}

void ABCentralWidget::toggleTitle()
{
    sTitle->setText( "" );

    if ( cTitle->isChecked() ) {
        sTitle->setEnabled( TRUE );
        sTitle->setFocus();
    }
    else
        sTitle->setEnabled( FALSE );
}

void ABCentralWidget::togglePackageName()
{
    sPackageName->setText( "" );

    if ( cPackageName->isChecked() ) {
        sPackageName->setEnabled( TRUE );
        sPackageName->setFocus();
    }
    else
        sPackageName->setEnabled( FALSE );
}

void ABCentralWidget::toggleSize()
{
    sSize->setText( "" );

    if ( cSize->isChecked() ) {
        sSize->setEnabled( TRUE );
        sSize->setFocus();
    }
    else
        sSize->setEnabled( FALSE );
}

void ABCentralWidget::toggleFtpSite()
{
    sFtpSite->setText( "" );

    if ( cFtpSite->isChecked() ) {
        sFtpSite->setEnabled( TRUE );
        sFtpSite->setFocus();
    }
    else
        sFtpSite->setEnabled( FALSE );
}

void ABCentralWidget::findEntries()
{
    if ( !cTitle->isChecked() &&
         !cPackageName->isChecked() &&
         !cSize->isChecked() &&
         !cFtpSite->isChecked() ) {
        listView->clearSelection();
        return;
    }

    QListViewItemIterator it( listView );

    for ( ; it.current(); ++it ) {
        bool select = TRUE;

        if ( cTitle->isChecked() ) {
            if ( select && it.current()->text( 0 ).contains( sTitle->text() ) )
                select = TRUE;
            else
                select = FALSE;
        }
        if ( cPackageName->isChecked() ) {
            if ( select && it.current()->text( 1 ).contains( sPackageName->text() ) )
                select = TRUE;
            else
                select = FALSE;
        }
        if ( cSize->isChecked() ) {
            if ( select && it.current()->text( 2 ).contains( sSize->text() ) )
                select = TRUE;
            else
                select = FALSE;
        }
        if ( cFtpSite->isChecked() ) {
            if ( select && it.current()->text( 3 ).contains( sFtpSite->text() ) )
                select = TRUE;
            else
                select = FALSE;
        }

        if ( select )
            it.current()->setSelected( TRUE );
        else
            it.current()->setSelected( FALSE );
        it.current()->repaint();
    }
}
