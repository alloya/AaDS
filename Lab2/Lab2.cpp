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

int main(int argc, char* argv[])
{
    Tree *root = 0;
    FILE *Fin;
    setlocale(LC_ALL, "rus");
    if (argc != 2)
    {
       printf("\nNumber parameters is wrong");
       getchar();
       return -1;
    }
    Fin = fopen(argv[1], "r");
    if (Fin == NULL )
    {
         printf("\nCan not open file %s", argv[1]);
         getchar();
	 return -1;
    } 
    read_from_file(Fin, &root);
    printf("������� ������ ���������\n");
    getchar();
   /* printf("����� �� ��������� ������ ������ �����������\n");
    back_from_bin(root);
    getchar(); */
	printf("test ");
	printf(root->name);
    printf("����� ��������� ������ ������ ����\n");
    print_down_bin(root, 0);
    getchar();
   /* printf("����� ��������� ������ ����� �����\n");
    print_up_bin(root, 0);
    getchar();
    printf("����� ��������� ������ ����� �������\n");
    print_right_bin(root, 0);
    getchar();*/
}
