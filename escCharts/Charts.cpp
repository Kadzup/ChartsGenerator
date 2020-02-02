#include "Charts.h"

void Charts::ShowXY(const bool& show = true)
{
    if (show)
    {
        RGBColor lineColor;
        if (frame.GetXYColor().IsEmpty())
            lineColor = GenerateColor(NULL);
        else
            lineColor = frame.GetXYColor();

        img.DrawLine(frame.TopLeft.x, frame.TopLeft.y, frame.TopLeft.x + 6, frame.TopLeft.y + 10, lineColor);
        img.DrawLine(frame.TopLeft.x, frame.TopLeft.y, frame.TopLeft.x - 6, frame.TopLeft.y + 10, lineColor);

        img.DrawLine(frame.TopLeft.x, frame.TopLeft.y, frame.BottomLeft.x, frame.BottomLeft.y, lineColor);
        img.DrawLine(frame.BottomLeft.x, frame.BottomLeft.y, frame.BottomRight.x, frame.BottomRight.y, lineColor);

        img.DrawLine(frame.BottomRight.x, frame.BottomRight.y, frame.BottomRight.x - 10, frame.BottomRight.y + 6, lineColor);
        img.DrawLine(frame.BottomRight.x, frame.BottomRight.y, frame.BottomRight.x - 10, frame.BottomRight.y - 6, lineColor);

        frame.SetXYColor(lineColor);
    }
    else
    {
        img.DrawLine(frame.TopLeft.x, frame.TopLeft.y, frame.BottomLeft.x, frame.BottomLeft.y, img.GetBGColor());
        img.DrawLine(frame.BottomLeft.x, frame.BottomLeft.y, frame.BottomRight.x, frame.BottomRight.y, img.GetBGColor());
    }
}

void Charts::ShowFrame(const bool& show = true)
{
    if (isVisible != show)
        isVisible = !isVisible;

    if (isVisible)
    {
        RGBColor outlineColor;
        if (img.GetBGColor() == COLOR_BLACK)
            outlineColor = COLOR_WHITE;
        else if (img.GetBGColor() == COLOR_WHITE)
            outlineColor = COLOR_GREY;
        else
            outlineColor = COLOR_FRAME_DARK;

        DrawRectangleByLines(frame.TopLeft, frame.BottomRight, outlineColor);
    }
    else {
        DrawRectangleByLines(frame.TopLeft, frame.BottomRight, img.GetBGColor());
    }
}

void Charts::ShowFrameCorners(const bool& show = true)
{
    if (show)
    {
        RGBColor outlineColor;
        if (img.GetBGColor() == COLOR_BLACK)
            outlineColor = COLOR_WHITE;
        else if (img.GetBGColor() == COLOR_WHITE)
            outlineColor = COLOR_GREY;
        else
            outlineColor = COLOR_FRAME_DARK;

        DrawRectangleByLines(frame.TopLeft - frame.Spacing / 2, frame.TopLeft + frame.Spacing / 2, outlineColor);
        DrawRectangleByLines(frame.Top - frame.Spacing / 2, frame.Top + frame.Spacing / 2, outlineColor);
        DrawRectangleByLines(frame.TopRight - frame.Spacing / 2, frame.TopRight + frame.Spacing / 2, outlineColor);

        DrawRectangleByLines(frame.Left - frame.Spacing / 2, frame.Left + frame.Spacing / 2, outlineColor);
        DrawRectangleByLines(frame.Right - frame.Spacing / 2, frame.Right + frame.Spacing / 2, outlineColor);

        DrawRectangleByLines(frame.BottomLeft - frame.Spacing / 2, frame.BottomLeft + frame.Spacing / 2, outlineColor);
        DrawRectangleByLines(frame.Bottom - frame.Spacing / 2, frame.Bottom + frame.Spacing / 2, outlineColor);
        DrawRectangleByLines(frame.BottomRight - frame.Spacing / 2, frame.BottomRight + frame.Spacing / 2, outlineColor);
    }
    else
    {
        DrawRectangleByLines(frame.TopLeft - frame.Spacing / 2, frame.TopLeft + frame.Spacing / 2, img.GetBGColor());
        DrawRectangleByLines(frame.Top - frame.Spacing / 2, frame.Top + frame.Spacing / 2, img.GetBGColor());
        DrawRectangleByLines(frame.TopRight - frame.Spacing / 2, frame.TopRight + frame.Spacing / 2, img.GetBGColor());

        DrawRectangleByLines(frame.Left - frame.Spacing / 2, frame.Left + frame.Spacing / 2, img.GetBGColor());
        DrawRectangleByLines(frame.Right - frame.Spacing / 2, frame.Right + frame.Spacing / 2, img.GetBGColor());

        DrawRectangleByLines(frame.BottomLeft - frame.Spacing / 2, frame.BottomLeft + frame.Spacing / 2, img.GetBGColor());
        DrawRectangleByLines(frame.Bottom - frame.Spacing / 2, frame.Bottom + frame.Spacing / 2, img.GetBGColor());
        DrawRectangleByLines(frame.BottomRight - frame.Spacing / 2, frame.Bottom + frame.Spacing / 2, img.GetBGColor());
    }
}

