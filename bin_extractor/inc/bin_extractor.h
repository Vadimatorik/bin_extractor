#include "cmd_controller.h"

#include <vector>

class bin_extractor {
public:
    bin_extractor() {}

public:
    int init (int argc, char **argv);
    int start (void);

private:
    int read_bin (void);
    int check_input_prarm (void);
    void get_real_section_len (uint32_t& len);
    int write_section (void);

private:
    cmd_controller c_controller;

private:
    bin_extractor_cfg cfg;
    std::vector<uint8_t> bin;
    std::vector<uint8_t> section;

private:
    uint32_t section_start = 0;
    uint32_t section_len = 0;

};