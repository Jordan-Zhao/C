#ifndef FTPVIEW_H
#define FTPVIEW_H

#include <qlistview.h>
#include <qvaluelist.h>
#include <qurlinfo.h>

class FtpViewItem : public QListViewItem
{
public:
    FtpViewItem( QListView *parent, const QUrlInfo &i );

    int compare( QListViewItem * i, int col, bool ascending ) const;
    QString text( int c ) const;
    const QPixmap* pixmap( int c ) const;

    QUrlInfo entryInfo() {
        return info;
    }

private:
    QUrlInfo info;

};

class FtpView : public QListView
{
    Q_OBJECT

public:
    FtpView( QWidget *parent );
    QValueList<QUrlInfo> selectedItems() const;

public slots:
    void slotInsertEntries( const QValueList<QUrlInfo> &info );

signals:
    void itemSelected( const QUrlInfo &info );

private slots:
    void slotSelected( QListViewItem *item );

};

#endif
