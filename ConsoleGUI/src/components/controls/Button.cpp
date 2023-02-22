#include "Button.h"

#include <algorithm>

namespace cg {
    Button::Button(std::string text) : text(text) {
        setPreferredSize(Dimensions((int)text.length() + 2, 3));
        setMinSize(Dimensions(std::min((int)text.length(), 3) + 2, 3));
    }

    void Button::drawComponent(draw::DrawingClip clip) const {
        // Draw top border
        clip.drawLineSegment({ 0, 0 }, draw::DrawingClip::LINE_SEGMENTS.SE);
        clip.drawLineSegment({ 1, 0 }, std::string(int(getSize().getWidth() - 2), draw::DrawingClip::LINE_SEGMENTS.EW));
        clip.drawLineSegment({ getSize().getWidth() - 1, 0 }, draw::DrawingClip::LINE_SEGMENTS.SW);
        
        // Draw left and right border
        for(int y = 1; y < getSize().getHeight() - 1; y++) {
            clip.drawLineSegment({ 0, y }, draw::DrawingClip::LINE_SEGMENTS.NS);
            clip.drawLineSegment({ getSize().getWidth() - 1, y }, draw::DrawingClip::LINE_SEGMENTS.NS);
        }

        // Draw bottom border
        clip.drawLineSegment({ 0, getSize().getHeight() - 1 }, draw::DrawingClip::LINE_SEGMENTS.NE);
        clip.drawLineSegment({ 1, getSize().getHeight() - 1 }, std::string(int(getSize().getWidth() - 2), draw::DrawingClip::LINE_SEGMENTS.EW));
        clip.drawLineSegment({ getSize().getWidth() - 1, getSize().getHeight() - 1 }, draw::DrawingClip::LINE_SEGMENTS.NW);

        // Now draw the button text, first by formatting it
        int widthForText = int(getSize().getWidth() - 2);

        std::string formattedText = text;

        if(widthForText > formattedText.length()) {
            // If the space is bigger than the text, pad the text to fill the space
            while(true) {
                formattedText = " " + formattedText;
                if(formattedText.length() == widthForText) {
                    break;
                }
                formattedText = formattedText + " ";
                if(formattedText.length() == widthForText) {
                    break;
                }
            }
        } else if(widthForText < formattedText.length()) {
            // If the space is too small, truncate the text and add ellipsis
            formattedText.resize((size_t)widthForText - 3);
            formattedText = formattedText + "...";
        }

        clip.drawText({ 1, 1 }, formattedText);
    }
}
