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

	printf("Binary tree was built.\n");
	return 0;
}

char *ToChar(string string)
{
	char *newChar = new char[DL];
	std::strcpy(newChar, string.c_str());
	return newChar;
}

void FindRelations(Tree *tree)
{
	Tree *first = 0, *second = 0;
	cout << "Enter two different names" << endl;
	string firstName, secondName;
	cin >> firstName;
	cin >> secondName;

	first = GetChilds(tree, ToChar(firstName));
	second = GetChilds(tree, ToChar(secondName));

	GetRelations(first, second);


}

void GetRelations(Tree *first, Tree *second)
{
	if (first == second)
	{
		cout << "Please enter different names." << endl;
	}
	if ((first == 0) || (second == 0))
	{
		cout << "One or more name is not in the list." << endl;
	}
	

	if (IsParent(first, second))
	{
		cout << first->name << " is parent of " << second->name << endl;
	}
	else if (IsParent(second, first))
	{
		cout << second->name << " is parent of " << first->name << endl;
	}
	else
	{
		Tree *parent = GetParent(first, second);
		if (parent != 0)
		{
			cout << "Parent of " << first->name << " and " << second->name 
				<< " is " << parent->name << endl;
		}
		else
		{
			cout << first->name << " and " << second->name 	<< " are not close relatives." << endl;
		}
	}
}

bool IsParent(Tree *parent, Tree *child)
{
	if (parent->urov >= child->urov)
	{
		return false;
	}

	Tree *tmp = child;
	while (tmp->urov > parent->urov)
	{
		tmp = tmp->fath;
	}
	if (tmp == parent)
		return true;
	return false;
}

Tree *GetParent(Tree *first, Tree *second)
{
	Tree *tmp1 = first;
	Tree *tmp2 = second;
	if (tmp1->urov != tmp2->urov)
	{
		while (tmp1->urov > tmp2->urov)
		{
			tmp1 = tmp1->fath;
		}
		while (tmp2->urov > tmp1->urov)
		{
			tmp2 = tmp2->fath;
		}
	}
	while ((tmp1 != tmp2) && (tmp1 != 0))
	{
		tmp1 = tmp1->fath;
		tmp2 = tmp2->fath;
	}
	if (tmp1 == tmp2)
	{
		return tmp1;
	}
	else return 0;
}

void PrintTree(Tree *p)
{
	int i, j;
	char st[DL];
	if (p)
	{
		for (i = 0; i < p->urov; i++) st[i] = '.';
		j = 0;
		while (st[i++] = (p->name)[j++]);
		printf("%s\n", st);
		PrintTree(p->left);
		PrintTree(p->right);
	}
}

Tree *GetChilds(Tree *tree, char* name)
{
	Tree *result = 0;
	if (tree != 0)
	{
		if (strcmp(name, tree->name) == 0)
		{
			return tree;
		}
		result = GetChilds(tree->right, name);
		if (result == 0)
			result = GetChilds(tree->left, name);
	}
	return result;
}