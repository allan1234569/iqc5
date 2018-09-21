#include "RuleR4S.h"
#include <math.h>
#include "Project.h"

RuleR4S::RuleR4S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;

    Project p;
    p.CaculateZ(rnds, means, sds);
}

int RuleR4S::GetValidCount(int level)
{
    int vaildCount = 0;
    for(int i = 0; i < rnds[level].count(); i++)
    {
        if (IsValid(level,i))
        {
            vaildCount++;
        }
    }

    return vaildCount;
}

bool RuleR4S::IsValid(int level, int index)
{

    QVector<QVector<int> > indexs;
    indexs.resize((*rnds).count());
    for(int l = 0; l < (*rnds).count(); l++)
    {
        bool flag = false;
        for(int i = 0; i < (*rnds)[l].count(); i++)
        {
            if((*rnds)[l][i].TestTime == (*rnds)[level][index].TestTime)
            {
                indexs[l].push_back(i);
                flag = true;
                break;
            }
        }

        if(!flag)
        {
            indexs[l].push_back(-1);
        }
    }

    if(index == 0)
    {
        for(int l = 0 ; l < (*rnds).count(); l++)
        {
            if(l == level)
            {
                continue;
            }
            if((index < (*rnds)[level].count()) && (indexs[level][0] != -1) && ((*rnds)[l].count() > 0))
            {
                if(fabs((*rnds)[level][index].z_value - (*rnds)[l][index].z_value) > 4)
                {
                    return false;
                }
            }
        }
    }

    if(index >= 1)
    {
        if((*rnds)[level][index].ResultNum > 1)
        {
            for(int l = 0; l < (*rnds).count(); l++)
            {
                if(l == level)
                {
                    continue;
                }

                if (indexs[l][0] != -1
                        && ((*rnds)[l].count() > (indexs[l][0] + (*rnds)[level][index].ResultNum -1))
                        )
                {
                    if((*rnds)[level][index].TestTime == (*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum -1 ].TestTime)
                    {
                        if(fabs((*rnds)[level][index].z_value - (*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum -1 ].z_value) > 4)
                        {
                            return false;
                        }
                    }
                }
            }
//            if(index >= 1)
//            {
//                if(fabs((*rnds)[level][index].z_value - (*rnds)[level][index - 1].z_value) > 4)
//                {
//                    return false;
//                }
//            }
        }
        else    //批内
        {
            for(int l = 0; l < (*rnds).count(); l++)
            {
                if((l == level) )
                {
                    continue;
                }

                if (indexs[l][0] != -1 && indexs[l][0] < (*rnds)[l].count())
                {
                    if(fabs((*rnds)[level][index].z_value - (*rnds)[l][indexs[l][0]].z_value) > 4)
                    {
                        return false;
                    }
                }
            }
        }
    }


    return true;
}
