#ifndef RULE31S_H
#define RULE31S_H
#include "IRule.h"
#include <QVector>

class Rule31S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule31S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // RULE31S_H
