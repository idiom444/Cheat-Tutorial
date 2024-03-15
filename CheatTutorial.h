#pragma once

#include <string>
#include <Windows.h>
#include <iostream>

HANDLE hProcess{};

void getProcessHandle(DWORD proID);
void readTargetMemory(HANDLE Handle, long long memAddress, SIZE_T varSize, LPVOID storageLoc);
void writeTargetMemory(HANDLE Handle, long long memAddress, SIZE_T varSize, LPVOID storageLoc);