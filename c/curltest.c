/* basename() */
#include <libgen.h>
/* strlen() */
#include <string.h>
/* fprintf() */
#include <stdio.h>
/* curl*() */
#include <curl/curl.h>
/* unlink() */
#include <unistd.h>
/* free() */
#include <stdlib.h>

#define HttpTimeout 10

#include "iput.h"
#include "strdupf.h"

static int
onProgress (
  void * clientp,
  double dltotal,
  double dlnow,
  double ultotal,
  double ulnow ) {
  double ratio = (dltotal != 0.0)? dlnow * 100 / dltotal: 0.0;
    iput("Progress: %f %f (%f) %f %f\n", dltotal, dlnow, ratio,
     ultotal, ulnow );
    return (0);
}

static int
fetchFileSub (
  const char * pszUrl,
  CURL * pcurl ) {
  int rc = -1;
  char * pszBaseName = NULL;
  char * pszDestFile = NULL;
  FILE * pfileDest = NULL;
    do {
      CURLcode curlrc;
      long int liResponse;
      const char * pszDestDir = ".";
        if (pszUrl && pszUrl[strlen(pszUrl) - 1] == '/') {
            pszBaseName = strdup("index.html");
        } else {
          char * pszTmp;
            pszBaseName = strdup(basename(pszTmp = strdup(pszUrl)));
            free(pszTmp);
        }
        if (pszBaseName && strlen(pszBaseName) == 0) {
            free(pszBaseName);
            pszBaseName = strdup("index.html");
        }
        pszDestFile = strdupf("%s/%s", pszDestDir, pszBaseName);
        unlink(pszDestFile);
        if (! (pfileDest = fopen(pszDestFile, "w"))) {
            eput("Opening \"%s\" failed.\n", pszDestFile);
            break;
        }
        curl_easy_reset(pcurl);
        curl_easy_setopt(pcurl, CURLOPT_URL, pszUrl);
        curl_easy_setopt(pcurl, CURLOPT_WRITEDATA, pfileDest);
        curl_easy_setopt(pcurl, CURLOPT_TIMEOUT, HttpTimeout);
        curl_easy_setopt(pcurl, CURLOPT_PROGRESSFUNCTION, onProgress);
        curl_easy_setopt(pcurl, CURLOPT_NOPROGRESS, 0);
        if ((curlrc = curl_easy_perform(pcurl)) != CURLE_OK) {
            eput("curl_easy_perform(): %s (%s).\n",
             curl_easy_strerror(curlrc), pszUrl );
            break;
        }
        if ((curlrc = curl_easy_getinfo(pcurl, CURLINFO_RESPONSE_CODE,
         & liResponse ))) {
            eput("%s (%s).\n", curl_easy_strerror(curlrc), pszUrl);
            break;
        }
        if (! (200 <= liResponse && liResponse < 300)) {
            eput("Response == %ld (%s)\n", liResponse, pszUrl);
            break;
        }
        iput("Succeeded to download \"%s\" to \"%s\".\n",
         pszUrl, pszDestFile );
        rc = 0;
    } while (0);
    if (rc != 0) {
        if (pszDestFile) { unlink(pszDestFile); }
    }
    if (pfileDest) { fclose(pfileDest); }
    if (pszBaseName) { free(pszBaseName); }
    if (pszDestFile) { free(pszDestFile); }
    return (rc);
}

//#include <mcheck.h>

int
fetchFiles (
  int nNumUrl,
  const char * * ppszUrl ) {
  int rc = -1;
  CURL * pcurl = NULL;
    //mtrace();
    do {
      int i;
      const char * pszUrl;
        if (! (pcurl = curl_easy_init())) {
            eput("curl_easy_init()\n");
            break;
        }
        for (i = 0; i < nNumUrl && (pszUrl = ppszUrl[i]); ++ i) {
            if (fetchFileSub(pszUrl, pcurl) != 0) {
                goto exception;
            }
        }
        rc = 0;
    } while (0);
exception:
    if (pcurl) { curl_easy_cleanup(pcurl); }
    //muntrace();
    return (rc);
}

int
fetchFile (
  const char * pszUrl ) {
  const char * apsz[] = { pszUrl };
    return (fetchFiles(1, apsz));
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
    do {
        if (argc <= 1) {
            eput("Too few argument.\n");
            break;
        }
        if (argc == 2) {
            if (fetchFile(argv[1]) != 0) {
                break;
            }
        } else {
            if (fetchFiles(argc - 1, (const char * *) argv + 1) != 0) {
                break;
            }
        }
        rc = 0;
    } while (0);
    return (rc);
}
