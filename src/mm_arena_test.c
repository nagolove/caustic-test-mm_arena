// vim: set colorcolumn=85
// vim: fdm=marker

#include "koh_mm.h"
#include "munit.h"
#include "stdbool.h"
#include "stdbool.h"
#include <unistd.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool verbose = false;

typedef struct Block {
    char payload[3];
} __attribute__((packed)) Block;

_Static_assert(
    sizeof(struct Block) == 3,
    "struct Block should be packed"
);

static MunitResult test_mm_init_shutdown(
    const MunitParameter params[], void* data
) {
    MMArena mm;

    _Static_assert(sizeof(Block) == 3, "Block has not proper size");

    {
        mm_arena_init(&mm, (struct MMArenaOpts) {
            .capacity1 = 100,
            .block_sz = sizeof(struct Block),
            .capacity2 = 300,
            .mult2 = 1.5,
            .capacity3 = 1300,
            .mult3 = 1.6,
            .capacity4 = 3000,
            .mult4 = 2,
        });
        mm_arena_shutdown(&mm);
    }

    {
        MMArenaOpts opts = mm_arena_opts_default;
        opts.block_sz = 1;
        mm_arena_init(&mm, opts);
        mm_arena_shutdown(&mm);
    }

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  {
    (char*) "/mm_init_shutdown",
    test_mm_init_shutdown,
    NULL,
    NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "strset",
 test_suite_tests,
 NULL,
 1,
 MUNIT_SUITE_OPTION_NONE,
 .verbose = &verbose,
};

int main(int argc, char **argv) {
    return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
