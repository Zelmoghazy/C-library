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

/*Utilities*/
void delay(int ms);
void LogColor(char *text, char c);
void Swap(int *a, int *b);
int Randomize(int start, int end);
void Shuffle(int *array, int n);
/*Dynamic Array*/
DynamicArray *newArray(int initialSize);
void FreeArray(DynamicArray *DA);
bool isEmpty(DynamicArray *DA);
void PrintArray(DynamicArray *DA, int start, int final);
void Expand(DynamicArray *DA);
void Shrink(DynamicArray *DA);
void Append(DynamicArray *DA, int value);
void Pop(DynamicArray *DA);
/*Array*/
void InsertArray(DynamicArray *DA, int value, int index);
void RemoveArray(DynamicArray *DA, int index);
void RemoveArrayValue(DynamicArray *DA, int value);
void RemoveArrayRange(DynamicArray *DA, int start, int end);
int GetArray(DynamicArray *DA, int index);
int GetSize(DynamicArray *DA);
void ChangeArray(DynamicArray *DA, int value, int index);
void ClearArray(DynamicArray *DA, int newSize);
void CopyArray(DynamicArray *DA1, DynamicArray *DA2, int start, int end);
void ReverseArray(DynamicArray *DA);

int BinarySearch(DynamicArray *DA, int value, bool first);
int Count(int const *A, int value);

int MedianOfThree(int *A, int left, int right);
int Partition(int *A, int start, int end);
void QuickSort(DynamicArray *DA, int start, int end);
void ArrayPopulator(DynamicArray *DA, ...);
int Power(int x, int n);
void Exponentiate(DynamicArray *DA, int pow);
int Maximum(DynamicArray *DA);
int Minimum(DynamicArray *DA);