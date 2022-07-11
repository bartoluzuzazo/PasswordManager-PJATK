#include "CMD_exit.h"

void CMD_exit::execute(const std::vector<std::string> &command) {
    exit(0);
}
