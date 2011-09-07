/* malloc(), free() */
#include <stdlib.h>
/* printf() */
#include <stdio.h>
/* pthread_*() */
#include <pthread.h>
/* EAGAIN */
#include <errno.h>
/* sleep() */
#include <unistd.h>
/* raise(), SIGTRAP */
#include <signal.h>

struct Matrix {
    int nRow;
    int nCol;
    int * pn;
};

struct Matrix *
Matrix_create (
  int nRow,
  int nCol ) {
  struct Matrix * self;
    self = malloc(sizeof (struct Matrix));
    self->nRow = nRow;
    self->nCol = nCol;
    self->pn = malloc((sizeof (int)) * nRow * nCol);
    return (self);
}

void
Matrix_free (
  struct Matrix * self ) {
    free(self->pn);
    free(self);
}

#define Matrix_set(self, iRow, iCol, n) do { \
  self->pn[(iRow * self->nCol) + iCol] = (n); \
} while (0)

#define Matrix_get(self, iRow, iCol) (self->pn[(iRow * self->nCol) + iCol])

void
Matrix_multSub (
  struct Matrix * pmatrixC,
  struct Matrix * pmatrixA,
  struct Matrix * pmatrixB,
  int iRow,
  int iCol ) {
  int i;
    Matrix_set(pmatrixC, iRow, iCol, 0);
    for (i = 0; i < pmatrixA->nCol; i ++) {
        Matrix_set(pmatrixC, iRow, iCol, Matrix_get(pmatrixC, iRow, iCol) +
         Matrix_get(pmatrixA, iRow, i) * Matrix_get(pmatrixB, i, iCol) );
    }
}            

struct MatrixMultOrder {
    struct Matrix * pmatrixC;
    struct Matrix * pmatrixA;
    struct Matrix * pmatrixB;
    int iRow;
    int iCol;
};

void *
Matrix_multWorker (
  void * pv ) {
  struct MatrixMultOrder * porder = (struct MatrixMultOrder *) pv;
    Matrix_multSub(
     porder->pmatrixC,
     porder->pmatrixA,
     porder->pmatrixB,
     porder->iRow,
     porder->iCol );
    return (NULL);
}

int
Matrix_mult (
  struct Matrix * pmatrixC,
  struct Matrix * pmatrixA,
  struct Matrix * pmatrixB ) {
  int rc = -1;
  pthread_t * ppthread = NULL;
  struct MatrixMultOrder * porderAll = NULL;
    do {
      int iRow;
      int iCol;
      pthread_attr_t attr;
      size_t sizeStack;
        if (pmatrixA->nRow != pmatrixB->nCol ||
         pmatrixA->nCol != pmatrixB->nRow ) {
            break;
        }
        pthread_attr_init(& attr);
        pthread_attr_getstacksize(& attr, & sizeStack);
        sizeStack = 16384;
        pthread_attr_setstacksize(& attr, sizeStack);
        if (NULL == (ppthread = (pthread_t *)
         malloc((sizeof (pthread_t)) * pmatrixC->nRow * pmatrixC->nCol) )) {
            break;
        }
        if (NULL == (porderAll = (struct MatrixMultOrder *)
         malloc((sizeof (struct MatrixMultOrder)) *
         pmatrixC->nRow * pmatrixC->nCol ))) {
            break;
        }
        for (iRow = 0; iRow < pmatrixC->nRow; iRow ++) {
            for (iCol = 0; iCol < pmatrixC->nCol; iCol ++) {
              struct MatrixMultOrder * porder =
               & porderAll[(iRow * pmatrixC->nCol) + iCol];
                porder->pmatrixA = pmatrixA;
                porder->pmatrixB = pmatrixB;
                porder->pmatrixC = pmatrixC;
                porder->iRow = iRow;
                porder->iCol = iCol;
                if (pthread_create(
                 & ppthread[(iRow * pmatrixC->nCol) + iCol],
                 & attr,
                 Matrix_multWorker,
                 (void *) porder ) != 0) {
                    perror("Error");
                    goto finally;
                }
            }
        }
        for (iRow = 0; iRow < pmatrixC->nRow; iRow ++) {
            for (iCol = 0; iCol < pmatrixC->nCol; iCol ++) {
                pthread_join(ppthread[(iRow * pmatrixC->nCol) + iCol], NULL);
            }
        }
        rc = 0;
    } while (0);
finally:
    if (porderAll) { free(porderAll); }
    if (ppthread) { free(ppthread); }
    return (rc);
}

void
Matrix_show (
  struct Matrix * pmatrix ) {
  int iRow;
  int iCol;
    for (iRow = 0; iRow < pmatrix->nRow; iRow ++) {
      const char * pszDelim = "";
        for (iCol = 0; iCol < pmatrix->nCol; iCol ++) {
            printf("%s%3d", pszDelim, Matrix_get(pmatrix, iRow, iCol));
            pszDelim = " ";
        }
        printf("\n");
    }
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  struct Matrix * pmatrixA = NULL;
  struct Matrix * pmatrixB = NULL;
  struct Matrix * pmatrixC = NULL;
    do {
      int iRow;
      int iCol;
        //__asm__ __volatile__("int3");
        //raise(SIGTRAP);
        //pmatrixA = Matrix_create(360, 5);
        pmatrixA = Matrix_create(2, 2);
        for (iRow = 0; iRow < pmatrixA->nRow; iRow ++) {
            for (iCol = 0; iCol < pmatrixA->nCol; iCol ++) {
                Matrix_set(pmatrixA, iRow, iCol, iRow + iCol + 1);
            }
        }
        printf("A =\n");
        Matrix_show(pmatrixA);
        //pmatrixB = Matrix_create(5, 360);
        pmatrixB = Matrix_create(2, 2);
        for (iRow = 0; iRow < pmatrixB->nRow; iRow ++) {
            for (iCol = 0; iCol < pmatrixB->nCol; iCol ++) {
                Matrix_set(pmatrixB, iRow, iCol, iRow + iCol + 1);
            }
        }
        printf("B =\n");
        Matrix_show(pmatrixB);
        pmatrixC = Matrix_create(pmatrixA->nRow, pmatrixB->nCol);
        if (Matrix_mult(pmatrixC, pmatrixA, pmatrixB) != 0) {
            break;
        }
        printf("C = A * B =\n");
        Matrix_show(pmatrixC);
        rc = 0;
    } while (0);
    if (pmatrixC) { Matrix_free(pmatrixC); }
    if (pmatrixB) { Matrix_free(pmatrixB); }
    if (pmatrixA) { Matrix_free(pmatrixA); }
    //pthread_exit(NULL); // cannot return value
    return (rc);
}
