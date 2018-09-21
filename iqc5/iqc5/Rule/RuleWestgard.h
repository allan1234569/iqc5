#ifndef RULEWESTGARD_H
#define RULEWESTGARD_H

#include "IRule.h"
#include "Rule10X.h"
#include "Rule12S.h"
#include "Rule13S.h"
#include "Rule22S.h"
#include "Rule2of32S.h"
#include "Rule41S.h"
#include "Rule6T.h"
#include "Rule9X.h"
#include "RuleR4S.h"
#include <QVector>
#include <QString>

class RuleWestgard : public IRule
{
//private:
//    double mean;
//    double variance;
//    QVector<double> *rnds;

//    Rule12S *rule12S;
//    Rule13S *rule13S;
//    Rule22S *rule22S;
//    RuleR4S *ruleR4S;
//    Rule41S *rule41S;
//    Rule10X *rule10X;

//public:
//    RuleWestgard(double mean, double variance, QVector<double> &rnds);
//    int GetValidCount();
//    bool IsValid(int index);

    private:
        QVector<double> *means;
        QVector<double>  *variances;
        QVector< QVector<Result> > *rnds;

        Rule12S *rule12S;
        Rule13S *rule13S;
        Rule22S *rule22S;
        RuleR4S *ruleR4S;
        Rule41S *rule41S;
        Rule10X *rule10X;

    public:
        RuleWestgard(QVector<double> &means, QVector<double> &variances, QVector<QVector<Result> > &rnds);

        int GetValidCount(int level);
        bool IsValid(int level, int index);
};

#endif // RULEWESTGARD_H
