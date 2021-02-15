#ifndef Q2_H_
#define Q2_H_

typedef unsigned char BYTE;

typedef struct
{
	int lineNum;
	int value;
} SortHelperStruct;

// Prints two dimensional matrix by rows
void printMatrix(int *matrix, int rows, int columns);

// Sort a matrix using "sum of elements in row" criteria
void   sortMatrixRowsBySum ( int *matrix, int rows, int columns);

// Sort a matrix using "number of non zero bits in row" criteria
void   sortMatrixRowsByBits ( int *matrix, int rows, int columns);

int compareByValue(const void* h1, const void* h2);
int compareByLine(const void* h1, const void* h2);
void sortMatrixRowsByValue(int* matrix, int rows, int columns, SortHelperStruct* helper);
void swap(int* a, int* b);
void getSumIntoHelper(int* matrix, int rows, int columns, SortHelperStruct* helper);
void countNonZeroIntoHelper(int* matrix, int rows, int columns, SortHelperStruct* helper);

int Q2(void);


#endif /* Q2_H_ */
