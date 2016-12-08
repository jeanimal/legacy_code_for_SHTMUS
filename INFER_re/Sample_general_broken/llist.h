#include <stdio.h>
#include <stdlib.h>
#include "umacros.h"

typedef long DATATYPE;


typedef struct node {
DATATYPE i;
struct node *next;
} *LListPtr,LList;

typedef struct list {
LListPtr front;
LListPtr back;
} ListType;

long Equal_long_Test(long *s1,long *s2);
long Less_Than_long_Test(long *s1,long *s2);
long Greater_Than_long_Test(long *s1,long *s2);
long Length_List(ListType *AList);
void Init_List (ListType *AList);
void Free_List (ListType *AList);
void Copy_To_Array(ListType *AList,DATATYPE AnArray[]);
DATATYPE Top_N(long n,ListType *AList);
DATATYPE Bot_N(long n,ListType *AList);
void Draw_Wo_Replacement (DATATYPE retarray[], long range);
void Draw_Wo_Replacement_List (ListType *AList,long range);
long Remove_Certain_Items(DATATYPE n,ListType *AList,long (*qual)(void *,void *));
void Print_List (ListType *AList);
long Remove_Item (DATATYPE n, ListType *AList);
DATATYPE Remove_Nth (DATATYPE n,ListType *AList);
extern void Append (DATATYPE x,ListType *AList);
                                                                
