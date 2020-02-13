#include "DataTable.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <xlocmon>

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

void DataTable::Add(const DataNode& node)
{
	nodes.push_back(node);
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

void DataTable::Unite(const DataTable& table)
{
	if (table.nodes.empty())
		return;

	for(auto&& node : table.nodes)
		this->nodes.push_back(node);
}

void DataTable::ReadFromFile(const string& filePath, const char& separator = ';')
{
	std::vector<std::pair<std::string, std::vector<string>>> result;

	// Create an input filestream
	std::ifstream myFile(filePath);

	// Make sure the file is open
	if (!myFile.is_open()) throw std::runtime_error("Could not open file");

	std::string line, colname;
	string val;

	if (myFile.good())
	{
		// Extract the first line in the file
		std::getline(myFile, line);

		// Create a stringstream from line
		std::stringstream ss(line);

		// Extract each column name
		while (std::getline(ss, colname, separator)) {

			// Initialize and add <colname, int vector> pairs to result
			result.push_back({ colname, std::vector<string> {} });
		}
	}

	long i = 0, j = 0;
	vector<vector<string>> table;

	while (std::getline(myFile, line))
	{
		std::stringstream ss(line);

		string word = "";
		table.push_back(vector <string>());
		
		for(int k = 0; k < line.size(); k++){
			if(line[k] == ';')
			{
				table[i].push_back(word);
				word = "";
				j++;
			}
			else
			{
				word += line[k];
			}
		}
		j = 0;
		i++;
			
	}

	myFile.close();
	
	for(auto&& line : table)
		this->ParseString(line);
}

void DataTable::SaveToFile(const string& filePath, const char& separator = ';')
{
	if (this->nodes.empty())
		return;
	
	std::ofstream myFile(filePath);

	myFile << "Title" << separator << "Value" << separator << "Percent" << separator << "Color" << separator << "\n";

	for(auto&& node : this->nodes)
	{
		myFile << node.title << separator << node.value << separator << node.percent << separator << node.color << separator << "\n";
	}
	
	myFile.close();
}

void DataTable::ParseString(const vector<string>& input)
{
	if (input.empty() || input.size() < 3)
		return;

	DataNode newNode;

	newNode.title = input[0];
	newNode.value = stod(input[1]);
	newNode.percent = stoi(input[2]);
	
	int rgbInt[3], k = 0;
	string rgb = input[3], word = "";
	
	for(int i = 0; i < input[3].size(); i++)
	{
		if(rgb[i] == ',' || rgb[i] == ')')
		{
			rgbInt[k] = stoi(word);
			k++;
			word = "";
		}
		else if(word == "RGB(")
			word = rgb[i];
		else
		{
			word += rgb[i];
		}
	}
	
	int r, g, b;
	r = rgbInt[0];
	g = rgbInt[1];
	b = rgbInt[2];
	
	if (rgbInt[0] < 0 || rgbInt[0] > 255)
		r = 0;
	if (rgbInt[1] < 0 || rgbInt[1] > 255)
		g = 0;
	if (rgbInt[2] < 0 || rgbInt[2] > 255)
		b = 0;
	
	newNode.color = RGBColor();

	this->Add(newNode);
}
