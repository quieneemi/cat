# @author  quieneemi

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# NAME     project name
#
# CC       compiler
# CFLAGS   compiler flags
#
# OS       operating system
# SRCS     source files

NAME       := my_cat

CC         := gcc
CFLAGS     := -Wall -Wextra

OS         := $(shell uname -s)
SRCS       := cat.h cat.c

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all      build program and run test
# my_cat   build program
# clean    remove binary
# test     run tests
# cppcheck run static code analys
# leaks    run memory analyzer

all: $(NAME) test

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm $(NAME)

test: $(NAME)
	bash tests.sh

cppcheck:
	cppcheck --enable=all \
	--suppress=missingIncludeSystem \
	*.c *.h

leaks: $(NAME)
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./$(NAME) data.txt
else
	valgrind --tool=memcheck ./$(NAME) data.txt
endif

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: my_cat clean test cppcheck leaks
.SILENT:
