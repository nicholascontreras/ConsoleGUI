#include <iostream>
#include <thread>
#include <chrono>

#include "components/Frame.h"
#include "components/layouts/GridLayout.h"
#include "components/controls/Button.h"

int main() {
    cg::GridLayout grid = cg::GridLayout(3);

    std::unique_ptr<cg::Button> button1 = std::make_unique<cg::Button>("Button Text 1!");
    std::unique_ptr<cg::Button> button2 = std::make_unique<cg::Button>("Button Text 2!");
    std::unique_ptr<cg::Button> button3 = std::make_unique<cg::Button>("Button Text 3!");
    cg::Button button4 = cg::Button("Button Text 4!");

    grid.addChild(std::move(button1));
    grid.addChild(std::move(button2));
    grid.addChild(std::move(button3));
    grid.addChild(std::make_unique<cg::Button>(button4));

    cg::Frame::setChild(std::make_unique<cg::GridLayout>(std::move(grid)));
    cg::Frame::show();

    return 0;
}