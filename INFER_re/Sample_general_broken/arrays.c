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
 * Most of this code comes from Namir C. Shamas' book.
 * JFC copied and then modified it.
 */

/* INFER is for comparing the accuracy and frugality of
 * different inference (prediction) heuristics.
 *
 * The task is to infer which of two objects drawn from a population has
 * a higher value on a criterion variable based on several
 * numeric or binary variables.
 *
 * file: arrays.c
 * purpose: functions for creating and manipulating arrays, used by regression 
 */


#include "arrays.h"

#include <stdio.h>
#include <stdlib.h>


long newMat(Matrix* Mat, long maxRows, long maxCols)

{

  maxRows = (maxRows < 1) ? 1 : maxRows;

  maxCols = (maxCols < 1) ? 1 : maxCols;

  Mat->maxRows = maxRows;

  Mat->maxCols = maxCols;

  Mat->pData = NULL;

  Mat->pData = (double*) malloc(maxRows * maxCols *

                                sizeof(double));

  return (Mat->pData != NULL) ? 1 : 0;

}



void deleteMat(Matrix* Mat)

{

  if (Mat->pData)

    free(Mat->pData);

  Mat->pData = NULL;

  Mat->maxCols = 0;

  Mat->maxRows = 0;

}



long newVect(Vector* Vect, long maxSize)

{

  maxSize = (maxSize < 1) ? 1 : maxSize;

  Vect->maxSize = maxSize;

  Vect->pData = NULL;

  Vect->pData = (double*) malloc(maxSize * sizeof(double));

  return (Vect->pData != NULL) ? 1 : 0;

}



void deleteVect(Vector* Vect)

{

  if (Vect->pData)

    free(Vect->pData);

  Vect->pData = NULL;

  Vect->maxSize = 0;

}



long newlongVect(longVector* Vect, long maxSize)

{

  maxSize = (maxSize < 1) ? 1 : maxSize;

  Vect->maxSize = maxSize;

  Vect->pData = NULL;

  Vect->pData = (long*) malloc(maxSize * sizeof(long));

  return (Vect->pData != NULL) ? 1 : 0;

}



void deletelongVect(longVector* Vect)

{

  if (Vect->pData)

    free(Vect->pData);

  Vect->pData = NULL;

  Vect->maxSize = 0;

}





long checkRowCol(Matrix Mat, long row, long col)

{

  return (row >= 0 && col >= 0 &&

          row < Mat.maxRows && col < Mat.maxCols) ? 1 : 0;



}



long checkIndex(Vector Vect, long index)

{

  return (index >= 0 && index < Vect.maxSize) ? 1 : 0;

}





