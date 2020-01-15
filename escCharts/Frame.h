#pragma once
#include "Image.h"

class Frame
{
public:
    Point Top;
    Point TopLeft;
    Point TopRight;

    Point Bottom;
    Point BottomLeft;
    Point BottomRight;

    Point Left;
    Point Right;

    Point Spacing;

	~Frame(){}
    Frame(Image img);
    Frame(Point _TopLeft, Point _BottomRight);

    inline int64_t GetDistance(const Point from, const Point to)
    {
        return sqrt((to.x - from.x) * (to.x - from.x) + (to.y - from.y) * (to.y - from.y));
    }

    void InitFrame();

    inline RGBColor GetFrameColor() const { return frameColor; }
    inline RGBColor GetXYColor() const { return XYColor; }

    inline void SetFrameColor(const RGBColor& inColor) { frameColor = inColor; }
    inline void SetXYColor(const RGBColor& inColor) { XYColor = inColor; }

private:
    RGBColor frameColor;
    RGBColor XYColor;
};

