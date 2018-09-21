#ifndef W_HC9884_H
#define W_HC9884_H

#include "basewindow.h"

class W_Hc9884 : public BaseWindow
{
    Q_OBJECT

public:
    W_Hc9884(QWidget *parent = 0);
    ~W_Hc9884();

    // BaseWindow interface
public:
    void decode(QString data);

    void loadConfig();

private:
    QString m_sItems;
    QStringList m_slItems;
};

#endif // W_HC9884_H
