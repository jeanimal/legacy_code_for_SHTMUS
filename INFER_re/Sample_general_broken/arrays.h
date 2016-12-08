#ifndef _ARRAYS_H_

#define _ARRAYS_H_



struct VectTag {

  double* pData;

  long maxSize;

};



struct MatTag {

  double* pData;

  long maxRows;

  long maxCols;

};



struct longVectTag {

  long* pData;

  long maxSize;

};



typedef struct MatTag Matrix;

typedef struct VectTag Vector;

typedef struct longVectTag longVector;



long newMat(Matrix* Mat, long maxRows, long maxCols);

void deleteMat(Matrix* Mat);

long newVect(Vector* Vect, long maxSize);

void deleteVect(Vector* Vect);

long newlongVect(longVector* Vect, long maxSize);

void deletelongVect(longVector* Vect);

long checkRowCol(Matrix Mat, long row, long col);

long checkIndex(Vector Vect, long index);



#define MAT(Mat, row, col) Mat.pData[(row) + Mat.maxRows * (col)]

#define VEC(Vect, index) Vect.pData[(index)]





#endif



