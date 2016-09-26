#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
int p = 0;
int i = 0;
int k = 0;
int z = 0;
char *imo;
struct shpion {
	char name[20];
	int period;
	int vrem9;
	shpion *next;
};
struct shpion kol[100];
struct Node //описание узла списка
{
	char *name;
	int period;
	int vrem9;
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
		printf("%s %d %d\n", tmp->next->name, tmp->next->period, tmp->next->vrem9);
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
	voz = kol[i].vrem9;
	Q->last->next = new Node;
	Q->last = Q->last->next;
	Q->last->name = im9; //добавление элемента в конец
	Q->last->vrem9 = voz;
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
	FILE *file;
	int s = 0;
	Node *tmp = Q->first;
	for (i = 0; i < k; i++)
	{
		file = fopen("output.txt", "a");
		z += tmp->next->period;
		if (z >= tmp->next->vrem9) {
			fprintf(file, "¬рем€ %d\n", tmp->next->vrem9);
			fprintf(file, "%s-покинул очередь\n", tmp->next->name);
			z = z - tmp->next->period;
			tmp = tmp->next;
			return 1;
		}
		else {
			fprintf(file, "¬рем€ %d\n", z - tmp->next->period);
			fprintf(file, "%s-начало наблюдени€\n", tmp->next->name);
			if (z - tmp->next->period > 0)
				fprintf(file, "%s-конец наблюдени€\n", imo);
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
	voz = tmp->next->vrem9;
	Q->last->next = new Node;
	Q->last = Q->last->next;
	Q->last->name = im9; //добавление элемента в конец
	Q->last->vrem9 = voz;
	Q->last->period = value;
	Q->last->next = NULL; //обнуление указател€ на следующий элемент
	Q->size++;
	imo = Q->last->name = im9;
}
int main() {
	setlocale(LC_ALL, "Russian");
	FILE *file;
	Queue Q;
	Creation(&Q);
	int j = 0;
	int y = 0;
	int z = 0;
	char *kolname;
	int kolperiod;
	int kolvrem9;
	if ((file = fopen("shpion.txt", "r")) == NULL)
	{
		printf("ошибка при прочтении");
		exit(1);
	}
	file = fopen("shpion.txt", "r");
	while (fscanf(file, "%s%d%d", kol[i].name, &(kol[i].period), &(kol[i].vrem9)) != EOF) {
		i++;
	}
	fclose(file);
	p = i;
	for (i = 0; i < p; i++) {
		kolname = kol[i].name;
		kolperiod = kol[i].period;
		kolvrem9 = kol[i].vrem9;
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
}