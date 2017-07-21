
CC = gcc
INCLUDES = -I./src -I./lib/fwprofile/src -I./tests/config -I./tests -include stdint.h
CFLAGS = -W -Wall -Wextra -Werror -pedantic -g2 -O0 -fprofile-arcs -ftest-coverage -DPC_TARGET
LFLAGS =
LIBS = -lpthread
HEADERS = $(shell find . -name *.h)
SRCS_FW = $(shell find ./lib/fwprofile/src -name *.c)
SRCS_CR = $(shell find ./src -name *.c)
SRCS_TS = $(shell find ./tests -name *.c)
SRCS = $(SRCS_FW) $(SRCS_CR) $(SRCS_TS)
ODIR = bin
OBJS = $(patsubst %,$(ODIR)/%,$(SRCS:.c=.o))
GCOV = $(patsubst %,$(ODIR)/%,$(SRCS:.c=.gcov))
OBJS_DIR = $(dir $(OBJS))
MAIN = $(ODIR)/testsuite

.PHONY: clean test create_dir coverage run-test coverage-info coverage-cp info

all: test

info:
	@echo $(shell echo $$0)

test: create_dir $(MAIN)
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

$(OBJS): $(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS): $(HEADERS)

run-test: 
	$(MAIN)

coverage-info: coverage-cp $(GCOV)
coverage-cp:
	@cp -r src/. bin/src/

$(GCOV): $(ODIR)/%.gcov: %.c
ifeq ($(CC), gcc)
	@gcov -b -o $(shell dirname $@) $<
endif	

clean:
	@$(RM) *.gcov
	@$(RM) -r $(ODIR)

create_dir:
	@mkdir -p $(OBJS_DIR)

print-%: ; @echo $*=$($*)
