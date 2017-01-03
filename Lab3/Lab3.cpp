// Lab3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <assert.h>
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

void ResizeMatrix(AdjacencyMatrix& matrix, size_t maxValue)
{
	matrix.resize(maxValue);
	for (auto& row : matrix)
	{
		row.resize(maxValue, 0);
	}
}

void BuildMatrix(istream& inputStream, AdjacencyMatrix& matrix, AdjacencyMatrix& way)
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
			ResizeMatrix(matrix, maxValue);
		}

		--firstValue;
		--secondValue;
		matrix[firstValue][secondValue] = matrix[secondValue][firstValue] = weight;
	}
}

void PrintMatrix(AdjacencyMatrix& matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		cout.width(5);
		cout << i + 1 << " Vertex: ";
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
		cout << "Расстояние до вершины " << i + 1 << " = ";
		if (distance[i] != INT_MAX)
		{
			cout << distance[i] << endl;
		}
		else
		{
			cout << "Infinity" << endl;
		}
	}
	cout << endl;
}

void CheckResidualVertex(vector<bool>& checked)
{
	for (vector<bool>::iterator it = checked.begin(); it != checked.end(); ++it)
	{
		if (!*it)
		{
			cout << "Вершина [" << distance(checked.begin(), it) + 1 << "] не связана с основным графом" << endl;
		}
	}
}

void PrintPath(const AdjacencyMatrix& way, size_t vertex, vector<bool> checked)
{
	if (vertex <= way.size())
	{
		if (checked[vertex - 1])
		{
			if (vertex != 1)
			{
				cout << "Путь до вершины " << vertex << ":  Начало ";
				vertex -= 1;
				for (size_t i = 0; i < way[vertex].size(); i++)
				{
					cout << "-> " << way[vertex][i];
				}
				cout << endl << endl;
			}
			else
			{
				cout << "Вы на месте." << endl << endl;
			}
		}
		else
		{
			cout << "Вершина [" << vertex << "] не связана с основным графом" << endl << endl;
		}
	}
	else
	{
		cout << "Такой вершины нет в графе." << endl << endl;
	}
	
}

void FillNewPath(AdjacencyMatrix& way, size_t destRow, size_t srcRow)
{
	way[destRow].clear();
	for (size_t i = 0; i < way[srcRow].size(); ++i)
	{
		way[destRow].resize(way[srcRow].size());
		way[destRow][i] = way[srcRow][i];
	}
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
	AdjacencyMatrix way;
	BuildMatrix(input, matrix, way);
	size_t temp;
	size_t minIndex, max;
	size_t maxIndex = matrix.size();
	way.resize(maxIndex);
	cout << "Полученная матрица смежности" << endl;
	PrintMatrix(matrix);

	//Для каждой вершины задаем статус посещённости false и дистанцию до нее стремящейся к бесконечности 
	vector<size_t> distance;
	vector<bool> checked;

	for (size_t i = 0; i < maxIndex; i++)
	{
		distance.push_back(INT_MAX);
		checked.push_back(false);
	}
	distance[0] = 0;
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
		if (minIndex != INT_MAX)
		{
			cout << "Начинаем обход вершин, соединенных с вершиной [" << minIndex + 1 << "]" << endl;
			for (size_t i = 0; i < maxIndex; i++)
			{
				if (matrix[minIndex][i] > 0)
				{
					temp = max + matrix[minIndex][i];
					if (temp < distance[i])
					{
						distance[i] = temp;
						cout << "Путь до вершины [" << i + 1 << "] становится равным " << temp << " = " << max << " + " << matrix[minIndex][i] << endl;
						if (max != 0)
						{
							FillNewPath(way, i, minIndex);
						}
						way[i].push_back(i+1);
						//PrintMatrix(way);
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
	} while (minIndex < INT_MAX);
	CheckResidualVertex(checked);
	int vertexToLookFor;
	
	while (!cin.eof() && !cin.fail())
	{
		cout << "Введите вершину путь до которой нужно отобразить: ";
		cin >> vertexToLookFor;
		PrintPath(way, vertexToLookFor, checked);
	}
	return 0;
}