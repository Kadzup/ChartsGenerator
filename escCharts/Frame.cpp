#include "Frame.h"

Frame::Frame(Image img)
{
    Spacing = { 10,10 };

    TopLeft = Spacing;
    BottomRight.x = img.Width() - Spacing.x;
    BottomRight.y = img.Height() - Spacing.y;

    InitFrame();
}

Frame::Frame(Point _TopLeft, Point _BottomRight)
{
    Spacing = { 10,10 };

    TopLeft = _TopLeft;
    BottomRight = _BottomRight;

    InitFrame();
}

void Frame::InitFrame()
{
    TopRight.x = BottomRight.x;
    TopRight.y = TopLeft.y;

    BottomLeft.x = TopLeft.x;
    BottomLeft.y = BottomRight.y;

    Top.x = GetDistance(TopLeft, TopRight) / 2;
    Top.y = TopLeft.y;

    Bottom.x = GetDistance(BottomLeft, BottomRight) / 2;
    Bottom.y = BottomRight.y;

    Left.x = TopLeft.x;
    Left.y = GetDistance(TopLeft, BottomLeft) / 2;

    Right.x = TopRight.x;
    Right.y = GetDistance(TopRight, BottomRight) / 2;;
}