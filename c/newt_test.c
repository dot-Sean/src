#include <stdio.h>
#include <newt.h>
#include <string.h>
#include <distro.h>

const char *
getPass (
  char * psz,
  size_t nBufSize ) {
  const char * pszRet = NULL;
  newtComponent tbMsg;
  newtComponent entryPass;
  newtComponent btnOk;
  newtComponent btnCancel;
  const char * pszPass;
  newtComponent btnResult;
  newtGrid gridAll;
  newtGrid gridBtns;
  /* dynamic */
  newtComponent frmMain = NULL;
    do {
        if (! (frmMain = newtForm(NULL, NULL, 0))) {
            break;
        }
        tbMsg = newtTextboxReflowed(-1, -1,
         "Please enter your initial password.", 60, 10, 10, 0 );
        entryPass = newtEntry(-1, -1, NULL, 24, & pszPass,
         NEWT_FLAG_PASSWORD );
        btnOk = newtButton(-1, -1, "OK");
        btnCancel = newtButton(-1, -1, "Cancel");
        newtFormAddComponents(frmMain, tbMsg, entryPass,
         btnOk, btnCancel, NULL );
        newtFormSetCurrent(frmMain, entryPass);
        gridBtns = newtGridHStacked(
         NEWT_GRID_COMPONENT, btnOk,
         NEWT_GRID_COMPONENT, btnCancel,
         NULL );
        if (! (gridAll = newtCreateGrid(1, 3))) {
            break;
        }
        newtGridSetField(gridAll, 0, 0, NEWT_GRID_COMPONENT, tbMsg,
         0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(gridAll, 0, 1, NEWT_GRID_COMPONENT, entryPass,
         0, 1, 0, 0, 0, 0);
        newtGridSetField(gridAll, 0, 2, NEWT_GRID_SUBGRID, gridBtns,
         0, 1, 0, 0, 0, NEWT_GRID_FLAG_GROWX);
        newtRefresh();
        newtGridWrappedWindow(gridAll, "Test");
        newtGridDestroy(gridAll, 1);
        btnResult = newtRunForm(frmMain);
        if (btnResult == btnOk) {
            strncpy(psz, pszPass, nBufSize);
            pszRet = psz;
        }
        newtPopWindow();
    } while (0);
    if (frmMain) { newtFormDestroy(frmMain); }
    return (pszRet);
}

int
main (
  int argc,
  char * * argv ) {
  char sz[256];
  const char * psz = NULL;
  char * pszSavedColor = NULL;
  int i;
    newtInit();
    for (i = 0; i < 2; i ++) {
        struct newtColors * pcolors = dget_colors();
        if (i == 0) {
            pszSavedColor = pcolors->windowBg;
            pcolors->windowBg = pcolors->borderBg = pcolors->titleBg = pcolors->textboxBg = "green";
        } else {
            pcolors->windowBg = pcolors->borderBg = pcolors->titleBg = pcolors->textboxBg = pszSavedColor;
        }
        newtSetColors(* pcolors);
        psz = getPass(sz, sizeof (sz));
        if (psz) {
            printf("d: %s\n", sz);
        }
    }
    newtFinished();
    return (0);
}
