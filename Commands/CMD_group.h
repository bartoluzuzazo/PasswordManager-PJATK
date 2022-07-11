#pragma once

#include <iostream>
#include <vector>
#include "CMD.h"

/**
 * Command used to manage password groups.
 */
class CMD_group : public CMD {
public:
    auto execute(std::vector<std::string> const& command) -> void override;

private:
    /**
    * Function invoked with an option "-a".\n
    * Allows you to add new password categories.
    * @param command - a vector of strings containing command input.
    */
    auto static addGroup(std::vector<std::string> const& command) -> void;
    /**
     * Function invoked with an option "-r".\n
     * Allows you to remove password groups along with all its contents.
     * @param command - a vector of strings containing command input.
     */
    auto static removeGroup(std::vector<std::string> const& command) -> void;
    /**
     * Converts a vector of strings into a single string divided by spaces.
     * @param command - a vector of strings containing command input.
     * @return String containing a group name.
     */
    auto static getGName(std::vector<std::string> const& command) -> std::string;
};
