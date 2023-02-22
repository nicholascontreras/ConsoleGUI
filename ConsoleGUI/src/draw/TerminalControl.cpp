#include "TerminalControl.h"

#include <Windows.h>

namespace cg::draw {
    const std::string TerminalControl::ESC = "\x1B";
    const int TerminalControl::MAX_VAL = 32767;

    Dimensions TerminalControl::getSize() {
        HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if(outputHandle == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Unable to get output handle!");
        }

        CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
        GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);

        int width = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
        int height = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;
        return Dimensions(width, height);
    }
}