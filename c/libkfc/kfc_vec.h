#ifndef K_VEC_H /* { */
#define K_VEC_H

struct VecImp;
typedef struct VecImp * Vec;

typedef int (* Vec_CompareFunction) (void *, void *);

Vec Vec_new();
void Vec_delete(Vec self);

void Vec_add(Vec self, void * pv);
void * Vec_chop(Vec self);
void Vec_sort(Vec self, Vec_CompareFunction compare);
void * Vec_get(Vec self, void * pv);
void Vec_remove(Vec self, void * pv);
void * Vec_getAt(Vec self, int i);
void Vec_removeAt(Vec self, int i);

int Vec_getLength(Vec self);

/* ---------------------------------------------------------------- */

struct SVecImp;
typedef struct SVecImp * SVec;

typedef int (* SVec_CompareFunction) (void *, void *);

SVec SVec_new(SVec_CompareFunction compare);
void SVec_delete(SVec self);

void SVec_add(SVec self, void * pv);
void * SVec_get(SVec self, void * pv);
void SVec_remove(SVec self, void * pv);
void * SVec_getAt(SVec self, int i);
void SVec_removeAt(SVec self, int i);

int SVec_getLength(SVec self);

#endif /* } */

