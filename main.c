#include "Header.h"

int main() {
	tree *root = NULL;
	int N = 0, rec = 0;
	while (root == NULL) { // Цикл для создание и заполнения текстового файла и дерева
		system("cls");
		Create_Textfile(); // Создание и заполнение текстового файла
		root = Create_Tree(); // Создание дерева
	}
	printf("Tree in the default order:\n");
	Print_Tree(root);// Вывод элементов дерева по возрастанию
	printf("\n");
	printf("------------------------------------------------\n");
	printf("Tree in the reverse order:\n"); 
	Print_Reverse_Tree(root); // Вывод элементов дерева по убыванию
	printf("\n");
	printf("------------------------------------------------\n");
	printf("Tree in the straight order:\n");
	Print_Straight(root);
	printf("\n");
	printf("------------------------------------------------\n");
	printf("Tree in the wide order:\n");
	WidePrint(root); // Вывод дерева при обходе в ширину
	printf("------------------------------------------------\n\n");
	while ((N = Input_N()) == 0) // Ввод уровня, на котором нужно посчитать количество слов
		N = Input_N;
	
	Task(root, 1, N, &rec); // Вызов рекурентной функции задания
	printf("At the %d level - %d word(s).\n", N, rec); // Вывод количества слов на уровне N
	Free_Tree(root); // Вызов функции очистки узлов дерева
	system("pause");
	return 0;
}


