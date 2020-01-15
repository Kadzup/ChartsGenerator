#include "RGBColor.h"

RGBColor::RGBColor(uint8_t _r, uint8_t _g, uint8_t _b)
{
    SetColor(_r, _g, _b);
}

void RGBColor::SetColor(uint8_t _r, uint8_t _g, uint8_t _b)
{
    r = _r;
    g = _g;
    b = _b;
}

const bool RGBColor::IsEmpty()
{
    return !(r && g && b);
}