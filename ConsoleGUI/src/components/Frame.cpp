#include "Frame.h"

#include <chrono>
#include <stdexcept>

#include "../draw/TerminalControl.h"
#include "../draw/AsciiCanvas.h"

namespace cg {
    bool Frame::isBeingShown = false;

    std::unique_ptr<Component> Frame::child;

    void Frame::show() {
        if(!child) {
            throw std::logic_error("Cannot show Frame, no child component to display!");
        }

        runGraphics();
    }

    void Frame::hide() {
        isBeingShown = false;
    }

    bool Frame::getIsBeingShown() {
        return isBeingShown;
    }

    void Frame::setChild(std::unique_ptr<Component> c) {
        child = std::move(c);
    }
    
    void Frame::runGraphics() {
        std::chrono::milliseconds targetTotalTime(50);

        draw::TerminalControl::setAlternateScreen();
        draw::TerminalControl::setCursorHidden();

        isBeingShown = true;
        while(isBeingShown) {
            std::chrono::time_point startTime = std::chrono::system_clock::now();

            child->updateSizeLimits();
            
            Dimensions termSize = draw::TerminalControl::getSize();
            child->updateRenderSizes(termSize);

            std::shared_ptr<draw::AsciiCanvas> canvas = std::make_shared<draw::AsciiCanvas>(termSize);
            draw::DrawingClip clip(termSize, canvas);
            child->drawComponent(clip);
            canvas->renderToTerminal();
            draw::TerminalControl::setCursorHidden();

            std::chrono::time_point endTime = std::chrono::system_clock::now();
            std::chrono::duration runTime = endTime - startTime;
            if(runTime < targetTotalTime) {
                std::chrono::duration sleepTime = targetTotalTime - runTime;
                std::this_thread::sleep_for(sleepTime);
            }
        }

        draw::TerminalControl::setMainScreen();
        draw::TerminalControl::setCursorShown();
    }
}
