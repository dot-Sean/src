#include "kfc_tree.h"

#include "kfc.h"

/* #define MemDebug */
#include "kfc_mem.h"

#include <gnome-xml/parser.h>

struct TreeImp {
    xmlDocPtr doc;
    SVec svec;
};

struct NodeImp {
    xmlNodePtr xmlnode;
    Tree tree;
    xmlNodePtr xmlnodeCurrent;
};

static int
compare (
  void * pv1,
  void * pv2 ) {
    return ((((Node) pv1)->xmlnode) - (((Node) pv2)->xmlnode));
}

static Node
Node_new (
  xmlNodePtr xmlnode,
  Tree tree ) {
  Node self;
  struct NodeImp nodeimp;
    if (! xmlnode) {
        return ((void *) 0);
    }
    nodeimp.xmlnode = xmlnode;
    self = (Node) SVec_get(tree->svec, (void *) & nodeimp);
    if (! self) {
        self = New(struct NodeImp, 1);
        self->xmlnode = xmlnode;
        self->tree = tree;
        SVec_add(self->tree->svec, (void *) self);
    }
    return (self);
}

Tree 
Tree_new(
  const char * pszName ) {
  Tree self;
    self = New(struct TreeImp, 1);
    self->doc = xmlNewDoc(XML_DEFAULT_VERSION);
    self->doc->root =
     xmlNewDocNode(self->doc, (void *) 0, (pszName)? pszName: "hoge",
     (void *) 0 );
    self->svec = SVec_new(compare);
    Node_new(self->doc->root, self);
    return (self);
}

static void Node_delAllChild(Node self);
  
void
Node_delete (
  Node self ) {
    Node_delAllChild(self);
    xmlUnlinkNode(self->xmlnode);
    xmlFreeNode(self->xmlnode);
    /* Be careful of the order of the following 2 lines */
    SVec_remove(self->tree->svec, (void *) self);
    self->xmlnode = (void *) 0;
    Delete(self);
}

static void
Node_delAllChild (
  Node self ) {
  Node node;
    for (
     node = Node_getFirstChild(self);
     node;
     node = Node_getNextChild(self) ) {
        Node_delete(node);
    }
}

void
Tree_delete (
  Tree self ) {
    Node_delete(Tree_getRoot(self));
    SVec_delete(self->svec);
    self->doc->root = (void *) 0;
    xmlFreeDoc(self->doc);
    Delete(self);
}

void
Tree_save (
  Tree self,
  const char * pszFilename ) {
    xmlSaveFile(pszFilename, self->doc);
}

Node
Tree_getRoot(
  Tree self ) {
    return (Node_new(self->doc->root, self));
}

Node
Node_getNextChild (
  Node self ) {
  xmlNodePtr xmlnodeRet = self->xmlnodeCurrent;
    if (xmlnodeRet) {
        self->xmlnodeCurrent = xmlnodeRet->next;
    }
    return (Node_new(xmlnodeRet, self->tree));
}

Node
Node_getFirstChild (
  Node self ) {
    self->xmlnodeCurrent = self->xmlnode->childs;
    return (Node_getNextChild(self));
}

Node
Tree_getNode (
  Tree self,
  const char * pszPath ) {
  RE re;
  Str str;
  Node node;
    str = Str_new(pszPath);
    re = RE_new("^/+([^/]+)(.*)$");
    node = Tree_getRoot(self);
    if (RE_match_("^/+$", pszPath)) {
        return (node);
    }
    while (RE_match(re, Str_get(str))) {
        if (! (node = Node_getChild(node, RE_getSubStr(re, 1)))) {
            return ((void *) 0);
        }
        RE_getSubStr(re, 2);
        Str_assign(str, RE_getSubStr(re, 2));
    }
    RE_delete(re);
    Str_delete(str);
    return (node);
}

/* The names of nodes can not be unique */
Node
Node_addChild (
  Node node,
  const char * pszNodeName ) {
    return (Node_new(xmlNewChild(node->xmlnode, (void *) 0, pszNodeName,
     (void *) 0), node->tree));
}

const char *
Node_getName (
  Node self ) {
    return (self->xmlnode->name);
}

#include <string.h>

Node
Node_getChild (
  Node self,
  const char * pszNodeName ) {
  Node node;
    for (
     node = Node_getFirstChild(self);
     node;
     node = Node_getNextChild(self) ) {
        if (strcmp(pszNodeName, Node_getName(node)) == 0) {
            return (node);
        }
    }
    return ((void *) 0);
}

void
Node_setProp (
  Node self,
  const char * pszKey,
  const char * pszVal ) {
    Node_delProp(self, pszKey);
    xmlNewProp(self->xmlnode, pszKey, pszVal);
}

static xmlAttrPtr
Node_getAttr (
  Node node,
  const char * pszPropName ) {
  xmlAttrPtr xmlattr;
    for (
     xmlattr = node->xmlnode->properties;
     xmlattr;
     xmlattr = xmlattr->next ) {
        if (strcmp(pszPropName, xmlattr->name) == 0) {
            return (xmlattr);
        }
    }
    return ((void *) 0);
}

void
Node_delProp (
  Node self,
  const char * pszKey ) {
  xmlAttrPtr xmlattr;
    while ((xmlattr = Node_getAttr(self, pszKey))) {
#if 0
        xmlRemoveProp(xmlattr);
#endif
    }
}

void
Node_delChild (
  Node self,
  const char * pszNodeName ) {
  Node node = Node_getChild(self, pszNodeName);
    if (node) {
        Node_delete(node);
    }
}

const char *
Node_getProp (
  Node self,
  const char * pszKey ) {
  const char * psz;
    psz = xmlGetProp(self->xmlnode, pszKey);
    return ((psz)? psz: "");
}

Node
Node_getNext (
  Node self ) {
    return (Node_new(self->xmlnode->next, self->tree));
}

Tree
Tree_load (
  const char * pszFilename ) {
  Tree self;
  xmlDocPtr doc;
    doc = xmlParseFile(pszFilename);
    if (! doc) {
        return ((void *) 0);
    }
    self = New(struct TreeImp, 1);
    self->doc = doc;
    self->svec = SVec_new(compare);
    Node_new(self->doc->root, self);
    return (self);
}

void
Tree_removeNode(
  Tree self,
  const char * pszPath ) {
  Node node;
    node = Tree_getNode(self, pszPath);
    if (node) {
        Node_delete(node);
    }
}

int
Node_getNumChild (
  Node self ) {
  int n;
  xmlNodePtr xmlnode;
    n = 0;
    for (xmlnode = self->xmlnode->childs; xmlnode; xmlnode = xmlnode->next) {
        n ++;
    }
    return (n);
}
