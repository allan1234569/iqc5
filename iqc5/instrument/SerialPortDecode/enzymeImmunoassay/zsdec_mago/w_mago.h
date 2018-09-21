#ifndef W_MAGO_H
#define W_MAGO_H

#include "basewindow.h"

class W_Mago : public BaseWindow
{
    Q_OBJECT

public:
    W_Mago(QWidget *parent = 0);
    ~W_Mago();

    QString getItemNo(QString as_item);

    /**
     * @brief getResult 获取定性结果
     * @param as_result
     * @return
     */
    QString getResult(QString as_result);

    // BaseWindow interface
public:
    void decode(QString data);

};

#endif // W_MAGO_H
