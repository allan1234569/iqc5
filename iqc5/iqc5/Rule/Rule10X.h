#ifndef Rule10X_H
#define Rule10X_H

#include "IRule.h"
#include <QVector>
#include <QString>

class Rule10X : public IRule
{
private:
    QVector<double> *means;
    QVector<double> *sds;
    QVector< QVector<Result> > *rnds;

public:
    /**
     * @brief Rule10X
     * @param means     均值
     * @param variances 方差
     * @param rnds      数据
     */
    Rule10X(QVector<double> &means, QVector<double> &sds, QVector<QVector<Result> > &rnds);

    int GetValidCount(int level);

    bool IsValid(int level, int index);
};

#endif // Rule10X_H
