#define _GNU_SOURCE // to use getresuid(), getresgid()
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <grp.h> // for setgroups(2), initgroups(3)

#define ExePath "/usr/bin/id"

int
main (
  int argc,
  char * * argv,
  char * * envp ) {
  int rc = -1;
    do {
      uid_t ruid; // Real
      uid_t euid; // Effective
      uid_t suid; // Saved
      gid_t rgid;
      gid_t egid;
      gid_t sgid;
#if 0
        {
          char * argvNew[] = { ExePath, NULL };
            execve(ExePath, argvNew, envp);
            /* never reached */
            break;
        }
#endif
        getresuid(& ruid, & euid, & suid);
        fprintf(stderr, "ruid: %d\n", ruid);
        fprintf(stderr, "euid: %d\n", euid);
        fprintf(stderr, "suid: %d\n", suid);
        getresgid(& rgid, & egid, & sgid);
        fprintf(stderr, "rgid: %d\n", rgid);
        fprintf(stderr, "egid: %d\n", egid);
        fprintf(stderr, "sgid: %d\n", sgid);
        if (setresgid(0, 0, 0) != 0) {
        //if (setregid(0, 0) != 0) {
        //if (setgid(0) != 0) {
            perror("d1");
            break;
        }
        fprintf(stderr, "### setgid(0) done\n");
        getresuid(& ruid, & euid, & suid);
        fprintf(stderr, "ruid: %d\n", ruid);
        fprintf(stderr, "euid: %d\n", euid);
        fprintf(stderr, "suid: %d\n", suid);
        getresgid(& rgid, & egid, & sgid);
        fprintf(stderr, "rgid: %d\n", rgid);
        fprintf(stderr, "egid: %d\n", egid);
        fprintf(stderr, "sgid: %d\n", sgid);
        if (setresuid(0, 0, 0) != 0) {
            perror("d0");
            break;
        }
        fprintf(stderr, "### setuid(0) done\n");
        getresuid(& ruid, & euid, & suid);
        fprintf(stderr, "ruid: %d\n", ruid);
        fprintf(stderr, "euid: %d\n", euid);
        fprintf(stderr, "suid: %d\n", suid);
        getresgid(& rgid, & egid, & sgid);
        fprintf(stderr, "rgid: %d\n", rgid);
        fprintf(stderr, "egid: %d\n", egid);
        fprintf(stderr, "sgid: %d\n", sgid);
#if 0
        {
          int nGroups;
          gid_t * pgetgroups;
            nGroups = getgroups(0, NULL);
            pgetgroups = malloc((sizeof (gid_t)) * nGroups);
            fprintf(stderr, "cp0: %d\n", getgroups(nGroups, pgetgroups));
            fprintf(stderr, "cp1: %d\n", setgroups(nGroups, (const gid_t *) pgetgroups));
        }
#endif
        initgroups("root", 0);
        {
          char * argvNew[] = { ExePath, NULL };
            execve(ExePath, argvNew, envp);
            /* never reached */
            break;
        }
        rc = 0;
    } while (0);
    return (rc);
}
