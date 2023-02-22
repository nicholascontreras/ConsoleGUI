#pragma once

#include <string>
#include <iostream>

#include "../util/Dimensions.h"

namespace cg::draw {
    class TerminalControl {
    public:
        static Dimensions getSize();

        inline static void writeStr(std::string str) { std::cout << str << std::flush; }

#define GEN_VTS_FUNC_0(FUNC_NAME, SEQ) \
inline static void FUNC_NAME() { \
    std::cout << (ESC + SEQ) << std::flush; \
}

#define GEN_VTS_FUNC_1(FUNC_NAME, SEQ_0, TYPE_1, SEQ_1) \
inline static void FUNC_NAME(TYPE_1 var1) { \
    std::cout << (ESC + SEQ_0 + std::to_string(var1) + SEQ_1) << std::flush; \
}

#define GEN_VTS_FUNC_2(FUNC_NAME, SEQ_0, TYPE_1, SEQ_1, TYPE_2, SEQ_2) \
inline static void FUNC_NAME(TYPE_1 var1, TYPE_2 var2) { \
    std::cout << (ESC + SEQ_0 + std::to_string(var1) + SEQ_1 + std::to_string(var2) + SEQ_2) << std::flush; \
}

        GEN_VTS_FUNC_0(setAlternateScreen, "[?1049h");
        GEN_VTS_FUNC_0(setMainScreen, "[?1049l");

        GEN_VTS_FUNC_0(setModeASCII, "(B");
        GEN_VTS_FUNC_0(setModeLineDrawing, "(0");

        GEN_VTS_FUNC_0(setCursorShown, "[?25h");
        GEN_VTS_FUNC_0(setCursorHidden, "[?25l");

        GEN_VTS_FUNC_1(deleteChars, "[", int, "P");

        GEN_VTS_FUNC_2(setCursorPos, "[", int, ";", int, "H");

#undef GEN_VTS_FUNC_0
#undef GEN_VTS_FUNC_2

    private:
        static const std::string ESC;
        static const int MAX_VAL;
    };
}
