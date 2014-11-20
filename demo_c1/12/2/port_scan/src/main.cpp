#include <qapplication.h>
#include "portscan.h"

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    portscan * mw = new portscan();
    a.setMainWidget( mw );
    mw->show();
    return a.exec();
}
