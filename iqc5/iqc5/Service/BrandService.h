#ifndef BRANDSERVICE_H
#define BRANDSERVICE_H
#include "Brand.h"

class BrandService
{
public:
    BrandService();

    Brand GetById(QString BrandId);
    QVector<Brand> GetBrands(QString name);
    QString Insert(Brand brand);
    void Update(Brand brand);
    void DeleteById(QString BrandId);
};

#endif // BRANDSERVICE_H
