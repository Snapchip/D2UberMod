#include "framework.h"
#include "D2UberMod.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        return D2UberMod::OnAttach(hModule, lpReserved);       
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        return D2UberMod::OnDetach();       
    }
    return TRUE;
}

