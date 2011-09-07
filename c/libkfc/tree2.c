#include "kfc_tree.h"

#define MemDebug
#include "kfc_mem.h"

struct NodeImp {
    const char * pszName;
    Tree treeOwner;
    Dic dic;
    Node nodeParent;
    Node nodePrev;
    Node nodeNext;
    Node nodeChilds;
    Node nodeCurrent;
};

static Node
Node_new (
  const char * pszName,
  Tree treeOwner,
  Node nodeParent,
  Node nodePrev,
  Node nodeNext,
  Node nodeChilds ) {
  Node self;
    self = New(struct NodeImp, 1);
    self->pszName = StrDup(pszName);
    self->treeOwner = treeOwner;
    self->dic = Dic_new();
    self->nodeParent = nodeParent;
    self->nodePrev = nodePrev;
    self->nodeNext = nodeNext;
    self->nodeChilds = nodeChilds;
    return (self);
}

Node
Node_addChild (
  Node self,
  const char * pszName ) {
  Node node;
  Node nodePrev;
  Node nodeNew;
    for (
     node = self->nodeChilds;
     node;
     node = node->nodeNext) {
        ;
    }
    nodePrev = node;
    nodeNew = Node_new(pszName, self->treeOwner, self, nodePrev,
     (void *) 0, (void *) 0 );
    if (nodePrev) {
        nodePrev->nodeNext = nodeNew;
    }
    return (nodeNew);
}

static void
Node_delete (
  Node self ) {
    Dic_delete(self->dic);
    Delete(self->pszName);
    Delete(self);
}

struct TreeImp {
    Node nodeRoot;
};

Tree
Tree_new () {
  Tree self;
    self = New(struct TreeImp, 1);
    self->nodeRoot = Node_new("root", self, (void *) 0, (void *) 0,
     (void *) 0, (void *) 0 );
    return (self);
}

void
Tree_delete(
  Tree self ) {
    Node_delete(self->nodeRoot);
    Delete(self);
}

#include <stdio.h>

Result
Tree_load (
  Tree self,
  const char * pszFile ) {
  FILE * pfile = (void *) 0;
  Str strEntry = Str_new("");
  RE reEntry = RE_new("^( *)([a-zA-Z0-9-]+) *(.*)$");
  Result r = Failure;
  char sz[100];
  int nIndentUnit = 0;
  int iCurrentLevel = 0;
  Node nodeParent = self->nodeRoot;
  Node nodePrev = (void *) 0;
    if (! (pfile = fopen(pszFile, "r"))) {
        goto Tree_load_end;
    }
    Str_assign(strEntry, "");
    while (fgets(sz, sizeof (sz), pfile) || strlen(Str_get(strEntry))) {
        /* The line is longer than the buffer. */
        if (
         (strlen(sz) == ((sizeof (sz)) - 1)) &&
         (sz[strlen(sz) - 1] != '\n') ) {
            Str_append(strEntry, sz);
            continue;
        }
        /* Cut off the trailing newline. */
        if (sz[strlen(sz) - 1] == '\n') {
            sz[strlen(sz) - 1] = '\0';
        }
        Str_append(strEntry, sz);
        if (RE_match(reEntry, Str_get(strEntry))) {
          int nNumIndent;
          int iNextLevel;
          const char * pszName;
          const char * pszProps;
            nNumIndent = strlen(RE_getSubStr(reEntry, 1));
            if (nIndentUnit == 0 && nNumIndent > 0 ) {
                nIndentUnit = nNumIndent;
            }
            iNextLevel = (nNumIndent == 0)? 0: (nNumIndent / nIndentUnit);
            if (iCurrentLevel < iNextLevel) {
                printf("d: >\n");
                nodeParent = nodePrev;
                iCurrentLevel ++;
            }
            while (iNextLevel < iCurrentLevel) {
                printf("d: <\n");
                nodeParent = nodeParent->nodeParent;
                iCurrentLevel --;
            }
            pszName = RE_getSubStr(reEntry, 2);
            pszProps = RE_getSubStr(reEntry, 3);
            printf("d: %s-<%s>\n", pszName, pszProps);
            nodePrev = Node_addChild(nodeParent, pszName);
            //for () {
            //    Node_setProp(nodePrev, pszKey, pszVal);
            //}
        }
        Str_assign(strEntry, "");
    }
    r = Success;
Tree_load_end:
    if (pfile) {
        fclose(pfile);
    }
    Str_delete(strEntry);
    RE_delete(reEntry);
    return (r);
}

Node
Node_getNextChild (
  Node self ) {
  Node nodeRet = (void *) 0;
    if (self->nodeCurrent) {
        nodeRet = self->nodeCurrent;
        self->nodeCurrent = self->nodeCurrent->nodeNext;
    }
    return (nodeRet);    
}

Node
Node_getFirstChild (
  Node self ) {
    self->nodeCurrent = self->nodeChilds;
    return (Node_getNextChild(self));
}


