#include "Rule41S.h"
#include <math.h>

Rule41S::Rule41S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->sds = &sds;
    this->rnds = &rnds;
}

int Rule41S::GetValidCount(int level)
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

bool Rule41S::IsValid(int level, int index)
{
    int InvalidCount = 0;   //无效值个数
    bool preHasFound = false;   //前一批失控
    bool flag;  //连续性检测标志

    if(index < (*rnds)[level].count())
    {
        if(((*rnds)[level][index].value - (*means)[level]) > (*sds)[level])
        {
            for(int l = 0; l < (*rnds).count(); l++)
            {
                if(index < (*rnds)[l].count())
                {
                    if(((*rnds)[l][index].value - (*means)[l]) > (*sds)[l])
                    {
                        for(int i = 0; i < (*rnds)[l].count(); i++)
                        {
                            if(((*rnds)[l][index - i].value - (*means)[l]) > (*sds)[l])
                            {
                                InvalidCount++;
                            }
                            else
                            {
                                break;
                            }

                            if(InvalidCount >= 4)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        else if(((*rnds)[level][index].value - (*means)[level]) < -(*sds)[level])
        {
            for(int l = 0; l < (*rnds).count(); l++)
            {
                if(index < (*rnds)[l].count())
                {
                    if(((*rnds)[l][index].value - (*means)[l]) < -(*sds)[l])
                    {
                        for(int i = 0; i < (*rnds)[l].count(); i++)
                        {
                            if(((*rnds)[l][index - i].value - (*means)[l]) < -(*sds)[l])
                            {
                                InvalidCount++;
                            }
                            else
                            {
                                break;
                            }

                            if(InvalidCount >= 4)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

//    if(index < (*rnds)[level].count())
//    {
//        if(fabs((*rnds)[level][index].value - (*means)[level]) < (*sds)[level])
//        {
//                return true;
//        }

//        if (((*rnds)[level][index].value - (*means)[level]) > 0)
//        {
//            for (int i = 0; i < 2; i++)
//            {
//                if(index >= i)
//                {
//                    flag = false;
//                    for(int l = 0; l < rnds->count(); l++)
//                    {
//                        if(index < (*rnds)[l].count())
//                        {
//                            if(((*rnds)[l][index - i].value - (*means)[l]) > (*sds)[l])
//                            {
//                                InvalidCount++;
//                                flag = true;
//                            }
//                            else
//                            {
////                                InvalidCount = 0;
////                                flag = false;
////                                break;
//                            }

//                            if(preHasFound && InvalidCount >= 4)
//                            {
//                                return false;
//                            }
//                        }
//                    }

//                    preHasFound = flag;
//                }

//                if(!preHasFound)
//                {
//                    return true;
//                }
//            }


//            InvalidCount = 0;
//            if((*rnds)[level].count() >= 4)
//            {
//                for(int i = 0; i < 4; i++)
//                {
//                    if((*rnds)[level][index - i].value - (*means)[level] > (*sds)[level])
//                    {
//                        InvalidCount++;
//                    }
//                    if(InvalidCount >= 4)
//                    {
//                        return false;
//                    }
//                }
//            }

//        }
//        else
//        {
//            for (int i = 0; i < 2; i++)
//            {
//                if(index >= i)
//                {
//                    flag = false;
//                    for(int l = 0; l < rnds->count(); l++)
//                    {
//                        if(index < (*rnds)[l].count())
//                        {
//                            if( ((*means)[l] - (*rnds)[l][index - i].value) > (*sds)[l])
//                            {
//                                InvalidCount++;
//                                flag = true;
//                            }
//                            else
//                            {
////                                InvalidCount = 0;
////                                flag = false;
////                                break;
//                            }

//                        }

//                        if(preHasFound && InvalidCount >= 4)
//                        {
//                            return false;
//                        }

//                        preHasFound = flag;
//                    }
//                }

//                if(!preHasFound)
//                {
//                    return true;
//                }
//            }


//            InvalidCount = 0;
//            if((*rnds)[level].count() >= 4)
//            {
//                for(int i = 0; i < 4; i++)
//                {
//                    if((*rnds)[level][index - i].value - (*means)[level] < (*sds)[level])
//                    {
//                        InvalidCount++;
//                    }
//                    if(InvalidCount >= 4)
//                    {
//                        return false;
//                    }
//                }
//            }


//        }
//    }

    return true;
}
