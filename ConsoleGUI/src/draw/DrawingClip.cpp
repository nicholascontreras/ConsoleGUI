#include "DrawingClip.h"

#include <stdexcept>

#include "TerminalControl.h"

namespace cg::draw {
    DrawingClip::DrawingClip(Dimensions size, std::shared_ptr<AsciiCanvas> canvas) : 
        canvas(canvas) {
        absoluteClip = Rectangle({ 0, 0 }, size);
    }

    DrawingClip DrawingClip::createSubclip(Rectangle subclip) const {
        Point newAbslouteUpperLeft(absoluteClip.getUpperLeft().getX() + subclip.getUpperLeft().getX(),
            absoluteClip.getUpperLeft().getY() + subclip.getUpperLeft().getY());
        Point newAbslouteBottomRight(absoluteClip.getBottomRight().getX() + subclip.getBottomRight().getX(),
            absoluteClip.getBottomRight().getY() + subclip.getBottomRight().getY());

        return DrawingClip(Rectangle(newAbslouteUpperLeft, newAbslouteBottomRight), canvas);
    }

    void DrawingClip::drawText(Point p, std::string s) {
        if(s.length() == 0) {
            throw std::invalid_argument("Cannot draw empty string!");
        }

        verifyInClip(p);
        verifyInClip(Point(p.getX() + (int)s.length() - 1, p.getY()));

        canvas->setText(getAbsolutePoint(p), s);
    }

    void DrawingClip::drawLineSegment(Point p, std::string s) {
        if(s.length() == 0) {
            throw std::invalid_argument("Cannot draw empty string!");
        }

        verifyInClip(p);
        verifyInClip(Point(p.getX() + (int)s.length() - 1, p.getY()));

        canvas->setLineSegment(getAbsolutePoint(p), s);
    }

    DrawingClip::DrawingClip(Rectangle absoluteClip, std::shared_ptr<AsciiCanvas> canvas) : 
        absoluteClip(absoluteClip),
        canvas(canvas) {}

    Point DrawingClip::getAbsolutePoint(Point pointInClip) {
        verifyInClip(pointInClip);
        return Point(pointInClip.getX() + absoluteClip.getUpperLeft().getX(),
            pointInClip.getY() + absoluteClip.getUpperLeft().getY());
    }
    void DrawingClip::verifyInClip(Point point) {
        if(point.getX() >= absoluteClip.getDimensions().getWidth()) {
            throw std::invalid_argument("X value is not within the DrawingClip!");
        }
        if(point.getY() >= absoluteClip.getDimensions().getHeight()) {
            throw std::invalid_argument("Y value is not within the DrawingClip!");
        }
    }
}