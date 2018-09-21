#include "ShowToolTip.h"
#include "TipBox.h"
#include <unistd.h>

ShowToolTip::ShowToolTip(QWidget *widget, QString message, int msec)
{
    TipBox *tipBox = new TipBox(widget);
    tipBox->SetStr(message);
    tipBox->show();
    usleep(msec);
    tipBox->close();
}
