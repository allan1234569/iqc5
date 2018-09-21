#ifndef W_REPID_H
#define W_REPID_H

#include "basewindow.h"

class W_Repid : public BaseWindow
{
    Q_OBJECT

public:
    W_Repid(QWidget *parent = 0);
    ~W_Repid();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    QStringList m_slItems;
};

#endif // W_REPID_H
