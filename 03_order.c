#include <stdio.h>
#include <stdlib.h>

// Структура для хранения узла дерева
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node
{
    int value;           // значение, которое хранит узел
    struct node *left;   // ссылка на левого потомка
    struct node *right;  // ссылка на правого потомка
    struct node *parent; // ссылка на предка
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree
{
    struct node *root; // корень
    int count;         // количество элементов
} tree;

// Инициализация дерева
void init(tree *t)
{
    t->root = NULL;
    t->count = 0;
}

int insert(tree *t, int value)
{
    node *prev = t->root, *next = NULL;
    node *star = malloc(sizeof(node));
    star->value = value;
    if (t->root == NULL)
    {
        star->parent = NULL;
        star->left = NULL;
        star->right = NULL;
        t->root = star;
        t->count = 1;
        return 0;
    }
    while (prev != NULL)
    {
        next = prev;
        if (value == prev->value)
        {
            return 1;
        }
        if (value < prev->value)
        {
            prev = prev->left;
        }
        else
        {
            prev = prev->right;
        }
    }
    star->parent = next;
    star->left = NULL;
    star->right = NULL;
    if (value < next->value)
    {
        next->left = star;
        t->count++;
        return 0;
    }
    if (value > next->value)
    {
        next->right = star;
        t->count++;
        return 0;
    }
}

//Функция, возвращающая указатель на корень
node *Root(tree *t)
{
    return t->root;
}

void Post_Order(node *t)
{
    if (t == NULL)
        return;
    Post_Order(t->left);
    Post_Order(t->right);
    printf("%d ", t->value);
}

int main()
{
    int n, a;
    tree t;
    init(&t);
    for (int i = 0; i < 7; ++i)
    {
        (void)scanf("%d", &a);
        insert(&t, a);
    }
    // ОБРАТНЫЙ ОБХОД
    Post_Order(Root(&t));
    return 0;
}