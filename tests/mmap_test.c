#include "unity_fixture.h"
#include "multiboot.h"
#include "mmap.h"
#include <string.h>

static multiboot_info_t mb;

TEST_GROUP(mmap);

TEST_SETUP(mmap) {
    memset(&mb, 0, sizeof(multiboot_info_t));
    mb.flags = 0x01;
}

TEST_TEAR_DOWN(mmap) {
}

TEST(mmap, should_return_available_mmap_when_mb_flags_bit_zero_is_set) {
    mb.flags = 0x05;
    mmap_t memory_map = get_mmap(&mb);
    TEST_ASSERT_TRUE(memory_map.is_available);
}

TEST(mmap, should_return_not_available_mmap_when_mb_flags_bit_zero_is_not_set) {
    mb.flags = 0x08;
    mmap_t memory_map = get_mmap(&mb);
    TEST_ASSERT_FALSE(memory_map.is_available);
}

TEST(mmap, should_get_memory_size) {
    mb.mem_upper = 16384;
    mmap_t mmap = get_mmap(&mb);
    TEST_ASSERT_EQUAL(16384, mmap.mem_size);
}

TEST(mmap, should_get_memory_size_as_mb) {
    mb.mem_upper = 16384;
    mmap_t mmap = get_mmap(&mb);
    TEST_ASSERT_EQUAL(16, mmap.mem_size_mb);   
}

TEST_GROUP_RUNNER(mmap) {
    RUN_TEST_CASE(mmap, should_return_available_mmap_when_mb_flags_bit_zero_is_set);
    RUN_TEST_CASE(mmap, should_return_not_available_mmap_when_mb_flags_bit_zero_is_not_set);
    RUN_TEST_CASE(mmap, should_get_memory_size);
    RUN_TEST_CASE(mmap, should_get_memory_size_as_mb);
}