#ifndef RULE12DOT5S_H
#define RULE12DOT5S_H

#include "IRule.h"
#include <QVector>

class Rule12dot5S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule12dot5S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // RULE12DOT5S_H
