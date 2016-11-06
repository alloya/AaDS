#pragma once
#include "stdafx.h"


const int DL = 20;          // ������������ �����

using namespace std;

struct Tree
{
	char name[DL];
	int urov;
	Tree *fath;         // ���� � �������� ������
	Tree *left;
	Tree *right;
};

int read_from_file(FILE *F, Tree **r);  // ������ �� �����, ������������ ������
void back_from_bin(Tree *p);            // ������ �������� ������ �� ��������� 
void print_down_bin(Tree *p, int lev);  // ������ ��������� ������ ����
void print_up_bin(Tree *p, int lev);    // ������ ��������� ����� �����
void print_right_bin(Tree *p, int lev); // ������ ��������� ����� �������