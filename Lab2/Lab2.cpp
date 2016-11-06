// TreeObhod.cpp: определяет точку входа для консольного приложения.
//
/*
В файле дерево в виде
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
Построить бинарное дерево. Обеспечить выдачу бинарного дерева в
3 порядках обхода. Выдать исходное дерево из бинарного. 
Имя входного файла - через командную строку. */

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
    printf("Бинарое дерево построено\n");
    getchar();
   /* printf("Вывод из бинарного дерева сильно ветвящегося\n");
    back_from_bin(root);
    getchar(); */
	printf("test ");
	printf(root->name);
    printf("Вывод бинарного дерева сверху вниз\n");
    print_down_bin(root, 0);
    getchar();
   /* printf("Вывод бинарного дерева снизу вверх\n");
    print_up_bin(root, 0);
    getchar();
    printf("Вывод бинарного дерева слева направо\n");
    print_right_bin(root, 0);
    getchar();*/
}
