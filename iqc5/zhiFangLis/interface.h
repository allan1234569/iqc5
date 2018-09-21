#ifndef INTERFACE_H
#define INTERFACE_H

#include "zhiFangInterface.h"

// extern "C" 生成的导出符号没有任何修饰，方便主程序找到它
extern "C"
{
    Q_DECL_EXPORT LisInterface* CreateInterface();
    Q_DECL_EXPORT void ReleaseInterface(LisInterface* interface);
}

#endif // INTERFACE_H
