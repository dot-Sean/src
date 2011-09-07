#include <stdio.h>
#include <getopt.h>

unsigned char fVerbose_ = 0;
unsigned char fHelp_ = 0;

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  const char * options = "hvx:";
  const struct option long_options[] = {
      { "help",    no_argument, (void *) 0, 'h' },
      { "verbose", no_argument, (void *) 0, 'v' },
      { "xtra", required_argument, (void *) 0, 'x' },
      { (void *) 0, 0, (void *) 0, 0 }
  };
  int c;
  int i;
    do {
        while ((c = getopt_long(argc, argv, options,
         long_options, NULL )) != -1 ) {
            switch (c) {
                case ('h'): {
                    fHelp_ = 1;
                    break;
                }
                case ('v'): {
                    fVerbose_ = 1;
                    break;
                }
                case ('x'): {
                    fprintf(stderr, "d1: %s\n", optarg);
                    break;
                }
                default: {
                    break;
                }
            }
        }
        for (i = optind; i < argc; i ++) {
            fprintf(stderr, "d: %s\n", argv[i]);
        }
        rc = 0;
    } while (0);
    return (rc);
}
