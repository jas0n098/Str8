#include <windows.h>
#include <psapi.h>
#include <stdint.h>

#include "memory.h"

void Patch()
{
    HMODULE modBase = GetModuleHandle(NULL);

    MODULEINFO modInfo;
    GetModuleInformation(GetCurrentProcess(), modBase, &modInfo, sizeof(modInfo));

    DWORD oldProtect;

    int16_t * bypass = (int16_t *)ScanBasic("\x74\x54\xb9\x02\x00\x00\x80\x00\x00\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x84\xc0\x74\x07\xb8\xfe\xff\xff\xff", "xxxxxxx??????x????xxxxxxxxx", (void *)modBase, modInfo.SizeOfImage);
    if (!bypass)
    {
        return;
    }
    VirtualProtect(bypass, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
    *bypass = 0x9090; // 2 NOPs
    VirtualProtect(bypass, 2, oldProtect, &oldProtect);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        Patch();
    }

    return TRUE;
}
