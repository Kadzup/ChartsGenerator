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

	/* Get distance between Two Frames Points */
    inline int64_t GetDistance(const Point from, const Point to)
    {
        return sqrt((to.x - from.x) * (to.x - from.x) + (to.y - from.y) * (to.y - from.y));
    }

	/* Return Frame Outline Color */
    inline RGBColor GetFrameColor() const { return frameColor; }
    /* Return XY Lines Color */
    inline RGBColor GetXYColor() const { return XYColor; }

    /* Set Frame Outline Color */
    inline void SetFrameColor(const RGBColor& inColor) { frameColor = inColor; }
    /* Set XY Lines Color */
    inline void SetXYColor(const RGBColor& inColor) { XYColor = inColor; }

private:
    void InitFrame();
	
    RGBColor frameColor;
    RGBColor XYColor;
};

