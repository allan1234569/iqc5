#include "RuleWestgard.h"
#include "RuleManager.h"
#include "IRule.h"
#include "Rule10X.h"
#include "Rule12S.h"
#include "Rule13S.h"
#include "Rule22S.h"
#include "Rule2of32S.h"
#include "Rule41S.h"
#include "Rule6T.h"
#include "Rule9X.h"
#include "RuleR4S.h"
#include <math.h>
#include <QDebug>

//RuleWestgard::RuleWestgard(double mean, double variance, QVector<double> &rnds)
//{
//    this->mean = mean;
//    this->variance = variance;
//    this->rnds = &rnds;

//    rule12S = new Rule12S (mean, variance, rnds);
//    rule13S = new Rule13S (mean, variance, rnds);
//    rule22S = new Rule22S (mean, variance, rnds);
//    ruleR4S = new RuleR4S (mean, variance, rnds);
//    rule41S = new Rule41S (mean, variance, rnds);
//    rule10X = new Rule10X (mean, variance, rnds);
//}

//int RuleWestgard::GetValidCount()
//{

//    int validCount = 0;

//    for(int i = 1; i < rnds->count(); i++)
//    {
//        if (IsValid(i))
//        {
//            validCount++;
//        }
//    }

//    return validCount;
//}

//bool RuleWestgard::IsValid(int index)
//{

//    if(rule12S->IsValid(index))
//    {
//        return true;
//    }
//    else
//    {
//        return rule13S->IsValid(index) && rule22S->IsValid(index) && ruleR4S->IsValid(index)&& rule41S->IsValid(index) && rule10X->IsValid(index);
//    }
//}


RuleWestgard::RuleWestgard(QVector<double> &means, QVector<double> &variances, QVector<QVector<Result> > &rnds)
{
    this->means = &means;
    this->variances = &variances;
    this->rnds = &rnds;

    rule12S = new Rule12S (means, variances, rnds);
    rule13S = new Rule13S (means, variances, rnds);
    rule22S = new Rule22S (means, variances, rnds);
    ruleR4S = new RuleR4S (means, variances, rnds);
    rule41S = new Rule41S (means, variances, rnds);
    rule10X = new Rule10X (means, variances, rnds);
}

int RuleWestgard::GetValidCount(int level)
{
    int validCount = 0;

    for(int i = 1; i < rnds[level].count(); i++)
    {
        if (IsValid(level,i))
        {
            validCount++;
        }
    }

    return validCount;
}

bool RuleWestgard::IsValid(int level, int index)
{
    if(rule12S->IsValid(level,index))
    {
        return true;
    }
    else
    {
        return rule13S->IsValid(level, index) && rule22S->IsValid(level, index) && ruleR4S->IsValid(level, index)&& rule41S->IsValid(level, index) && rule10X->IsValid(level, index);
    }
}
