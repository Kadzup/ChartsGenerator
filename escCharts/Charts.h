#pragma once
#include "Frame.h"
#include "Image.h"
#include <vector>
#include <ctime>

#define M_PI 3.141592653589793238462643383279502884

class DataNode
{
public:
    ~DataNode() {}
    DataNode() : title("Lorem"), value(0), percent(0) {}
    DataNode(string _title) : title(_title), value(0), percent(0) {}
    DataNode(string _title, double _value) : title(_title), value(_value), percent(0) {}
    DataNode(string _title, double _value, int64_t _percent) : title(_title), value(_value), percent(_percent) {}
	
public:
    string title;
    int64_t percent;
    double value;
};

class Charts
{
public:
    ~Charts() {};
    Charts() : img(Image(256, 256)), frame(img), isVisible(false) {};
    Charts(Image& _img) : img(_img), frame(_img), isVisible(false) {};
    Charts(Image& _img, Frame _frame) : img(_img), frame(_frame), isVisible(false) {};
    Charts(Image& _img, Frame _frame, bool _isVisible) : img(_img), frame(_frame), isVisible(_isVisible) {};

private:
    std::vector<int64_t> data;
    void DrawTower(const Point& Top, const int64_t& containerWidth, int64_t spacing);
    void DrawRectangleByLines(const Point& TopLeft, const Point& BottomRight, const RGBColor& outlineColor);
    inline void DrawCircleSelection(const Point& Center, const uint64_t& radius, const double& angleBegin, const double& angleEnd, const RGBColor& fillColor);

    inline int64_t GetPositionByPercent(const double& value, const int64_t& maxHeight) { return maxHeight - ceil((value * maxHeight) / 100); }
    inline double GetAngleByPercent(const double& value) { return (value * 360) / 100; }
    inline double GetRadians(const double& angle) { return angle * M_PI / 180.0; }

    RGBColor GenerateColor(const uint64_t& seed)
    {
        srand(seed);
        return RGBColor{ (uint8_t)(rand() % 255 + 1), (uint8_t)(rand() % 255 + 1), (uint8_t)(rand() % 255 + 1) };
    }

public:
	/* Show/Hide Charts Frame area */
    void ShowFrame(const bool& show);
    /* Show/Hide Charts Frame Corners area */
    void ShowFrameCorners(const bool& show);
    /* Show/Hide XY Charts lines */
    void ShowXY(const bool& show);

	/* Build Tower Charts on Image */
    void DrawTowerChart(const std::vector<DataNode>& data_nodes);
	/* Build Line Charts on Image */
    void DrawLineChart(const std::vector<DataNode>& data_nodes);
	/* Build Pie Charts on Image */
    void DrawPieChart(const std::vector<DataNode>& data_nodes);

	/* Get Current Image */
    inline Image GetImage() { return img; }

    Frame frame;
    Image img;

	/* Update Image */
    inline void Update() { img.Save(); }

private:
    bool isVisible;
};

