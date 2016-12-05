// TreeObhod.cpp: определяет точку входа для консольного приложения.
//
/*
В файле дерево в виде
Ann
.Boris
..Cat
..Dora
...Eva
...Fred
..Goga
...Helmut
....Marta
.....Bred
.....Stiv
.....Jon
......Tom
...Nata
.Nina
Построить бинарное дерево. Обеспечить выдачу бинарного дерева в
3 порядках обхода. Выдать исходное дерево из бинарного. 
Имя входного файла - через командную строку. */

#include "stdafx.h"   
#include "utils.h"
using namespace std;

int main(int argc, char* argv[])
{
    Tree *root = 0;
    FILE *Fin;
    setlocale(LC_ALL, "rus");
	if (!CheckInput(argc))
	{
		return -1;
	}
	Fin = fopen(argv[1], "r");
	if (!OpenFile(Fin, argv[1]))
	{
		return -1;
	}
	ReadFile(Fin, &root);
	PrintTree(root);

	cout << "Enter two different names" << endl;
	while (!cin.eof() && !cin.fail())
	{
		FindRelations(root);
	}
}
