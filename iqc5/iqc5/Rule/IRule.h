#ifndef IRule_H
#define IRule_H

#include "Result.h"
#include <QDebug>

class IRule
{
public:
    /**
     * @brief GetValidCount 获取某个水平有效数据个数
     * @param level         0,1分别表示水平1,2
     * @return
     */
    virtual int GetValidCount(int level) = 0;

    /**
     * @brief IsValid   判断控制数据是否失控
     * @param level     0,1分别表示水平1,2
     * @param index
     * @return
     */
    virtual bool IsValid(int level, int index) = 0;

    bool accept();

};

#endif // IRule_H
