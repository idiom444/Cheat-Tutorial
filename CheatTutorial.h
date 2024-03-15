#pragma once

#include <string>
#include <Windows.h>
#include <iostream>

HANDLE hReadProcess{};
HANDLE hWriteProcess{};

void getReadProcessHandle(DWORD proID);
void getWriteProcessHandle(DWORD proID);
void readTargetMemory(HANDLE Handle, long long memAddress, SIZE_T varSize, LPVOID storageLoc);