void Charts::DrawTower(const Point& Top, const int64_t& containerWidth, int64_t spacing = 5)
{
    assert(Top.x >= 0 and Top.y >= 0 and Top.x < img.Width() and Top.y < img.Height());
    assert(containerWidth > 0);

    Point LT = Point{ Top.x - ((containerWidth - spacing) / 2), Top.y },
        RB = Point{ Top.x + ((containerWidth - spacing) / 2), frame.Bottom.y };

    img.DrawLine(Top.x - ((containerWidth - spacing) / 2) + 1, Top.y, Top.x + ((containerWidth - spacing) / 2) - 1, Top.y, COLOR_BLUE);
    img.DrawLine(Top.x - ((containerWidth - spacing) / 2) + 1, Top.y, Top.x - ((containerWidth - spacing) / 2) + 1, frame.Bottom.y, COLOR_BLUE);
    img.DrawLine(Top.x + ((containerWidth - spacing) / 2) - 1, Top.y, Top.x + ((containerWidth - spacing) / 2) - 1, frame.Bottom.y, COLOR_BLUE);

    img.FillRectangle(LT.x, LT.y, RB.x, RB.y, GenerateColor(frame.GetDistance(Top, frame.Bottom) + frame.GetDistance({ Top.x - ((containerWidth - spacing) / 2) + 1, Top.y }, { Top.x + ((containerWidth - spacing) / 2) - 1, frame.Bottom.y })));
}

void Charts::DrawTowerChart(const std::vector<DataNode>& data_nodes)
{
    if (data_nodes.empty())
        return;

    int64_t maxHeight = img.Height() - frame.Top.y + frame.Spacing.y;
    int64_t containerWidth = ceil(frame.GetDistance(frame.BottomLeft, frame.BottomRight) / data_nodes.size());

    Point containerCenter = Point{ frame.BottomLeft.x + containerWidth / 2, frame.BottomLeft.y };

    for (DataNode node : data_nodes) {
        containerCenter.y = GetPositionByPercent(node.percent+5, maxHeight);
        DrawTower(containerCenter, containerWidth);
        containerCenter.x += containerWidth;
    }
}

void Charts::DrawLineChart(const std::vector<DataNode>& data_nodes) {
    if (data_nodes.empty())
        return;

    int64_t maxHeight = img.Height() - frame.Top.y + frame.Spacing.y;
    int64_t partialPoint = ceil(frame.GetDistance(frame.BottomLeft, frame.BottomRight) / data_nodes.size());

    Point pointCenter = frame.BottomLeft;
    RGBColor lineColor = GenerateColor(NULL);

    for (DataNode node : data_nodes) {
        img.DrawLine(pointCenter.x, pointCenter.y, pointCenter.x + partialPoint, GetPositionByPercent(node.percent, maxHeight), lineColor);

        img.DrawCircle(pointCenter.x, pointCenter.y, 4, COLOR_BLUE_LIGHT, 4, false, img.GetBGColor());
        pointCenter.x += partialPoint;
        pointCenter.y = GetPositionByPercent(node.percent, maxHeight);
        img.DrawCircle(pointCenter.x, pointCenter.y, 4, COLOR_BLUE_LIGHT, 4, false, img.GetBGColor());
    }
}

