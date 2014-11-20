#include "portscan.h"

portscan::portscan(QWidget* parent, const char* name, WFlags fl)
: scandlg(parent,name,fl)
{
}

portscan::~portscan()
{
}

void portscan::option()
{
    opt *nainWin=new opt(this);
    nainWin->show();
}

void portscan::scan()
{
    textEdit->append("------------------start scan---------------------");
    for(port=startp;port<=endp;port++)
    {
        sa.sin_family=AF_INET;
        host=gethostbyname(lineEdit->text());
        strncpy((char *)&sa.sin_addr,(char *)host->h_addr,sizeof(sa.sin_addr));
        sa.sin_port=htons(port);
        bzero(&(sa.sin_zero),8);
        sd=socket(AF_INET,SOCK_STREAM,0);
        if(::connect(sd,(struct sockaddr *)&sa,sizeof(struct sockaddr))==0)
        {
            sprintf(temp,"port %d is open",port);
            textEdit->append(temp);
        }
        
    }
    textEdit->append("------------------end scan---------------------");
}



