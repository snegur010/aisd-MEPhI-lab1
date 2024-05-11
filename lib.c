#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib.h"

//  todo
//  нулевая строка
//  tail append
// обработать NULL

Matrix *Matrix_create(const int rows) {
    Matrix *matrix = (Matrix *) calloc(1, sizeof(Matrix));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    matrix->amount = rows;
    matrix->line = NULL;

    return matrix;
}


void List_free(List *list) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        Node *nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}


void Line_free(Line *line) {
    List_free(line->head);
    free(line->tail);
    free(line);
}


void Matrix_free(Matrix *matrix) {
    Line *currentLine = matrix->line;
    while (currentLine != NULL) {
        Line *nextLine = currentLine->next;
        if (currentLine->head != NULL) {
            Line_free(currentLine);
        } else {
            free(currentLine);
        }
        currentLine = nextLine;
    }
    free(matrix);
}


int getInteger(int *d) {
    int k = 0;
    while (k != 1) {
        k = scanf("%d", d);

        if (k == EOF) {
            printf("End of file\n");
            return 1;
        }
        if (k != 1) {
            printf("Incorrect input! Try again: ");
            scanf("%*[^\n]"); // Очистка буфера до новой строки
            scanf("%*c"); // Очистка символа новой строки
        } else {
            int nextChar = getchar(); 
            if (nextChar != '\n' && nextChar != EOF) {
                printf("Extra characters found! Try again: ");
                while ((getchar()) != '\n'); 
                k = 0; 
            }
        }
    }
    return 0;
}

int getPositiveInteger(int *num) {
    int k = getInteger(num);
    while (k != 0 || *num < 0) {
        if (k == 1) {
            return 1;
        }
        printf("Incorrect input! Try again: ");
        k = getInteger(num);
    }
    return 0;
}

Node *Node_create(int data) {
    Node *newNode = (Node *) calloc(1, sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(List *tail, int data, Line *line) {
    Node *newNode = Node_create(data);
    if (tail->head == NULL) {
        line->head->head = newNode;
        tail->head = newNode;
    } else {
        Node *tmp = tail->head;
        tmp->next = newNode;
        tail->head = newNode;
    }
}

void Line_print(const Line *line) {
    List *list = line->head;
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}


void Matrix_print(const Matrix *matrix) {
    Line *currentLine = matrix->line;
    while (currentLine != NULL) {
        if (currentLine->head != NULL) {
            Line_print(currentLine);
        } else {
            printf("\n");
        }
        currentLine = currentLine->next;
    }
}


Line *readLine(int cols) {
    Line *line = (Line *) calloc(1, sizeof(Line));

    if (line == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    line->head = (List *) calloc(1, sizeof(List));
    line->tail = (List *) calloc(1, sizeof(List));
    if (line->head == NULL) {
        printf("Memory allocation failed\n");
        free(line);
        return NULL;
    }

    for (int i = 0; i < cols; i++) {
        int num;
        printf("Enter element %d of the row: ", i + 1);
        int k = getInteger(&num);
        if (k == 1) {
            Line_free(line); 
            return NULL;
        }
        append(line->tail, num, line);
    }

    return line;
}

int readMatrix(const int rows, Matrix *matrix) {
    for (int i = 0; i < rows; i++) {
        int cols = 0;
        printf("Enter the number of elements in row %d of the matrix: ", i + 1);
        int k = getPositiveInteger(&cols);
        if (k == 1) {
            return 1;
        }
        if (cols == 0) {
            Line *line = (Line *) calloc(1, sizeof(Line));
            line->head = NULL;
            line->tail = NULL;
            if (matrix->line == NULL) { 
                matrix->line = line;
            } else {
                Line *tmp = matrix->line;
                while (tmp->next != NULL) {
                    tmp = tmp->next;
                }
                tmp->next = line;
            }

        }else {
            Line *line = readLine(cols);
            if (line == NULL) {
                printf("Error reading line %d\n", i + 1);
                return 1;
            }

            if (matrix->line == NULL) { 
                matrix->line = line;
            } else {
                Line *tmp = matrix->line;
                while (tmp->next != NULL) {
                    tmp = tmp->next;
                }
                tmp->next = line;
            }
        }   
    }

    return 0;
}

int reverseNumber(int num) {
    int nums = abs(num);
    int point = 1;
    if (num < 0) {
        point = -1;
    }
    int reversedNum = 0;
    while (nums != 0) {
        int digit = nums % 10;
        reversedNum = reversedNum * 10 + digit;
        nums /= 10;
    }
    return point * reversedNum;
}


int individual(Matrix *matrix, Matrix *new_matrix) {
    new_matrix->amount = matrix->amount;
    Line *currentLine = matrix->line;
    Line *new_matrix_line = NULL;

    for (int i = 0; i < matrix->amount; i++) {
        Line *new_line = (Line *) calloc(1, sizeof(Line));

        if (new_line == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        new_line->head = (List *) calloc(1, sizeof(List));
        new_line->tail = (List *) calloc(1, sizeof(List));
        
        if (new_line->head == NULL) {
            printf("Memory allocation failed\n");
            free(new_line);
            return 1;
        }

        if (new_line->tail == NULL) {
            printf("Memory allocation failed\n");
            free(new_line);
            return 1;
        }

        if (currentLine->head == NULL) {
            new_line->head->head = NULL;
            new_line->tail->head = NULL;
            if (new_matrix_line == NULL) {
                new_matrix->line = new_line;
                new_matrix_line = new_line;
            } else {
                new_matrix_line->next = new_line;
                new_matrix_line = new_line;
            }

        } else {
            Node *currentNode = currentLine->head->head;
            while (currentNode != NULL) {
                int reversed = reverseNumber(currentNode->data);
                append(new_line->tail, reversed, new_line);
                currentNode = currentNode->next;
            }

            if (new_matrix_line == NULL) {
                new_matrix->line = new_line;
                new_matrix_line = new_line;
            } else {
                new_matrix_line->next = new_line;
                new_matrix_line = new_line;
            }
        }
        currentLine = currentLine->next;
    }
    return 0;
}
