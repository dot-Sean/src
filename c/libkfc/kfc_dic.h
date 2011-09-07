#ifndef K_DIC_H /* { */
#define K_DIC_H

struct DicImp;
typedef struct DicImp * Dic;

Dic Dic_new();
void Dic_delete(Dic self);

void Dic_add(Dic self, const char * psz, void * pv);
void Dic_remove(Dic self, const char * psz);
void * Dic_refer(Dic self, const char * psz);
const char * Dic_getFirstKey(Dic self);
const char * Dic_getNextKey(Dic self);

const char * Dic_getKeyAt(Dic self, int i);

#endif /* } */
