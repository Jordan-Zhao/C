#ifndef OPT_H
#define OPT_H

#include "myvar.h"
#include "optdlg.h"
#include "qspinbox.h"
#include "qmessagebox.h"

class opt : public optdlg
{
  Q_OBJECT

public:
  opt(QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
  ~opt();

public slots:
  virtual void          zero();
  virtual void          set();

};

#endif

