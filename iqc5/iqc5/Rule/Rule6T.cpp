#include "Rule6T.h"
#include <math.h>

Rule6T::Rule6T(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule6T::GetValidCount(int level)
{
    int vaildCount = 0;

        for(int i = 0; i < rnds[level].count(); i++)
        {
            if(IsValid(level, i))
            {
                vaildCount++;
            }
        }

    return vaildCount;
}

bool Rule6T::IsValid(int level, int index)
{
    if(index >= 5)
    {
        if (
                (
                      ((*rnds)[level][index - 5].value > (*rnds)[level][index - 4].value)
                    &&((*rnds)[level][index - 4].value > (*rnds)[level][index - 3].value)
                    &&((*rnds)[level][index - 3].value > (*rnds)[level][index - 2].value)
                    &&((*rnds)[level][index - 2].value > (*rnds)[level][index - 1].value)
                    &&((*rnds)[level][index - 1].value > (*rnds)[level][index - 0].value)
                )
                ||
                (
                      ((*rnds)[level][index - 5].value < (*rnds)[level][index - 4].value)
                    &&((*rnds)[level][index - 4].value < (*rnds)[level][index - 3].value)
                    &&((*rnds)[level][index - 3].value < (*rnds)[level][index - 2].value)
                    &&((*rnds)[level][index - 2].value < (*rnds)[level][index - 1].value)
                    &&((*rnds)[level][index - 1].value < (*rnds)[level][index - 0].value)
                )
            )
        {
            return false;
        }
    }

    return true;
}

