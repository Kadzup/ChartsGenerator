#pragma once
#include "RGBColor.h"
#include "Point.h"

#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
using std::string;
using std::int64_t;
using std::uint32_t;
using std::uint8_t;
using std::ofstream;

class Image
{
public:
    ~Image();
    Image() { width = height = 0; };
    Image(int64_t _width, int64_t _height);
    Image(int64_t _width, int64_t _height, const std::string& _outFileName);
    Image(int64_t _width, int64_t _height, const RGBColor& _backgroundColor);
    Image(int64_t _width, int64_t _height, const std::string& _outFileName, const RGBColor& _backgroundColor);
    Image(const Image& _image);

    /*
     Set Pixel on current Image
	 using X,Y position and
	 RGB color for Pixel
	 */
    void SetPixel(int64_t x, int64_t y, const RGBColor& color, bool ignore_err);

	/*
	 Draw Line on current Image
	 using 2 Points coordinates
	 X,Y position of First Point
	 X,Y position of Second Point
	 RGB color for Line
	 */
    void DrawLine(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);
    /*
     Draw Bezier Line on current Image
	 using 3 Points coordinates
	 X,Y position of First Point
	 X,Y position of Second Point
	 X,Y position of Third Point
	 RGB color for Line
	 */
	void DrawBezier(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3, const RGBColor& color);
    /*
     Draw Circle on current Image
	 using center Point coordinates
	 X,Y position of Center Point
	 Radius of Circle As Integer
	 Outline color As RGB Color
	 Outline Width As Integer - default=1
	 Fill circle flag As Boolean - default=False
	 Fill color As RGB Color - default=White
	*/
    void DrawCircle(int64_t x0, int64_t y0, int64_t r, const RGBColor& outlineColor, int64_t outlineWidth, bool fill, const RGBColor& fillColor);

	/*
     Draw Rectangle on current Image
	 using two Points coordinates
	 X,Y position of Top Left Point
	 X,Y position of Bottom Right Point
	 Outline color As RGB Color
	 Outline Width As Integer - default=1
	 Fill circle flag As Boolean - default=False
	 Fill color As RGB Color - default=White
	*/
    void DrawRectangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, const RGBColor& outlineColor, int64_t outlineWidth, bool fill, const RGBColor& fillColor);

    /* Change Out File Name */
    void SetFileName(const std::string& _outFileName);

    void SmartFill(int64_t x, int64_t y, RGBColor fillColor, RGBColor borderColor);
    /* Fill Rectangle Area with color */
	void FillRectangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, const RGBColor& fillColor);

    /* Save Image */
    void Save(const std::string& _outFileName);
    /* Save Image */
    void Save();

	/* Get Image Width */
    inline int64_t Width() const { return this->width; }
	/* Get Image Height */
    inline int64_t Height() const { return this->height; }

	/* Get BackGround Color */
    inline RGBColor GetBGColor() const { return backgroundColor; }

    Image& operator = (const Image& img)
    {
        if (this == &img)
            return *this;
    	
        this->width = img.width;
        this->height = img.height;
        this->buffer = img.buffer;
        this->outFileName = img.outFileName;
        this->backgroundColor = img.backgroundColor;

        return *this;
    }

    /* Get Color of Pixel on current Point coordinate */
    RGBColor GetPixelColor(const int64_t& x, const int64_t& y) const;

    void FloodFill(int64_t x, int64_t y, RGBColor newColor);

private:
    void Init(int64_t _width, int64_t _height);
    void Setup();

    void DrawLineLow(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);
    void DrawLineHigh(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);


    void FloodFillUtil(int64_t x, int64_t y, RGBColor prevColor, RGBColor newColor);
	
    int64_t width;
    int64_t height;
    ofstream outFile;
    string outFileName;
    RGBColor backgroundColor;
    vector<vector<RGBColor>> buffer;
};
