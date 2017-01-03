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

vector<size_t> FindAdjustedVertex(AdjacencyMatrix matrix, size_t index)
{
	vector<size_t> adjustedVertex;
	for (size_t i = 1; i < matrix.size(); ++i)
	{
		if (matrix[index][i] != 0)
		{
			adjustedVertex.push_back(i);
		}
	}
	return adjustedVertex;
}


size_t RowSum(vector<int> row)
{
	size_t sum = 0;
	for (size_t i = 0; i < row.size(); ++i)
	{
		sum += row[i];
	}
	return sum;
}


void FillMinWay(AdjacencyMatrix& way, size_t srcIndex, size_t destIndex)
{
	/*for each (int elem in way[srcIndex])
	{
		way[destIndex][elem] = way[srcIndex][elem];
	}*/
	for (size_t i = 0; i < way.size(); ++i)
	{
		way[destIndex][i] = way[srcIndex][i];
	}
}

void FindMinWay(const AdjacencyMatrix& matrix, AdjacencyMatrix& way, size_t index)
{
	//vector<size_t> vertexes = FindAdjustedVertex(matrix, index);
	//assert(vertexes.size() != 0);
	//size_t minWay = RowSum(way[vertexes[0]]);
	//size_t minWayvertex = vertexes[0];
	//for each (size_t elem in way[index])
	//{
	//	if (RowSum(way[vertexes[elem]]) < minWay)
	//	{
	//		minWay = RowSum(way[vertexes[elem]]);
	//		minWayvertex = elem;
	//	}
	//}
	//FillMinWay(way, minWayvertex, index);
}

void ClearRow(AdjacencyMatrix& row, size_t rowNumder)
{
	for (size_t i = 0; i < row.size(); ++i)
	{
		if (row[rowNumder][i] != 0)
		{
			row[rowNumder][i] = 0;
		}
	}
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
			ResizeMatrix(way, maxValue);
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

void PrintPath(const AdjacencyMatrix& way, size_t vertex)
{
	if (vertex <= way.size())
	{
		if (vertex != 1)
		{
			cout << "Путь до вершины " << vertex << ":  Начало ";
			for (size_t i = 0; i < way.size(); i++)
			{
				{
					if (way[vertex - 1][i] != 0)
					{
						cout << "-> " << i + 1 << "(" << way[vertex - 1][i] << ")";
					}
				}
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
		cout << "Такой вершины нет в графе." << endl;
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
	//const int& maximum = maxIndex;
	cout << "Полученная матрица смежности" << endl;
	PrintMatrix(matrix);
	//cout << "------------------------" << endl;
	//Printmatrix(way);

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
						way[i][i] = matrix[minIndex][i];
						cout << "way[" << i << "][" << i << "] = " << way[i][i] << endl;
						if (RowSum(way[i]) < temp)
						{
							ClearRow(way, i);
							if (matrix[0][minIndex] == 0)
							{
								FillMinWay(way, minIndex, minIndex + 1);
							}
							else
							{
								way[i][minIndex] = matrix[0][minIndex];
							}
							way[i][i] = matrix[minIndex][i];
							//way[i][minIndex] = FindMinWay(matrix, minIndex);
							
							cout << "way[" << i << "][" << minIndex << "] = " << way[i][minIndex] << endl;
						}
						PrintMatrix(way);
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
		PrintPath(way, vertexToLookFor);
	}
	return 0;
}