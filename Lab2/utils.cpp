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
	size_t len;
	int i, k, m;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // ������� �������
	t = 0;
	while (!feof(F))
	{
		k = fscanf(F, "%s", buf);
		len = strlen(buf);
		if (len == 0) break;            // ���� ����� ����� � ��������� ������
		k = 0;
		while (buf[k] == '.') k++;     // k-������� �������
		p = new Tree;
		strncpy(p->name, &buf[k], len - k + 1);  // 0-(k-1) - �����, (k-1)-(len-1) - ���, \0 - ����� ������
		buf[0] = '\0';                  // ���� ����� ����� � ��������� ������
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // ������
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // ������� �� ��������� �������
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)            // ��� �� �������
		{
			t->right = p;
			p->fath = t->fath;  // ���� ��� ��
		}
		else        // ������ �� ������ �� m-k �������
		{
			q = t;
			for (i = 0; i < m - k; i++) q = q->fath;
			// q - ���������� ������� ���� �� ������
			p->fath = q->fath;   // ���� ��� ��, ��� � �����
			q->right = p;
		}
		m = k;      // ������� �������
		t = p;      // ������� �������
	}
	fclose(F);

	printf("Binary tree was built.\n");
	return 0;
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

char *ToChar(string string)
{
	char *newChar = new char[DL];
	strcpy(newChar, string.c_str());
	return newChar;
}

bool FindRelations(Tree *tree)
{
	cout << endl;
	Tree *first = 0;
	Tree *second = 0;
	string firstName, secondName;
	cin >> firstName;
	cin >> secondName;

	first = GetChilds(tree, ToChar(firstName));
	second = GetChilds(tree, ToChar(secondName));

	if (GetRelations(first, second, tree))
		return true;
	return false;
}

bool GetRelations(Tree *first, Tree *second, Tree *tree)
{
	if ((first == 0) || (second == 0))
	{
		cout << "One or more name is not in the list." << endl;
		return false;
	}

	if (first == second)
	{
		cout << "Please enter different names." << endl;
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
			cout << "Closest parent of " << first->name << " and " << second->name 
				<< " is " << parent->name << endl;
		}
	}
	return true;
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
	Tree *firstTree = first;
	Tree *secondTree = second;
	if (firstTree->urov != secondTree->urov)
	{
		while (firstTree->urov > secondTree->urov)
		{
			firstTree = firstTree->fath;
		}
		while (secondTree->urov > firstTree->urov)
		{
			secondTree = secondTree->fath;
		}
	}
	while ((firstTree != secondTree) && (firstTree != 0))
	{
		firstTree = firstTree->fath;
		secondTree = secondTree->fath;
	}
	if (firstTree == secondTree)
	{
		return firstTree;
	}
	else return 0;
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