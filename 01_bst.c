#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node
{
	int value;		   // значение, которое хранит узел
	struct node *left; // ссылка на следующий элемент списка
	struct node *right;
	struct node *mother; // ссылка на предыдущий элемент списка
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree
{
	struct node *root;
	int count_usel;
} tree;

// Инициализация дерева
void init(tree *t)
{
	t->root = NULL;
	t->count_usel = 0;
}

// Удалить все элементы из дерева
void clean(tree *t)
{
	if (t->root == NULL)
		return;
	node *star = t->root, *temp;
	while ((t->root->left != NULL) || (t->root->right != NULL))
	{
		while ((star->left != NULL) || (star->right != NULL))
		{
			if (star->left != NULL)
			{
				star = star->left;
				continue;
			}
			if (star->right != NULL)
			{
				star = star->right;
				continue;
			}
		}
		temp = star->mother;
		free(star);
		star->left = star->right = star->mother = NULL;
		if (star == temp->left)
			temp->left = star->right;
		else
			temp->right = star->right;
		star = temp;
		t->count_usel--;
	}
	free(t->root);
	t->root->left = t->root->right = NULL;
	temp = NULL;
	star = NULL;
	t->root = NULL;
	t->count_usel--;
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node *find(tree *t, int value, bool count)
{
	node *star = t->root;
	if (value == star->value)
		return star;
	while ((star->left != NULL) || (star->right != NULL))
	{
		if (value < star->value && star->left != NULL)
		{
			star = star->left;
			continue;
		}
		if (value > star->value && star->right != NULL)
		{
			star = star->right;
			continue;
		}
		break;
	}
	if (value == star->value)
		return star;
	if (count == true)
		return star;
	else
		return NULL;
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree *t, int value)
{
	if (t->root == NULL)
	{
		node *star = malloc(sizeof(node));
		t->root = star;
		star->value = value;
		t->count_usel++;
		star = NULL;
		return 0;
	}
	else
	{
		node *star = find(t, value, true);
		if (value == star->value)
			return 1;
		if (value < star->value)
		{
			star->left = malloc(sizeof(node));
			star->left->value = value;
			star->left->mother = star;
			t->count_usel++;
		}
		else
		{
			star->right = malloc(sizeof(node));
			star->right->value = value;
			star->right->mother = star;
			t->count_usel++;
		}
		return 0;
	}
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree *t, int value)
{
	node *star = find(t, value, false);
	if (star == NULL)
		return 1;
	else
	{
		if (star->left == NULL && star->right == NULL)
		{

			free(star);
			star->left = NULL;
			star->right = NULL;
			if (star->mother != NULL)
			{
				if (star == star->mother->left)
					star->mother->left = NULL;
				else
					star->mother->right = NULL;
				star->mother = NULL;
			}
			else
				t->root = NULL;
			star = NULL;
			t->count_usel--;
			return 0;
		}
		if (star->left != NULL && star->right != NULL)
		{
			if (star->mother != NULL)
			{
				if (star == star->mother->left)
					star->mother->left = star->right;
				else
					star->mother->right = star->right;
				star->right->mother = star->mother;
			}
			else
			{
				t->root = star->right;
				t->root->mother = NULL;
			}
			node *temp = star->right;
			while (temp->left != NULL)
				temp = temp->left;
			temp->left = star->left;
			star->left->mother = temp;
			temp = NULL;
			free(star);
			star->mother = star->left = star->right = NULL;
			star = NULL;
			t->count_usel--;
			return 0;
		}
		if (star->left != NULL)
		{
			if (star->mother != NULL)
			{
				if (star == star->mother->left)
					star->mother->left = star->left;
				else
					star->mother->right = star->left;
			}
			else
			{
				t->root = star->left;
				t->root->mother = NULL;
			}
			star->left->mother = star->mother;
			free(star);
			star->left = star->mother = NULL;
			star = NULL;
			t->count_usel--;
			return 0;
		}
		if (star->right != NULL)
		{
			if (star->mother != NULL)
			{
				if (star == star->mother->left)
					star->mother->left = star->right;
				else
					star->mother->right = star->right;
			}
			else
			{
				t->root = star->right;
				t->root->mother = NULL;
			}
			star->right->mother = star->mother;
			free(star);
			star->right = star->mother = NULL;
			star = NULL;
			t->count_usel--;
			return 0;
		}
	}
}

void rescue(tree *t, bool option)
{
	if (t->root == NULL)
		return;
	if (option)
		t->count_usel--;
	else
		while (t->root->mother != NULL)
			t->root = t->root->mother;
	return;
}

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node *n)
{
	while (n->left != NULL)
		n = n->left;
	int value = n->value;
	if (n->right != NULL)
	{
		if (n->mother != NULL)
		{
			if (n == n->mother->left)
				n->mother->left = n->right;
			else
				n->mother->right = n->right;
		}
		else
			return 1;
		n->right->mother = n->mother;
		free(n);
		n->right = n->mother = NULL;
		n = NULL;
	}
	else
	{
		if (n->mother != NULL)
		{
			if (n == n->mother->left)
				n->mother->left = NULL;
			else
				n->mother->right = NULL;
			n->mother = NULL;
		}
		else
			return 1;
		free(n);
		n->left = NULL;
		n->right = NULL;
		n = NULL;
	}
	return value;
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_right(node *n)
{
	if (n == NULL)
		return 1;
	if (n->left == NULL)
		return 1;
	node *temp_mother = n->mother, *temp_right = n->left->right;
	n->mother = n->left;
	n->left->right = n;
	n->mother->mother = temp_mother;
	n->left = temp_right;
	if (temp_right != NULL)
		temp_right->mother = n;
	if (temp_mother != NULL)
		if (temp_mother->left == n)
			temp_mother->left = n->mother;
		else
			temp_mother->right = n->mother;
	return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node *n)
{
	if (n == NULL)
		return 1;
	if (n->right == NULL)
		return 1;
	node *temp_mother = n->mother, *temp_left = n->right->left;
	n->mother = n->right;
	n->right->left = n;
	n->mother->mother = temp_mother;
	n->right = temp_left;
	if (temp_left != NULL)
		temp_left->mother = n;
	if (temp_mother != NULL)
		if (temp_mother->right == n)
			temp_mother->right = n->mother;
		else
			temp_mother->left = n->mother;
	return 0;
}

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке.
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _.
// Если дерево пусто, вывести -
void print(node *n)
{
	if (n == NULL)
	{
		printf("-");
		printf("\n");
		return;
	}
	node *star = n;
	int count = 1, row = 1, temp_row, temp_k;
	bool see = 0;
	for (int i = 1; i <= count; i++)
	{
		for (int k = 1; k <= row; k++)
		{
			temp_k = k;
			temp_row = row;
			star = n;
			for (int lvl = 1; lvl < i; lvl++)
			{
				temp_row /= 2;
				if (temp_k > temp_row)
				{
					temp_k -= temp_row;
					if (star->right != NULL)
						star = star->right;
					else
					{
						k += temp_row - 1;
						for (int j = 1; j <= temp_row; j++)
						{
							printf("_");
							printf(" ");
						}
						temp_row = 0;
						break;
					}
				}
				else
				{
					if (star->left != NULL)
						star = star->left;
					else
					{
						k += temp_row - 1;
						for (int j = 1; j <= temp_row; j++)
						{
							printf("_");
							if (k < row)
								printf(" ");
						}
						temp_row = 0;
						break;
					}
				}
			}
			if (temp_row == 1)
			{
				if (star->left != NULL || star->right != NULL)
					see = 1;
				printf("%d", star->value);
				if (k < row)
					printf(" ");
			}
		}
		printf("\n");
		if (see)
		{
			count += see;
			row *= 2;
			see = 0;
		}
	}
	return;
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree *t)
{
	print(t->root);
	return;
}

int main()
{
	tree t;
	init(&t);
	int ai;
	for (int i = 1; i <= 4; i++)
	{
		(void)scanf("%d", &ai);
		insert(&t, ai);
	}

	print_tree(&t);
	printf("\n");

	for (int i = 1; i <= 3; i++)
	{
		(void)scanf("%d", &ai);
		insert(&t, ai);
	}

	print_tree(&t);
	printf("\n");

	for (int m2 = 0; m2 <= 1; m2++)
	{
		int m1;
		(void)scanf("%d", &m1);
		node *star = find(&t, m1, false);
		if (star == NULL)
		{
			printf("-");
			printf("\n\n");
		}
		else
		{
			if (star->mother != NULL)
			{
				printf("%d", star->mother->value);
				printf(" ");
			}
			else
			{
				printf("_");
				printf(" ");
			}
			if (star->left != NULL)
			{
				printf("%d", star->left->value);
				printf(" ");
			}
			else
			{
				printf("_");
				printf(" ");
			}
			if (star->right != NULL)
			{
				printf("%d", star->right->value);
				printf(" ");
			}
			else
				printf("_");
			printf("\n\n");
		}
	}

	int m3;
	(void)scanf("%d", &m3);
	remove_node(&t, m3);

	print_tree(&t);
	printf("\n");

	int count = 0;
	while (count != 1)
	{
		count = rotate_left(t.root);
		rescue(&t, false);
	}

	print_tree(&t);
	printf("\n");

	count = 0;
	while (count != 1)
	{
		count = rotate_right(t.root);
		rescue(&t, false);
	}

	print_tree(&t);
	printf("\n");

	printf("%d", t.count_usel);
	printf("\n\n");

	clean(&t);

	print_tree(&t);
	printf("\n");

	return 0;
}