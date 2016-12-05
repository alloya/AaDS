// TreeObhod.cpp: ���������� ����� ����� ��� ����������� ����������.
//
/*
� ����� ������ � ����
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
��������� �������� ������. ���������� ������ ��������� ������ �
3 �������� ������. ������ �������� ������ �� ���������. 
��� �������� ����� - ����� ��������� ������. */

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
