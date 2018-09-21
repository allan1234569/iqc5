#include "Rule2of32S.h"
#include <math.h>

Rule2of32S::Rule2of32S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule2of32S::GetValidCount(int level)
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

bool Rule2of32S::IsValid(int level, int index)
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
    if(((*rnds)[level][index].value - (*means)[level]) > 2 * (*sds)[level])
    {

        for(int l = 0; l < (*rnds).count(); l++)
        {
            if(l == level)
            {
                continue;
            }

            if(index < (*rnds)[l].count())
            {
                if(((*rnds)[l][index].value - (*means)[l]) > 2 * (*sds)[l])
                {
                    return false;
                }
            }
        }
        if(index > 1)
        {
            for(int i = 1; i < 3; i++)
            {
                if(((*rnds)[level][index - i].value - (*means)[level]) > 2 * (*sds)[level])
                {
                    return false;
                }
            }
        }

    }
    else if(((*rnds)[level][index].value - (*means)[level]) < -2 * (*sds)[level])
    {
        for(int l = 0; l < (*rnds).count(); l++)
        {
            if(l == level)
            {
                continue;
            }

            if(index < (*rnds)[l].count())
            {
                if(((*rnds)[l][index].value - (*means)[l]) < -2 * (*sds)[l])
                {
                    return false;
                }
            }
        }

        if(index > 1)
        {
            for(int i = 1; i < 3; i++)
            {
                if(((*rnds)[level][index - i].value - (*means)[level]) < -2 * (*sds)[level])
                {
                    return false;
                }
            }
        }
    }

//    int InValidCount = 0;

//    QVector<QVector<int> > indexs;
//    indexs.resize((*rnds).count());
//    for(int l = 0; l < (*rnds).count(); l++)
//    {
//        bool flag = false;
//        for(int i = 0; i < (*rnds)[l].count(); i++)
//        {
//            if((*rnds)[l][i].TestTime == (*rnds)[level][index].TestTime)
//            {
//                indexs[l].push_back(i);
//                flag = true;
//                break;
//            }
//        }

//        if(!flag)
//        {
//            indexs[l].push_back(-1);
//        }
//    }

//    if(index == 0)  //第一个点，只能与批内其他水平比较
//    {
//        if((*rnds).count() >= 3)
//        {
//            if((*rnds)[level][index].value- (*means)[level] > 2 * (*sds)[level])
//            {
//                for(int l = 0; l < (*rnds).count(); l++)
//                {
//                    if((*rnds).count() >= 1)
//                    {
//                        if((*rnds)[l][index].value- (*means)[l] > 3 * (*sds)[l])
//                        {
//                            InValidCount++;
//                        }
//                        if(InValidCount >= 3)
//                        {
//                            return false;
//                        }
//                    }
//                }
//            }
//            else
//            {
//                for(int l = 0; l < (*rnds).count(); l++)
//                {
//                    if((*rnds).count() >= 1)
//                    {
//                        if((*rnds)[l][index].value- (*means)[l] < -2 * (*sds)[l])
//                        {
//                            InValidCount++;
//                        }
//                        if(InValidCount >= 3)
//                        {
//                            return false;
//                        }
//                    }
//                }
//            }
//        }
//    }

//    if(index == 1)  //第二个点，先批内，再批间
//    {
//        if((*rnds)[level][index].value- (*means)[level] > 2 * (*sds)[level])
//        {
//            InValidCount++;
//            for(int i =  0; i < 2; i++)
//            {

//                for(int l = 0; l < (*rnds).count(); l++)
//                {
//                    if((*rnds)[l][i].value- (*means)[l] > 2 * (*sds)[l])
//                    {
//                        InValidCount++;
//                    }

//                    if(InValidCount >= 3)
//                    {
//                        return false;
//                    }
//                }
//            }
//        }
//        else
//        {
//            InValidCount++;
//            for(int i =  0; i < 2; i++)
//            {

//                for(int l = 0; l < (*rnds).count(); l++)
//                {
//                    if((*rnds)[l][i].value- (*means)[l] < -2 * (*sds)[l])
//                    {
//                        InValidCount++;
//                    }

//                    if(InValidCount >= 3)
//                    {
//                        return false;
//                    }
//                }
//            }
//        }
//    }

//    if(index >= 2)
//    {
//        if (((*rnds)[level][index].value - (*means)[level]) > 2 * (*sds)[level])
//        {
//            if((*rnds)[level][index].ResultNum > 3) //批内该水平内
//            {
//                if (((*rnds)[level][index - 1].value - (*means)[level]) > 2 * (*sds)[level]
//                    ||((*rnds)[level][index - 2].value - (*means)[level]) > 2 * (*sds)[level])
//                {
//                    return false;
//                }
//            }
//            else
//            {
//                for(int i = 0; i < 3; i++)  //先批内再批间
//                {
//                    if(index >= i)
//                    {
//                        for(int l = 0; l < (*rnds).count(); l++)
//                        {
//                            if((i == 0) && (l == level))
//                            {
//                                continue;
//                            }

//                            if(indexs[l][0] != -1
//                                    &&((*rnds)[l].count() > indexs[l][0] + (*rnds)[level][index].ResultNum - 1 - i)
//                                    &&((*rnds)[level][index].TestTime.compare((*rnds)[l][indexs[l][0] + (*rnds)[level][index].ResultNum - 1].TestTime) == 0)
//                             )
//                            {
//                                if((*rnds)[l][indexs[l][0] + (*rnds)[level][index].ResultNum - 1 - i].value - (*means)[l] > 2 * (*sds)[l])
//                                {
//                                    return false;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        else if (((*rnds)[level][index].value - (*means)[level]) < -2 * (*sds)[level])
//        {

//            if((*rnds)[level][index].ResultNum > 3) //批内该水平内
//            {
//                if (((*rnds)[level][index - 1].value - (*means)[level]) < -2 * (*sds)[level]
//                        ||((*rnds)[level][index - 2].value - (*means)[level]) < -2 * (*sds)[level])
//                {
//                    return false;
//                }
//            }
//            else
//            {
//                for(int i = 0; i < 3; i++)  //先批内再批间
//                {
//                    if(index >= i)
//                    {
//                        for(int l = 0; l < (*rnds).count(); l++)
//                        {
//                            if((i == 0) && (l == level))
//                            {
//                                continue;
//                            }

//                            if(indexs[l][0] != -1
//                                    &&((*rnds)[l].count() > indexs[l][0] + (*rnds)[level][index].ResultNum - 1 - i)
//                                    &&((*rnds)[level][index].TestTime.compare((*rnds)[l][ indexs[l][0] + (*rnds)[level][index].ResultNum - 1 ].TestTime) == 0)
//                                    )
//                            {
//                                if((*rnds)[l][indexs[l][0] + (*rnds)[level][index].ResultNum - 1 - i].value - (*means)[l] < -2 * (*sds)[l])
//                                {
//                                    return false;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }

    return true;
}
