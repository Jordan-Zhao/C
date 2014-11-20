#ifndef PORTSCAN_H
#define PORTSCAN_H

#include "myvar.h"
#include "scandlg.h"
#include "opt.h"
#include "qlineedit.h"
#include "qtextedit.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "netdb.h"
#include "string.h"
#include "strings.h"

class portscan : public scandlg
{
  Q_OBJECT

public:
  portscan(QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
  ~portscan();

public slots:
  virtual void          option();
  virtual void          scan();

private:
    int sd;
    int port;
    struct hostent *host;
    struct sockaddr_in sa;
    char temp[100];

};

#endif

