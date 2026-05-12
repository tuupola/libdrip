#include "unit.h"
#include "greatest.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(manifest_suite);

    GREATEST_MAIN_END();
}
