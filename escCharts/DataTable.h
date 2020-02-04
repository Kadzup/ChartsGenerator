#pragma once
#include <vector>
#include <string>
#include "RGBColor.h"

using namespace std;

class DataNode
{
public:
    ~DataNode() {}
    DataNode() : title("Lorem"), value(0), percent(0) {}
    DataNode(std::string _title) : title(_title), value(0), percent(0) {}
    DataNode(string _title, double _value) : title(_title), value(_value), percent(0) {}
    DataNode(string _title, double _value, int64_t _percent) : title(_title), value(_value), percent(_percent) {}
    DataNode(string _title, double _value, int64_t _percent, RGBColor _color) : title(_title), value(_value), percent(_percent), color(_color) {}

public:
    string title;
    int64_t percent;
    double value;
    RGBColor color;
};

class DataTable
{
public:
    ~DataTable() {}
    DataTable() : nodes(NULL) {};
    DataTable(vector<DataNode> _nodes) : nodes(_nodes) {};

	/*
	 Return Vector of DataNode
	 */
    std::vector<DataNode> GetNodes() { return nodes; };
	// Clear Vector of DataNode
    void Clear() { nodes.clear(); };
	// Add new DataNode in Vector
    void Add(std::string Text, double Value);
    void Set(vector<DataNode> _nodes);
	
private:
    void CalculatePercent();
    double GetValueSum();
    double GetPercentSum();
    vector <DataNode> nodes;
};

