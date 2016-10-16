#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>
#include <queue>

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
	cout << "Moment " << timeMoment << " : " << spyQueue[spyNumber].name << " left queue." << endl;
	//cout << "vector size = " << spyQueue.size() << endl ;
	spyQueue.erase(number);
	//cout << "vector size = " << spyQueue.size() << endl ;
}

//void isAnySpyHasToGo(vector<SpyData> &spyQueue, int time)
//{
//	for (int i = 0; i < spyQueue.size(); i++)
//	{
//		if (time >= spyQueue[i].allTime)
//		{
//			DeleteSpyFromQueue(spyQueue, i, time);
//		}
//	}
//}

void isAnySpyHasToGoRightNow(vector<SpyData> &spyQueue, int time)
{
	for (int i = 0; i < spyQueue.size(); i++)
	{
		if (time >= spyQueue[i].allTime)
		{
			DeleteSpyFromQueue(spyQueue, i, time);
			//cout << "Deleted elem" << i << " in isAnySpyHasToGoRightNow" << endl;
		}
	}
}

void MoveQueue(vector<SpyData> &spyQueue)
{
	//cout << spyQueue[0].name << endl;
	spyQueue.push_back(spyQueue[0]);
	//cout << "first elem pushed back" << endl;
	spyQueue.erase(spyQueue.begin());
	//cout << spyQueue[0].name << endl;
}

void CalculateQueue1(vector<SpyData> &spyQueue)
{
	int timeMoment = 0;
	cout << "The watch has begun." << endl;
	while (spyQueue.size() != 1)
	{
		
		for (int i = 0; i < 3; i++)
		{
			isAnySpyHasToGoRightNow(spyQueue, timeMoment);
			cout << "Moment " << timeMoment << " : " << spyQueue[i].name << " started his watch." << endl;
			timeMoment += spyQueue[i].activeTime;
			MoveQueue(spyQueue);
			cout << "next iteration" << endl;
		}
	}
	cout << "Moment " << spyQueue[0].allTime << " : " << spyQueue[0].name << " ended his watch." << endl;
	spyQueue.clear();
}

bool IsHeWillStayForFullWatch(vector<SpyData> &vector, int currSpy, int currtime)
{
	if (vector[currSpy].allTime < (currtime + vector[currSpy].activeTime))
	{
		//int newTime = vector[currSpy].allTime;
		//cout << "CheckForFullWatch = true" << endl;;
		//DeleteSpyFromQueue(vector, currSpy, vector[currSpy].allTime);
		//return vector[currSpy].allTime;
		return true;
	}
	return false;
}

void PrintVector(vector<SpyData> vector)
{
	//cout << "vector order:  ";
	for (int k = 0; k < vector.size(); ++k)
	{
		cout.width(15);
		cout << vector[k].name << "\t\tActive time: " << vector[k].activeTime << "\tAll time: " << vector[k].allTime << endl;
	}
	//cout << endl;
}

//void CalculateQueue2(vector<SpyData> &vector)
//{
//	int currTime = 0;
//	while(vector.size())
//	{
//		//int i = 0;
//		for (int i = 0; i < vector.size(); i++)
//		{
//			cout << "Moment " << currTime << " : " << vector[i].name << " started his watch." << endl;
//			if (!isAnySpyHasToGoRightNow)
//			{
//				DeleteSpyFromQueue(vector, i, currTime);
//			}
//			cout << "before check for full watch" << endl;
//			IsHeWillStayForFullWatch(vector, i, currTime);
//			cout << "before move queue" << endl;
//			currTime += vector[i].activeTime;
//			MoveQueue(vector);
//		}
//		//i++;
//	}
//}

void CalculateQueue(vector<SpyData> &vector)
{
	int currTime = 0;

	while (vector.size() != 1)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			cout << "iteration # " << i << endl;
			cout << "curr time = " << currTime << endl;
			//int activeTimeOfCurrSpy = vector[i].activeTime;
			cout << "Moment " << currTime << " : " << vector.front().name << " started his watch." << endl;
			isAnySpyHasToGoRightNow(vector, currTime);
			if (IsHeWillStayForFullWatch(vector, i, currTime))
			{
				currTime = vector[i].allTime;
			}
			else
			{
				currTime += vector[i].activeTime;
			}
			//currTime += activeTimeOfCurrSpy;
			
			MoveQueue(vector);
			cout << endl;
		}
	}
	cout << "Moment " << vector.front().allTime << " : " << vector.front().name << " left queue." << endl;
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

	//MoveQueue(spyQueue);
	//PrintVector(spyQueue);
	//isAnySpyHasToGo(spyQueue, 5);
	//DeleteSpyFromQueue(spyQueue, 1, spyQueue[1].allTime);
	//PrintVector(spyQueue);
	//CheckForFullWatch(spyQueue, 1, 4);
	CalculateQueue(spyQueue);
	//PrintVector(spyQueue);
	return 0;
}



