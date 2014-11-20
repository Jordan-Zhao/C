#ifndef AB_CENTRALWIDGET_H
#define AB_CENTRALWIDGET_H

#include <qwidget.h>
#include <qstring.h>

class QTabWidget;
class QListView;
class QGridLayout;
class QLineEdit;
class QPushButton;
class QListViewItem;
class QCheckBox;

class ABCentralWidget : public QWidget
{
    Q_OBJECT

public:
    ABCentralWidget( QWidget *parent, const char *name = 0 );

    void save( const QString &filename );
    void load( const QString &filename );

protected slots:
    void addEntry();
    void changeEntry();
    void itemSelected( QListViewItem* );
    void selectionChanged();
    void toggleTitle();
    void togglePackageName();
    void toggleSize();
    void toggleFtpSite();
    void findEntries();

protected:
    void setupTabWidget();
    void setupListView();

    QGridLayout *mainGrid;
    QTabWidget *tabWidget;
    QListView *listView;
    QPushButton *add, *change, *find;
    QLineEdit *iTitle, *iPackageName, *iSize, *iFtpSite,
        *sTitle, *sPackageName, *sSize, *sFtpSite;
    QCheckBox *cTitle, *cPackageName, *cSize, *cFtpSite;

};

#endif
