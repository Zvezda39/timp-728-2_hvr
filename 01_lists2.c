#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	int value;		   // значение, которое хранит узел
	struct node *next; // ссылка на следующий элемент списка
	struct node *prev; // ссылка на предыдущий элемент списка
} node;

typedef struct list
{
	struct node *head; // начало списка
	struct node *tail; // конец списка
} list;

// инициализация пустого списка
void init(list *l)
{
	l->head = NULL;
	l->tail = NULL;
}

// удалить все элементы из списка
void clean(list *l)
{
	if (l->head != NULL)
	{

		node *star = NULL;
		while (l->head->next)
		{
			star = l->head;
			l->head = l->head->next;
			free(star);
		}
		free(l->head);
		l->head = NULL;
		l->tail = NULL;
		star = NULL;
	}
	else
		printf("Ошибка");
}

// проверка на пустоту списка
bool is_empty(list *l)
{
	if (l->head != NULL)
		return false;
	else
		return true;
}

// поиск элемента по значению. вернуть NULL, если элемент не найден
node *find(list *l, int value)
{
	node *star = l->head;
	while ((star != NULL) && (star->value != value))
		star = star->next;
	if (star == NULL)
	{
		printf("0 ");
		return NULL;
	}
	else
	{
		printf("1 ");
		star = NULL;
	}
}

// вставка значения в конец списка. вернуть 0, если успешно
int push_back(list *l, int value)
{
	if (l->head != NULL)
	{
		node *star = l->head;
		while (star->next != NULL)
			star = star->next;
		star->next = malloc(sizeof(node));
		star->next->value = value;
		star->next->prev = star;
		star->next->next = NULL;
		l->tail = star->next;
		star = NULL;
		return 0;
	}
	else
	{
		node *star = malloc(sizeof(node));
		star->value = value;
		star->next = l->head;
		l->head = star;
		l->head->prev = NULL;
		l->tail = star;
		star = NULL;
		return 0;
	}
}

// вставка значения в начало списка. вернуть 0, если успешно
int push_front(list *l, int value)
{
	node *star = malloc(sizeof(node));
	star->value = value;
	star->next = l->head;
	star->prev = NULL;
	l->head->prev = star;
	l->head = star;
	star = NULL;
	return 0;
}

// вставка значения после указанного узла. вернуть 0, если успешно
int insert_after(list *l, node *n, int value)
{
	if (n != NULL)
	{
		node *star = malloc(sizeof(node));
		star->value = value;
		star->next = n->next;
		star->prev = n;
		if (n->next != NULL)
			n->next->prev = star;
		else
			l->tail = star;
		n->next = star;
		star = NULL;
		return 0;
	}
	else
	{
		printf("Ошибка");
		return 2;
	}
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value)
{
	if (n != NULL)
	{
		node *star = malloc(sizeof(node));
		star->value = value;
		star->next = n;
		star->prev = n->prev;
		if (n->prev != NULL)
			n->prev->next = star;
		else
			l->head = star;
		n->prev = star;
		star = NULL;
		return 0;
	}
	else
	{
		printf("Ошибка");
		return 2;
	}
}

// поиск элемента по индексу
node *list_index(list *l, int j)
{
	node *star = l->head;
	int index = 0;
	while (index != j - 1 && star != NULL)
	{
		star = star->next;
		++index;
	}
	return star;
}

// удалить первый элемент из списка с указанным значением. вернуть 0, если успешно
int remove_first(list *l, int value)
{
	if (l->head == NULL)
		return 1;
	else
	{
		node *star = l->head;
		while (star->next != NULL)
		{
			if (star->value == value)
			{
				if (star->prev == NULL)
				{
					l->head = star->next;
					l->head->prev = NULL;
					free(star);
					star = NULL;
					return 0;
				}
				star->prev->next = star->next;
				star->next->prev = star->prev;
				free(star);
				star = NULL;
				return 0;
			}
			star = star->next;
		}
		if (star->value == value)
		{
			l->tail = star->prev;
			l->tail->next = NULL;
			free(star);
			star = NULL;
			return 0;
		}
		return 1;
	}
}

// удалить последний элемент из списка с указанным значением. вернуть 0, если успешно
int remove_last(list *l, int value)
{
	if (l->head == NULL)
		return 1;
	else
	{
		node *star = l->tail;
		while (star->prev != NULL)
		{
			if (star->value == value)
			{
				if (star->next == NULL)
				{
					l->tail = star->prev;
					l->tail->next = NULL;
					free(star);
					star = NULL;
					return 0;
				}
				star->next->prev = star->prev;
				star->prev->next = star->next;
				free(star);
				star = NULL;
				return 0;
			}
			star = star->prev;
		}
		if (star->value == value)
		{
			l->head = star->next;
			l->head->prev = NULL;
			free(star);
			star = NULL;
			return 0;
		}
		return 1;
	}
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l)
{
	node *star = l->head;
	while (star != NULL)
	{
		printf("%d ", star->value);
		star = star->next;
	}
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l)
{
	node *star = l->tail;
	while (star != NULL)
	{
		printf("%d ", star->value);
		star = star->prev;
	}
}

int main()
{
	// количество элементов n
	int n;
	(void)scanf("%d", &n);

	// пустой список
	list l;
	init(&l);

	// занесение n элементов a в список
	int a;
	for (int i = 1; i <= n; ++i)
	{
		(void)scanf("%d", &a);
		push_back(&l, a);
	}

	// вывод содержимого списка
	print(&l);
	printf("\n");

	// поиск элементов по значению
	for (int k = 1; k <= 3; ++k)
	{
		(void)scanf("%d", &a);
		find(&l, a);
	}
	printf("\n");

	// добавление в конец списка
	int m;
	(void)scanf("%d", &m);
	push_back(&l, m);

	// вывод содержимого списка в обратном порядке
	print_invers(&l);
	printf("\n");

	// добавление в начало списка
	int t;
	(void)scanf("%d", &t);
	push_front(&l, t);

	// вывод содержимого списка
	print(&l);
	printf("\n");

	// добавление элемента после указанного узла
	int j, x;
	(void)scanf("%d", &j);
	(void)scanf("%d", &x);
	node *usel = list_index(&l, j);
	insert_after(&l, usel, x);

	// вывод содержимого списка в обратном порядке
	print_invers(&l);
	printf("\n");

	// добавление элемента перед указанным узлом
	int u, y;
	(void)scanf("%d", &u);
	(void)scanf("%d", &y);
	node *xsel = list_index(&l, u);
	insert_before(&l, xsel, y);

	// вывод содержимого списка
	print(&l);
	printf("\n");

	// удаление первого элемента списка
	int z;
	(void)scanf("%d", &z);
	remove_first(&l, z);

	// вывод содержимого списка в обратном порядке
	print_invers(&l);
	printf("\n");

	// удаление последнего элемента
	int r;
	(void)scanf("%d", &r);
	remove_last(&l, r);

	// вывод содержимого списка
	print(&l);
	printf("\n");

	// очистка списка
	clean(&l);

	// проверка на пустоту
	bool b = is_empty(&l);

	return 0;
}