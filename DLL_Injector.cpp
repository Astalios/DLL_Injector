// DLL_Injector.cpp : This file contains the 'main' function. Program execution begins and ends there.
// THIS THIS BUILT FOR A 32 BIT APP

#include <iostream>
#include "proc.h"
#include <Windows.h>
#include <TlHelp32.h>

int main()
{
    const char* dllPath = "C:\\Users\\astalios\\Documents\\Visual Studio 2019\\Projects\\assaultCube_internalTrainer\\Debug\\internalHack.dll";
    const char* procName = "ac_client.exe";
    DWORD procId = 0;
    
    while (!procId)
    {
        procId = GetProcId(procName);
        Sleep(30);
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

        HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, nullptr);

        std::cout << "Injection Reussie !" << std::endl;

        if (hThread)
        {
            CloseHandle(hThread);
        }
    }

    if (hProc)
    {
        CloseHandle(hProc);
    }
    getchar();
    return 0;
}