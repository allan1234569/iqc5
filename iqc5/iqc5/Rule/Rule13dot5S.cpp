#include "Rule13dot5S.h"
#include <math.h>

Rule13dot5S::Rule13dot5S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule13dot5S::GetValidCount(int level)
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

bool Rule13dot5S::IsValid(int level, int index)
{
    if(fabs((*rnds)[level][index].value - (*means)[level]) > 3.5 * (*sds)[level])
    {
        return false;
    }
    else
    {
        return true;
    }
}
