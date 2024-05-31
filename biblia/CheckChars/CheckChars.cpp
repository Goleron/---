#include "pch.h"
#include <windows.h>

extern "C" __declspec(dllexport) bool containsChars(const char* str, const char* chars) {
    while (*chars) {
        const char* tempStr = str;
        bool found = false;
        while (*tempStr) {
            if (*tempStr == *chars) {
                found = true;
                break;
            }
            ++tempStr;
        }
        if (!found) {
            return false;
        }
        ++chars;
    }
    return true;
}
