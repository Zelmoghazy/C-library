#include <stdio.h>
#include <stdlib.h>

typedef struct DynamicArray
{
    int end;
    int MAX;
    int *A;
} DynamicArray;

void InitArray(DynamicArray *DA, int initialSize)
{
    DA->MAX = initialSize;
    DA->end = 0;
    DA->A = calloc(DA->MAX, sizeof(int));
    if (DA->A == NULL)
    {
        printf("Allocation failed");
        exit(0);
    }
}

void PrintArray(DynamicArray *DA, int start, int final)
{
    printf("-------------------------\n");
    for (int j = start; j < final; j++)
    {
        printf("%d ", DA->A[j]);
    }
    printf("\n");
    printf("Last used Index: %d\n", DA->end);
    printf("Array Max Index: %d\n", DA->MAX);
    printf("-------------------------\n");
}

void InsertArray(DynamicArray *DA, int value, int index)
{
    if (index >= 0)
    {
        // Pass address of pointer to be able to alter it
        if (index >= DA->MAX || DA->end >= DA->MAX)
        {
            // When it exceeds the capacity of array
            DA->MAX = DA->MAX * 2;
            int *B = realloc(DA->A, (DA->MAX + 1) * sizeof(int));

            for (int i = DA->MAX / 2; i < DA->MAX + 1; i++)
            {
                // realloc produce garbage values
                B[i] = 0;
            }
            if (B == NULL)
            {
                // check if reallocation succeeded
                printf("Reallocation failed");
                exit(0);
            }

            DA->A = B;

            InsertArray(DA, value, index);
        }
        // Append the array
        else if (index == DA->end)
        {
            DA->A[DA->end] = value;
            DA->end++;
        }
        // Insert at any position
        else
        {
            for (int j = DA->end + 1; j > index; j--)
            {
                DA->A[j] = DA->A[j - 1];
            }
            DA->A[index] = value;
            DA->end++;
        }
    }
    else
    {
        printf("Insert Array failed: index must be positive value\n");
        return;
    }
}

void RemoveArray(DynamicArray *DA, int index)
{
    if (index <= DA->end && index >= 0)
    {
        if (DA->end < DA->MAX / 2)
        {
            DA->MAX = DA->MAX / 2;
            int *B = realloc(DA->A, DA->MAX * sizeof(int));
            if (B == NULL)
            {
                // check if reallocation succeeded
                printf("Reallocation failed");
                exit(0);
            }
            DA->A = B;
            RemoveArray(DA, index);
        }
        else if (index == DA->end)
        {
            DA->end--;
            DA->A[DA->end] = 0;
        }
        else
        {
            for (int j = index; j < DA->end + 1; j++)
            {
                DA->A[j] = DA->A[j + 1];
            }
            DA->A[DA->end] = 0;
            DA->end--;
        }
    }
    else
    {
        printf("RemoveArray failed: cannot remove unintialized data, max index = %d \n", DA->end);
        return;
    }
}

int GetArray(DynamicArray *DA, int index)
{
    if (index > DA->end)
    {
        printf("GetArray failed: Cannot access uninitialized data \n");
        return 0;
    }
    return DA->A[index];
}

int GetSize(DynamicArray *DA)
{
    return DA->MAX;
}

void ChangeArray(DynamicArray *DA, int value, int index)
{
    if (index > DA->end || index < 0)
    {
        printf("Change Array failed: Cannot change not yet initialized data, Max index = %d \n", DA->end);
        return;
    }
    DA->A[index] = value;
}

void FreeArray(DynamicArray *DA)
{
    free(DA->A);
    DA->A = NULL;
}

void ClearArray(DynamicArray *DA, int newSize)
{

    if (DA->MAX > newSize)
    {
        DA->end = newSize;

        while (DA->MAX >= newSize * 2)
        {
            DA->MAX = DA->MAX / 2;
            int *B = realloc(DA->A, DA->MAX * sizeof(int));
            if (B == NULL)
            {
                // check if reallocation succeeded
                printf("Reallocation failed");
                exit(0);
            }
            DA->A = B;
        }
        for (int i = 0; i < DA->MAX; i++)
        {
            DA->A[i] = 0;
        }
    }
    else
    {
        for (int i = 0; i <= DA->end; i++)
        {
            DA->A[i] = 0;
        }
    }
}

void CopyArray(DynamicArray *DA1, DynamicArray *DA2, int start, int end)
{
    // copy from array2 from cerain range -> array1
    if (DA2->end >= end)
    {
        int j = 0;
        for (int i = start; i < end; i++)
        {
            DA1->A[j] = DA2->A[i];
            j++;
        }
        DA1->end = j;
    }
    else
    {
        printf("CopyArray failed: Cannot copy uninitialized data \n");
    }
}

int main()
{
    DynamicArray a1;
    DynamicArray a2;

    InitArray(&a1, 10);
    InitArray(&a2, 20);
    for (int i = 0; i < 20; i++)
    {
        InsertArray(&a2, i, a2.end);
    }
    PrintArray(&a2, 0, a2.end);
    PrintArray(&a1, 0, a1.end);

    CopyArray(&a1, &a2, 15, 20);
    PrintArray(&a1, 0, a1.end);

    FreeArray(&a1);
    FreeArray(&a2);

    system("pause");
    return 0;
}