#ifndef Rule9X_H
#define Rule9X_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule9X : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule9X(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);
    bool IsValid(int level, int index);
};

#endif // Rule9X_H
