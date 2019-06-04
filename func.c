#include "Header.h"

// Рекурсивная функция добавления узла к дереву
tree *Add_Tree(tree *p, char *w) {
	int cond;
	if (p == NULL) {
		p = (tree *)malloc(sizeof(tree)); // Выделение память под узел
		p->word = (char*)malloc(strlen(w)); // Выделение память под слово
		strcpy(p->word, w); // Копируем слово в узел дерева
		p->count = 1; // Присваиваем счетчику слов в узле значение 1
		p->left = p->right = NULL;
	}
	// Сравниваем очередное слово со словами в узлах
	else if ((cond = strcmp(w, p->word)) == 0) // Если они равны, то увеличиваем значение счетчика
		p->count++;
	else if (cond < 0) // Если слово меньше чем слово в узле, то вызываем рекурсивную функцию добавления узла дерева
		p->left = Add_Tree(p->left, w); //  и предеаем в нее указатель на левое поддерево
	else
		p->right = Add_Tree(p->right, w); // Если больше, то передаем в нее указатель на правое поддерево
	return p;
}


// Рекурсивная функция удаления поддерева
void Free_Tree(tree *tree) {
	if (tree != NULL) {
		Free_Tree(tree->left); // Рекурсивный обход левого поддерева
		Free_Tree(tree->right); // Рекурсивный обход правого поддерева 
		free(tree); // Очистка узла дерева
	}
}


// Рекурсивная функция вывода дерева (инфиксный обход)
void Print_Tree(tree *p) {
	if (p != NULL) {
		Print_Tree(p->left);  // Рекурсивный обход левого поддерева
		printf("(%d) %s ", p->count, p->word); // Вывод сожержимого узла
		Print_Tree(p->right);  // Рекурсивный обход правого поддерева 
	}
}
// Рекурсивная функция вывода дерева (постфиксный обход)
void Print_Reverse_Tree(tree *p) {
	if (p != NULL) {

		Print_Reverse_Tree(p->right);  // Рекурсивный обход правого поддерева 
		printf("(%d) %s ", p->count, p->word);  // Вывод сожержимого узла
		Print_Reverse_Tree(p->left);  // Рекурсивный обход левого поддерева
	}
}
// Функция проверки ввода строки
int Check_Str(char *str) {

	if (str[0] == '\n') // Случай если строка пустая
	{
		printf("The string is empty.Try again.\n");  // Сообщение о том, что была введена пустая строка
		system("pause");
		return -1;
	}

	for (int i = 0; i < strlen(str) - 1; i++)  // Проверка на ввод только латинских букв и цифр
	{

		if (!(str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z' || str[i] == ' ' || isdigit(str[i])))
		{
			printf("Entered unacceptable string.Try again.\n");  // Сообщение о том, что файл был совершен некорректный ввод
			system("pause");
			return -1;
		}

	}
	return 0;
}

// Функция создания и заполнения текстового файла
int Create_Textfile() {			
	FILE *f;
	char str[A];
	if (!(f = fopen("textfile.txt", "wt"))) {	// Открываем текстовый файл для записи туда строк и проверяем на корректность открытия
		printf("File could not be open.\n");	// Сообщение о том, что файл не открывается
		system("pause");
		exit(1);
	}

	printf("Enter a string: ");
	fgets(str, A, stdin);  // Ввод стркоки


	while (Check_Str(str)) // Проверка на корректность ввода и повторый ввод в случае некорректного ввода
	{
		system("cls");
		printf("Enter a string: ");
		fgets(str, A, stdin);
	}

	fwrite(str, sizeof(char), strlen(str), f);	 // Записываем в файл нашу строку
	fclose(f);  // Закрываем файл
	return 0;
}
// Функция создания дерева
tree *Create_Tree()
{
	tree *root;
	root = NULL;
	FILE *f;
	char str[A];
	char *s;
	if (!(f = fopen("textfile.txt", "rt"))) {	// Открываем текстовый файл для чтения и проверяем на корректность открытия
		printf("File could not be open.\n");	// Сообщение о том, что файл не открывается
		system("pause");
		exit(1);
	}

	fgets(str, sizeof(str), f); // Записываем содержимое файла в массив

	char sep[] = { ' ','\n','\0' };  // Массив с разделительными символами

	s = strtok(str, sep);  // Поиск первой лексемы в строке

	root = Add_Tree(root, s);  // Добавления узла списка и возвращение указатель на него


	while (s != NULL)
	{
		if (strlen(s) > 20) { // Проверка слова на длину и в случае длины большей 20 повторный ввод
			printf("The string contain a word which length more than 20.Try again.\n");
			system("pause");
			return NULL;
		}
		s = strtok(NULL, sep); // Выделение очередной лексемы
		if (s == NULL) // Условие выхода из цикла
			break;

		root = Add_Tree(root, s); // Добавления узла списка и возвращение указатель на него
	}

	fclose(f); // Закрываем файл
	return root;
}


// Функция ввода уровня, на котором нужно посчитать количество слов
int Input_N() { 

	double k1; // Переменная для проверки ввода

	int k; // Переменная ввода

	printf("Enter the level at which you want to find out the number of words: ");

	if (!scanf("%lf", &k1) || k1 <= 0) { printf("The level must be an integer not equal to 0.\nTry again.\n");   while (getchar() != '\n'); return 0; }

	if (getchar() != '\n') { printf("The level must be an integer not equal to 0.\nTry again.\n"); while (getchar() != '\n'); return 0; }

	k = k1;

	if (k != k1) { printf("The level must be an integer not equal to 0.\nTry again.\n"); return 0; }

	return k;  // В случае корректного ввода возвращаем номер уровня
}
// Рекурсивная функция вывода определенного уровня дерева (level)
int PrintLevel(tree* element, int* s, int p, int level) {
	int rec = 0;
	if (p == 1) {  // Если этот вход первый 
		printf("\n%d:  ", level);
	}
	if ((element) && (p <= level)) {  // Переход на следующий уровень
		PrintLevel(element->left, s, p + 1, level);
		PrintLevel(element->right, s, p + 1, level);
	}
	if ((p == level) && (element)) {  // Вывод содержимого узла, если он находится на необходимом уровне
		printf("(%d) %s    ", element->count, element->word);
		if ((element->left) || (element->right)) {  // Нахождение элементов, у которых есть потомки
			(*s)++;
		}
	}
	if ((p == 1) && (*s)) { //возвращение 1, если на следующем уровне есть элементы
		return 1;
	}
	return 0;
}
// Функция вывода дерева по уровням (обход в ширину)
void WidePrint(tree* first) {
	int flag = 1; 
	int s = 0; 
	int p = 1; 
	int level = 1; 
	while (flag) { 
		flag = PrintLevel(first, &s, p, level); // Вызов рекурсивной функции вывода определенного уровня дерева (level)
		level++;  // Переход не следующий уровень
		s = 0;
	}
	printf("\n");
}
// Рекурсивная функция задания
void Task(tree *element, int p, int N, int* rec) {
	if ((element) && (p <= N)) { // Переход на необходимый уровень N
		Task(element->left, p + 1, N, rec);
		Task(element->right, p + 1, N, rec);
	}
	if ((p == N) && (element)) { 
		(*rec)++; // Счетчик количества слов на необходимом уровне
	}
}
