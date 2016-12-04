#pragma once
#include "stdafx.h"


const int DL = 20;          // ������������ �����

struct Tree
{
	char name[DL];
	int urov;
	Tree *fath;         // ���� � �������� ������
	Tree *left;
	Tree *right;
};

bool CheckInput(int argc);
bool OpenFile(FILE *Fin, char* fileName);
int ReadFile(FILE *F, Tree **r);  // ������ �� �����, ������������ ������
void PrintTree(Tree *p, int lev);  // ������ ��������� ������ ����
void FindRelations(Tree *tree);