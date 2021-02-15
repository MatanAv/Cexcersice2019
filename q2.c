#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q2.h"

// Prints two dimensional matrix by rows
void printMatrix(int *matrix, int rows, int columns) {

	for (int i = 0;   i < rows;   i++) {
		for (int j = 0;   j < columns;   j++)
			printf(" %d", *(matrix + i*columns + j));
		printf("\n");
	}
}

int compareByValue(const void* h1, const void* h2)
{
	int s1 = (*(SortHelperStruct*)h1).value;
	int s2 = (*(SortHelperStruct*)h2).value;
	return s1 - s2;
}

int compareByLine(const void* h1, const void* h2)
{
	int s1 = (*(SortHelperStruct*)h1).lineNum;
	int s2 = (*(SortHelperStruct*)h2).lineNum;
	return s1 - s2;
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sortMatrixRowsByValue(int* matrix, int rows, int columns, SortHelperStruct* helper)
{
	qsort(helper, rows, sizeof(SortHelperStruct), compareByValue);

	int num;
	num = helper[0].lineNum;
	num = helper[1].lineNum;
	num = helper[2].lineNum;
	num = helper[3].lineNum;

	for (int i = 0; i < rows; i++)
		if (i < helper[i].lineNum)
		{
			for (int j = 0; j < columns; j++)
				swap(&matrix[columns * i + j], &matrix[columns * helper[i].lineNum + j]);	// Swapping the lines

			for (int j = 0; j < rows; j++)		// Updating line numbers
				if (helper[j].lineNum == i)
					swap(&helper[i].lineNum, &helper[j].lineNum);
		}
}

void getSumIntoHelper(int* matrix, int rows, int columns, SortHelperStruct* helper)
{
	int sum;
	for (int i = 0; i < rows; i++)
	{
		sum = 0;

		for (int j = 0; j < columns; j++)
			sum += matrix[columns * i + j];

		helper[i].lineNum = i;
		helper[i].value = sum;
	}
}

void countNonZeroIntoHelper(int* matrix, int rows, int columns, SortHelperStruct* helper)
{
	int sumOfNonZero;

	for (int i = 0; i < rows; i++)
	{
		sumOfNonZero = 0;

		for (int j = 0; j < columns; j++)
		{
			if ((matrix[columns * i + j] & 0x1) == 0x1)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x2) == 0x2)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x4) == 0x4)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x8) == 0x8)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x10) == 0x10)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x20) == 0x20)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x40) == 0x40)
				sumOfNonZero++;
			if ((matrix[columns * i + j] & 0x80) == 0x80)
				sumOfNonZero++;
		}

		helper[i].lineNum = i;
		helper[i].value = sumOfNonZero;
	}
}

// Sort a matrix using "sum of elements in row" criteria
void   sortMatrixRowsBySum ( int *matrix, int rows, int columns)
{
	if (!rows)
		return 0;

	SortHelperStruct* helper = (SortHelperStruct*)malloc(sizeof(SortHelperStruct) * rows);
	if (!helper)
		return 0;

	getSumIntoHelper(matrix, rows, columns, helper);
	sortMatrixRowsByValue(matrix, rows, columns, helper);

	free(helper);
}

// Sort a matrix using "number of non zero bits in row" criteria
void   sortMatrixRowsByBits ( int *matrix, int rows, int columns)
{
	if (!rows)
		return 0;

	SortHelperStruct* helper = (SortHelperStruct*)malloc(sizeof(SortHelperStruct) * rows);
	if (!helper)
		return 0;

	countNonZeroIntoHelper(matrix, rows, columns, helper);
	sortMatrixRowsByValue(matrix, rows, columns, helper);

	free(helper);
}


int Q2(void) {

	int matrixSum[4][3] = {{10, 20, 30}, {2, 4, 3}, {100, 200, 300}, {50, 60, 70}};

	int matrixBits[4][3] = {{0, 0, 7}, {1, 1, 3}, {7, 7, 7}, {1, 0, 1}};
					//			3			4			9		2
	
	// Sort matrixSum by the sum of elements in row
	printf("Before sorting\n");

	printMatrix(matrixSum, 4, 3);

	sortMatrixRowsBySum(matrixSum, 4, 3);

	printf("After sorting\n");

	printMatrix(matrixSum, 4, 3);

	printf("\n========\n\n");

	// Sort matrixBits by the sum of non zero bits of all elements in row
	printf("Before sorting\n");

	printMatrix(matrixBits, 4, 3);

	sortMatrixRowsByBits(matrixBits, 4, 3);

	printf("After sorting\n");

	printMatrix(matrixBits, 4, 3);

	return EXIT_SUCCESS;
}

