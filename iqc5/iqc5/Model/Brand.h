#ifndef BRAND_H
#define BRAND_H
#include <QString>
#include <QDateTime>

class Brand
{
public:
    Brand();

    QString BrandId;
    QString BrandName;
    int IfDefault;
    QDateTime AddTime;
    int Status;
};

#endif // BRAND_H
