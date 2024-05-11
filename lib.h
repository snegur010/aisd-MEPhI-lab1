#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct Line {
    List *head;
    List *tail;
    struct Line *next;
} Line;

typedef struct Matrix {
    int amount;
    Line *line;
} Matrix;

Matrix *Matrix_create(const int rows);
void List_free(List *list);
void Line_free(Line *line);
void Matrix_free(Matrix *matrix);

int getInteger(int *d);
int getPositiveInteger(int *num);

Node *Node_create(int data);
void append(List *list, int data, Line *line);

void Line_print(const Line *line);
void Matrix_print(const Matrix *matrix);

Line *readLine(int cols);
int readMatrix(const int rows, Matrix *matrix);

int reverseNumber(int num);
int individual(Matrix *matrix, Matrix *new_matrix);

#endif 
