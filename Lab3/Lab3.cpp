// Lab3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
using namespace std;
typedef vector<vector<int>> AdjacencyMatrix;


bool CheckInput(int argc)
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl << "Usage: lab3.exe <txt file>" << endl;
		return false;
	}
	return true;
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

void Resizematrix(AdjacencyMatrix& matrix, size_t maxValue)
{
	matrix.resize(maxValue);
	for (auto& row : matrix)
	{
		row.resize(maxValue, 0);
	}
}

void BuildMatrix(istream& inputStream, AdjacencyMatrix& matrix)
{
	string buffer;
	while (getline(inputStream, buffer))
	{
		stringstream ss(buffer);
		int firstValue, secondValue, weight;
		ss >> firstValue >> secondValue >> weight;

		size_t maxValue = max(firstValue, secondValue);
		if (matrix.size() < maxValue)
		{
			Resizematrix(matrix, maxValue);
		}

		--firstValue;
		--secondValue;
		matrix[firstValue][secondValue] = matrix[secondValue][firstValue] = weight;
	}
}

void Printmatrix(AdjacencyMatrix& matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		cout.width(5);
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			cout.width(5);
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void PrintFinalTable(size_t maxIndex, vector<size_t> distance)
{
	for (size_t i = 0; i < maxIndex; i++)
	{
		cout << "Расстояние до вершины " << i+1 << " = " << distance[i] << endl;
	}
	cout << endl;
}

int main(int argc, char * argv[]) 
{
	setlocale(LC_ALL, "Rus");
	if (!CheckInput(argc))
	{
		return 1;
	}

	ifstream input(argv[1]);
	if (!CheckArguments(input))
	{
		return 1;
	}

	AdjacencyMatrix matrix;
	BuildMatrix(input, matrix);
	size_t temp;
	size_t minIndex, max;
	size_t maxIndex = matrix.size();
	cout << "Полученная матрица смежности" << endl;
	Printmatrix(matrix);

	//Для каждой вершины задаем статус посещённости false и дистанцию до нее стремящейся к бесконечности 
	vector<size_t> distance;
	vector<bool> checked;
	
	for (size_t i = 0; i < maxIndex; i++) 
	{
		distance.push_back(INT_MAX);
		checked.push_back(false);
	}
	distance[0] = 0;
	// Шаг алгоритма
	do 
	{
		PrintFinalTable(maxIndex, distance);
		minIndex = INT_MAX;
		max = INT_MAX;
		for (size_t i = 0; i < maxIndex; i++)
		{
			if (!checked[i] && (distance[i] < max))
			{
				max = distance[i];
				minIndex = i;
				
			}
			
		}
		//getchar();
		cout << "Начинаем обход вершин, соединенных с вершиной [" << minIndex + 1 << "]" << endl;
		if (minIndex != INT_MAX)
		{
			for (size_t i = 0; i < maxIndex; i++) 
			{
				if (matrix[minIndex][i] > 0)
				{
					temp = max + matrix[minIndex][i];
					if (temp < distance[i])
					{
						distance[i] = temp;
						cout << "Путь до вершины [" << i + 1 << "] становится равным " << temp << " = " << max << " + " << matrix[minIndex][i] << endl;
					}
					else
					{
						cout << "Путь до вершины [" << i + 1 << "] не изменяется, т.к. " << distance[i] << " < " << max << " + " << matrix[minIndex][i] << endl;
					}
				}
			}
			checked[minIndex] = true;
			cout << "Вершина [" << minIndex + 1 << "] посещена." << endl << endl;
		}
		
	} 
	
	while (minIndex < INT_MAX);
	
	getchar(); 
	
}