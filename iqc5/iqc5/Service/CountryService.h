#ifndef COUNTRYSERVICE_H
#define COUNTRYSERVICE_H
#include "Country.h"

class CountryService
{
public:
    CountryService();

    Country GetById(QString CountryId);
    QVector<Country> GetCountrys(QString name);
    QString Insert(Country country);
    void Update(Country country);
    void DeleteById(QString CountryId);
};

#endif // COUNTRYSERVICE_H
