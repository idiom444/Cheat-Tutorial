#include "CheatTutorial.h"

int main()
{
    DWORD pid{};

    std::cout << "Enter Process ID: ";
    std::cin >> pid;
    
    getReadProcessHandle(pid);
    getWriteProcessHandle(pid);

    std::cout << "Enter address of first pointer to read a three pointer chain: 0x";
    long long intRead;
    std::cin >> std::hex >> intRead;

    //Follow pointer chain outputting address an values to console
    std::cout << "Reading 0x" << std::hex << intRead << "..." << '\n' << '\n';
    readTargetMemory(hReadProcess, intRead, sizeof(long long), &intRead);
    std::cout << "First Pointer Contains            = " << std::hex << intRead << '\n';
    readTargetMemory(hReadProcess, intRead, sizeof(long long), &intRead);
    std::cout << "Second Pointer Contains           = " << std::hex << intRead << '\n';
    readTargetMemory(hReadProcess, intRead, sizeof(long long), &intRead);
    std::cout << "Final Pointer Contains            = " << std::hex << intRead << '\n';
    int intStore{};
    readTargetMemory(hReadProcess, intRead, sizeof(long long), &intStore);
    std::cout << "Integer value pointers lead us to = "  << std::dec << intStore << '\n' << '\n';

    //Ask user for string variable address and read value
    std::cout << "Enter address containing string value: 0x";
    std::cin >> std::hex >> intRead;
    std::string strRead{};
    readTargetMemory(hReadProcess, intRead, sizeof(std::string), &strRead);
    std::cout << "String value at provided address is: " << strRead << '\n';

    //Ask user for char array address and read value
    std::cout << "Enter address containing char array value: 0x";
    std::cin >> std::hex >> intRead;
    char arrRead[128]{};
    readTargetMemory(hReadProcess, intRead, sizeof(char[128]), &arrRead);
    std::cout << "Char array value at provided address is: " << arrRead << '\n';
    
    //Pause and exit after keypress
    std::cout << "Press ENTER to exit.";
    system("pause");

    //If handles exist close them
    if (hReadProcess != NULL) {
        CloseHandle(hReadProcess);
    }
    if (hWriteProcess != NULL) {
        CloseHandle(hWriteProcess);
    }
    return 0;
}

//Get handle with write permissions
void getWriteProcessHandle(DWORD proID) {
    hWriteProcess = OpenProcess(PROCESS_VM_WRITE, false, proID);
    if (hWriteProcess == NULL) {
        std::cout << "OpenProcess failed. GetLastError = " << std::dec << GetLastError() << '\n';
        system("pause");
    }
}

//Get handle with read permissions
void getReadProcessHandle(DWORD proID) {
    hReadProcess = OpenProcess(PROCESS_VM_READ, false, proID);
    if (hReadProcess == NULL) {
        std::cout << "OpenProcess failed. GetLastError = " << std::dec << GetLastError() << '\n';
        system("pause");
    }
}

//Function wich uses a Handle and memory address to read the value and store at intRead
//Use when integer/address is expected value at target address
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