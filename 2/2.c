#include <stdio.h>
#include <stdlib.h>

typedef int DateType;

typedef struct Node
{
    DateType date;
    struct Node *next;
} Node;

void InitStack(Node *top)