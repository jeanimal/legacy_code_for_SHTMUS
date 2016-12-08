/*
 *            INFER SOFTWARE
 *
 *    Copyright (c) 1999 Jean Czerlinski & Dan Goldstein.
 *            All Rights Reserved
 *
 *
 * This software is confidential and proprietory information of the
 * above copyright holders. You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into the above copyright holders.
 *
 */

/* INFER is for comparing the accuracy and frugality of
 * different inference (prediction) heuristics.
 *
 * The task is to infer which of two objects drawn from a population has
 * a higher value on a criterion variable based on several
 * numeric or binary variables.
 *
 * file: llist.c
 * purpose: linked list functions, used for random ordering of questions
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "llist.h"

/*
 * Linked-list functions   Dan Goldstein Oktober 1995  These function are for
 * singly-linked lists and generally deal with numbers (longs specifically)
 * but have been designed to be easily modifiable for other data types.
 * Functions which make specific reference to longs have been marked.  Be sure
 * to look at llist.h for prototypes. 
 *
 * The variables of type ListType refer to a list and carry pointers to its
 * first and last elements.  So, if you have ListType *Alist then
 * AList->front and AList->back point to the beginning and ends of a list. 
 */
long
Equal_long_Test(long *s1, long *s2)
{
	if (*s1 == *s2)
	{
		return 1;
	} else
	{
		return 0;
	}
}

/*
 * FUNCTION Less_Than_long_Test assumes that s1 is the value in the list and
 * s2 is the value passed in 
 */
long
Less_Than_long_Test(long *s1, long *s2)
{
	if (*s1 < *s2)
	{
		return 1;
	} else
	{
		return 0;
	}
}

/*
 * FUNCTION Greater_Than_long_Test assumes that s1 is the value in the list
 * and s2 is the value passed in 
 */
long
Greater_Than_long_Test(long *s1, long *s2)
{
	if (*s1 > *s2)
	{
		return 1;
	} else
	{
		return 0;
	}
}

/*
 * FUNCTION PRINT LIST This function is for debugging and is not really
 * abstract (it assumes i is an long) 
 */

void
Print_List(ListType * AList)
{
LListPtr        temp = AList->front;
	printf("( ");
	while (temp)
	{
		printf("%ld ", temp->i);
		temp = temp->next;
	}
	printf(")\n");
}





void
Free_List(ListType *AList)
{
LListPtr	temp=AList->front,before;
while (temp)
	{
	before=temp;
	temp=temp->next;
	free(before);
        }
}






/*
 * FUNCTION LENGTH_LIST Measures the length of a list, returns 0 for empty
 * lists 
 */

long
Length_List(ListType * AList)
{
long             i = 0;
LListPtr        temp = AList->front;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return i;
}






/*
 * FUNCTION INIT LIST Pass the function the address of a variable of ListType
 * and it will initalize it.  E.g. from the main prog call ListType MyList;
 * InitList (&MyList); 
 */

void
Init_List(ListType * AList)
{
	AList->front = NULL;
	AList->back = NULL;
}






/* FUNCTION TOP_N
Returns the values of the last n items in the passed in list.  It
assumes these values are numbers.  Note that these are only the
highest values in the list if the list is sorted, also, it 
doesn't pay attention to repeated values in the list

*/
DATATYPE 
Top_N(long n,ListType *AList)
{
LListPtr temp;
long 	i,
	len;
DATATYPE sum=0;

if (!(AList->front))
        {
                printf("Empty in Top_N");
                exit(1);
        }
temp=AList->front;
len=Length_List(AList);
if (len<n)
        {
                printf("Request exceeds list length in Top_N");
                exit(1);
        }
for (i=0;i<len-n;i++)
	{
	temp=temp->next;
	}
for (i=0;i<n;i++)
	{
        sum+=temp->i;
	temp=temp->next;
	}
return sum;
}




/* FUNCTION BOT_N
Returns the values of the first n items in the passed in list.  It
assumes these values are numbers.  Note that these are only the
lowest values in the list if the list is sorted, also, it 
doesn't pay attention to repeated values in the list

*/
DATATYPE 
Bot_N(long n,ListType *AList)
{
LListPtr temp;
long 	i,
	len;
DATATYPE sum=0;

if (!(AList->front))
        {
                printf("Empty in Bot_N");
                exit(1);
        }
temp=AList->front;
len=Length_List(AList);
if (len<n)
        {
                printf("Request exceeds list length in Top_N");
                exit(1);
        }
for (i=0;i<n;i++)
	{
        sum+=temp->i;
	temp=temp->next;
	}
return sum;
}

void Copy_To_Array(ListType *AList,DATATYPE AnArray[])
{
LListPtr temp;
long     i=0;
        
if (!(AList->front))
        {
                printf("Empty in Copy_To_Array");
                exit(1);
        }
temp=AList->front;
do 
	{
	AnArray[i]=temp->i;
	i++;
	temp=temp->next;
	}
while (temp);

}  /* End Copy to array */





