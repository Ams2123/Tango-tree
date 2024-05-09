#include <stdio.h>
#include <stdlib.h>
#include "unrolledlinkedlist.h"

class SparseMatrix 
{
private:
    int rows, cols;
    unrolled_list* matrix;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) 
    {
        matrix = new unrolled_list[r];
    }

    void insert(int row, int col, int value);
    void display();
};

void SparseMatrix::insert(int row, int col, int value) 
{
    if (row >= 0 && row < rows && col >= 0 && col < cols) 
    {
        matrix[row].insert(value);
    } 
    else 
    {
        printf("Invalid position for insertion!\n");
    }
}

void SparseMatrix::display() 
{
    printf("Sparse Matrix:\n");
    for (int i = 0; i < rows; i++) 
    {
        printf("Row %d: ", i);
        matrix[i].display();
    }
}

int main() 
{
    int rows, cols;
    printf("Enter number of rows and columns for sparse matrix: ");
    scanf("%d %d", &rows, &cols);
    SparseMatrix matrix(rows, cols);

    int choice, row, col, value;
    while (1) 
    {
        printf("\n\nMENU\n");
        printf("1. Insert Element\n2. Display Matrix\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1: 
            {
                printf("Enter row, column, and value to insert: ");
                scanf("%d %d %d", &row, &col, &value);
                matrix.insert(row, col, value);
                break;
            }

            case 2:
                matrix.display();
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    return 0;
}
