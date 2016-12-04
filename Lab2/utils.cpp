#include "stdafx.h"
#include "utils.h"

using namespace std;

bool CheckInput(int argc)
{
	if (argc != 2)
	{
		printf("\nNumber of parameters is wrong. Usage: Lab2.exe <filename>");
		return false;
	}
	return true;
}

bool OpenFile(FILE *Fin, char* fileName)
{
	Fin = fopen(fileName, "r");
	if (Fin == NULL)
	{
		printf("\nCan not open file %s", fileName);
		return false;
	}
	return true;
}

int ReadFile(FILE *F, Tree **r)
{
	char buf[DL];
	int i, k, m, len;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // уровень вершины
	t = 0;
	while (!feof(F))
	{
		k = fscanf(F, "%s", buf);
		len = strlen(buf);
		if (len == 0) break;            // если конец файла в следующей строке
		k = 0;
		while (buf[k] == '.') k++;     // k-уровень вершины
		p = new Tree;
		strncpy(p->name, &buf[k], len - k + 1);  // 0-(k-1) - точки, (k-1)-(len-1) - имя, \0 - конец строки
		buf[0] = '\0';                  // если конец файла в следующей строке
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // корень
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // переход на следующий уровень
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)            // тот же уровень
		{
			t->right = p;
			p->fath = t->fath;  // отец тот же
		}
		else        // подъем по дереву на m-k уровней
		{
			q = t;
			for (i = 0; i < m - k; i++) q = q->fath;
			// q - предыдущая вершина того же уровня
			p->fath = q->fath;   // отец тот же, что у брата
			q->right = p;
		}
		m = k;      // текущий уровень
		t = p;      // текущая вершина
	}
	fclose(F);

	printf("Бинарое дерево построено\n");
	getchar();
	return 0;
}

void FindRelations(Tree *tree)
{
	printf("Введите имена двух людей\n");
	string firstName, secondName;
	cin >> firstName;
	cin >> secondName;
	//GetRelatives(tree, firstName);
}

void PrintTree(Tree *p, int level)
{
	if (p)
	{
		for (int i = 0; i < level; i++)
			printf("%c", '.');
		printf("%s\n", p->name);
		PrintTree(p->left, level + 1);
		PrintTree(p->right, level + 1);
	}
}

Tree  *GetRelatives(Tree *tree, char* name)
{
	Tree *result = 0;
	if (tree != 0)
	{
		if (strcmp(name, tree->name) == 0)
		{
			return tree;
		}
		result = GetRelatives(tree->right, name);
		if (result == 0)
			result = GetRelatives(tree->left, name);
	}
	return result;
}