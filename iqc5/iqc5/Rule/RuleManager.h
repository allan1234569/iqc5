#ifndef RuleManager_H
#define RuleManager_H

#include "IRule.h"
#include <QVector>
#include <QString>

class RuleManager : public IRule
{
public:
    static double GetValid(QString ruleName, QVector<double> means, QVector<double> variances, QVector<QVector<Result> > &rnds, int level);

    static IRule* GetRule(QString ruleName, QVector<double> &means, QVector<double> &variances, QVector<QVector<Result> > &rnds);
};

#endif // RuleManager_H
