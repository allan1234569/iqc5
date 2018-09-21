#ifndef RuleR4S_H
#define RuleR4S_H

#include "IRule.h"
#include <QVector>
#include <QString>

class RuleR4S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    RuleR4S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);
    bool IsValid(int level, int index);
};

#endif // RuleR4S_H
