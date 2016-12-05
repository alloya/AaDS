#pragma once
#include "stdafx.h"


const int DL = 20;          // максимальная длина

struct Tree
{
	char name[DL];
	int urov;
	Tree *fath;         // отец в исходном дереве
	Tree *left;
	Tree *right;
};

bool CheckInput(int argc);
bool OpenFile(FILE *Fin, char* fileName);
int ReadFile(FILE *F, Tree **r);  // чтение из файла, формирование дерева
void PrintTree(Tree *p);  // выдача бинарного сверху вниз
bool FindRelations(Tree *tree);
bool GetRelations(Tree *first, Tree *second, Tree *tree);
bool IsParent(Tree *parent, Tree *child);
Tree *GetChilds(Tree *tree, char* name);
Tree *GetParent(Tree *first, Tree *second);