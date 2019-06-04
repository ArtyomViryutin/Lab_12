#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#define A 100

typedef struct tree {  // Узел дерева
	char *word;  // Указатель на слово
	int count;   // Число вхождений
	struct tree *left;  // Левый потомок
	struct tree*right;  // Правый потомок
}tree;

tree *Add_Tree(tree *p, char *w); // Рекурсивная функция добавления узла к дереву
void Free_Tree(tree *tree); // Рекурсивная функция удаления поддерева
void Print_Tree(tree *p); // Рекурсивная функция вывода дерева (инфиксный обход)
void Print_Reverse_Tree(tree *p); // Рекурсивная функция вывода дерева (постфиксный обход)
int Check_Str(char *str); // Функция проверки ввода строки
int Create_Textfile(); // Функция создания и заполнения текстового файла
tree *Create_Tree(); // Функция создания дерева
int Input_N(); // Функция ввода уровня, на котором нужно посчитать количество слов
int PrintLevel(tree* element, int* s, int p, int level); // Рекурсивная функция вывода определенного уровня дерева (level)
void WidePrint(tree* first); // Функция вывода дерева по уровням (обход в ширину)
void Task(tree *element, int p, int N, int* rec); // Рекурсивная функция задания

