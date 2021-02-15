#ifndef __Q1__
#define __Q1__

#include <stdio.h>

#define FILE_NAME  "company.bin"
#define BASE_PRICE 1000

#define SOLDIER_PRICE (0.8F)
#define CHILD_PRICE	(0.5F)
#define BABY_PRICE	(0.0F)

typedef enum
{
	Adult,
	Child,
	Baby,
	Soldier
}CustomerType;

typedef struct
{
	char*			name;
	CustomerType	type;
	char*			country;
}Customer;

typedef struct
{
	char*	country;
	int		coustomersCount;
	Customer**	customersArr;
}Trip;

typedef struct
{
	Trip**	tripsArr;
	int		tripsCount;
}Company;


void 	Q1();
int		fillCompanySurvey(Company* pCompany);
void	printTotalIncomePerContry(Company* pCompany);

int		readCustomerFromFile(FILE* fp,Customer* pCust);
int		addCustomerToCompany(Company* pCompany, Customer* pCust);
float	calculateIncome(Trip* pTrip);

void	releaseCompany(Company* pCompany);

#endif