/*
 * FUNCTION APPEND This function appends to the front [CORRECTION: BACK]
 *  of the list a variable
 * of type datatype. If no list is there, it will create one and return the
 * correct pointer to it. Note that assignment is done with =, and this might
 * not hold with all types of variables 
 */
void
Append(DATATYPE x, ListType *AList)
{
LListPtr        temp;
	if (!(AList->front))
	{
		temp = (LListPtr) malloc(sizeof(LList));
		if (!temp)
		{
			printf("No More Memory in append in llist.c");
			exit(1);
		}
		temp->i = x;	/* This is the assignment referred to in the
				 * comment */
		temp->next = NULL;
		(AList->front) = (AList->back) = temp;
	} else
	{
		temp = (LListPtr) malloc(sizeof(LList));
		if (!temp)
		{
			printf("No Mo Memory");
			exit(1);
		}
		temp->i = x;
		temp->next = NULL;
		(AList->back)->next = temp;
		(AList->back) = temp;
	}
}



long
Remove_Certain_Items(DATATYPE n, ListType * AList, long (*qual) (void *, void *))
{
LListPtr        temp = AList->front;
LListPtr        prev = NULL;
long             found = 0;
	if (!(AList->front))
	{
		printf("Remove From Empty in Remove_Certain_Items");
		exit(1);
	}
	while (temp != NULL)
	{			/* begin while */
		if ((*qual) (&(temp->i), &n))
		{
			if (temp == AList->front)
			{
				AList->front = (AList->front)->next;
				free(temp);
				temp = AList->front;
				found++;
			} else
			if (temp == AList->back)
			{
				free(temp);
				temp = NULL;
				found++;
				AList->back = prev;
				prev->next = NULL;
			} else
			{
				prev->next = temp->next;
				free(temp);
				temp = prev->next;
				found++;
			}
		} else
		{
			prev = temp;
			temp = temp->next;
		}
	}			/* end while */
	return found;
}



/*
 * FUNCTION REMOVE_NTH Remove Nth takes out and returns the Nth element of a
 * list, starting counting from 0. Complains if no list or if the list has
 * fewer than n+1 items (remember, we are counting from 0) 
 */
DATATYPE
Remove_Nth(DATATYPE n, ListType * AList)
{
DATATYPE        i;
DATATYPE        retval;
LListPtr        temp = AList->front;
LListPtr        prev = NULL;
	if (!(AList->front))
	{
		printf("Remove From Empty in Remove_Nth");
		exit(1);
	}
	i = 0;
	while ((i < n) && (temp != NULL))
	{
		prev = temp;
		temp = temp->next;
		i++;
	}
	if (temp == NULL)
	{
		printf("Overshot end of list in llist.c");
		exit(1);
	}
	if (prev == NULL)
	{
		(AList->front) = (AList->front)->next;
	} else
	{
		prev->next = temp->next;
		temp->next = NULL;
		if ((AList->back) == temp)
			(AList->back) = prev;
	}
	retval = temp->i;
	free(temp);
	return retval;
}


/*
 * FUNCTION DRAW_WO_REPLACEMENT This function generates indices from 0 to
 * range-1 and returns them in a random order in an array provided by the
 * calling routine.  It does not check whether the array is large enough to
 * hold the indices. This must be determined by the call routine.  Note that
 * this routines assumes i is a number,so it is  not abstract 
 */

void
Draw_Wo_Replacement(DATATYPE retarray[], long range)
{
DATATYPE        i;
long             k, spot;
ListType        MyList;
	Init_List(&MyList);
	for (i = 0; i < range; i++)
		Append(i, &MyList);
	if(DEBUG2) {
        printf("Draw_Wo_Replacement printing of list\n");
		Print_List(&MyList);
		printf("\n");
	}
	k = range;
	for (i = 0; i < k; i++)
	{
		spot = (New_Rand(range));
		/* printf("spot = %ld\n",spot); */
		retarray[i] = Remove_Nth(spot, &MyList);
		range--;
	}
}
/*
 * FUNCTION DRAW_WO_REPLACEMENT_LIST This was recently improved by Dan so
 * that it takes a empty linked list and fills it up and returns it as a list
 * (used to be an array).  Could be modified so that it takes a list, and, if
 * the list is full, it returns, the contents in some random order.  In any
 * case, this starts counting from 0 
 */

void
Draw_Wo_Replacement_List(ListType *AList, long range)
{
DATATYPE        i;
long             k, spot;
ListType        MyList;
	Init_List(&MyList);
	Init_List(AList);
/* 	srand(time(0));  Assume this has been done! */
	for (i = 0; i < range; i++)
		Append(i, &MyList);
	Print_List(&MyList);
	printf("\n");
	k = range;
	for (i = 0; i < k; i++)
	{
		spot = (New_Rand(range));
		/* printf("spot = %ld\n",spot); */
		Append(Remove_Nth(spot, &MyList), AList);
		range--;
	}
}
