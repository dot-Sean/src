#include "kfc.h"

#include <stdio.h>

#if 0
int
main (
  int argc,
  char * * argv ) {
  Arg arg;
  const char * pszName;
  const char * pszValue;
  const char * pszRest;
    arg = Arg_new(argc, argv, "i, o, in, out", False);
    for (
     pszName = Arg_getFirstOpt(arg, & pszValue);
     pszName;
     pszName = Arg_getNextOpt(arg, & pszValue) ) {
        printf("opt: %s (%s)\n", pszName, (pszValue)? pszValue: "N/A");
    }
    for (
     pszRest = Arg_getFirstRest(arg);
     pszRest;
     pszRest = Arg_getNextRest(arg) ) {
        printf("rest: %s\n", pszRest);
    }
    Arg_delete(arg);
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  File file;
  const char * psz;
    //file = File_new(argv[1]);
    file = File_newProcess(argv[1]);
    for (
     psz = File_getFirst(file);
     psz;
     psz = File_getNext(file) ) {
        printf("d: %s\n", psz);
    }
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  Dir dir;
  const char * psz;
    dir = Dir_new(argv[1]);
    for (
     psz = Dir_getFirst(dir);
     psz;
     psz = Dir_getNext(dir) ) {
        printf("d: %s\n", psz);
    }
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  Cmd cmd;
  const char * psz;
    if (0) {
        cmd = Cmd_new("sort | cat -n", True);
        Cmd_write(cmd, "D\n2\nA\n4\n");
        Cmd_write(cmd, "B\n3\nC\n1\n");
        Cmd_closeWrite(cmd);
        while ((psz = Cmd_read(cmd))) {
            printf("d: %s\n", psz);
        }
    } else {
        cmd = Cmd_new("ls /bin | sort | cat -n", False);
        while ((psz = Cmd_read(cmd))) {
            printf("d: %s\n", psz);
        }
    }
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
    openLog("/tmp/tmp.log");
    log("Hello, World %d!", 256);
    closeLog();
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  Cmd cmd;
  const char * psz;
    cmd = Cmd_new("sort | cat -n");
    Cmd_printf(cmd, "Hello, World %d!\n", 256);
    Cmd_printf(cmd, "Good-bye, World %d!\n", 256 * 256);
    while ((psz = Cmd_read(cmd))) {
        printf("d: %s\n", psz);
    }
    Cmd_delete(cmd);
    return (0);
}
#endif 

#if 0
int
main (
  int argc,
  char * * argv ) {
  Dic dic;
  const char * psz;
  int i;
    dic = Dic_new();
    Dic_add(dic, "abc", (void *) "ABC");
    Dic_add(dic, "xyz", (void *) "XYZ");
    Dic_add(dic, "hoge", (void *) "KIICHIRO");
    Dic_remove(dic, "hoge");
    Dic_add(dic, "kiichiro", (void *) "KIICHIRO");
    for (i = 0; (psz = Dic_getKeyAt(dic, i)); i ++) {
        printf("d: %s %s\n", psz, (const char *) Dic_refer(dic, psz));
    }
    Dic_delete(dic);
    return (0);
}
#endif

#if 0

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main (
  int argc,
  char * * argv ) {
  int iFD;
  const char * psz;
    /* frequently used way to pass variable arguments to macros */
    EditErrMsg(("<%d: %s>", 256, "hoge"));
    printf("d: %s\n", getErrMsg());
    psz = "/etc/hoge";
    if (! ((iFD = open(psz, O_RDONLY)) >= 0)) {
        Die(("open(\"%s\", O_RDONLY) failed", psz));
    }
    return (0);
}
#endif

#if 0
#include <stdlib.h>
#include <regex.h>

