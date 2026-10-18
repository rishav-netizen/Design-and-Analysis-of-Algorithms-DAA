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
Node *Predecessor(const Dict *D, const Node *target);
Node *Successor(const Dict *D, const Node *target);
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

    printf("\nUnsorted doubly linked dictionary:\n");
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
            Node *pred = Predecessor(&D, node);
            Node *succ = Successor(&D, node);
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
    for (int i = 0; i < count; i++)
    {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &key) != 1 || !Insert(D, key))
            return;
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
    while (current != NULL)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}

/* Inserts at the head in constant time. Enter distinct keys for a dictionary. */
bool Insert(Dict *D, int key)
{
    Node *newNode = malloc(sizeof *newNode);
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return false;
    }
    newNode->key = key;
    newNode->prev = NULL;
    newNode->next = D->head;
    if (D->head != NULL)
        D->head->prev = newNode;
    else
        D->tail = newNode;
    D->head = newNode;
    D->length++;
    return true;
}

/* Given the target node, both neighbour links allow constant-time deletion. */
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
    Node *best = D->head;
    for (Node *current = D->head; current != NULL; current = current->next)
        if (best == NULL || current->key > best->key)
            best = current;
    return best;
}

Node *Min(const Dict *D)
{
    Node *best = D->head;
    for (Node *current = D->head; current != NULL; current = current->next)
        if (best == NULL || current->key < best->key)
            best = current;
    return best;
}

Node *Predecessor(const Dict *D, const Node *target)
{
    Node *best = NULL;
    for (Node *current = D->head; current != NULL; current = current->next)
        if (current->key < target->key && (best == NULL || current->key > best->key))
            best = current;
    return best;
}

Node *Successor(const Dict *D, const Node *target)
{
    Node *best = NULL;
    for (Node *current = D->head; current != NULL; current = current->next)
        if (current->key > target->key && (best == NULL || current->key < best->key))
            best = current;
    return best;
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
