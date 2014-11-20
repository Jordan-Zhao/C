#include <qapplication.h>

#include "mainwindow.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );

    ABMainWindow *mw = new ABMainWindow();
    mw->setCaption( "Addressbook" );
    a.setMainWidget( mw );
    mw->show();

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    int result = a.exec();
    delete mw;
    return result;
}
