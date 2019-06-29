#pragma once

#include <stdint.h>

struct bin_extractor_cfg {
public:
    char *f_in;
    char *f_out;

    uint32_t addr_base;
    uint32_t addr_start;
    uint32_t addr_end;

public:
    constexpr bin_extractor_cfg () :
        f_in(nullptr),
        f_out(nullptr),
        addr_base(0),
        addr_start(0),
        addr_end(0) {
    }
};

