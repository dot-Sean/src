#ifndef KFC_TREE_H
#define KFC_TREE_H

struct TreeImp;
typedef struct TreeImp * Tree;

struct NodeImp;
typedef struct NodeImp * Node;

Tree Tree_new(const char * pszName);
Tree Tree_load(const char * pszFilename);
void Tree_delete(Tree self);

void Tree_save(Tree self, const char * pszFilename);

Node Tree_getRoot(Tree self);

Node Tree_getNode(Tree self, const char * pszPath);

void Tree_removeNode(Tree self, const char * pszPath);

const char * Node_getName(Node self);

void Node_delete(Node self);

Node Node_getChild(Node self, const char * pszNodeName);
Node Node_addChild(Node self, const char * pszNodeName);
void Node_delChild(Node self, const char * pszNodeName);
#define Node_removeChild Node_delChild

const char * Node_getProp(Node self, const char * pszKey);
void Node_setProp(Node self, const char * pszKey, const char * pszVal);
void Node_delProp(Node self, const char * pszKey);

const char * Node_getContent(Node self);
const char * Node_setContent(Node self, const char * pszContent);
const char * Node_delContent(Node self);

Node Node_getFirstChild(Node self);
Node Node_getNext(Node self);
Node Node_getNextChild(Node self);

int Node_getNumChild(Node self);

#endif

/*

if (! (node = Tree_getNode(tree, "/users/knaka/editor"))) {
    Die(("Item not found"))
}
pszEditor = Node_getContent(node);

if (! (nodeGroup = Tree_getNode(tree, "/users/knaka/opened_files"))) {
    Die(("Group not found"))
}
while (
 nodeItem = Node_getFirstChild(nodeGroup);
 nodeItem;
 nodeItem = Node_getNextChild(nodeGroup) ) {
    printf("ki0: %s\n", Node_getName(nodeItem));
}
nodeItem = Node_addChild(nodeGroup, "file");
Node_setProp(nodeItem, "name", pszFileName);

*/