void Charts::DrawRectangleByLines(const Point& TopLeft, const Point& BottomRight, const RGBColor& outlineColor) {
    img.DrawLine(TopLeft.x, TopLeft.y, TopLeft.x, BottomRight.y, outlineColor);
    img.DrawLine(TopLeft.x, BottomRight.y, BottomRight.x, BottomRight.y, outlineColor);
    img.DrawLine(BottomRight.x, BottomRight.y, BottomRight.x, TopLeft.y, outlineColor);
    img.DrawLine(BottomRight.x, TopLeft.y, TopLeft.x, TopLeft.y, outlineColor);
}

void Charts::DrawCircleSelection(const Point& Center, const uint64_t& radius, const double& angleBegin, const double& angleEnd, const RGBColor& fillColor)
{
    int64_t selX, selY;
    bool wasFounded = false;
    img.DrawLine(Center.x, Center.y, Center.x + (radius - 5) * cos(GetRadians(angleBegin)), Center.y + (radius - 5) * sin(GetRadians(angleBegin)), fillColor);

    auto angleMiddle = angleEnd - angleBegin;

    img.DrawLine(Center.x, Center.y, Center.x + (radius - 5) * cos(GetRadians(angleMiddle)), Center.y + (radius - 5) * sin(GetRadians(angleMiddle)), fillColor);

    img.DrawLine(Center.x, Center.y, Center.x + (radius - 5) * cos(GetRadians(angleEnd - 1)), Center.y + (radius - 5) * sin(GetRadians(angleEnd - 1)), fillColor);

    for (double i = GetRadians(angleBegin); i <= GetRadians(angleEnd - 1); i += 0.0001)
    {
    	if(i >= GetRadians(angleEnd/2 - 1) && !wasFounded)
    	{
            selX = Center.x + (radius - 25) * cos(i);
            selY = Center.y + (radius - 25) * sin(i);
            wasFounded = true;
    	}

        img.SetPixel(Center.x + (radius - 5) * cos(i), Center.y + (radius - 5) * sin(i), fillColor, false);
    }

    img.FloodFill(selX, selY, fillColor);
}

void Charts::DrawPieChart(const std::vector<DataNode>& data_nodes)
{
    if (data_nodes.empty())
        return;

    RGBColor lineColor = GenerateColor(data_nodes[0].percent + time(NULL));
    Point center;
    center.y = frame.Bottom.y - frame.Bottom.y / 2 + frame.Spacing.y / 2;
    center.x = (frame.GetDistance(frame.Left, frame.Right) / 2) + frame.Spacing.x;

    int64_t radius = (frame.GetDistance(frame.Top, frame.Bottom) / 2) - frame.Spacing.x;

    /*img.DrawCircle(center.x, center.y, radius, lineColor, 5, false);
    img.DrawCircle(center.x, center.y, radius - 4, COLOR_BLACK, 1, false);*/

    double angleBegin = 0, angleEnd = 0;
    int i = 0;
    for (DataNode node : data_nodes) {
        angleEnd = angleBegin + GetAngleByPercent(node.percent);

        DrawCircleSelection(center, radius, angleBegin, angleEnd, GenerateColor(GetAngleByPercent(angleEnd)));

        std::cout << std::endl << "Begin: " << angleBegin << " End: " << angleEnd << std::endl;
        angleBegin = angleEnd;
        i++;
    }
    std::cout << std::endl << angleEnd;
}
