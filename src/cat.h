#ifndef CAT_SRC_CAT_H_
#define CAT_SRC_CAT_H_

#include <stdio.h>

int parse_flags(int argc, char **argv);
void cat(int argc, char **argv);
void print_file(FILE *fp);
void print_char(int ch);

#endif  // CAT_SRC_CAT_H_
