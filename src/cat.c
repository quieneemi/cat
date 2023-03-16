#include "cat.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool b, e, n, s, t, v;
int line_count = 1;

int main(int argc, char **argv)
{
  if (parse_flags(argc, argv))
  {
    cat(argc, argv);
  }

  return 0;
}

int parse_flags(int argc, char **argv)
{
  bool no_err = true;

  const char *short_options = "beEnstTv";
  const struct option long_options[] = {
    { "number-nonblank", no_argument, NULL, 'b' },
    { "number", no_argument, NULL, 'n' },
    { "squeeze-blank", no_argument, NULL, 's' },
    { NULL, 0, NULL, 0 }
  };

  int opt;
  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1 && no_err)
  {
    switch (opt)
    {
    case 'b':
      b = true;
      break;

    case 'e':
      e = true;
      v = true;
      break;

    case 'E':
      e = true;
      break;

    case 'n':
      n = true;
      break;

    case 's':
      s = true;
      break;

    case 't':
      t = true;
      v = true;
      break;

    case 'T':
      t = true;
      break;

    case 'v':
      v = true;
      break;
    
    default:
      no_err = false;
      break;
    }
  }

  if (b) n = false;

  return no_err;
}

void cat(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-')
    {
      FILE *fp = fopen(argv[i], "rb");
      if (fp != NULL)
      {
        print_file(fp);
        fclose(fp);
      }
      else
      {
        perror(argv[i]);
        break;
      }
    }
  }
}

void print_file(FILE *fp)
{
  int ch;
  if ((ch = getc(fp)) != EOF)
  {
    if (n || (b && ch != '\n'))
    {
      printf("%6d\t", line_count++);
    }

    int nxt;
    while ((nxt = getc(fp)) != EOF)
    {
      if (s && ch == '\n' && nxt == '\n')
      {
        printf("\n");
        while ((nxt = getc(fp)) == '\n') {}

        if (n) printf("%6d\t", line_count++);
        if (e) printf("$");
      }

      print_char(ch);

      if ((n || (b && nxt != '\n')) && ch == '\n')
      {
        printf("%6d\t", line_count++);
      }

      if (e && nxt == '\n') printf("$");

      ch = nxt;
    }

    print_char(ch);
  }
}

void print_char(int ch)
{
  if ((v && ch < 32 && ch != '\t' && ch != '\n') || (t && ch == '\t'))
  {
    printf("^%c", ch + 64);
  }
  else
  {
    printf("%c", ch);
  }
}
