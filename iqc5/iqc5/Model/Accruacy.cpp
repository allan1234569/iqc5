#include "Accruacy.h"
#include "formula.h"
#include <QString>
Accruacy_ReferenceMaterial::Accruacy_ReferenceMaterial()
{
    average = 0;
    sd = 0;
}

void Accruacy_ReferenceMaterial::Set(QMap<int, double> map)
{
    this->mData = map;
}

double Accruacy_ReferenceMaterial::GetTotalAverage()
{
    average = GetAverage(mData);
    return average;
}

double Accruacy_ReferenceMaterial::GetSd()
{
    return GetStandardDeviation(mData);
}

double Accruacy_ReferenceMaterial::GetVI()
{

}


Accruacy_PatientSample::Accruacy_PatientSample()
{
    averageBi = 0;
    averageBirel = 0;
}

void Accruacy_PatientSample::Set(data_Map map)
{
    this->mData = map;
}

QMap<int, double> Accruacy_PatientSample::GetBi()
{
    for(int i = 1; i <= 20; i++)
    {
        double data = mData[i]["Ri"]-mData[i]["Rc"];
        mBi.insert(i,data);
    }

    averageBi = GetAverage(mBi);

    return mBi;
}

QMap<int, double> Accruacy_PatientSample::GetBirel()
{
    for(int i = 1; i <= 20; i++)
    {
        double data  = ((mData[i]["Ri"]-mData[i]["Rc"])/mData[i]["Rc"])*100;
        mBirel.insert(i,data);
    }

    averageBirel = GetAverage(mBirel);

    return mBirel;
}

double Accruacy_PatientSample::GetBiSd()
{
    return GetStandardDeviation(mBi);
}

double Accruacy_PatientSample::GetBirelSd()
{
    return GetStandardDeviation(mBirel);
}
