#define FLG_HEAP_ENABLE_TAIL_CHECK 0x10
#define FLG_HEAP_ENALBLE_FREE_CHECK 0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENALBLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

extern "C" void* GetKernel32BaseAddress();

_PEB* peb;

typedef HMODULE(__stdcall* _LOADLIBRARYA)(IN LPCSTR lpLibFileName);
_LOADLIBRARYA _LoadLibraryA;

typedef DWORD(__stdcall* _GETCURRENTPROCESSID)();
_GETCURRENTPROCESSID _GetCurrentProcessId;

typedef PVOID(__stdcall* _GETSYSTEMINFO)(OUT LPSYSTEM_INFO lpSystemInfo);
_GETSYSTEMINFO _GetSystemInfo;

typedef BOOL(__stdcall* _GLOBALMEMORYSTATUSEX)(IN OUT LPMEMORYSTATUSEX lpBuffer);
_GLOBALMEMORYSTATUSEX _GlobalMemoryStatusEx;

typedef HANDLE(__stdcall* _CREATETOOLHELP32SNAPSHOT)(IN DWORD dwFlags, IN DWORD th32ProcessID);
_CREATETOOLHELP32SNAPSHOT _CreateToolhelp32Snapshot;

typedef BOOL(__stdcall* _PROCESS32FIRSTW)(IN HANDLE hSnapshot, IN OUT LPPROCESSENTRY32W lppe);
_PROCESS32FIRSTW _Process32FirstW;

typedef BOOL(__stdcall* _PROCESS32NEXTW)(IN HANDLE hSnapshot, OUT LPPROCESSENTRY32W lppe);
_PROCESS32NEXTW _Process32NextW;

typedef BOOL(__stdcall* _CLOSEHANDLE)(IN HANDLE hObject);
_CLOSEHANDLE _CloseHandle;

typedef BOOL(__stdcall* _GETCOMPUTERNAMEW)(OUT LPWSTR lpBuffer, IN OUT LPDWORD nSize);
_GETCOMPUTERNAMEW _GetComputerNameW;

typedef BOOL(__stdcall* _ISDEBUGGERPRESENT)();
_ISDEBUGGERPRESENT _IsDebuggerPresent;

typedef __kernel_entry NTSTATUS(__stdcall* _NTQUERYINFORMATIONPROCESS)(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT OPTIONAL PULONG ReturnLength);
_NTQUERYINFORMATIONPROCESS _NtQueryInformationProcess;

typedef VOID(__stdcall* _SETLASTERROR)(IN DWORD dwErrCode);
_SETLASTERROR _SetLastError;

typedef _Post_equals_last_error_ DWORD(__stdcall* _GETLASTERROR)();
_GETLASTERROR _GetLastError;

typedef VOID(__stdcall* _OUTPUTDEBUGSTRINGA)(IN OPTIONAL LPCSTR lpOutputString);
_OUTPUTDEBUGSTRINGA _OutputDebugStringA;