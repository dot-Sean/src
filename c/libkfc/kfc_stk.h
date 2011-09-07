#ifndef KFC_STK_H /* { */
#define KFC_STK_H

struct StkImp;
typedef struct StkImp * Stk;

Stk Stk_new();
void Stk_delete(Stk self);

void Stk_push(Stk self, void * pv);
void * Stk_pop(Stk self);

typedef int (* Stk_CompareFunction) (void *, void *);

void Stk_sort(Stk self, Stk_CompareFunction compare);

void * Stk_getAt(Stk self, int i);
void Stk_removeAt(Stk self, int i);

int Stk_getHeight(Stk self);

#endif /* } */

