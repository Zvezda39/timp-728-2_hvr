#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node
{
    int value;         // значение, которое хранит узел
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

void print(node *n)
{
    if (n == NULL)
    {
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
        printf(" ");
        if (see)
        {
            count += see;
            row *= 2;
            see = 0;
        }
    }
    return;
}

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
    for (int i = 1; i <= 7; i++)
    {
        (void)scanf("%d", &ai);
        insert(&t, ai);
    }
    print_tree(&t);
    printf("\n");
    return 0;
}
