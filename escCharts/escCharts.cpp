#include "Charts.h"
#include "Image.h"
#include <vector>

using namespace  std;

int main()
{
	std::vector<DataNode> node;
	node.push_back(DataNode{ "test", 5 ,7 });
	node.push_back(DataNode{ "test", 5 ,5 });
	node.push_back(DataNode{ "test", 5 ,13 });
	node.push_back(DataNode{ "test", 5, 5 });
	node.push_back(DataNode{ "test", 5, 7 });
	node.push_back(DataNode{ "test", 5, 23 });
	node.push_back(DataNode{ "test", 5, 10 });
	node.push_back(DataNode{ "test", 5, 12 });
	node.push_back(DataNode{ "test", 5, 18 });
	
    string pathName = "out/";
	
    Image img(720, 480, pathName + "sample1.bmp", COLOR_WHITE);
    Image img2(720, 480, pathName + "sample2.bmp", COLOR_WHITE);
    Image img3(200, 200, pathName + "sample3.bmp", COLOR_WHITE);
	
	Charts chart(img);
	Charts chart2(img2);
	Charts chart3(img3);

	chart.ShowFrame(true);
	chart.ShowFrameCorners(true);
	chart.DrawTowerChart(node);
	chart.ShowFrame(true);
	chart.ShowFrameCorners(true);
	chart.Update();

	chart2.ShowFrame(true);
	chart2.ShowXY(true);
	chart2.DrawLineChart(node);
	chart2.Update();

	//img3.IsBufferValid();
	chart3.DrawPieChart(node);
	chart3.ShowFrame(true);
	chart3.Update();
	
    return 0;
}