int
main (
  int argc,
  char * * argv ) {
  struct re_registers reg;
  struct re_pattern_buffer buf;
  const char * pszPat = "([a-z]+)[0-9]+([a-z]+)";
  const char * pszTgt = "123abc456xyz789";
  int iStart;
    re_syntax_options = RE_SYNTAX_EGREP;
    bzero(& buf, sizeof (buf));
    re_compile_pattern(pszPat, strlen(pszPat), & buf);
    reg.num_regs = 10;
    reg.start = (regoff_t *) malloc(sizeof (regoff_t) * reg.num_regs);
    reg.end = (regoff_t *) malloc(sizeof (regoff_t) * reg.num_regs);
    re_search(& buf, pszTgt, strlen(pszTgt), 0, strlen(pszTgt), & reg);
    printf("d: %d\n", iStart);
    printf("d: %d\n", reg.start[0]);
    printf("d: %d\n", reg.end[0]);
    printf("d: %d\n", reg.start[1]);
    printf("d: %d\n", reg.end[1]);
    printf("\n");
    {
      regex_t regex;
      regmatch_t * pregmatch;
      #define InitNumMatch 16
        regcomp(& regex, pszPat, REG_EXTENDED);
        pregmatch = 
         (regmatch_t *) Malloc((sizeof (regmatch_t)) * InitNumMatch);
        regexec(& regex, pszTgt, InitNumMatch, pregmatch, 0);
        printf("d: %d\n", pregmatch[0].rm_so);
        printf("d: %d\n", pregmatch[0].rm_eo);
        printf("d: %d\n", pregmatch[1].rm_so);
        printf("d: %d\n", pregmatch[1].rm_eo);
    }
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  RE re;
  const char * pszRE = "([a-z]+)[0-9]+([a-z]+)";
  const char * pszTgt = "123abc456xyz789";
    re = RE_new(pszRE);
    if (RE_match(re, pszTgt) == Success) {
        printf("regexp: %s\n", pszRE);
        printf("target: %s\n", pszTgt);
        printf("RE_getPrecStr: %s\n", RE_getPrecStr(re));
        printf("RE_getPostStr: %s\n", RE_getPostStr(re));
        printf("RE_getSubStr -1: %s\n", RE_getSubStr(re, -1));
        printf("RE_getSubStr 0: %s\n", RE_getSubStr(re, 0));
        printf("RE_getSubStr 1: %s, 2: %s\n", RE_getSubStr(re, 1),
         RE_getSubStr(re, 2) );
        printf("RE_getSubStr 3: %s\n", RE_getSubStr(re, 3));
        printf("RE_getSubStr 100: %s\n", RE_getSubStr(re, 16));
        RE_delete(re);
    }
    return (0);
}
#endif

#if 0

#include <gnome-xml/parser.h>

int
main (
  int argc,
  char * * argv ) {
  xmlDocPtr doc;
    doc = xmlNewDoc(XML_DEFAULT_VERSION);
    doc->root = xmlNewDocNode(doc, (void *) 0, "doc0", (void *) 0);
    {
      xmlNodePtr node0;
        xmlNewChild(xmlNewChild(doc->root, (void *) 0, "node0", "hoge"), (void *) 0, "node0", "hoge");
        xmlNewChild(doc->root, (void *) 0, "node1", (void *) 0);
    }
    xmlSaveFile("/tmp/tmp.xml", doc);
    xmlFreeDoc(doc);
    return (0);
}

#endif

