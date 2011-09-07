#include <stdlib.h>

#define MemMagic 0xA5
#define WordSize 4
#define WordAlign(addr) (((addr) + WordSize - 1) & (- WordSize))
#define HeapSize 64

struct MemMeta {
    size_t size;             /* the size of the block */
    unsigned char cMagic;    /* magic number */
    unsigned char fOccupied; /* flag of occupied */
    struct MemMeta * next;   /* pointer to next block */
    struct MemMeta * prev;   /* pointer to prev block */
};

#define Delta (sizeof (struct MemMeta) + 4)

struct MemMeta memmeta_;
char heap_[HeapSize];

void
initializeMemory () {
  struct MemMeta * pmemmetaInitOne;
    pmemmetaInitOne = (struct MemMeta *) heap_;
    memmeta_.size = sizeof (struct MemMeta) + (size_t) 0;
    memmeta_.cMagic = MemMagic;
    memmeta_.fOccupied = 1;
    memmeta_.next = memmeta_.prev = pmemmetaInitOne;
    pmemmetaInitOne->size = HeapSize;
    pmemmetaInitOne->cMagic = MemMagic;
    pmemmetaInitOne->fOccupied = 0;
    pmemmetaInitOne->next = pmemmetaInitOne->prev = & memmeta_;
}

void *
allocateMemory (
  size_t sizeReq ) {
  struct MemMeta * pmemmeta;
  size_t sizeNewBlock;
    sizeNewBlock = WordAlign(sizeReq + sizeof (struct MemMeta));
    for (
     pmemmeta = memmeta_.next;
     pmemmeta != & memmeta_;
     pmemmeta = pmemmeta->next ) {
        if ((! pmemmeta->fOccupied) && pmemmeta->size >= sizeNewBlock) {
            /* If the block is too small to fragmentate */
            if (pmemmeta->size - sizeNewBlock <= Delta) {
                pmemmeta->fOccupied = 1;
            } else {
              struct MemMeta * pmemmetaRest;
                pmemmetaRest =
                 (struct MemMeta *) ((char *) pmemmeta + sizeNewBlock);
                pmemmetaRest->cMagic = MemMagic;
                pmemmetaRest->fOccupied = 0;
                pmemmetaRest->size = pmemmeta->size - sizeNewBlock;
                pmemmeta->size = sizeNewBlock;
                pmemmeta->fOccupied = 1;
                /* Insert the "rest" block */
                pmemmeta->next->prev = pmemmetaRest;
                pmemmetaRest->next = pmemmeta->next;
                pmemmeta->next = pmemmetaRest;
                pmemmetaRest->prev = pmemmeta;
            }
            return ((char *) pmemmeta + (sizeof (struct MemMeta)));
        }
    }
    return ((void *) 0);
}

void
freeMemory (
  void * pv) {
  struct MemMeta *pmemmeta;
    pmemmeta =
     (struct MemMeta *) ((char *) pv - (sizeof (struct MemMeta)));
    if (pmemmeta->cMagic != MemMagic) {
        return;
    }
    if (! pmemmeta->prev->fOccupied) {
        pmemmeta->next->prev = pmemmeta->prev;
        pmemmeta->prev->next = pmemmeta->next;
        pmemmeta->prev->size += pmemmeta->size;
        pmemmeta = pmemmeta->prev;
    }
    if (! pmemmeta->next->fOccupied) {
        pmemmeta->next->next->prev = pmemmeta;
        pmemmeta->size += pmemmeta->next->size;
        pmemmeta->next = pmemmeta->next->next;
    }
    pmemmeta->fOccupied = 0;
}

#include <stdio.h>

#define RepNum 10

int
main (
  int argc,
  char * * argv ) {
  size_t i;
  void * apv[RepNum];
    initializeMemory();
    for (i = 1; i < RepNum; i ++) {
        apv[i] = allocateMemory((size_t) (i * 1));
        if (apv[i]) {
            printf("The address for the allocated memory: %p\n", apv[i]);
#if 0
            freeMemory(apv[i]);
            apv[i] = (void *) 0;
#endif
        } else {
            printf("Memory allocation failed!\n");
        }
    }
    for (i = 1; i < RepNum; i ++) {
        if (apv[i]) {
            freeMemory(apv[i]);
        }
    }
printf("%d\n", sizeof (struct MemMeta));
    return (0);
}

