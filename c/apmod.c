#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>

#include <apache/httpd.h>
#include <apache/http_config.h>
#include <string.h>

int
main (
  int argc,
  char * * argv ) {
  void * handle;
  module * pmodule;
  char * filename;
  char * recname;
  char * tmp;
    assert(argc == 2);
    filename = argv[1];
    handle = dlopen(filename, RTLD_GLOBAL | RTLD_LAZY);
    assert(handle);
    recname = filename;
    if ((tmp = rindex(recname, '/'))) {
        recname = tmp + 1;
    }
    if (strstr(recname, "mod_") == recname) {
        recname += strlen("mod_");
    }
    if (strstr(recname, "lib") == recname) {
        recname += strlen("lib");
    }
    tmp = (char *) malloc((sizeof (char)) * strlen(recname) + \
     strlen("_module") - strlen(".so") );
    strcpy(tmp, recname);
    recname = tmp;
    strcpy(recname + strlen(recname) - strlen(".so"), "_module");
    pmodule = dlsym(handle, recname);
    assert(pmodule);
    printf("version: %d\n", pmodule->version);
    printf("minor_version: %d\n", pmodule->minor_version);
    printf("name: %s\n", pmodule->name);
    dlclose(handle);
    return (0);
}
