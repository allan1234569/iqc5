#ifndef Rule6T_H
#define Rule6T_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule6T : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    Rule6T(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);
    bool IsValid(int level, int index);
};

#endif // Rule6X_H
