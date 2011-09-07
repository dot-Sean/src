#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  char sz[100];
  char * psz = "No Name";
    if (argc >= 2) {
        psz = argv[1];
    }
    fprintf(stderr, "[%s] Standard In Begin\n", psz);
    while (fgets(sz, sizeof (sz), stdin)) {
        fprintf(stderr, "[%s] %s", psz, sz);
    }
    fprintf(stderr, "[%s] Standard In End\n", psz);
    fprintf(stderr, "[%s] Standard Error\n", psz);
    return (0);
}

#if 0

typedef enum {
  TOKEN_INPUT,
  TOKEN_WRITE,
  TOKEN_APPEND,
  TOKEN_PIPE,
  TOKEN_STRING
} TokenType;

typedef struct TokenTab {
  TokenType type;
  char * string;
} Token;

processes = []
processes.append(Process())
for i in range(MaxNumProcess):
  token = get_token(data)
  while token and token != "|":
    if  token == "<":
      file = get_token()
      aprocess[i].stdin = open(file, read)
    elif token = ">":
      file = get_token()
      aprocess[i].stdout = open(file, write)
    elif token == ">>"
      file = get_token()
      aprocess[i].stdout = open(file, append)
    elif token == String:
      aprocess[i].args.append(data)
  }
  if len(aprocess[i].args) == 0:
    raise Exception, "Syntax Error"
  if (token == '|') {
    aprocess[i + 1] = Process()
  }
  if (! aprocess[i].stdin) {
    if (i == 0) {
      aprocess[i].stdin = stdin
    }
    aprocess[i - 1].stdout から aprocess[i].stdin へ、パイプでつなぐ
  }
  if (! aprocess[i].out) {
    aprocess[i].out = stdout
  }
}

#endif
