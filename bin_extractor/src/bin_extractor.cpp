#include "bin_extractor.h"

#include <iostream>
#include <fstream>
#include <memory>

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

int bin_extractor::read_bin () {
    auto f = std::make_unique<std::ifstream>(this->cfg.f_in, std::ifstream::in | std::ios::binary);

    if (f->bad()) {
        printf("Error open file: %s\n", this->cfg.f_in);
        return -1;
    }

    while (f->good()) {
        uint8_t b = f->get();
        this->bin.push_back(b);
    }

    printf("file size, byte:\t%lu\n"
           "file size, KiB:\t\t%lu\n", this->bin.size(), this->bin.size()/1024);

    f->close();

    return 0;
}

int bin_extractor::check_input_prarm () {
    int64_t len = this->cfg.addr_end - this->cfg.addr_start;
    if (len <= 0) {
        printf("Negative sector length!\n");
        return EINVAL;
    } else {
        this->section_len = static_cast<uint32_t>(len);
    }

    int64_t start = this->cfg.addr_start - this->cfg.addr_base;
    if (start < 0) {
        printf("Section out of file!\n");
        return EINVAL;
    } else {
        this->section_start = static_cast<uint32_t>(start);
    }

    printf("addr_base:\t\t\t0x%X\n"
           "addr_start:\t\t\t0x%X\n"
           "addr_end:\t\t\t0x%X\n"
           "section size, byte:\t%u\n"
           "section size, KiB:\t%u\n"
           "start_in_vector:\t0x%X\n",
           this->cfg.addr_base,
           this->cfg.addr_start,
           this->cfg.addr_end,
           this->section_len,
           this->section_len/1024,
           this->section_start);

    return 0;
}

void bin_extractor::get_real_section_len (uint32_t &len) {
    int i = this->section_start + this->section_len - 1;
    for (; i >= this->section_start; i--) {
        if (this->bin[i] != 0xFF) {
            break;
        }
    }

    len = i - this->section_start + 1;
    printf("real section len:\t%u\n", len);
}

int bin_extractor::write_section () {
    auto f = std::make_unique<std::ofstream>(this->cfg.f_out, std::ifstream::out | std::ios::binary);

    if (f->bad()) {
        printf("error opening file for writing: %s\n", this->cfg.f_out);
        return EINVAL;
    }

    f->write(reinterpret_cast<char*>(&this->bin[this->section_start]), this->section_len);
    f->close();

    printf("file was written successfully\n"
           "path: %s", this->cfg.f_out);

    return 0;
}

int bin_extractor::start () {
    int rv = 0;
    if ((rv = this->read_bin()) != 0) {
        return rv;
    }

    if ((rv = this->check_input_prarm()) != 0) {
        return rv;
    }

    this->get_real_section_len(this->section_len);

    if ((rv = this->write_section()) != 0) {
        return rv;
    }

    return rv;
}
