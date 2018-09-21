#ifndef MANUFACTURERSERVICE_H
#define MANUFACTURERSERVICE_H
#include "Manufacturer.h"
#include "Country.h"

class ManufacturerService
{
public:
    ManufacturerService();

    Manufacturer GetById(QString ManufacturerId);
    QVector<Manufacturer> GetManufacturers(QString name);
    QString Insert(Manufacturer manufacturer);
    void Update(Manufacturer manufacturer);
    void DeleteById(QString ManufacturerId);

    QVector<Country> GetCountries();
    Country GetCountryByName(QString name);
};

#endif // MANUFACTURERSERVICE_H
