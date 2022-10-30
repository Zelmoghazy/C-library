#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>

typedef struct DynamicArray
{
    int end;
    int MAX;
    int *A;
} DynamicArray;

void delay(int ms) // delay function
{
    clock_t timeDelay = ms + clock();
    while (timeDelay > clock())
        ;
}

void LogColor(char *text, char c)
{
    switch (c)
    {
    case 'r':
    {
        printf("\033[1;31m");
    }
    break;
    case 'y':
    {
        printf("\033[1;33m");
    }
    break;
    case 'b':
    {
        printf("\033[0;34m");
    }
    break;
    case 'p':
    {
        printf("\033[0;35m");
    }
    break;
    case 'g':
    {
        printf("\033[0;32m");
    }
    break;
    default:
    {
        printf("\033[0m");
    }
    break;
    }
    printf("%s\n", text);
    printf("\033[0m");
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void InitArray(DynamicArray *DA, int initialSize)
{
    DA->MAX = initialSize;
    DA->end = 0;
    DA->A = calloc(DA->MAX, sizeof(int));
    if (DA->A == NULL)
    {
        LogColor("Allocation failed", 'r');
        // delay(5000);
        exit(0);
    }
}

void PrintArray(DynamicArray *DA, int start, int final)
{
    if (final > DA->MAX)
    {
        LogColor("Print Array failed : Exceeded max size", 'r');
        return;
    }
    LogColor("-------------------------", 'p');
    for (int j = start; j < final; j++)
    {
        printf("%d ", DA->A[j]);
    }
    printf("\n");
    if (DA->end == 0)
    {
        LogColor("Empty Array !", 'y');
    }
    printf("\033[0;32m");
    printf("Last used Index: %d\n", DA->end);
    printf("Array Capacity: %d\n", DA->MAX);
    printf("\033[0m");
    LogColor("-------------------------", 'p');
}

void Expand(DynamicArray *DA)
{
    // When it exceeds the capacity of array
    DA->MAX = DA->MAX * 2;
    int *B = realloc(DA->A, (DA->MAX + 1) * sizeof(int));
    if (B == NULL)
    {
        // check if reallocation succeeded
        LogColor("Reallocation failed", 'r');
        delay(5000);
        exit(0);
    }
    for (int i = DA->MAX / 2; i < DA->MAX + 1; i++)
    {
        // realloc produce garbage values
        // reinitialized by 0
        B[i] = 0;
    }

    DA->A = B;
}

void Shrink(DynamicArray *DA)
{
    DA->MAX = DA->MAX / 2;
    int *B = realloc(DA->A, DA->MAX * sizeof(int));
    if (B == NULL)
    {
        // check if reallocation succeeded
        LogColor("Reallocation failed", 'r');
        exit(0);
    }
    DA->A = B;
}

void Append(DynamicArray *DA, int value)
{
    DA->A[DA->end] = value;
    DA->end++;
}

void Pop(DynamicArray *DA)
{
    DA->end--;
    DA->A[DA->end] = 0;
}

void InsertArray(DynamicArray *DA, int value, int index)
{
    if (index >= 0)
    {
        if (index >= DA->MAX || DA->end >= DA->MAX)
        {
            Expand(DA);
            InsertArray(DA, value, index);
        }

        // Append the array
        else if (index == DA->end)
        {
            Append(DA, value);
        }
        // Insert at any position
        else
        {
            for (int j = DA->end; j > index; j--)
            {
                DA->A[j] = DA->A[j - 1];
            }
            DA->A[index] = value;
            DA->end++;
        }
    }
    else
    {
        LogColor("Insert Array failed: index must be positive value", 'r');
        return;
    }
}

void RemoveArray(DynamicArray *DA, int index)
{
    if (index <= DA->end && index >= 0 && DA->end > 0)
    {
        if (DA->end < DA->MAX / 2)
        {
            Shrink(DA);
            RemoveArray(DA, index);
        }
        else if (index == DA->end)
        {
            Pop(DA);
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
        printf("\033[1;31m");
        printf("RemoveArray failed: cannot remove unintialized data,max index = %d \n", DA->end);
        printf("\033[0m");
        return;
    }
}

void RemoveArrayValue(DynamicArray *DA, int value)
{
    int count = 0;
    for (int i = 0; i < DA->end; i++)
    {
        if (DA->A[i] == value)
        {
            RemoveArray(DA, i);
            i--;
            count++;
        }
    }
    if (count == 0)
    {
        LogColor("RemoveArrayValue failed: The value couldnt be found", 'r');
    }
}

void RemoveArrayRange(DynamicArray *DA, int start, int end)
{
    if (start >= 0 && start < end && end <= DA->end)
    {
        for (int i = start; i <= end; i++)
        {
            RemoveArray(DA, start);
        }
    }
    else
    {
        LogColor("RemoveArrayRange failed: invalid range", 'r');
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

void ReverseArray(DynamicArray *DA)
{
    int i = 0;
    int j = DA->end - 1;
    while (j > i)
    {
        Swap(&DA->A[i++], &DA->A[j--]);
    }
}

int BinarySearch(DynamicArray *DA, int value, bool first)
{
    int start = 0;
    int end = DA->end - 1;
    int result = -1;

    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (DA->A[mid] == value)
        {
            result = mid;
            if (first)
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
        else if (value < DA->A[mid])
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return result;
}

int Count(DynamicArray *DA, int value)
{
    int firstIndex = BinarySearch(DA, value, true);
    int lastIndex = BinarySearch(DA, value, false);
    return lastIndex - firstIndex + 1;
}

int Randomize(int start, int end)
{
    if (end + 1 - start != 0)
    {
        srand(time(NULL));
        int r = rand() % (end + 1 - start) + start;
        return r;
    }
    else
    {
        printf("Randomize failed : set a valid range");
        return -1;
    }
}

void InsertionSort(int *a, int start, int end)
{
    for (int i = start + 1; i < end + 1; i++)
    {
        int value = a[i];
        int next = i;
        while (next > 0 && a[next - 1] > value)
        {
            a[next] = a[next - 1];
            next = next - 1;
        }
        a[next] = value;
    }
}

void Shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        srand(time(NULL));
        for (size_t i = 0; i < n - 1; i++)
        {
            size_t j = rand() % (i + 1);
            Swap(&array[j], &array[i]);
        }
    }
}

int MedianOfThree(int *A, int left, int right)
{
    int center = left + (right - left) / 2;
    if (A[center] < A[left])
    {
        Swap(&A[left], &A[center]);
    }
    if (A[right] < A[left])
    {
        Swap(&A[left], &A[right]);
    }
    if (A[right] < A[center])
    {
        Swap(&A[center], &A[right]);
    }
    return center;
}

int Partition(int *A, int start, int end)
{
    int PivotIndex = Randomize(start, end);
    // int PivotIndex = MedianOfThree(A, start, end);
    Swap(&A[PivotIndex], &A[start]);
    int i = start;
    int partitionIndex = end + 1;
    int pivot = A[start];

    while (1)
    {
        while (A[++i] < pivot)
        {
            if (i == end)
            {
                break;
            }
        }
        while (A[--partitionIndex] > pivot)
        {
            if (partitionIndex == start)
            {
                break;
            }
        }
        if (i >= partitionIndex)
        {
            break;
        }
        Swap(&A[i], &A[partitionIndex]);
    }
    Swap(&A[start], &A[partitionIndex]);
    return partitionIndex;
}

void QuickSort(DynamicArray *DA, int start, int end)
{
    if (start < end)
    {
        if (end - start < 2)
        {
            return;
        } // partition with two values
        else if (end - start == 2)
        {
            if (DA->A[start] > DA->A[end - 1])
            {
                Swap(&DA->A[start], &DA->A[end - 1]);
            }
            return;
        }
        // to deal with repitition
        for (int i = start; i < end; i++)
        {
            if (DA->A[i + 1] != DA->A[i])
            {
                break;
            }
            else if (i == end - 1)
            {
                return;
            }
        }
        if (end <= start + 100) // insertion sort for small partitions
        {
            InsertionSort(DA->A, start, end);
            return;
        }
        int partitionIndex = Partition(DA->A, start, end);
        QuickSort(DA, start, partitionIndex - 1);
        QuickSort(DA, partitionIndex + 1, end);
    }
}

void ArrayPopulator(DynamicArray *DA, ...)
{
    va_list args;
    va_start(args, DA);
    unsigned char choice = (unsigned char)va_arg(args, int);
    int start = va_arg(args, int);
    int end = va_arg(args, int);
    srand(time(NULL)); // seed is the current calendar time (seconds since Jan 1, 1970).
    for (int i = 0; i < DA->MAX; i++)
    {
        if (choice == 'r')
        {
            DA->A[i] = rand() % (end + 1 - start) + start;
            DA->end++;
        }
        else if (choice == 's')
        {
            DA->A[i] = i;
            DA->end++;
        }
        else if (choice == 'b')
        {
            DA->A[i] = DA->MAX - i;
            DA->end++;
        }
        else if (choice == 'c')
        {
            DA->A[i] = start;
            DA->end++;
        }
        else if (choice == 'v')
        {
            if (i % 2 == 0)
                DA->A[i] = start;
            else
                DA->A[i] = end;
            DA->end++;
        }
        else
        {
            choice = 's';
            i--;
        }
    }
    va_end(args);
}