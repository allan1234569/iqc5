#ifndef Rule2of32S_H
#define Rule2of32S_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule2of32S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule2of32S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // Rule2of32S_H
