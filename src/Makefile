CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
TFLAGS = -fprofile-arcs -ftest-coverage
FUNC_DIR = functions
COV_FLAGS = -fprofile-arcs -ftest-coverage
SRCS = $(wildcard $(FUNC_DIR)/*/*.c)
OBJS = $(SRCS:.c=.o)


SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    SYSTEM_FLAGS =  -lcheck -lpthread -lrt -lsubunit -lm
else ifeq ($(SYSTEM), Darwin)
    SYSTEM_FLAGS = -lcheck
endif


all: clean s21_decimal.a decimal_test

decimal_test: tests/s21_decimal_test.c s21_decimal.a
	$(CC) $(FLAGS) -o $@ $< s21_decimal.a $(SYSTEM_FLAGS) $(LFLAGS)
	./decimal_test

gcov_report: clean decimal_test
	gcc $(FLAGS) $(COV_FLAGS) $(SRCS) tests/s21_decimal_test.c -o test $(SYSTEM_FLAGS)
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	rm -rf *.gc* test coverage.info decimal_test

s21_decimal.a: $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf s21_decimal.a decimal_test $(OBJS)  *.gc* gcov_report coverage.info coverage_report/*
	rm -rf report_html