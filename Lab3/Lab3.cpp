// Lab3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
using namespace std;

typedef vector<vector<int>> Graph;


bool CheckInput(int argc)
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl << "Usage: lab3.exe <txt file>" << endl;
		return false;
	}
	return true;
}

void ReadGraphFrom(istream& inputStream, Graph& graph)
{
	string buffer;
	while (getline(inputStream, buffer))
	{
		stringstream ss(buffer);
		int sourceIndex;
		int destinationIndex;
		int weight;
		ss >> sourceIndex >> destinationIndex >> weight;

		size_t maxIndex = max(sourceIndex, destinationIndex);
		--sourceIndex;
		--destinationIndex;
		if (graph.size() < maxIndex)
		{
			graph.resize(maxIndex);
			for (auto& line : graph)
			{
				line.resize(maxIndex, 0);
			}
		}
		graph[sourceIndex][destinationIndex] = graph[destinationIndex][sourceIndex] = weight;
	}
}

bool CheckArguments(ifstream & firstFile)
{
	if (!firstFile.is_open())
	{
		cout << "Failed to open one of the files" << endl;
		return false;
	}
	return true;
}

void PrintGraph(Graph& graph)
{
	for (size_t i = 0; i < graph.size(); ++i)
	{
		for (size_t j = 0; j < graph[i].size(); ++j)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char * argv[]) 
{
	if (!CheckInput(argc))
	{
		return 1;
	}

	ifstream input(argv[1]);
	if (!CheckArguments(input))
	{
		return 1;
	}
	Graph graph;
	ReadGraphFrom(input, graph);
	size_t temp;
	size_t minindex, min;
	size_t maxIndex = graph.size();
	cout << maxIndex << endl;
	PrintGraph(graph);

	vector<size_t> distance;
	cout << "1" << endl;
	vector<bool> checked;
	cout << "2" << endl;
	//Инициализация
	for (size_t i = 0; i < maxIndex; i++) 
	{
		cout << "3" << endl;
		distance.push_back(10000);
		cout << "4" << endl;
		checked.push_back(false);
	}
	cout << distance[0] << endl;
	distance[0] = 0;
	// Шаг алгоритма
	do {
		minindex = 10000;
		min = 10000;
		for (size_t i = 0; i < maxIndex; i++) {
			if ((checked[i] == false) && (distance[i]<min)) {
				min = distance[i];
				minindex = i;
			}
		}
		if (minindex != 10000) {
			for (size_t i = 0; i < maxIndex; i++) {
				if (graph[minindex][i] > 0) {
					temp = min + graph[minindex][i];
					if (temp < distance[i])
						distance[i] = temp;
				}
			}
			checked[minindex] = true;
		}
	} while (minindex < 10000);
	// Вывод матрицы связей
	for (size_t i = 0; i < maxIndex; i++)
		printf("%5d \n", distance[i]);
	getchar(); getchar();
	
}