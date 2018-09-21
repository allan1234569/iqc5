#include "Rule31S.h"
#include "math.h"
#include <QDebug>

Rule31S::Rule31S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule31S::GetValidCount(int level)
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

bool Rule31S::IsValid(int level, int index)
{
    int InvalidCount = 0;   //无效值个数
    bool preHasFound = false;   //前一批失控
    bool flag;

    if(index < (*rnds)[level].count())
    {
        if(fabs((*rnds)[level][index].value - (*means)[level]) < (*sds)[level])
        {
                return true;
        }

        if (((*rnds)[level][index].value - (*means)[level]) > 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if(index >= i)
                {
                    flag = false;
                    for(int l = 0; l < rnds->count(); l++)
                    {
                        if(index < (*rnds)[l].count())
                        {
                            if(((*rnds)[l][index - i].value - (*means)[l]) > (*sds)[l])
                            {
                                InvalidCount++;
                                flag = true;
                            }
                            else
                            {
                                InvalidCount = 0;
                                flag = false;
                                break;
                            }

                        }
                        if(preHasFound && InvalidCount >= 3)
                        {
                            return false;
                        }
                    }

                    preHasFound = flag;
                }
                if (!preHasFound)
                {
                    return true;
                }
            }

        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if(index >= i)
                {
                    flag = false;

                    for(int l = 0; l < rnds->count(); l++)
                    {
                        if(index < (*rnds)[l].count())
                        {
                            if( ((*means)[l] - (*rnds)[l][index - i].value) > (*sds)[l])
                            {
                                InvalidCount++;
                                flag = true;
                            }
                            else
                            {
                                InvalidCount = 0;
                                flag = false;
                                break;
                            }
                        }
                        if( preHasFound && InvalidCount >= 3)
                        {
                            return false;
                        }
                    }

                    preHasFound = flag;
                }
                if(!preHasFound)
                {
                    return true;
                }
            }

        }
    }

    return true;
}
