#include "interface.h"


LisInterface *CreateInterface()
{
    return new zhiFangLisInterface();
}


void ReleaseInterface(LisInterface *interface)
{
    delete interface;
    interface = NULL;
}
