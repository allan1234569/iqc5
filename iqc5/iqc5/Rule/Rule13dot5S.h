#ifndef RULE13DOT5S_H
#define RULE13DOT5S_H

#include "IRule.h"
#include <QVector>

class Rule13dot5S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule13dot5S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);
    int GetValidCount(int level);
    bool IsValid(int level, int index);
};

#endif // RULE13DOT5S_H
