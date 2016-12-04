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
void PrintTree(Tree *p);  // ������ ��������� ������ ����
void FindRelations(Tree *tree);
void GetRelations(Tree *first, Tree *second);
bool IsParent(Tree *parent, Tree *child);
Tree *GetChilds(Tree *tree, char* name);
Tree *GetParent(Tree *first, Tree *second);