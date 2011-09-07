#include <stdio.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <string.h>

static struct pam_conv pc = {
    misc_conv,
    NULL
};

static int
conv (
  int nmsgs,
  const struct pam_message * * msg,
  struct pam_response * * resp,
  void * closure ) {
  struct pam_closure * c = (struct pam_closure *) closure;
  struct pam_response *reply = 0;
  int i;
    reply = (struct pam_response *) calloc (nmsgs, sizeof (*reply));

    for (i = 0; i < nmsgs; ++ i) {
        switch (msg[i]->msg_style) {
            case (PAM_PROMPT_ECHO_ON): {
                fprintf(stderr, "d0\n");
                break;
            }
            case (PAM_PROMPT_ECHO_OFF): {
                fprintf(stderr, "d0\n");
                break;
            }
            default: {
                break;
            }
        }
    }
    (* resp) = reply;
    return (PAM_SUCCESS);
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
    do {
      pam_handle_t * pamh = NULL;
      //struct pam_conv pc;
      int rcPam;
        //bzero(& pc, sizeof (pc));
        //pc.conv = conv;
        //pam_set_item(pamh, PAM_TTY, strdup(":0.0"));
        pam_set_item(pamh, PAM_USER_PROMPT, "Hoge:");
        rcPam = pam_start("check", "knaka", & pc, & pamh);
        if (rcPam != PAM_SUCCESS) {
            fprintf(stderr, "pam_start() failed.\n");
            break;
        }
        rcPam = pam_authenticate(pamh, 0);
        printf("d: %d\n", rcPam);
        pam_end(pamh, 0);
        rc = 0;
    } while (0);
    return (rc);
}
