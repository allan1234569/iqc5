#ifndef MACHINECODE_H
#define MACHINECODE_H

#include <QStringList>

const QString MACHINE_CODE_PATH = "HKEY_LOCAL_MACHINE/SOFTWARE/iqc5/setting";

class MachineCode
{
public:
    MachineCode();
    ~MachineCode();

    /**
     * @brief get_mac   获取机器的Mac地址
     * @return
     */
    QStringList get_mac();

    void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType);

    void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);

    QString get_cpuId();

    QString getMachineCode();

    QString calAccreditCode(QString machineCode);
};

#endif // MACHINECODE_H
