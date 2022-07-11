#pragma once

#include <iostream>
#include <map>
#include <vector>

/**
 * Base class for all the commands.
 */
class CMD {
public:

    /**
    * Map of all available commands. \n
    * Used to invoke execute() method of a desired command.
    */
    static const std::map<std::string,CMD*> commands;

     /**
     * Base method for every command. \n
     * Generally used to select a correct command option.
     * @param command - A vector of strings containing command given by user.
     */
    virtual auto execute(std::vector<std::string> const& command) -> void = 0;
};
