#include "kfc.h"

static int Stk_InitSize_ = 8;

struct StkImp {
    void * * ppv;
    int nAllocated;
    int iCurrent;
};

int
Stk_getHeight (
  Stk self ) {
    return (self->iCurrent);
}

Stk
Stk_new () {
  Stk self;
    self = New(struct StkImp, 1);
    self->nAllocated = Stk_InitSize_;
    self->ppv = New(void *, self->nAllocated);
    self->iCurrent = 0;
    self->ppv[self->iCurrent] = (void *) 0;
    return (self);
}

void
Stk_delete (
  Stk self ) {
    Delete(self->ppv);
    Delete(self);
}

void
Stk_push (
  Stk self,
  void * pv ) {
    if (self->iCurrent == self->nAllocated - 1) {
        self->nAllocated *= 2;
        self->ppv = Renew(void *, self->nAllocated, self->ppv);
    }
    self->ppv[self->iCurrent ++] = pv;
    self->ppv[self->iCurrent] = (void *) 0;
}

void *
Stk_pop (
  Stk self ) {
    if (self->iCurrent > 0) {
        return (self->ppv[-- self->iCurrent]);
    }
    return ((void *) 0);
}

/* Insertion sort */
static void
Stk_isort (
  Stk self,
  Stk_CompareFunction compare ) {
  int i1;
  int i2;
  void * pv;
  void * * ppv = self->ppv;
  const int nLength = Stk_getHeight(self);
    for (i1 = 1; i1 < nLength; i1 ++) {
        pv = ppv[i1];
        for (
         i2 = i1 - 1;
         (i2 >= 0) && (compare(ppv[i2], pv) > 0);
         i2 -- ) {
            ppv[i2 + 1] = ppv[i2];
        }
        ppv[i2 + 1] = pv;
    }
}

/* Quick sort */
static int Stk_StackSize_ = 32;
static int Stk_Threshold_ = 10;
static void
Stk_qsort (
  Stk self,
  Stk_CompareFunction compare ) {
  int i1;
  int i2;
  int iLeft;
  int iRight;
  int iSP;
  int aiLeft[Stk_StackSize_];
  int aiRight[Stk_StackSize_];
  void * pvPivot;
  void * pvSwapTmp;
  void * * ppv = self->ppv;
    iLeft = 0;
    iRight = self->iCurrent - 1;
    iSP = 0;
    while (True) {
        if (iRight - iLeft <= Stk_Threshold_) {
            if (iSP == 0) {
                break;
            }
            iSP --;
            iLeft = aiLeft[iSP];
            iRight = aiRight[iSP];
        }
        pvPivot = ppv[(iLeft + iRight) / 2];
        i1 = iLeft;
        i2 = iRight;
        while (1) {
            while (compare(pvPivot, ppv[i1]) > 0) {
                i1 ++;
            }
            while (compare(ppv[i2], pvPivot) > 0) {
                i2 --;
            }
            if (i2 <= i1) {
                break;
            }
            pvSwapTmp = ppv[i1];
            ppv[i1] = ppv[i2];
            ppv[i2] = pvSwapTmp;
            i1 ++;
            i2 --;
        }
        if (i1 - iLeft > iRight - i2) {
            if (i1 - iLeft > Stk_Threshold_) {
                aiLeft[iSP] = iLeft;
                aiRight[iSP] = i1 - 1;
                iSP ++;
            }
            iLeft = i2 + 1;
        } else {
            if (iRight - i2 > Stk_Threshold_) {
                aiLeft[iSP] = i2 + 1;
                aiRight[iSP] = iRight;
                iSP ++;
            }
            iRight = i1 - 1;
        }
    }
    Stk_isort(self, compare);
}

void
Stk_sort (
  Stk self,
  Stk_CompareFunction compare ) {
    Stk_qsort(self, compare);
}

void *
Stk_getAt (
  Stk self,
  int i ) {
    return (self->ppv[i]);
}

void
Stk_removeAt (
  Stk self,
  int i ) {
  void * pvRet;
  int nHeight = Stk_getHeight(self);
  void * * ppv = self->ppv;
    if (i < 0 || nHeight <= i) {
        return;
    }
    pvRet = ppv[i];
    for (; i < nHeight; i ++) {
        ppv[i] = ppv[i + 1];
    }
    ppv[i + 1] = (void *) 0;
    self->iCurrent --;
}
