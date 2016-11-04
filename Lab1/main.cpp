#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>

using namespace std;

struct SpyData
{
	char name[20];
	int activeTime;
	int allTime;
	int test;
};

void DeleteSpyFromQueue(vector<SpyData> &spyQueue, char *spyName, int timeMoment)
{
	int i = 0;
	vector<SpyData>::iterator number = spyQueue.begin();
	for (i = 0; i < spyQueue.size(); ++i)
	{
		if (!strcmp(spyName, spyQueue[i].name))
		{
			number += i;
			break;
		}
	}
	
	cout << "Moment " << timeMoment << " : \t" << spyQueue[i].name << " left queue." << endl;
	spyQueue.erase(number);
}

void isAnySpyHasToGoRightNow(vector<SpyData> &spyQueue, int time)
{
	for (size_t i = 0; i < spyQueue.size(); i++)
	{
		if (time >= spyQueue[i].allTime)
		{
			DeleteSpyFromQueue(spyQueue, spyQueue[i].name, time);
		}
	}
}

void MoveQueue(vector<SpyData> &spyQueue, int timeMoment)
{
	cout << "Moment " << timeMoment << " : \t" << spyQueue[0].name << " moved to the end of queue." << endl;
	spyQueue.push_back(spyQueue[0]);
	spyQueue.erase(spyQueue.begin());
	
}

vector<SpyData> IsHeWillStayForFullWatch(vector<SpyData> &inputVector, int currSpy, int currtime)
{
	vector<SpyData> vecToDelete;
	for (int i = 0; i < inputVector.size(); ++i)
	{
		if ((inputVector[i].allTime < (currtime + inputVector[currSpy].activeTime)))
		{
			vecToDelete.push_back(inputVector[i]);
		}
	}
	
	return vecToDelete;
}

void PrintVector(vector<SpyData> vector)
{
	for (size_t k = 0; k < vector.size(); ++k)
	{
		cout.width(15);
		cout << vector[k].name << "\tActive time: " << vector[k].activeTime << "\tAll time: " << vector[k].allTime << endl;
	}
}

void CalculateQueue(vector<SpyData> &inputVector)
{
	int currTime = 0;
	vector<SpyData> listToDelete;
	while (inputVector.size() != 1)
	{
		for (size_t i = 0; i < inputVector.size(); i++)
		{
			cout << "Moment " << currTime << " : \t" << inputVector.front().name << " started his watch." << endl;
			isAnySpyHasToGoRightNow(inputVector, currTime);
			listToDelete = IsHeWillStayForFullWatch(inputVector, i, currTime);
			if (!listToDelete.empty())
			{
				for (int k = 0; k < listToDelete.size(); ++k)
				{
					currTime = listToDelete[k].allTime;
					DeleteSpyFromQueue(inputVector, listToDelete[k].name, currTime);
				}
			}
			else
			{
				currTime += inputVector[i].activeTime;
				MoveQueue(inputVector, currTime);
			}
			isAnySpyHasToGoRightNow(inputVector, currTime);
			i = inputVector.size();
		}
	}
	cout << "Moment " << inputVector.front().allTime << " : \t" << inputVector.front().name << " left queue." << endl;
	return;
}

int main()
{
	SpyData spy[100];
	vector<SpyData> spyQueue;
	FILE *data;
	int i = 0;
	if ((data = fopen("spy.txt", "r")) == NULL)
	{
		printf("ошибка при прочтении");
		exit(1);
	}
	data = fopen("spy.txt", "r");
	while (fscanf(data, "%s%d%d", spy[i].name, &(spy[i].activeTime), &(spy[i].allTime)) != EOF) 
	{
		spyQueue.push_back(spy[i]);
		i++;
	}
	
	PrintVector(spyQueue);
	CalculateQueue(spyQueue);
	return 0;
}



