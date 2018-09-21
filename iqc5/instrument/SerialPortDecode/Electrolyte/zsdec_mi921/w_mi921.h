#ifndef W_MI921_H
#define W_MI921_H

#include "basewindow.h"

class W_Mi921 : public BaseWindow
{
    Q_OBJECT

public:
    W_Mi921(QWidget *parent = 0);
    ~W_Mi921();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

    void decode_autoCrLf(QString data);

private:
    QString m_sItems;
    QStringList m_slItems;
    bool m_bAutoCrLf;
    bool m_bLastHaveData;
};

#endif // W_MI921_H
