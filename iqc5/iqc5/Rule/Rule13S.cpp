#include "Rule13S.h"
#include <math.h>

Rule13S::Rule13S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule13S::GetValidCount(int level)
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

bool Rule13S::IsValid(int level, int index)
{
    if(fabs((*rnds)[level][index].value - (*means)[level]) > 3 * (*sds)[level])
    {
        return false;
    }
    else
    {
        return true;
    }
}
