#include "CheatTutorial.h"

int main()
{    
    std::cout << "Enter Process ID: ";
    DWORD pid{};
    std::cin >> pid;
    
    getProcessHandle(pid);
    

    std::cout << "Enter address of first pointer to read a three pointer chain: 0x";
    long long intRead;
    std::cin >> std::hex >> intRead;

    //Follow pointer chain outputting address an values to console
    std::cout << "Reading 0x" << std::hex << intRead << "..." << '\n' << '\n';
    readTargetMemory(hProcess, intRead, sizeof(long long), &intRead);
    std::cout << "First Pointer Contains            = " << std::hex << intRead << '\n';
    readTargetMemory(hProcess, intRead, sizeof(long long), &intRead);
    std::cout << "Second Pointer Contains           = " << std::hex << intRead << '\n';
    readTargetMemory(hProcess, intRead, sizeof(long long), &intRead);
    std::cout << "Final Pointer Contains            = " << std::hex << intRead << '\n';
    int intStore{};
    readTargetMemory(hProcess, intRead, sizeof(int), &intStore);
    std::cout << "Integer value pointers lead us to = "  << std::dec << intStore << '\n' << '\n';

    //Ask user for string variable address and read value
    std::cout << "Enter address containing string value: 0x";
    std::cin >> std::hex >> intRead;
    std::string strRead{};
    readTargetMemory(hProcess, intRead, sizeof(std::string), &strRead);
    std::cout << "String value at" << std::hex << intRead << " is: " << strRead << '\n' << '\n';

    //Ask user for char array address and read value
    std::cout << "Enter address containing char array value: 0x";
    std::cin >> std::hex >> intRead;
    char arrRead[128]{};
    readTargetMemory(hProcess, intRead, sizeof(arrRead), &arrRead);
    std::cout << "Char array value at " << std::hex << intRead << " is: " << arrRead << '\n' << '\n';

    std::cout << "Enter address of integer to write: 0x";
    std::cin >> std::hex >> intRead;
    int intToWrite{};
    std::cout << "Enter integer value to write to process: ";
    std::cin >> std::dec >> intToWrite;
    std::cout << "Writing target\n\n";
    DWORD oldProtect{};
    VirtualProtectEx(hProcess, (LPVOID)intRead, sizeof(intToWrite), PAGE_EXECUTE_READWRITE, &oldProtect);
    writeTargetMemory(hProcess, intRead, sizeof(intToWrite), &intToWrite);
    VirtualProtectEx(hProcess, (LPVOID)intRead, sizeof(intToWrite), oldProtect, &oldProtect);

    std::cout << "Enter address of string to write: 0x";
    std::cin >> std::hex >> intRead;
    std::string strToWrite{};
    std::cout << "Enter string to write to process: ";
    std::cin >> strToWrite;
    std::cout << "Writing target\n\n";
    VirtualProtectEx(hProcess, (LPVOID)intRead, sizeof(strToWrite), PAGE_EXECUTE_READWRITE, &oldProtect);
    writeTargetMemory(hProcess, intRead, sizeof(strToWrite), &strToWrite);
    VirtualProtectEx(hProcess, (LPVOID)intRead, sizeof(strToWrite), oldProtect, &oldProtect);

    std::cout << "Enter address of char array to write: 0x";
    std::cin >> std::hex >> intRead;
    char arrToWrite[128]{};
    std::cout << "Enter char array to write to process: ";
    std::cin >> arrToWrite;
    std::cout << "Writing target\n\n";
    VirtualProtectEx(hProcess, (LPVOID)intRead, sizeof(arrToWrite), PAGE_EXECUTE_READWRITE, &oldProtect);
    writeTargetMemory(hProcess, intRead, sizeof(arrToWrite), &arrToWrite);
    VirtualProtectEx(hProcess, (LPVOID)intRead, sizeof(arrToWrite), oldProtect, &oldProtect);

    //Pause and exit after keypress
    std::cout << "Press ENTER to exit.";
    system("pause");

    //If handle exists close it
    if (hProcess != NULL) {
        CloseHandle(hProcess);
    }
}
//Get handle with permissions
void getProcessHandle(DWORD proID) {
    hProcess = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE, false, proID);
    if (hProcess == NULL) {
        std::cout << "OpenProcess failed. GetLastError = " << std::dec << GetLastError() << '\n';
        system("pause");
    }
}

void readTargetMemory(HANDLE Handle, long long memAddress, SIZE_T varSize, LPVOID storageLoc) {
    BOOL rpmReturn{ ReadProcessMemory(
        Handle,
        (LPCVOID)memAddress,
        storageLoc,
        varSize,
        NULL) };
    if (rpmReturn == FALSE) {
        std::cout << "ReadProcessMemory failed. GetLastError = " << std::dec << GetLastError() << '\n';
        system("pause");
        exit(1);
    }
}

void writeTargetMemory(HANDLE Handle, long long memAddress, SIZE_T varSize, LPVOID storageLoc) {
    BOOL wpmReturn{ WriteProcessMemory(
        Handle,
        (LPVOID)memAddress,
        storageLoc,
        varSize,
        NULL) };
    if (wpmReturn == FALSE) {
        std::cout << "WriteProcessMemory failed. GetLastError = " << std::dec << GetLastError() << '\n';
        system("pause");
        exit(1);
    }
}
