#ifndef LISINTERFACE_H
#define LISINTERFACE_H

#include "LisData.h"
#include <QStringList>

class LisInterface
{
public:
    ~LisInterface();

    virtual LisData* getData(const QString dir = "") = 0 ;
    virtual QStringList readSetting() = 0;
    virtual QString InterfaceName() = 0;
};

#endif // LISINTERFACE_H
