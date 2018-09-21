#ifndef FORMULA_H
#define FORMULA_H

#include <QVector>
#include <stdarg.h>
#include <math.h>
#include <QMap>

template<typename T>
T GetAverage(int n_value,...)
{
    va_list var_arg;
    T sum = 0;
    va_start(var_arg,n_value);
    for(int i = 0; i < n_value; i++)
    {
        sum += va_arg(var_arg,int);
    }
    va_end(var_arg);
    return sum/n_value;
}

template<typename T>
T GetAverage(QVector<T> &vec)
{
    T sum = 0;
    foreach (T data, vec) {
        sum += data;
    }
    return sum/vec.count();
}

template<typename T>
T GetAverage(QMap<int,T> &map)
{
    T sum = 0;
    foreach (T data, map) {
        sum += data;
    }
    return sum/map.count();
}


/**
 * @brief GetStandardDeviation 计算标准差
 * @param vec
 * @return
 */
template<typename T>
T GetStandardDeviation(QVector<T> vec)
{
    T av = GetAverage(vec);
    int count = vec.size();
    T value = 0;
    T sum = 0;
    for(int i = 0; i < count; i++)
    {
        value = vec.at(i);
        sum += (av -value)*(av -value);
    }
    sum = sum/(count-1);
    return sqrtf(sum);
}

template<typename T>
T GetStandardDeviation(QMap<int,T> map)
{
    T av = GetAverage(map);
    T sum = 0;
    foreach (T data, map) {
       sum += (av -data)*(av -data);
    }
    sum = sum/(map.size()-1);
    return sqrtf(sum);
}

#endif // FORMULA_H
