#ifndef ZHIFANGINTERFACE_H
#define ZHIFANGINTERFACE_H


#include "lisinterface.h"
#include "configure.h"
#include <QSettings>

class  zhiFangLisInterface : public LisInterface
{

public:
    zhiFangLisInterface();
    ~zhiFangLisInterface();

    // LisInterface interface
public:
        LisData *getData(const QString dir = "");

        QStringList readSetting();

        QString InterfaceName();

        LisData *data;

        QString buildNameSpaceStr(QString key, QString str = "");

        Configure configure;
        QSettings *setting;
};

#endif // ZHIFANGINTERFACE_H
