#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

using namespace std;

int p = 0;
int i = 0;
int k = 0;
int z = 0;
char *imo;
struct spy {
	char name[20];
	int period;
	int time;
	spy *next;
};
struct spy kol[100];

struct Node //описание узла списка
{
	char *name;
	int period;
	int time;
	Node *next; //указатель на следующий элемент
};

struct Queue //описание очереди
{
	int size; //счетчик размера очереди
	Node *first; //указатель на начало очереди
	Node *last; //указатель на конец очереди
};

void Creation(Queue *Q) //создание очереди
{
	Q->first = new Node;
	Q->first->next = NULL;
	Q->last = Q->first;
	Q->size = 0;
}

void Print(Queue *Q, char kolname, int kolperiod, int kolvrem9)
{
	Node *tmp = Q->first;
	for (i = 0; i < k; i++)
	{
		printf("%s %d %d\n", tmp->next->name, tmp->next->period, tmp->next->time);
		tmp = tmp->next;
	}
}
bool Full(Queue *Q) //проверка очереди на пустоту
{
	if (Q->first == Q->last) return true;
	else return false;
}
void Add(Queue *Q, char kolname, int kolperiod, int kolvrem9) //добавление элемента
{
	int value;
	int voz;
	char *im9;
	im9 = kol[i].name;
	value = kol[i].period;
	voz = kol[i].time;
	Q->last->next = new Node;
	Q->last = Q->last->next;
	Q->last->name = im9; //добавление элемента в конец
	Q->last->time = voz;
	Q->last->period = value;
	Q->last->next = NULL; //обнуление указател€ на следующий элемент
	Q->size++;
	imo = Q->last->name = im9;
}
void Delete(Queue *Q) //удаление элемента
{
	Node *tmp = Q->first;
	Q->first = Q->first->next; //смещение указател€
	Q->size--;
	delete tmp;
	printf("\nЁлемент удален\n\n");
};

int Size(Queue *Q) //размер очереди
{
	return Q->size;
}

int Proverka(Queue *Q)
{
	FILE *output;
	int s = 0;
	Node *tmp = Q->first;
	for (i = 0; i < k; i++)
	{
		//file = fopen("output.txt", "a");
		
		z += tmp->next->period;
		if (z >= tmp->next->time) {
			fprintf(output, "¬рем€ %d\n", tmp->next->time);
			fprintf(output, "%s-покинул очередь\n", tmp->next->name);
			z = z - tmp->next->period;
			tmp = tmp->next;
			return 1;
		}
		else {
			fprintf(output, "¬рем€ %d\n", z - tmp->next->period);
			fprintf(output, "%s-начало наблюдени€\n", tmp->next->name);
			if (z - tmp->next->period > 0)
				fprintf(output, "%s-конец наблюдени€\n", imo);
			tmp = tmp->next;
			return 0;
		}
	}

}
void Add1(Queue *Q, char kolname, int kolperiod, int kolvrem9) //добавление элемента
{
	Node *tmp = Q->first;
	int value;
	int voz;
	char *im9;
	im9 = tmp->next->name;
	value = tmp->next->period;
	voz = tmp->next->time;
	Q->last->next = new Node;
	Q->last = Q->last->next;
	Q->last->name = im9; //добавление элемента в конец
	Q->last->time = voz;
	Q->last->period = value;
	Q->last->next = NULL; //обнуление указател€ на следующий элемент
	Q->size++;
	imo = Q->last->name = im9;
}

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	
	FILE *file;
	Queue Q;
	Creation(&Q);
	int j = 0;
	int y = 0;
	int z = 0;
	char *kolname;
	int kolperiod;
	int kolvrem9;
	
	file = fopen("test.txt", "r");
	while (fscanf(file, "%s%d%d", kol[i].name, &(kol[i].period), &(kol[i].time)) != EOF) {
		i++;
	}
	fclose(file);
	p = i;
	for (i = 0; i < p; i++) {
		kolname = kol[i].name;
		kolperiod = kol[i].period;
		kolvrem9 = kol[i].time;
		Add(&Q, *kolname, kolperiod, kolvrem9);
	}
	k = Size(&Q);
	if (Full(&Q)) fprintf(file, "ќчередь пуста");
	else Print(&Q, *kolname, kolperiod, kolvrem9);
	system("pause");
	while (k != 0) {
		if (Proverka(&Q) == 0) {
			Add1(&Q, *kolname, kolperiod, kolvrem9);
			Delete(&Q);
		}
		else
			Delete(&Q);
		k = Size(&Q);
	}

	if (!output.flush()) 
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}


