#ifndef Rule22S_H
#define Rule22S_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule22S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule22S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // Rule22S_H
