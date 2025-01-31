#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

DWORD GetProcessID(const wchar_t* processName) {
    DWORD processID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W pe;
        pe.dwSize = sizeof(pe);
        if (Process32FirstW(hSnap, &pe)) {
            do {
                if (!_wcsicmp(pe.szExeFile, processName)) {
                    processID = pe.th32ProcessID;
                    break;
                }
            } while (Process32NextW(hSnap, &pe));
        }
        CloseHandle(hSnap);
    }
    return processID;
}

uintptr_t GetModuleBaseAddress(DWORD processID, const wchar_t* moduleName) {
    uintptr_t baseAddress = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32FirstW(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, moduleName)) {
                    baseAddress = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnap, &modEntry));
        }
        CloseHandle(hSnap);
    }
    return baseAddress;
}

uintptr_t GetPointerAddress(HANDLE hProcess, uintptr_t baseAddress, std::vector<uintptr_t> offsets) {
    uintptr_t addr = baseAddress;
    for (uintptr_t offset : offsets) {
        ReadProcessMemory(hProcess, (LPCVOID)addr, &addr, sizeof(addr), nullptr);
        addr += offset;
    }
    return addr;
}

bool WriteMemory(HANDLE hProcess, uintptr_t address, int value) {
    SIZE_T bytesWritten;
    return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), &bytesWritten);
}

int main() {
    const wchar_t* processName = L"Starrail.exe";
    const wchar_t* moduleName = L"UnityPlayer.dll";
    int newValue = 0;

    DWORD processID = GetProcessID(processName);
    if (processID == 0) {
        std::cout << "Process not found" << std::endl;
        return 1;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (!hProcess) {
        std::cout << "Process access error" << std::endl;
        return 1;
    }

    uintptr_t moduleBase = GetModuleBaseAddress(processID, moduleName);
    if (!moduleBase) {
        std::cout << "Module" << moduleName << " not found" << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    // FPS1 (UnityPlayer.dll + 01DE9070) → [ +20 ]
    uintptr_t fps1Address = GetPointerAddress(hProcess, moduleBase + 0x01DE9070, { 0x20 });

    // FPS2 (UnityPlayer.dll + 01C9A860) → [ +50 ]
    uintptr_t fps2Address = GetPointerAddress(hProcess, moduleBase + 0x01C9A860, { 0x50 });

    if (WriteMemory(hProcess, fps1Address, newValue)) {
        std::cout << "Value at address " << std::hex << fps1Address << " successfully changed" << std::endl;
    }
    else {
        std::cout << "Error writing to memory at address " << std::hex << fps1Address << std::endl;
    }

    if (WriteMemory(hProcess, fps2Address, newValue)) {
        std::cout << "Value at address " << std::hex << fps2Address << " successfully changed" << std::endl;
    }
    else {
        std::cout << "Error writing to memory at address " << std::hex << fps2Address << std::endl;
    }

    CloseHandle(hProcess);
    system("pause");
    return 0;
}
