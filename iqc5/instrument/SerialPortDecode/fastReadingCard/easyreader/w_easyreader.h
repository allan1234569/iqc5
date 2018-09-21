#ifndef W_EASYREADER_H
#define W_EASYREADER_H

#include "basewindow.h"

class W_EasyReader : public BaseWindow
{
    Q_OBJECT

public:
    W_EasyReader(QWidget *parent = 0);
    ~W_EasyReader();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    qint32 m_nItemIndex;
    qint32 m_nSampleDateIndex;
    qint32 m_nSampleNoIndex;
    qint32 m_nResultIndex;
};

#endif // W_EASYREADER_H
