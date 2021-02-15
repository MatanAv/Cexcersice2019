#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "q1.h"

/* This is the data in the file
11 customers
David Adult France
Jon Child France
Helena Baby Germany
Lidia Adult Germany
Judith Soldier France
Zeus Adult Italy
Josef Child Italy
Michel Baby France
Tal Adult Italy
Guy Soldier France
Moshe Child Germany
*/

/*
Correct output is:
In country France the income is: 3100.00
In country Germany the income is: 1500.00
In country Italy the income is: 2500.00
*/

void Q1()
{
	Company theCompany = { NULL, 0 };


	if (!fillCompanySurvey(&theCompany))
	{
		printf("Error filling the survey\n");
		return;
	}

	printTotalIncomePerContry(&theCompany);
	releaseCompany(&theCompany);
}


int		readCustomerFromFile(FILE* fp,Customer* pCust)
{
	int len;
	// Get Name
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	pCust->name = (char*)malloc(sizeof(char) * len);
	if (!pCust->name)
		return 0;
	if (fread(pCust->name, sizeof(char), len, fp) != len)
		return 0;

	// Get Type
	if (fread(&pCust->type, sizeof(int), 1, fp) != 1)
		return 0;
	
	// Get Country
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	pCust->country = (char*)malloc(sizeof(char) * len);
	if (!pCust->country)
		return 0;
	if (fread(pCust->country, sizeof(char), len, fp) != len)
		return 0;

	return 1;
}

int		addCustomerToCompany(Company* pCompany, Customer* pCust)
{
	int i = 0;

	while (strcmp(pCust->country, pCompany->tripsArr[i]->country) != 0 && i < pCompany->tripsCount)
		i++;

	if (i == pCompany->tripsCount)
	{
		pCompany->tripsCount++;
		pCompany->tripsArr = (Trip**)realloc(pCompany->tripsArr, (sizeof(Trip*) * pCompany->tripsCount));
		if (!pCompany->tripsArr)
			return 0;
		pCompany->tripsArr[i] = (Trip*)malloc(sizeof(Trip));
		if (!pCompany->tripsArr[i])
			return 0;
		pCompany->tripsArr[i]->coustomersCount = 1;
		pCompany->tripsArr[i]->country = (char*)malloc(sizeof(char) * (strlen(pCust->country) + 1));
		if (!pCompany->tripsArr[i]->country)
			return 0;
		strcpy(pCompany->tripsArr[i]->country, pCust->country);
		pCompany->tripsArr[i]->customersArr = (Customer**)malloc(sizeof(Customer*));
		if (!pCompany->tripsArr[i]->customersArr)
			return 0;
		pCompany->tripsArr[i]->customersArr[0] = pCust;

		return 1;
	}

	pCompany->tripsArr[i]->coustomersCount++;
	pCompany->tripsArr[i]->customersArr = (Customer**)realloc(pCompany->tripsArr[i]->customersArr,
		(sizeof(Customer*) * pCompany->tripsArr[i]->coustomersCount));
	if (!pCompany->tripsArr[i]->customersArr)
		return 0;
	pCompany->tripsArr[i]->customersArr[pCompany->tripsArr[i]->coustomersCount - 1] = pCust;

	return 1;
}

float	calculateIncome(Trip* pTrip)
{
	int sumIncome = 0;

	for (int i = 0; i < pTrip->coustomersCount; i++)
	{
		float percent;
		if (pTrip->customersArr[i]->type == Baby)
			percent = BABY_PRICE;
		else if (pTrip->customersArr[i]->type == Child)
			percent = CHILD_PRICE;
		else if (pTrip->customersArr[i]->type == Soldier)
			percent = SOLDIER_PRICE;
		else
			percent = 1;

		sumIncome += BASE_PRICE * percent;
	}

	return sumIncome;
}



void releaseCompany(Company* pCompany)
{

	for (int i = 0; i < pCompany->tripsCount; i++)
	{
		for (int j = 0; j < pCompany->tripsArr[i]->coustomersCount; j++)
		{
			free(pCompany->tripsArr[i]->customersArr[j]->country);
			free(pCompany->tripsArr[i]->customersArr[j]->name);
			free(pCompany->tripsArr[i]->customersArr[j]);
		}
		free(pCompany->tripsArr[i]->country);
		free(pCompany->tripsArr[i]->customersArr);
		free(pCompany->tripsArr[i]);
	}
	free(pCompany->tripsArr);
	free(pCompany);
}



int fillCompanySurvey(Company* pCompany)
{
	FILE* fp;
	int count,i;
	Customer temp;

	fp = fopen(FILE_NAME, "rb");
	if (!fp)
		return 0;
	if (!fread(&count, sizeof(int), 1, fp))
	{
		fclose(fp);
		return 0;
	}

	for (i = 0; i < count; i++)
	{
		if(!readCustomerFromFile(fp,&temp))
		{
			fclose(fp);
			return 0;
		}
		
		if (!addCustomerToCompany(pCompany, &temp))
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}



void printTotalIncomePerContry(Company* pCompany)
{
	int i;
	float income;
	for (i = 0; i < pCompany->tripsCount; i++)
	{
		income = calculateIncome(pCompany->tripsArr[i]);
		printf("In country %s the income is: %.2f\n", pCompany->tripsArr[i]->country, income);
	}
}
