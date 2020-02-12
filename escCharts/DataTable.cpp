#include "DataTable.h"
#include <cassert>
#include <algorithm>

DataNode& DataNode::operator=(const DataNode& node) {
	if (this != &node) {
		this->title = node.title;
		this->percent = node.percent;
		this->value = node.value;
		this->color = node.color;
	}
	return *this;
}

double DataTable::GetValueSum()
{
	double sum = 0;
	for(auto node : nodes)
	{
		sum += abs(node.value);
	}
	
	return sum;
}

double DataTable::GetPercentSum()
{
	double sum = 0;
	for (auto node : nodes)
	{
		sum += abs(node.percent);
	}

	return sum;
}

void DataTable::Add(std::string Text, double Value)
{
	nodes.push_back({ Text, Value });
	CalculatePercent();
}

void DataTable::Add(std::string Text, double Value, RGBColor Color)
{
	nodes.push_back({ Text, Value, Color });
	CalculatePercent();
}

void DataTable::CalculatePercent()
{
	if(nodes.empty())
		return;
	
	double sum = 0;

	for(auto node : nodes)
		sum += abs(node.value);

	for (auto& node : nodes)
		node.percent = ceil((node.value * 100) / sum);
	

	if (GetPercentSum() > 100) {
		int64_t i = 0;
		while (GetPercentSum() > 100)
		{
			if(nodes[i].percent > 1)
				nodes[i].percent--;
			i++;
		}
	}
	else if(GetPercentSum() < 100)
	{
		int64_t i = 0;
		while (GetPercentSum() < 100)
		{
			nodes[i].percent++;
			i++;
		}
	}
}

void DataTable::Set(vector<DataNode> _nodes)
{
	if (_nodes.empty())
		return;

	this->nodes = _nodes;
	CalculatePercent();
}
