#pragma once
#include <Windows.h>

inline void SetColour(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}