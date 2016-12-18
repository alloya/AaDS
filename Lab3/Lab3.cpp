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
		--firstValue;
		--secondValue;
		if (matrix.size() < maxValue)
		{
			Resizematrix(matrix, maxValue);
		}
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

bool IsThereDirectWay(AdjacencyMatrix matrix, int firstPoint, int targetPoint)
{
	return matrix[firstPoint][targetPoint] != 0;
}

void FindMaxWeight(AdjacencyMatrix matrix, int firstPoint, int targetPoint)
{
	cout << IsThereDirectWay(matrix, firstPoint, targetPoint);
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

	AdjacencyMatrix matrix;
	BuildMatrix(input, matrix);
	//size_t temp;
	//size_t minindex, min;
	//size_t maxIndex = matrix.size();
	Printmatrix(matrix);

	int firstPoint, targetPoint;
	cout << endl << "Enter start point and target point: ";
	cin >> firstPoint >> targetPoint;

	FindMaxWeight(matrix, firstPoint, targetPoint);
/*
	vector<size_t> distance;
	vector<bool> checked;
	//Инициализация
	for (size_t i = 0; i < maxIndex; i++) 
	{
		distance.push_back(10000);
		checked.push_back(false);
	}
	distance[0] = 0;
	// Шаг алгоритма
	do 
	{
		minindex = 10000;
		min = 10000;
		for (size_t i = 0; i < maxIndex; i++) 
		{
			if ((checked[i] == false) && (distance[i]<min)) 
			{
				min = distance[i];
				minindex = i;
			}
		}
		
		if (minindex != 10000) 
		{
			for (size_t i = 1; i < maxIndex; i++) 
			{
				if (matrix[minindex][i] > 0) 
				{
					temp = min + matrix[minindex][i];
					if (temp < distance[i])
					{
						distance[i] = temp;
					}
				}
			}
			checked[minindex] = true;
		}
	} 
	while (minindex < 10000);
	// Вывод матрицы связей
	for (size_t i = 0; i < maxIndex; i++)
		printf("%5d \n", distance[i]);
	getchar(); getchar();
	*/
}