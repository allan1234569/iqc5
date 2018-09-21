#include "Rule22S.h"
#include <math.h>
#include <QDebug>

Rule22S::Rule22S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule22S::GetValidCount(int level)
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

bool Rule22S::IsValid(int level, int index)
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

    int InValidCount = 0;

    if(index == 0)
    {
        if((*rnds)[level][index].value- (*means)[level] > 2 * (*sds)[level])
        {
            for(int l = 0; l < (*rnds).count(); l++)
            {
                if((*rnds).count() >= 1)
                {
                    if((*rnds)[l][index].value- (*means)[l] > 2 * (*sds)[l])
                    {
                        InValidCount++;
                    }
                    if(InValidCount >= 2)
                    {
                        return false;
                    }
                }
            }
        }
        else
        {
            for(int l = 0; l < (*rnds).count(); l++)
            {
                if((*rnds).count() >= 1)
                {
                    if((*rnds)[l][index].value- (*means)[l] < -2 * (*sds)[l])
                    {
                        InValidCount++;
                    }
                    if(InValidCount >= 2)
                    {
                        return false;
                    }
                }
            }
        }
    }


    if(index >= 1)
    {
        if (((*rnds)[level][index].value - (*means)[level]) > 2 *(*sds)[level])
        {
            if((*rnds)[level][index].ResultNum > 1) //批内该水平内
            {
                if (((*rnds)[level][index - 1].value - (*means)[level]) > 2 * (*sds)[level])
                {
                    return false;
                }
                else    //批内与其他水平间
                {
                    for(int l = 0; l < (*rnds).count(); l++)
                    {
                        if(l == level)
                        {
                            continue;
                        }

                        if((indexs[l][0] != -1)
                                &&((*rnds)[l].count() > (indexs[l][0] + (*rnds)[level][index].ResultNum - 1))
                                && ((*rnds)[level][index].TestTime.compare((*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum - 1 ].TestTime) == 0)
                                )
                        {
                            if (((*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum - 1 ].value - (*means)[l]) > 2 * (*sds)[l])
                            {
                                return false;
                            }
                        }
                    }
                }
            }
            else
            {
                for(int i = 0; i < 2; i++)  //先批内再批间
                {
                    if(index >= i)
                    {
                        for(int l = 0; l < (*rnds).count(); l++)
                        {
                            if((i == 0) && (l == level))
                            {
                                continue;
                            }
                            if(indexs[l][0] != -1
                                    && (*rnds)[l].count() > indexs[l][0])
                            {
                                if((*rnds)[l][ indexs[l][0] - i].value - (*means)[l] > 2 *(*sds)[l])
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (((*rnds)[level][index].value - (*means)[level]) < -2 * (*sds)[level])
        {

            if((*rnds)[level][index].ResultNum > 1) //批内该水平内
            {
                if (((*rnds)[level][index - 1].value - (*means)[level]) < -2 * (*sds)[level])
                {
                    return false;
                }
                else    //批内与其他水平间
                {
                    for(int l = 0; l < (*rnds).count(); l++)
                    {
                        if(l == level)
                        {
                            continue;
                        }

                        if((indexs[l][0] != -1)
                                &&((*rnds)[l].count() > (indexs[l][0] + (*rnds)[level][index].ResultNum - 1))
                                && ((*rnds)[level][index].TestTime.compare((*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum - 1 ].TestTime) == 0)
                                )
                        {
                            if (((*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum - 1 ].value - (*means)[l]) < -2 *(*sds)[l])
                            {
                                return false;
                            }
                        }
                    }
                }
            }
            else
            {
                for(int i = 0; i < 2; i++)  //先批内再批间
                {
                    if(index >= i)
                    {
                        for(int l = 0; l < (*rnds).count(); l++)
                        {
                            if((i == 0) && (l == level))
                            {
                                continue;
                            }

                            if(indexs[l][0] != -1
                                    && (*rnds)[l].count() > indexs[l][0])
                            {
                                if((*rnds)[l][ indexs[l][0] - i].value - (*means)[l] < -2 * (*sds)[l])
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
