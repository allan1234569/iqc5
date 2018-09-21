#include "MachineCode.h"
#include <QString>

#include <windows.h>
#include <QString>
#include <QDebug>
#include <QNetworkInterface>
#include <QCryptographicHash>
#include <QClipboard>
#ifdef __GNUC__
#include <cpuid.h>
#elif defined(_MSC_VER)
#if _MSC_VER >= 1400
#include <intrin.h>
#endif
#else
#error Only supports MSVC or GCC
#endif

MachineCode::MachineCode()
{
}

MachineCode::~MachineCode()
{

}


QStringList MachineCode::get_mac()
{
    QStringList mac_list;
    QString strMac;
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for (int i=0; i<ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        //过滤掉本地回环地址、没有开启的地址
        if (iface.flags().testFlag(QNetworkInterface::IsUp) && !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            //过滤掉虚拟地址
            if (!(iface.humanReadableName().contains("VMware",Qt::CaseInsensitive)))
            {
                strMac = iface.hardwareAddress();
                mac_list.append(strMac);
            }
        }
    }
    return mac_list;
}

void MachineCode::getcpuid(unsigned int CPUInfo[4], unsigned int InfoType)
{
#if defined(__GNUC__)// GCC
    __cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)// MSVC
#if _MSC_VER >= 1400 //VC2005才支持__cpuid
    __cpuid((int*)(void*)CPUInfo, (int)(InfoType));
#else //其他使用getcpuidex
    getcpuidex(CPUInfo, InfoType, 0);
#endif
#endif
}

void MachineCode::getcpuidex(unsigned int CPUInfo[], unsigned int InfoType, unsigned int ECXValue)
{
#if defined(_MSC_VER) // MSVC
#if defined(_WIN64)	// 64位下不支持内联汇编. 1600: VS2010, 据说VC2008 SP1之后才支持__cpuidex.
    __cpuidex((int*)(void*)CPUInfo, (int)InfoType, (int)ECXValue);
#else
    if (NULL==CPUInfo)	return;
    _asm{
        // load. 读取参数到寄存器.
        mov edi, CPUInfo;
        mov eax, InfoType;
        mov ecx, ECXValue;
        // CPUID
        cpuid;
        // save. 将寄存器保存到CPUInfo
        mov	[edi], eax;
        mov	[edi+4], ebx;
        mov	[edi+8], ecx;
        mov	[edi+12], edx;
    }
#endif
#endif
}

QString MachineCode::get_cpuId()
{
    QString cpu_id = "";
    unsigned int dwBuf[4];
    unsigned long long ret;
    getcpuid(dwBuf, 1);
    ret = dwBuf[3];
    ret = ret << 32;
    cpu_id = QString::number(dwBuf[3], 16).toUpper();
    cpu_id = cpu_id + QString::number(dwBuf[0], 16).toUpper();
    return cpu_id;
}

QString MachineCode::getMachineCode()
{
    QString machineInfo="";
    machineInfo.append(get_cpuId());
    machineInfo.append("@");
    QStringList mac_list;
    QString mac;
    for(int i = 0; i < mac_list.size(); i++)
    {
        mac.append(mac_list.at(i));
    }

    machineInfo.append(mac);

    QCryptographicHash sha1(QCryptographicHash::Sha1);

    QByteArray datagram(machineInfo.toStdString().data());
    const char* tempConstChar = datagram.data();
    sha1.addData(tempConstChar);
    QString  machineCode=sha1.result().toHex();

    return machineCode;
}

QString MachineCode::calAccreditCode(QString machineCode)
{
    QCryptographicHash sha1(QCryptographicHash::Sha1);

    QByteArray datagram(machineCode.toLatin1());
    const char* tempConstChar = datagram.data();
    sha1.addData(tempConstChar);
    QString  activeCode=sha1.result().toHex();

    return activeCode;
}
