#pragma once
#include <iostream>
#include <vector>
#include "CMD.h"

/**
 * Command used to display a list of all commands.
 */
class CMD_help : public CMD {
public:
    void execute(const std::vector<std::string> &command) override;

private:
    static std::string prompt;
};
