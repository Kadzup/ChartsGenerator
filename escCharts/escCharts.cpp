#include "Charts.h"
#include "DataTable.h"
#include "Image.h"
#include <vector>

using namespace  std;

int main()
{
	DataTable table;
	table.Add("text1", 23);
	table.Add("text1", 90);
	table.Add("text1", 15);
	table.Add("text1", 45);
	table.Add("text1", 5);
	table.Add("text1", 19);
	table.Add("text1", 34);
	table.Add("text1", 12);
	
    string pathName = "out/";

	table.SaveToFile(pathName + "data.csv", ';');
	table.ReadFromFile(pathName + "data.csv", ';');

	table.Add("text1", 100);
	table.Add("text1", 200);
	table.Add("text1", 100);
	
	table.SaveToFile(pathName + "data.csv", ';');
	
    Image img(720, 480, pathName + "sample1.bmp", COLOR_WHITE);
    Image img2(720, 480, pathName + "sample2.bmp", COLOR_WHITE);
    Image img3(720, 720, pathName + "sample3.bmp", COLOR_WHITE);
	
	Charts chart(img);
	Charts chart2(img2);
	Charts chart3(img3);

	chart.DrawTowerChart(table.GetNodes());
	chart.Update();

	chart2.DrawLineChart(table.GetNodes());
	chart2.Update();

	chart3.DrawPieChart(table.GetNodes());
	chart3.Update();
	
    return 0;
}