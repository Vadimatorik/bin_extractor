#include "cmd_controller.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int cmd_controller::set_arg (int c, char **v) {
    if ((c != 7) || (v == nullptr)) {
        this->print_help();
        return EINVAL;
    }

    this->argc = c;
    this->argv = v;

    return 0;
}

void cmd_controller::print_help () {
    printf("Usage:\n"
           "\tcmd_controller -b addr_base -s addr_start -e addr_end\n");
    exit(0);
}

int cmd_controller::parse (bin_extractor_cfg *return_struct) {
    /// Код символа аргумента (ASCII код буквы-аргумента или -1,
    /// если аргументы закончились).
    char c;

    int rv = 0;

    /// Символ <<:>> означает, что после буквы должен быть строка-аргумент.
    while ((c = getopt(argc, argv, "b:s:e:h?")) != -1) {
        switch (c) {
            case 'b':
                if ((rv = this->check_cmd_arg('b')) != 0) {
                    return rv;
                }

                if ((rv = this->extract_uint32_t_hex_variable('b', &return_struct->addr_base)) != 0) {
                    return rv;
                }
                break;

            case 's':
                if ((rv = this->check_cmd_arg('s')) != 0) {
                    return rv;
                }

                if ((rv = this->extract_uint32_t_hex_variable('s', &return_struct->addr_start)) != 0) {
                    return rv;
                }
                break;

            case 'e':
                if ((rv = this->check_cmd_arg('e')) != 0) {
                    return rv;
                }

                if ((rv = this->extract_uint32_t_hex_variable('e', &return_struct->addr_end)) != 0) {
                    return rv;
                }
                break;

            case 'h':
            case '?':
                this->print_help();
                break;

            default:
                break;
        }
    }

    return rv;
}

int cmd_controller::check_cmd_arg (char arg) {
    if (optarg == nullptr) {
        printf("Argument <<-%c>> not have parameter!\n\r", arg);
        return EINVAL;
    }

    return 0;
}

int cmd_controller::extract_uint32_t_hex_variable (char arg, uint32_t *value) {
    int rv = 0;
    rv = sscanf(optarg, "%x", value);
    if (rv != 1) {
        printf("Parameter of argument -%c not been recognized!\n\r", arg);
        return EINVAL;
    }

    return 0;
}
