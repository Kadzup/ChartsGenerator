#pragma once
#include <vector>
#include <string>
#include "RGBColor.h"

using namespace std;

class DataNode
{
public:
    ~DataNode() {}
    DataNode() : title("Lorem"), value(0), color(COLOR_DEFAULT) {}
    DataNode(std::string _title) : title(_title), value(0), color(COLOR_DEFAULT) {}
    DataNode(string _title, double _value) : title(_title), value(_value), color(COLOR_DEFAULT) {}
    DataNode(string _title, double _value, RGBColor _color) : title(_title), value(_value), color(_color) {}

    DataNode& operator=(const DataNode& node);

public:
    //Node Title
    string title;
    //Node Percent of Value
    int64_t percent;
    //Node Value
    double value;
    //Node fill Color
    RGBColor color;
};

class DataTable
{
public:
    ~DataTable() {}
    DataTable() : nodes(NULL) {};
    DataTable(vector<DataNode> _nodes) : nodes(_nodes) {};

	//Return Vector of DataNode
    std::vector<DataNode> GetNodes() { return nodes; };
	// Clear Vector of DataNode
    void Clear() { nodes.clear(); };
	// Add new DataNode in Vector
    void Add(std::string Text, double Value);
    // Add new DataNode in Vector
    void Add(std::string Text, double Value, RGBColor Color);

    // Add DataNode vector in Table
    void Set(vector<DataNode> _nodes);

	/*  Read data from file
		FilePath As String
		( path/path/file.type )
		Separator As String
		Default is ';'
	 */
    void ReadFromFile(const string& filePath, const char& separator);
    /*  Save data to file
        FilePath As String
        ( path/path/file.type )
        Separator As String
        Default is ';'
     */
    void SaveToFile(const string& filePath, const char& separator);

	// Unite Two DataTables
    void Unite(const DataTable& table);
	
private:
    void CalculatePercent();
    double GetValueSum();
    double GetPercentSum();
    vector <DataNode> nodes;
};

