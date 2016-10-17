#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

struct SpyData
{
	char name[20];
	int activeTime;
	int allTime;
};

void DeleteSpyFromQueue(vector<SpyData> &spyQueue, int spyNumber, int timeMoment)
{
	vector<SpyData>::iterator number = spyQueue.begin();
	number += spyNumber;
	cout << "Moment " << timeMoment << " : \t" << spyQueue[spyNumber].name << " left queue." << endl;
	spyQueue.erase(number);
}

void isAnySpyHasToGoRightNow(vector<SpyData> &spyQueue, int time)
{
	for (size_t i = 0; i < spyQueue.size(); i++)
	{
		if (time >= spyQueue[i].allTime)
		{
			DeleteSpyFromQueue(spyQueue, i, time);
		}
	}
}

void MoveQueue(vector<SpyData> &spyQueue)
{
	spyQueue.push_back(spyQueue[0]);
	spyQueue.erase(spyQueue.begin());
}

bool IsHeWillStayForFullWatch(vector<SpyData> &vector, int currSpy, int currtime)
{
	return (!(vector[currSpy].allTime < (currtime + vector[currSpy].activeTime)));
}

void PrintVector(vector<SpyData> vector)
{
	for (size_t k = 0; k < vector.size(); ++k)
	{
		cout.width(15);
		cout << vector[k].name << "\tActive time: " << vector[k].activeTime << "\tAll time: " << vector[k].allTime << endl;
	}
}

void CalculateQueue(vector<SpyData> &vector)
{
	int currTime = 0;
	while (vector.size() != 1)
	{
		for (size_t i = 0; i < vector.size(); i++)
		{
			cout << "Moment " << currTime << " : \t" << vector.front().name << " started his watch." << endl;
			isAnySpyHasToGoRightNow(vector, currTime);
			if (!IsHeWillStayForFullWatch(vector, i, currTime))
			{
				currTime = vector[i].allTime;
			}
			else
			{
				currTime += vector[i].activeTime;
				MoveQueue(vector);
			}
			isAnySpyHasToGoRightNow(vector, currTime);
			i = vector.size();
		}
	}
	cout << "Moment " << vector.front().allTime << " : \t" << vector.front().name << " left queue." << endl;
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



