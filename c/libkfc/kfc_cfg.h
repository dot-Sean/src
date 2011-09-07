#ifndef KFC_TREE_H /* { */
#define KFC_TREE_H

#include "kfc.h"

struct TreeImp;
typedef struct TreeImp * Tree;

struct NodeImp;
typedef struct NodeImp * Node;

Tree Tree_new();
void Tree_delete(Tree self);

Result Tree_load(Tree self, const char * pszFile);
Result Tree_save(Tree self, const char * pszFile);

Node Tree_getNode(Tree self, const char * pszPath);

#endif /* } */
