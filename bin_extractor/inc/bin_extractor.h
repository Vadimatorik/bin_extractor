#include "cmd_controller.h"

class bin_extractor {
public:
    constexpr bin_extractor() {}

public:
    int init (int argc, char **argv);
    int start (void);

private:
    cmd_controller c_controller;

private:
    bin_extractor_cfg cfg;

};