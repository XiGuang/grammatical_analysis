//
// Created by xiguang on 2023/4/16.
//

#include "Error.h"
#include <iostream>
#include <windows.h>

void Error::error(const std::string &message) {
    hasError = true;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    std::cout << message << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

bool Error::hasErrorOccurred() const {
    return hasError;
}
