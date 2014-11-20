#ifndef AB_MAINWINDOW_H
#define AB_MAINWINDOW_H

#include <qmainwindow.h>
#include <qstring.h>

class QPopupMenu;
class ABCentralWidget;

class ABMainWindow: public QMainWindow
{
    Q_OBJECT

public:
    ABMainWindow();
    ~ABMainWindow();

protected slots:
    void fileOpen();
    void fileSave();
    void fileSaveAs();

protected:
    void setupMenuBar();
    void setupStatusBar();
    void setupCentralWidget();


    QString filename;
    ABCentralWidget *view;

};


#endif
