#include "Rule10X.h"
#include <math.h>

Rule10X::Rule10X(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule10X::GetValidCount(int level)
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

bool Rule10X::IsValid(int level, int index)
{

    int InvalidCount = 0;
    bool preHasFound = false;   //前一批失控
    bool flag;  //连续性检测标志

    if(index < (*rnds)[level].count())
    {

        if ((*rnds)[level][index].value > (*means)[level])  //大于均值
        {
            for(int l = 0; l < (*rnds).count();l++)
            {
                if((*rnds)[l].count() > index)
                {
                    if((*rnds)[l][index].value > (*means)[l])
                    {
                        for(int i = 0; i < 10; i++)
                        {
                            if((*rnds)[l][index - i].value > (*means)[l])
                            {
                                InvalidCount++;
                            }
                            else
                            {
                                break;
                            }

                            if(InvalidCount >= 10)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        else    //小于均值
        {
            for(int l = 0; l < (*rnds).count();l++)
            {
                if((*rnds)[l].count() > index)
                {
                    if((*rnds)[l][index].value < (*means)[l])
                    {
                        for(int i = 0; i < 10; i++)
                        {
                            if((*rnds)[l][index - i].value < (*means)[l])
                            {
                                InvalidCount++;
                            }
                            else
                            {
                                break;
                            }

                            if(InvalidCount >= 10)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

