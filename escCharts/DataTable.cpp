#include "DataTable.h"
#include <algorithm>
#include <fstream>
#include <sstream>

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

void DataTable::Unite(const DataTable& table)
{
	if (table.nodes.empty())
		return;

	for(auto&& node : table.nodes)
		this->nodes.push_back(node);
}

void DataTable::ReadFromFile(const string& filePath, const char& separator = ';')
{
	std::vector<std::pair<std::string, std::vector<int>>> result;

	// Create an input filestream
	std::ifstream myFile(filePath);

	// Make sure the file is open
	if (!myFile.is_open()) throw std::runtime_error("Could not open file");

	// Helper vars
	std::string line, colname;
	int val;

	// Read the column names
	if (myFile.good())
	{
		// Extract the first line in the file
		std::getline(myFile, line);

		// Create a stringstream from line
		std::stringstream ss(line);

		// Extract each column name
		while (std::getline(ss, colname, separator)) {

			// Initialize and add <colname, int vector> pairs to result
			result.push_back({ colname, std::vector<int> {} });
		}
	}

	// Read data, line by line
	while (std::getline(myFile, line))
	{
		// Create a stringstream of the current line
		std::stringstream ss(line);

		// Keep track of the current column index
		int colIdx = 0;

		// Extract each integer
		while (ss >> val) {

			// Add the current integer to the 'colIdx' column's values vector
			result.at(colIdx).second.push_back(val);

			// If the next token is a comma, ignore it and move on
			if (ss.peek() == ',') ss.ignore();

			// Increment the column index
			colIdx++;
		}
	}

	// Close file
	myFile.close();
}

void DataTable::SaveToFile(const string& filePath, const char& separator = ';')
{
	if (this->nodes.empty())
		return;
	
	std::ofstream myFile(filePath);

	vector<string> colnames;
	colnames.push_back("Title");
	colnames.push_back("Value");
	colnames.push_back("Percent");
	colnames.push_back("Color");
	
	for (auto& colname : colnames)
		myFile << colname << separator;

	myFile << "\n";

	for(auto&& node : this->nodes)
	{
		myFile << node.title << separator << node.value << separator << node.percent << separator << node.color << "\n";
	}
	
	myFile.close();
}