#include "bin_extractor.h"

int bin_extractor::init (int argc, char **argv) {
    int rv = 0;
    if ((rv = c_controller.set_arg(argc, argv)) != 0) {
        return rv;
    }

    if ((rv = c_controller.parse(&this->cfg)) != 0) {
        return rv;
    }

    return 0;
}

int bin_extractor::start () {
    return 0;
}
