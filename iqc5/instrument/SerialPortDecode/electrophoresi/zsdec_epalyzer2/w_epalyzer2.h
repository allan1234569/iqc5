#ifndef W_EPALYZER2_H
#define W_EPALYZER2_H

#include "basewindow.h"

class W_Epalyzer2 : public BaseWindow
{
    Q_OBJECT

public:
    W_Epalyzer2(QWidget *parent = 0);
    ~W_Epalyzer2();

    // BaseWindow interface
public:
    void loadConfig();

    void decode(QString data);

private:
    int m_nSampleNoStart;   //样本号
    int m_nSampleNoLen;

    int m_nSampleDateStart; //样本日期
    int m_nSampleDateLen;

    int m_nResultSegStart;
    int m_nResultSegLen;

    int m_nItemStart;       //项目
    int m_nItemLen;

    int m_nResultStart;     //结果
    int m_nResultLen;

};

#endif // W_EPALYZER2_H
