#include "Image.h"

int main()
{
    string pathName = "out/";

    Image img(720, 480, pathName + "image.bmp", COLOR_WHITE);
	
    Point center{img.Width()/2, img.Height()/2};

	for(int i = 0; i < 10; i++)
	{
		img.DrawCircle(center.x-i*5, center.y-i*5, 150-i*5, {0+i+1*2, 20+i+1*2, 50+i+1*2}, 5, false, img.GetBGColor());
	}
	
	img.Save();
	
    return 0;
}