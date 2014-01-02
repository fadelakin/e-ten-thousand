#include <stdio.h>
#include <limits.h>

#define ILIMIT 3300

/* CAUTION: there are limits on the reliable actions with 	*/
/* this size of base.										*/

#if (INT_MAX>(ILIMIT*100000))	
#define NUMBER_BASE 100000
#define DIGS_IN_BASE 5
#else
#define NUMBER_BASE 10
#define DIGS_IN_BASE 10
#endif

#if (DIGS_IN_BASE==5)
#define NUMBER_WIDTH 2001
#else
#define NUMBER_WIDTH 10001
#endif

int LongDivide (int * Numerator, int * Denominator, int * Answer);
int LongAdd (int * iFirst, int * iSecond, int * iAnswer);

int main(int argc, char *argv[])
{
	int aResult[NUMBER_WIDTH+1];
	int aWork[NUMBER_WIDTH+1];
	int i;
	int j;

	aResult[0] = NUMBER_WIDTH;
	aResult[1] = 1;
	aWork[0] = NUMBER_WIDTH;
	aWork[1] = 1;
	for (i=2;(i<=NUMBER_WIDTH);i++)
	{
		aResult[i] = 0;
		aWork[i] = 0;
	}
	for (i=1;(i<ILIMIT);i++)
	{
		j = LongDivide(aWork, &i, aWork);
		if (j<=0)
			i = ILIMIT + 1;
		LongAdd(aWork, aResult, aResult);
	}
	printf("e = ");
	printf("%1.1d.", aResult[1]);
	for (i=2;(i<NUMBER_WIDTH);i++)
	{
		#if (DIGS_IN_BASE==5)
		printf("%5.5d ", aResult[i]);
		#endif
		#if (DIGS_IN_BASE==1)
		printf("%1.1d", aResult[i]);
		if ((i % 5)==1)
			printf(" ");
		#endif
		if ((i % 10)==0)
		{
			printf("\n");
			if ((i % 100)==0)
				printf("\n");
		}
	}
	printf("\n");
	return 1;
} 

int LongDivide(int *Numerator, int *Denominator, int *Answer)
{
	int iStatus = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	int d = 0;

	d = *Denominator;
	Answer[0] = Numerator[0];
	for (j=1;(j<=Numerator[0]);j++)
	{
		if (k>0)
			m = Numerator[j] + (k * NUMBER_BASE);
		else
			m = Numerator[j];
		Answer[j] = m / d;
		if (Answer[j] != 0)
			iStatus = 1;
		k = m % d;
	}
	return iStatus;
}

int LongAdd(int *iFirst, int *iSecond, int *iAnswer)
{
	int iStatus = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;

	i = iFirst[0];
	k = 0;
	for (j=i;(j>0);j--)
	{
		if (iFirst[j]!=0)
			iStatus = 1;
		m = iFirst[j] + iSecond[j] + k;
		k = 0;
		while (m>=NUMBER_BASE)
		{
			m -= NUMBER_BASE;
			k += 1;
		}
		iAnswer[j] = m;
	}
	return iStatus;
}