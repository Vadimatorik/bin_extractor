#pragma once

#include "bin_extractor_cfg.h"

class cmd_controller {
public:
    constexpr cmd_controller () {
    }

public:
    int set_arg (int c, char **v);

public:
    int parse (bin_extractor_cfg *return_struct);

private:
    int check_cmd_arg (char arg);
    int extract_uint32_t_hex_variable (char arg, uint32_t *value);
    void print_help (void);

private:
    int argc = 0;
    char **argv = nullptr;

};