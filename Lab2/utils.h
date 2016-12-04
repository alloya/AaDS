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
void PrintTree(Tree *p, int lev);  // выдача бинарного сверху вниз
void FindRelations(Tree *tree);