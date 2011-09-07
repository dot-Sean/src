#include <stdio.h>

#include <rpm/rpmlib.h>
#include <rpm/rpmts.h>
#include <rpm/rpmmacro.h>

#define MacroFiles "/usr/lib/rpm/macros:/etc/rpm/macros:~/.rpmmacros"

static void *
notify (
  void * arg,
  rpmCallbackType what,
  unsigned long amount,
  unsigned long total,
  fnpyKey Key,
  void * data ) {
  void * pvRet = NULL;
    fprintf(stderr, "d: %s\n", (const char *) Key);
    switch (what) {
        case RPMCALLBACK_UNKNOWN: {
            fprintf(stderr, "RPMCALLBACK_UNKNOWN\n");
            break;
        }
        case RPMCALLBACK_INST_PROGRESS: {
            fprintf(stderr, "RPMCALLBACK_INST_PROGRESS\n");
            break;
        }
        case RPMCALLBACK_INST_START: {
            fprintf(stderr, "RPMCALLBACK_INST_START\n");
            break;
        }
        case RPMCALLBACK_INST_OPEN_FILE: {
            fprintf(stderr, "RPMCALLBACK_INST_OPEN_FILE\n");
            pvRet = Fopen((const char *) Key, "r.ufdio");
            break;
        }
        case RPMCALLBACK_INST_CLOSE_FILE: {
            fprintf(stderr, "RPMCALLBACK_INST_CLOSE_FILE\n");
            break;
        }
        case RPMCALLBACK_TRANS_PROGRESS: {
            fprintf(stderr, "RPMCALLBACK_TRANS_PROGRESS\n");
            break;
        }
        case RPMCALLBACK_TRANS_START: {
            fprintf(stderr, "RPMCALLBACK_TRANS_START\n");
            break;
        }
        case RPMCALLBACK_TRANS_STOP: {
            fprintf(stderr, "RPMCALLBACK_TRANS_STOP\n");
            break;
        }
        case RPMCALLBACK_UNINST_PROGRESS: {
            fprintf(stderr, "RPMCALLBACK_UNINST_PROGRESS\n");
            break;
        }
        case RPMCALLBACK_UNINST_START: {
            fprintf(stderr, "RPMCALLBACK_UNINST_START\n");
            break;
        }
        case RPMCALLBACK_UNINST_STOP: {
            fprintf(stderr, "RPMCALLBACK_UNINST_STOP\n");
            break;
        }
        case RPMCALLBACK_REPACKAGE_PROGRESS: {
            fprintf(stderr, "RPMCALLBACK_REPACKAGE_PROGRESS\n");
            break;
        }
        case RPMCALLBACK_REPACKAGE_START: {
            fprintf(stderr, "RPMCALLBACK_REPACKAGE_START\n");
            break;
        }
        case RPMCALLBACK_REPACKAGE_STOP: {
            fprintf(stderr, "RPMCALLBACK_REPACKAGE_STOP\n");
            break;
        }
        case RPMCALLBACK_UNPACK_ERROR: {
            fprintf(stderr, "RPMCALLBACK_UNPACK_ERROR\n");
            break;
        }
        case RPMCALLBACK_CPIO_ERROR: {
            fprintf(stderr, "RPMCALLBACK_CPIO_ERROR\n");
            break;
        }
        default: {
            ;
        }
    }
    return (pvRet);
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  rpmts pts = NULL; /* Transaction Set */
  rpmps pps = NULL; /* Problem Set */
  int i;
#define Num 2
  char * apszPath[Num] = {
   "/home/knaka/rpm/RPMS/noarch/rpmtest-1.0-1.noarch.rpm",
   "/home/knaka/rpm//RPMS/i686/hello-libs-1.0-1.i686.rpm",
  };
  FD_t apfd[Num] = { NULL, NULL };
  Header apheader[Num] = { NULL, NULL };
  const char * pszTarget = ""; /* ? */
    /* if %{?_rpmlock_path} is be expanded, runTS can cause SEGV */
    rpmInitMacros((void *) 0, MacroFiles);
    rpmReadConfigFiles("/usr/lib/rpm/rpmrc", pszTarget);
    if (! (pts = rpmtsCreate())) {
        fprintf(stderr, "Failed to create transaction set.\n");
        goto except;
    }
    rpmtsSetRootDir(pts, "/");
    rpmtsSetNotifyCallback(pts, (rpmCallbackFunction) notify, NULL);
    rpmtsSetVSFlags(pts, RPMVSF_NOMD5 | RPMVSF_NODSA | RPMVSF_NORSA | RPMVSF_NEEDPAYLOAD);
    rpmtsClean(pts);
    for (i = 0; i < Num; i ++) {
        if (! (apfd[i] = Fopen(apszPath[i], "r.ufdio"))) {
            fprintf(stderr, "Failed to open file.\n");
            goto except;
        }
        if (rpmReadPackageFile(pts,
         apfd[i], apszPath[i], & apheader[i]) != RPMRC_OK ) {
            fprintf(stderr, "Failed to read file.\n");
            goto except;
        }
        if (rpmtsAddInstallElement(pts, apheader[i],
         (const fnpyKey) apszPath[i], /* const fnpyKey key */
         0, /* int upgrade */
         NULL /* rpmRelocation * relocs */ ) != 0) {
            fprintf(stderr, "Failed to add element.\n");
            goto except;
        }
        fprintf(stderr, "Added \"%s\".\n", apszPath[i]);
    }
    rpmtsSetFlags(pts,(rpmtsFlags(pts) &
     ~ (RPMTRANS_FLAG_NOSCRIPTS | _noTransScripts | _noTransTriggers)));
    pps = rpmtsProblems(pts);
    if (rpmpsNumProblems(pps) > 0) {
        rpmpsPrint(stderr, pps);
        goto except;
    }
    pps = rpmpsFree(pps);
    rpmtsClean(pts);
    if (rpmtsRun(pts, NULL, 0) != 0) {
        fprintf(stderr, "Failed to run transaction.\n");
        pps = rpmtsProblems(pts);
        if (rpmpsNumProblems(pps) > 0) {
            fprintf(stderr, "Rpm problems.\n");
            rpmpsPrint(stderr, pps);
        }
        goto except;
    }
    rc = 0;
except:
    for (i = 0; i < Num; i ++) {
        if (apfd[i]) {
            Fclose(apfd[i]);
        }
    }
    if (pts) { rpmtsFree(pts); }
    if (pps) { rpmpsFree(pps); }
    return (rc);
}
