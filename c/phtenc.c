/* */
/* $ gcc -lcrypt phtenc.c -Wall */

#define _XOPEN_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define p (1 + 2 * 3 *  5 * 7 * 11 * 13 * 17 * 19 * 23)
#define SerLen 12
#define SrcLen 20

int
div2 (
  int a0,
  int a1 ) {
    return ((a0 - (a0 % a1)) / a1);
}

int
hpow (
  int a0,
  int a1 ) {
  int n;
    if (a1 <= 1) {
        return (a0);
    }
    n = div2(a1, 2);
    return ((hpow(a0,n) & 0x0000ffff) * (hpow(a0,a1-n) & 0x0000ffff));
}

int randomize (
  int a0,
  int a1,
  int a2,
  int a3,
  int a4 ) {
    return (a0 ^ (0x01ffffff & (hpow(p, a2 * 26 * 26 + a3 * 26 + a4 + 1))));
}

int
encode (
  char * psz,
  const char * pszSrc ) {
  int ch, ch1, ch2, n1, n2, nSrc;
  const char * pszCrypt;
    nSrc = atoi(pszSrc);
    pszCrypt = crypt(pszSrc, "aa") ;
    ch = pszCrypt[11] & 3;
    ch = ch * 128 + pszCrypt[12];
    ch = ch * 128 + pszCrypt[13];
    ch = hpow(p, 0x00000fff & nSrc);
    ch1 = ch % 26;
    ch = (ch - ch1) / 26;
    ch2 = ch % 26;
    ch = (ch - ch2) / 26;
    n1 = ch % 10;
    n2 = ((ch - n1) / 10) % 10;
    return (sprintf(psz, "%08d%d%d%c%c",
     randomize(nSrc, n2, n1, ch2, ch1),
     n2,
     n1,
     ch2 + 'A',
     ch1 + 'A' ));
}

int
extract (
  const char * pszSer ) {
  char sz[SerLen + 1];
  int n;
    strcpy(sz, pszSer);
    sz[8] = '\0';
    n = atoi(sz);
    return (randomize(n,
     pszSer[8] - '0',
     pszSer[9] - '0',
     pszSer[10] - 'A',
     pszSer[11] - 'A' ));
}

int
decode (
  const char * pszSer) {
  int nSrc;
  int i;
  char szSer2[SerLen + 1];
  char szSrc[SrcLen + 1];
    nSrc = extract(pszSer);
    if (strlen(pszSer) != SerLen) {
        return (1);
    }
    for (i = 0; i < SerLen - 2; i ++) {
        if (! isdigit(pszSer[i])) {
            return (1);
        }
    }
    for (i = SerLen - 2; i < SerLen; i ++) {
        if (! isupper(pszSer[i])) {
            return (1);
        }
    }
    sprintf(szSrc, "%d", nSrc);
    encode(szSer2, szSrc);
    if(strcmp(pszSer, szSer2) == 0) {
        return (0);
    } else {
        //print $n, ",0: ", a0, ",en:", encode($n), "\n";
        return (1);
    }
}

int
usage () {
    printf("Scode v0.0 (C) PacificHiTech '98.4\n");
    printf("  scode -e <n1> <n2> <printf pattern>\n");
    printf("    encode a number from <n1> to <n2> and print with patten.\n");
    printf("  scode -d <n>\n");
    printf("    decode a number and return with exit code\n");
    return (1);
}

int
main (
  int argc,
  char * * argv ) {
  int rc;
    if (argc <= 2) {
        rc = usage();
#if 0
    } else if (strcmp(argv[1], "-e") == 0) {
      char szSer[SerLen + 1];
        encode(szSer, argv[2]);
        printf("%s\n", szSer);
#endif
    } else if (strcmp(argv[1], "-d") == 0) {
        rc = decode(argv[2]);
    } else {
        rc = usage();
    }
    return (rc);
}
