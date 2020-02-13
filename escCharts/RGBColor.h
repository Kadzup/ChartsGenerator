#pragma once
#include <cstdint>
#include <ostream>

#define COLOR_DEFAULT RGBColor{204, 204, 204}
#define COLOR_WHITE RGBColor{255, 255, 255}
#define COLOR_BLACK RGBColor{0, 0, 0}
#define COLOR_RED RGBColor{255, 0, 0}
#define COLOR_GREEN RGBColor{0, 255, 0}
#define COLOR_BLUE RGBColor{0, 0, 255}
#define COLOR_ORANGE RGBColor{255, 128, 0}
#define COLOR_YELLOW RGBColor{255, 255, 0}
#define COLOR_GREEN_LIGHT RGBColor{128, 255, 0}
#define COLOR_CYAN RGBColor{0, 255, 128}
#define COLOR_BLUE_LIGHT RGBColor{0, 255, 255}
#define COLOR_BLUE_SKY RGBColor{0, 128, 255}
#define COLOR_MAGENTA RGBColor{153, 51, 255}
#define COLOR_PINK RGBColor{255, 102, 178}
#define COLOR_GREY RGBColor{96, 96, 96}
#define COLOR_BROWN RGBColor{51, 25, 0}
#define COLOR_FRAME_LIGHT RGBColor{153, 204, 255}
#define COLOR_FRAME_DARK RGBColor{226, 226, 226}

class RGBColor
{
public:
    RGBColor() {};
    ~RGBColor() {};
    RGBColor(uint8_t _r, uint8_t _g, uint8_t _b);
    RGBColor(int _r, int _g, int _b);

    /*
     Set RGB Color by 3 parameters
	 R = 0 ... 255
	 G = 0 ... 255
	 B = 0 ... 255
	 */
    void SetColor(uint8_t _r, uint8_t _g, uint8_t _b);

    /*
     Check if RGB Color object is empty
	 Return  {false} - if all members are present
	*/
    const bool IsEmpty();

    inline const bool operator == (const RGBColor& in) { return (this->r == in.r) && (this->g == in.g) && (this->b == in.b); }
    inline const bool operator != (const RGBColor& in) { return (this->r != in.r) || (this->g != in.g) || (this->b != in.b); }
    friend std::ostream& operator<<(std::ostream& output, const RGBColor& color)
    {
        output << "RGB(" << (int)color.r << "," << (int)color.g << "," << (int)color.b << ")";
	    return output;
    }
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

