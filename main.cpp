#include "bin_extractor.h"

int main (int argc, char *argv[]) {
    auto *o = new bin_extractor();

    int rv = 0;
    if ((rv = o->init(argc, argv)) != 0) {
        return rv;
    }

    return o->start();
}
