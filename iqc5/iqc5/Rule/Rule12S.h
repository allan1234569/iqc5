#ifndef Rule12S_H
#define Rule12S_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule12S : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule12S(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);
    bool IsValid(int level, int index);

};

#endif // Rule12S_H
