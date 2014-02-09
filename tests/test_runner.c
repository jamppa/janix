#include "unity_fixture.h"

static void run_all_tests(void) {
    RUN_TEST_GROUP(hello);
    RUN_TEST_GROUP(mmap);
}

int main(int argc, char** argv) {
    return UnityMain(argc, argv, run_all_tests);
}