#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int length;
} Dict;

void Input(Dict *D, int count);
void Display(const Dict *D);
Node *Search(const Dict *D, int key);
bool Insert(Dict *D, int key);
bool Delete(Dict *D, Node *target);
Node *Max(const Dict *D);
Node *Min(const Dict *D);
Node *Predecessor(const Node *target);
Node *Successor(const Node *target);
void Destroy(Dict *D);

int main(void)
{
    Dict D = {NULL, NULL, 0};
    Node *node;
    int count;
    int key;

    printf("Enter number of initial elements: ");
    if (scanf("%d", &count) != 1 || count < 0)
    {
        printf("Enter a non-negative number of elements.\n");
        return 1;
    }
    Input(&D, count);

    printf("\nSorted doubly linked dictionary:\n");
    Display(&D);

    printf("\nEnter element to insert: ");
    if (scanf("%d", &key) == 1)
        Insert(&D, key);
    printf("Dictionary after insertion: ");
    Display(&D);

    printf("\nEnter key to search: ");
    if (scanf("%d", &key) == 1)
    {
        node = Search(&D, key);
        printf(node == NULL ? "Key not found.\n" : "Key found: %d\n", key);
    }

    node = Max(&D);
    printf(node == NULL ? "\nMaximum does not exist.\n" : "\nMaximum = %d\n", node->key);
    node = Min(&D);
    printf(node == NULL ? "Minimum does not exist.\n" : "Minimum = %d\n", node->key);

    printf("\nEnter an existing key for predecessor and successor: ");
    if (scanf("%d", &key) == 1)
    {
        node = Search(&D, key);
        if (node == NULL)
            printf("Key not found.\n");
        else
        {
            Node *pred = Predecessor(node);
            Node *succ = Successor(node);
            printf(pred == NULL ? "No predecessor exists.\n" : "Predecessor = %d\n", pred == NULL ? 0 : pred->key);
            printf(succ == NULL ? "No successor exists.\n" : "Successor = %d\n", succ == NULL ? 0 : succ->key);
        }
    }

    printf("\nEnter key to delete: ");
    if (scanf("%d", &key) == 1)
    {
        node = Search(&D, key);
        if (Delete(&D, node))
            printf("Key deleted successfully.\n");
        else
            printf("Key not found.\n");
    }

    printf("\nDictionary after deletion:\n");
    Display(&D);
    Destroy(&D);
    return 0;
}

void Input(Dict *D, int count)
{
    int key;
    for (int i = 0; i < count;)
    {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &key) != 1)
            return;
        if (Insert(D, key))
            i++;
    }
}

void Display(const Dict *D)
{
    const Node *current = D->head;
    printf("{ ");
    while (current != NULL)
    {
        printf("%d", current->key);
        current = current->next;
        if (current != NULL)
            printf(", ");
    }
    printf(" }\n");
}

Node *Search(const Dict *D, int key)
{
    Node *current = D->head;
    while (current != NULL && current->key <= key)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}

bool Insert(Dict *D, int key)
{
    Node *current = D->head;
    while (current != NULL && current->key < key)
        current = current->next;
    if (current != NULL && current->key == key)
    {
        printf("Duplicate keys are not allowed.\n");
        return false;
    }

    Node *newNode = malloc(sizeof *newNode);
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return false;
    }
    newNode->key = key;
    newNode->next = current;

    if (current == NULL)
    {
        newNode->prev = D->tail;
        if (D->tail != NULL)
            D->tail->next = newNode;
        else
            D->head = newNode;
        D->tail = newNode;
    }
    else
    {
        newNode->prev = current->prev;
        if (current->prev != NULL)
            current->prev->next = newNode;
        else
            D->head = newNode;
        current->prev = newNode;
    }

    D->length++;
    return true;
}

bool Delete(Dict *D, Node *target)
{
    if (target == NULL)
        return false;
    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        D->head = target->next;
    if (target->next != NULL)
        target->next->prev = target->prev;
    else
        D->tail = target->prev;
    free(target);
    D->length--;
    return true;
}

Node *Max(const Dict *D)
{
    return D->tail;
}

Node *Min(const Dict *D)
{
    return D->head;
}

Node *Predecessor(const Node *target)
{
    return target->prev;
}

Node *Successor(const Node *target)
{
    return target->next;
}

void Destroy(Dict *D)
{
    Node *current = D->head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    D->head = NULL;
    D->tail = NULL;
    D->length = 0;
}
