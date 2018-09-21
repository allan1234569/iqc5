#ifndef Rule13S_H
#define Rule13S_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule13S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule13S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // Rule13S_H
