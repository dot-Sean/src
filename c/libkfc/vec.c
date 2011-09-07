#include "kfc_vec.h"

#include "kfc.h"

struct SVecImp {
    void * * ppv;
    int nAllocated;
    int iCurrent;
    SVec_CompareFunction compare;
    Boolean fSorted;
};

static const int SVec_InitSize = 32;

SVec
SVec_new (
  SVec_CompareFunction compare ) {
  SVec self;
    self = New(struct SVecImp, 1);
    self->nAllocated = SVec_InitSize;
    self->ppv = New(void *, self->nAllocated);
    self->iCurrent = 0;
    self->compare = compare;
    self->fSorted = True;
    return (self);
}

void
SVec_delete (
  SVec self ) {
    Delete(self->ppv);
    Delete(self);
}

void
SVec_add (
  SVec self,
  void * pv ) {
    if (self->iCurrent == self->nAllocated - 1) {
        self->nAllocated *= 2;
        self->ppv = Renew(void *, self->nAllocated, self->ppv);
    }
    self->ppv[self->iCurrent ++] = pv;
    self->ppv[self->iCurrent] = (void *) 0;
    self->fSorted = False;
}

/* Insertion sort */
static void
SVec_isort (
  SVec self ) {
  int i1;
  int i2;
  void * pv;
  void * * ppv = self->ppv;
  SVec_CompareFunction compare = self->compare;
  const int nLength = SVec_getLength(self);
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
#define SVec_StackSize 32
#define SVec_Threshold 10
static void
SVec_qsort (
  SVec self ) {
  int i1;
  int i2;
  int iLeft;
  int iRight;
  int iSP;
  int aiLeft[SVec_StackSize];
  int aiRight[SVec_StackSize];
  void * pvPivot;
  void * pvSwapTmp;
  void * * ppv = self->ppv;
  SVec_CompareFunction compare = self->compare;
    iLeft = 0;
    iRight = self->iCurrent - 1;
    iSP = 0;
    while (True) {
        if (iRight - iLeft <= SVec_Threshold) {
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
            if (i1 - iLeft > SVec_Threshold) {
                aiLeft[iSP] = iLeft;
                aiRight[iSP] = i1 - 1;
                iSP ++;
            }
            iLeft = i2 + 1;
        } else {
            if (iRight - i2 > SVec_Threshold) {
                aiLeft[iSP] = i2 + 1;
                aiRight[iSP] = iRight;
                iSP ++;
            }
            iRight = i1 - 1;
        }
    }
    SVec_isort(self);
}

static void
SVec_sort (
  SVec self ) {
    SVec_qsort(self);
    self->fSorted = True;
}

void *
SVec_getAt (
  SVec self,
  int i ) {
    if (! self->fSorted) {
        if (self->compare) {
            SVec_sort(self);
        }
    }
    return (self->ppv[i]);
}

static int
SVec_getSub (
  SVec self,
  void * pv ) {
    if (! self->fSorted) {
        if (self->compare) {
            SVec_sort(self);
        /* Baka search for not sorted array */
        } else {
          int i;
          const int nLength = SVec_getLength(self);
          void * * ppv = self->ppv;
            for (i = 0; i < nLength; i ++) {
                if (ppv[i] == pv) {
                    return (i);
                }
            }
            /* not found */
            return (-1);
        }
    }
    /* quick search */
    {
      int iLow = 0;
      int iHigh = self->iCurrent - 1;
      int iMiddle;
      void * * ppv = self->ppv;
      SVec_CompareFunction compare = self->compare;
        while (iLow <= iHigh) {
            iMiddle = (int) ((iLow + iHigh) / 2);
            if (compare(ppv[iMiddle], pv) == 0) {
                return (iMiddle);
            } else if (compare(ppv[iMiddle], pv) > 0) {
                iHigh = iMiddle - 1;
            } else {
                iLow = iMiddle + 1;
            }
        }
    }
    /* not found */
    return (-1);
}

void *
SVec_get (
  SVec self,
  void * pv ) {
  int i = SVec_getSub(self, pv);
    return ((i >= 0)? self->ppv[i]: (void *) 0);
}  

void
SVec_removeAt (
  SVec self,
  int i ) {
  void * pvRet;
  int nLength = SVec_getLength(self);
  void * * ppv = self->ppv;
    if (i < 0 || nLength <= i) {
        return;
    }
    pvRet = ppv[i];
    for (; i < nLength; i ++) {
        ppv[i] = ppv[i + 1];
    }
    ppv[i + 1] = (void *) 0;
    self->iCurrent --;
}

void
SVec_remove (
  SVec self,
  void * pv ) {
  int nLength = SVec_getLength(self);
  int i;
  void * * ppv = self->ppv;
    if ((i = SVec_getSub(self, pv)) < 0) {
        return;
    }
    for (; i < nLength; i ++) {
        ppv[i] = ppv[i + 1];
    }
    ppv[i + 1] = (void *) 0;
    self->iCurrent --;
}

static void
SVec_sortWithGiven (
  SVec self,
  SVec_CompareFunction compare ) {
  SVec_CompareFunction compareSav = self->compare;
    self->compare = compare;
    SVec_sort(self);
    self->compare = compareSav;
}

int
SVec_getLength (
  SVec self ) {
    return (self->iCurrent);
}

/* ---------------------------------------------------------------- */

struct VecImp {
    SVec svec;
};

Vec
Vec_new () {
  Vec self;
    self = New(struct VecImp, 1);
    self->svec = SVec_new((void *) 0);
    return (self);
}

void
Vec_delete (
  Vec self ) {
    SVec_delete(self->svec);
    Delete(self);
}

void
Vec_add (
  Vec self,
  void * pv ) {
    SVec_add(self->svec, pv);
}

void *
Vec_chop (
  Vec self ) {
  int i;
  void * pvRet = (void *) 0;
    i = SVec_getLength(self->svec) - 1;
    if (i >= 0) {
        pvRet = SVec_getAt(self->svec, i);
        SVec_removeAt(self->svec, i);
    }
    return (pvRet);
}

void
Vec_sort (
  Vec self,
  Vec_CompareFunction compare ) {
    SVec_sortWithGiven(self->svec, (SVec_CompareFunction) compare);
}

void *
Vec_get (
  Vec self,
  void * pv) {
    return (SVec_get(self->svec, pv));
}

void
Vec_remove (
  Vec self,
  void * pv ) {
    SVec_remove(self->svec, pv);
}

void *
Vec_getAt (
  Vec self,
  int i ) {
    return (SVec_getAt(self->svec, i));
}

void
Vec_removeAt (
  Vec self,
  int i ) {
    SVec_removeAt(self->svec, i);
}

int
Vec_getLength (
  Vec self ) {
    return (SVec_getLength(self->svec));
}