#if 1
int
main (
  int argc,
  char * * argv ) {
  Tree tree;
  Node root;
  Node node;
  Node node0;
  Node node1;
    tree = Tree_new("hoge hoge");
    //tree = Tree_load("/tmp/tmp.xml");
    root = Tree_getNode(tree, "/");
      node0 = Node_addChild(root, "bin");
        Node_setProp(node0, "comment", "executables");
      node0 = Node_addChild(root, "hoge1");
      node0 = Node_addChild(root, "hoge2");
      node0 = Node_addChild(root, "hoge3");
      Node_delChild(root, "hoge2");
      node0 = Node_addChild(root, "usr");
        node1 = Node_addChild(node0, "bin");
        node1 = Node_addChild(node0, "local");
      node0 = Node_addChild(root, "etc");
      node0 = Node_addChild(root, "var");
      node0 = Node_addChild(root, "var");
    for (
     node = Node_getFirstChild(root);
     node;
     node = Node_getNextChild(root) ) {
        printf("d: %s\n", Node_getName(node));
    }
    printf("d2: %d\n", Node_getNumChild(root));
    Tree_save(tree, "/tmp/tmp.xml");
    Tree_delete(tree);
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  Str str;
    str = Str_new("");
    Str_appendf(str, "d0: %s %d\n", "hoge0", 0);
    Str_appendf(str, "d1: %s %d\n", "hoge1", 1);
    Str_appendf(str, "d2: long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long long line.", (void *) 0);
    printf("<%s>\n", Str_get(str));
    Str_delete(str);
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
    if (argc >= 2) {
      Dir dir;
      const char * psz;
        dir = Dir_new(argv[1]);
        for (psz = Dir_getFirst(dir); psz; psz = Dir_getNext(dir)) {
            fprintf(stderr, "d: %s\n", psz);
        }
        Dir_delete(dir);
    }
    return (0);
}
#endif

#if 0
static char sz[] = "
lkdsjfalsdjfl;sdajf;alsdjf;aksljf;aksljf;alksj
";

int
main (
  int argc,
  char * * argv ) {
    {
      Tree tree;
        (void *) sz;
        tree = Tree_new();
        Tree_delete(tree);
    }
    {
      Str str = Str_newf("%s %s!", "Hello,", "World");
        printf("d: %s\n", Str_get(str));
        Str_delete(str);
    }
    {
      RE re = RE_newf("^[^#].*\\<%s\\>.*$", "stream");
      Cmd cmd = Cmd_newf("cat %s", "/etc/inetd.conf");
      const char * psz;
        while ((psz = Cmd_read(cmd))) {
            if (RE_match(re, psz)) {
                printf("d: %s\n", RE_getSubStr(re, 0));
            }
        }
        Cmd_delete(cmd);
        RE_delete(re);
    }
    return (0);
}
#endif

#if 0

#include <string.h>

static int
compare (
  void * pv1,
  void * pv2 ) {
    return (strcmp((const char *) pv1, (const char *) pv2));
}

int
main (
  int argc,
  char * * argv ) {
  SVec vec;
  const char * psz;
  int i;
    vec = SVec_new(compare);
    SVec_add(vec, (void *) "ZZZ");
    SVec_add(vec, (void *) "abc");
    SVec_add(vec, (void *) "123");
    SVec_add(vec, (void *) "XYZ");
    SVec_add(vec, (void *) "xyz");
    for (i = 0; (psz = (const char *) SVec_getAt(vec, i)); i ++) {
        printf("d: %s\n", psz);
    }
    printf("d0: %s\n", (const char *) SVec_get(vec, (void *) "ZZZ"));
    SVec_delete(vec);
    return (0);
}

#endif

#if 0

static int
sortInt (
  void * pv1,
  void * pv2 ) {
    return (((int) pv1) - ((int) pv2));
}

int
main (
  int argc,
  char * * argv ) {
  Stk stk;
    stk = Stk_new();
    {
      int i;
        for (i = 10; i > 0; i --) {
            Stk_push(stk, (void *) (i * 3));
        }
    }
    {
      int i;
        for (i = 0; i < Stk_getHeight(stk); i ++) {
            printf("d0: %d, ", (int) Stk_getAt(stk, i));
        }
    }
    Stk_sort(stk, sortInt);
    {
      int i;
        for (i = 0; i < Stk_getHeight(stk); i ++) {
            printf("d1: %d, ", (int) Stk_getAt(stk, i));
        }
    }
    {
      int n;
        while ((n = (int) Stk_pop(stk))) {
            printf("d2: %d, ", n);
        }
    }
    return (0);
}
#endif

#if 0
int
main (
  int argc,
  char * * argv ) {
  Tree tree;
    tree = Tree_new();
    Tree_load(tree, "/tmp/test.cfg");
    Tree_delete(tree);
    return (0);
}
#endif
