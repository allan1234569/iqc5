#ifndef CHISQUARE_H
#define CHISQUARE_H
#include <QStringList>
#include <QMap>
#include <QMultiMap>

int DofCode[] = {
    5,  6,  7,  8,  9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 25, 30, 35, 40,
    50, 60, 70, 75, 79,
    80, 90, 100
};

double _95_[] = {
    11.1,   12.6,   14.1,   15.5,   16.9,
    18.3,   19.7,   21.0,   22.4,   23.7,
    25.0,   26.3,   27.6,   28.9,   30.1,
    31.4,   37.7,   43.8,   49.8,   55.8,
    67.5,   79.0,   90.5,   96.2,   100.7,
    101.7,  113.1,  124.3

};
double _99_[] = {
    15.1,   16.8,   18.5,   20.1,   21.7,
    23.2,   24.7,   26.2,   27.7,   29.1,
    30.6,   32.0,   33.4,   34.8,   36.2,
    37.6,   44.3,   50.9,   57.3,   63.7,
    76.2,   88.4,   100.4,  106.4,  111.1,
    112.3,  124.1,  135.6
};

double GetChiSquare(const double dof, const double alpha)   //卡方限值表
{
    double limit = 100 -alpha;
    int minIndex = 0;
    double cur_d_value, min_d_value;
    cur_d_value = min_d_value = abs(DofCode[0] - qRound(dof));
    for(int i = 1; i < sizeof(DofCode)/sizeof(int); i++)
    {
        cur_d_value = abs(DofCode[i] - qRound(dof));
        if(cur_d_value < min_d_value)
        {
            minIndex = i;
            min_d_value = cur_d_value;
        }
    }
    if(limit == 95)
        return _95_[minIndex];
    else if(limit == 99)
        return _99_[minIndex];
    else
        return -1;
}

#endif // CHISQUARE_H
