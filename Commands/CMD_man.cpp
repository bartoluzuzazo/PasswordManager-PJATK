#include "CMD_man.h"
#include "../Classes/manual.h"

void CMD_man::execute(std::vector<std::string> const&command) {
    manual::manPrompt(command.at(2));
}
