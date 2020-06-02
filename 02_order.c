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

typedef struct stack
{
    int top;
    node *items[10];
} stack;

void push_stack(stack *star_stack, node *item)
{
    if (star_stack->top < 10 - 1)
    {
        star_stack->items[++(star_stack->top)] = item;
    }
    else
    {
        printf("Стек полон\n");
    }
}

node *pop_stack(stack *star_stack)
{
    if (star_stack->top > -1)
    {
        return star_stack->items[(star_stack->top)--];
    }
    else
    {
        printf("Стек пуст\n");
    }
}

node *peek_stack(stack star_stack)
{
    if (star_stack.top < 0)
    {
        printf("Стек пуст\n");
        return 0;
    }
    return star_stack.items[star_stack.top];
}

int isEmpty(stack star_stack)
{
    if (star_stack.top < 0)
        return 1;
    else
        return 0;
}

void Pre_Order(node *t)
{
    stack star_stack;
    star_stack.top = -1;

    if (t == NULL)
        return;

    node *star = NULL;
    push_stack(&star_stack, t);

    while (!isEmpty(star_stack))
    {
        star = pop_stack(&star_stack);
        printf("%d ", star->value);
        if (star->right)
        {
            push_stack(&star_stack, star->right);
        }
        if (star->left)
        {
            push_stack(&star_stack, star->left);
        }
    }
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
    // ПРЯМОЙ ОБХОД
    Pre_Order(Root(&t));
    printf("\n");
    return 0;
}