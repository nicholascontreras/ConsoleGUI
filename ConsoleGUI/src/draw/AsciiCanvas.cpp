#include "AsciiCanvas.h"

#include <stdexcept>

#include "TerminalControl.h"

namespace cg::draw {
    AsciiCanvas::AsciiCanvas(Dimensions size) : size(size) {
        textCanvas = std::vector<char>((size_t)size.getWidth() * size.getHeight(), '\0');
        lineCanvas = std::vector<char>((size_t)size.getWidth() * size.getHeight(), '\0');
    }

    void AsciiCanvas::setText(Point p, std::string s) {
        for(int i = 0; i < s.length(); i++) {
            Point curPoint = Point(p.getX() + i, p.getY());
            verifyBlank(curPoint);
            int index = indexOf(curPoint);
            textCanvas.at(index) = s.at(i);
        }        
    }

    void AsciiCanvas::setLineSegment(Point p, std::string s) {
        for(int i = 0; i < s.length(); i++) {
            Point curPoint = Point(p.getX() + i, p.getY());
            verifyBlank(curPoint);
            int index = indexOf(curPoint);
            lineCanvas.at(index) = s.at(i);
        }
    }

    void AsciiCanvas::renderToTerminal() {

        TerminalControl::setModeASCII();
        bool asciiMode = true;

        for(int row = 0; row < size.getHeight(); row++) {
            TerminalControl::setCursorPos(row + 1, 1);

            std::string bufferStr;
            int bufferStrStart = 1;
            for(int col = 0; col < size.getWidth(); col++) {
                int index = indexOf({ col, row });
                if(asciiMode) {
                    if(lineCanvas.at(index) != '\0') {
                        if(bufferStr.length() > 0) {
                            TerminalControl::writeStr(bufferStr);
                        }
                        bufferStrStart = bufferStrStart + (int)bufferStr.length();
                        TerminalControl::setModeLineDrawing();
                        TerminalControl::setCursorPos(row + 1, bufferStrStart);
                        bufferStr = lineCanvas.at(index);
                        asciiMode = false;
                    } else if(textCanvas.at(index) != '\0') {
                        bufferStr += textCanvas.at(index);
                    } else {
                        bufferStr += " ";
                    }
                } else if(!asciiMode) {
                    if(textCanvas.at(index) != '\0') {
                        if(bufferStr.length() > 0) {
                            TerminalControl::writeStr(bufferStr);
                        }
                        bufferStrStart = bufferStrStart + (int)bufferStr.length();
                        TerminalControl::setModeASCII();
                        TerminalControl::setCursorPos(row + 1, bufferStrStart);
                        bufferStr = textCanvas.at(index);
                        asciiMode = true;
                    } else if(lineCanvas.at(index) != '\0') {
                        bufferStr += lineCanvas.at(index);
                    } else {
                        bufferStr += " ";
                    }
                }
            }
            if(bufferStr.length() > 0) {
                TerminalControl::writeStr(bufferStr);
            }
        }
    }

    int AsciiCanvas::indexOf(Point p) {
        return p.getY() * size.getWidth() + p.getX();
    }

    void AsciiCanvas::verifyBlank(Point p) {
        verifyOnCanvas(p);
        int index = indexOf(p);

        if(textCanvas.at(index) != '\0') {
            throw std::logic_error("Text already exists at the given location!");
        }
        if(lineCanvas.at(index) != '\0') {
            throw std::logic_error("Line already exists at the given location!");
        }
    }

    void AsciiCanvas::verifyOnCanvas(Point p) {
        if(p.getX() >= size.getWidth()) {
            throw std::invalid_argument("X value must be less than width of canvas!");
        }
        if(p.getY() >= size.getHeight()) {
            throw std::invalid_argument("Y value must be less than height of canvas!");
        }
    }
}
