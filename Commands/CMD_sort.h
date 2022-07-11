#pragma once

#include <iostream>

#include "CMD.h"

/**
 * Command used to print sorted passwords.
 */
class CMD_sort : public CMD {
    void execute(std::vector<std::string> const& command) override;
};


