#include "kfc_dic.h"

/* #define MemDebug */
#include "kfc_mem.h"

#define Dic_TableSize 256

typedef struct Dic_NodeTab {
    char * psz;
    void * pv;
    struct Dic_NodeTab * prev;
    struct Dic_NodeTab * next;
} Dic_Node;

struct DicImp {
    Dic_Node anode[Dic_TableSize];
    int iCurrent;
    Dic_Node * pnodeCurrent;
};

#include <string.h>

Dic
Dic_new () {
  Dic self;
    self = New(struct DicImp, 1);
    return (self);
}

void
Dic_delete (
  Dic self ) {
  int i;
  Dic_Node * pnode;
  Dic_Node * pnodeBak;
    for (i = 0; i < Dic_TableSize; i ++) {
        for (pnode = self->anode[i].next; pnode; pnode = pnodeBak) {
            pnodeBak = pnode->next;
            Free((void *) pnode->psz);
            Free((void *) pnode);
        }
    }
    Free((void *) self);
}

static int
Dic_hash (
  const char * psz ) {
  int nSum;
    nSum = 0;
    while (* psz) {
        nSum += (* psz);
        psz ++;
    }
    return (((nSum + (nSum * nSum)) / 2) % Dic_TableSize);
}

static Dic_Node *
Dic_referSub (
  Dic self,
  const char * psz ) {
  int i;
  Dic_Node * pnode;
    i = Dic_hash(psz);
    for (pnode = self->anode[i].next; pnode; pnode = pnode->next) {
        if (strcmp(pnode->psz, psz) == 0) {
            return (pnode);
        }
    }
    return ((void *) 0);
}

void
Dic_add (
  Dic self,
  const char * psz,
  void * pv ) {
  Dic_Node * pnode;
    pnode = Dic_referSub(self, psz);
    if (pnode) {
        /* overwrite it. user have to manage not to */
        pnode->pv = pv;
    } else {
      int i;
        i = Dic_hash(psz);
        for (pnode = & self->anode[i]; pnode->next; pnode = pnode->next) {
            ;
        }
        pnode->next = New(Dic_Node, 1);
        pnode->next->prev = pnode;
        pnode = pnode->next;
        pnode->psz = StrDup(psz);
        pnode->pv = pv;
    }
}

void *
Dic_refer (
  Dic self,
  const char * psz ) {
  Dic_Node * pnode;
    pnode = Dic_referSub(self, psz);
    if (pnode) {
        return (pnode->pv);
    } else {
        return ((void *) 0);
    }
}

void
Dic_remove (
  Dic self,
  const char * psz ) {
  Dic_Node * pnode;
    pnode = Dic_referSub(self, psz);
    if (pnode) {
        pnode->prev->next = pnode->next;
        if (pnode->next) {
            pnode->next->prev = pnode->prev;
        }
        Free((void *) pnode->psz);
        Free((void *) pnode);
    } else {
        /* Not found */
        ;
    }
}

const char *
Dic_getNextKey (
  Dic self ) {
    for (
     ;
     self->iCurrent < Dic_TableSize;
     self->iCurrent ++, self->pnodeCurrent =
      self->anode[self->iCurrent].next ) {
        if (self->pnodeCurrent) {
          const char * psz = self->pnodeCurrent->psz;
            self->pnodeCurrent = self->pnodeCurrent->next;
            return (psz);
        }        
    }
    return ((void *) 0);
}

const char *
Dic_getFirstKey (
  Dic self ) {
    self->iCurrent = 0;
    self->pnodeCurrent = self->anode[0].next;
    return (Dic_getNextKey(self));
}

const char *
Dic_getKeyAt (
  Dic self,
  int i ) {
  int iCtr;
  int iEntry;
  Dic_Node * pnode;
    for (
     iEntry = 0, iCtr = 0;
     iEntry < Dic_TableSize;
     iEntry ++ ) {
        for (
         pnode = self->anode[iEntry].next;
         pnode;
         pnode = pnode->next ) {
            if (i == iCtr) {
                return (pnode->psz);
            }
            iCtr ++;
        }        
    }
    return ((void *) 0);
}
