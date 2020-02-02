#include "Charts.h"
#include "DataTable.h"
#include "Image.h"
#include <vector>

using namespace  std;

int main()
{
	DataTable table;
	table.Add("text1", 20);
	table.Add("text1", 15);
	table.Add("text1", 78);
	table.Add("text1", 11);
	table.Add("text1", 302);
	table.Add("text1", 200);
	table.Add("text1", 87);
	table.Add("text1", 9);
	
    string pathName = "out/";
	
    Image img(720, 480, pathName + "sample1.bmp", COLOR_WHITE);
    Image img2(720, 480, pathName + "sample2.bmp", COLOR_WHITE);
    Image img3(200, 200, pathName + "sample3.bmp", COLOR_WHITE);
	
	Charts chart(img);
	Charts chart2(img2);
	Charts chart3(img3);

	chart.ShowFrame(true);
	chart.ShowFrameCorners(true);
	chart.DrawTowerChart(table.GetNodes());
	chart.ShowFrame(true);
	chart.ShowFrameCorners(true);
	chart.Update();

	chart2.ShowFrame(true);
	chart2.ShowXY(true);
	chart2.DrawLineChart(table.GetNodes());
	chart2.Update();

	chart3.DrawPieChart(table.GetNodes());
	chart3.ShowFrame(true);
	chart3.Update();
	
    return 0;
}