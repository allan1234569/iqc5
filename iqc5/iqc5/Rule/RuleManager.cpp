#include "RuleManager.h"
#include "Rule10X.h"
#include "Rule12S.h"
#include "Rule12dot5S.h"
#include "Rule13S.h"
#include "Rule13dot5S.h"
#include "Rule14S.h"
#include "Rule15S.h"
#include "Rule22S.h"
#include "Rule2of32S.h"
#include "Rule31S.h"
#include "Rule41S.h"
#include "Rule6T.h"
#include "Rule9X.h"
#include "RuleR4S.h"
#include "RuleWestgard.h"
#include <math.h>
#include <QDebug>

double RuleManager::GetValid(QString ruleName, QVector<double> means, QVector<double> variances, QVector<QVector<Result> > &rnds,int level)
{
    int totalCount = rnds[level].count();
    int validCount = 0;

    IRule *rule = GetRule(ruleName, means, variances, rnds);
    validCount = rule->GetValidCount(level);

    return 100.0 * validCount / totalCount;
}

IRule *RuleManager::GetRule(QString ruleName, QVector<double> &means, QVector<double> &variances, QVector<QVector<Result> > &rnds)
{

    if (QString::compare(ruleName, "12S") == 0)
    {
        return new Rule12S(means, variances, rnds);
    }
    else if(QString::compare(ruleName,"12.5S") == 0)
    {
        return new Rule12dot5S(means,variances,rnds);
    }
    else if (QString::compare(ruleName, "13S") == 0)
    {
        return new Rule13S(means, variances, rnds);
    }
    else if(QString::compare(ruleName,"13.5S") == 0)
    {
        return new Rule13dot5S(means,variances,rnds);
    }
    else if(QString::compare(ruleName,"14S") == 0)
    {
        return new Rule14S(means,variances,rnds);
    }
    else if(QString::compare(ruleName,"15S") == 0)
    {
        return new Rule15S(means,variances,rnds);
    }
    else if (QString::compare(ruleName, "22S") == 0)
    {
        return new Rule22S(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "R4S") == 0)
    {
        return new RuleR4S(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "31S") == 0)
    {
        return new Rule31S(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "41S") == 0)
    {
        return new Rule41S(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "9X") == 0)
    {
        return new Rule9X(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "10X") == 0)
    {
        return new Rule10X(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "6T") == 0)
    {
        return new Rule6T(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "2/32S") == 0)
    {
        return new Rule2of32S(means, variances, rnds);
    }
    else if (QString::compare(ruleName, "Westgard") == 0)
    {
        return new RuleWestgard(means, variances, rnds);
    }
    else
    {
       return NULL;
    }

}
