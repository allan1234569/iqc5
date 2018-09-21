#ifndef Rule41S_H
#define Rule41S_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule41S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule41S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // Rule41S_H
