#ifndef RULE14S_H
#define RULE14S_H
#include "IRule.h"
#include <QVector>

class Rule14S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule14S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // RULE14S_H
