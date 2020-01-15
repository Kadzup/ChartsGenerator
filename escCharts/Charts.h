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

        uint8_t r = rand() % 255 + 1, g = rand() % 255 + 1, b = rand() % 255 + 1;

        return RGBColor{ r, g ,b };
    }
    uint64_t GenerateSeed()
    {
        srand(time(NULL) + sizeof(RGBColor));

        time_t curr_time;
        curr_time = time(NULL);

        tm* tm_local = localtime(&curr_time);

        uint32_t dist = curr_time;

        if (rand() % 10 + 1 == 1)
            dist += frame.GetDistance(frame.TopLeft, frame.BottomRight) * 5;
        else if (rand() % 10 + 1 == 2)
            dist += frame.GetDistance(frame.Top, frame.Bottom) * 5;
        else if (rand() % 10 + 1 == 3)
            dist += frame.GetDistance(frame.TopRight, frame.Left) * 5;
        else if (rand() % 10 + 1 == 4)
            dist += frame.GetDistance(frame.Right, frame.BottomLeft) * 5;
        else if (rand() % 10 + 1 >= 5)
            dist += frame.GetDistance(frame.BottomRight, frame.Top) * 5;

        return img.Width() * img.Height() + time(NULL) * tm_local->tm_sec + tm_local->tm_hour * tm_local->tm_year + dist;
    }

public:
    void ShowFrame(const bool& show);
    void ShowFrameCorners(const bool& show);
    void ShowXY(const bool& show);

    void DrawTowerChart(const std::vector<DataNode>& data_nodes);
    void DrawLineChart(const std::vector<DataNode>& data_nodes);

    void DrawPieChart(const std::vector<DataNode>& data_nodes);

    inline Image GetImage() { return this->img; }

    Frame frame;
    Image img;

    inline void Update() { this->img.Save(); }

private:
    bool isVisible;
};

