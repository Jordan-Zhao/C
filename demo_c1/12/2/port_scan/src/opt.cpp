#include "opt.h"

int startp,endp;

opt::opt(QWidget* parent, const char* name, WFlags fl)
: optdlg(parent,name,fl)
{
    start->setValue(startp);
    end->setValue(endp);
}

opt::~opt()
{
}

void opt::zero()
{
    start->setValue(0);
    end->setValue(0);
}

void opt::set()
{
    if(start->value()>end->value())
    {
        QMessageBox::warning(this,"","port range invalid","Retry");
    }
    else
    {
        startp=start->value();
        endp=end->value();
        close();
    }
}



