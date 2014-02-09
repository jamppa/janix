UNITY_HOME		= ../unity
INCLUDE			= -I$(UNITY_HOME)/src -I$(UNITY_HOME)/extras/fixture/src
TESTS_INCLUDE	= -I ../kernel
UNITY_OBJS		= $(UNITY_HOME)/src/unity.c $(UNITY_HOME)/extras/fixture/src/unity_fixture.c
TEST_OBJS		= hello_test.c mmap_test.c
UNDER_TEST_OBJS	= ../kernel/mmap.c
TEST_RUNNER		= test_runner.c

CC			= gcc
CFLAGS		= -Wall $(INCLUDE) $(TESTS_INCLUDE) 

all: clean default run

run:
	./run_tests.out

default:
	$(CC) $(CFLAGS) $(UNITY_OBJS) $(TEST_OBJS) $(UNDER_TEST_OBJS) $(TEST_RUNNER) -o run_tests.out

clean:
	rm -rf run_tests.out