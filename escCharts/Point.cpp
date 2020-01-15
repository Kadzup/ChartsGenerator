#include "Point.h"

double Point::distanceTo(const Point& seconPoint) {
    int64_t dx = (x - seconPoint.x);
    int64_t dy = (y - seconPoint.y);
    return sqrt(dx * dx + dy * dy);
}