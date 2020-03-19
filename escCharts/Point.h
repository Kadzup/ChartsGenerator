#pragma once
#include <cstdint>
#include <cmath>

class Point
{
public:
    int64_t x, y;

    Point(int64_t _x, int64_t _y) : x(_x), y(_y) { }
    Point() : x(NULL), y(NULL) { }

    /*
     Function to calculate distance between
	 This point and Second point
	 Return Double value
	 */
    double DistanceTo(const Point& seconPoint);

    inline Point operator + (const Point& rObj) { return Point{ x + rObj.x, y + rObj.y }; }
    inline Point operator - (const Point& rObj) { return Point{ x - rObj.x, y - rObj.y }; }
    inline Point operator / (double value) { return Point{ int64_t(ceil(x / value)), int64_t(ceil(y / value)) }; }
    inline bool operator > (const Point& rhs) { return (this->x > rhs.x) && (this->y > rhs.y); }
};
