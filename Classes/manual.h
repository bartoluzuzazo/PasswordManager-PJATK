#pragma once
#include <iostream>

/**
 * Manual for all valid commands in the application.
 */
class manual {
public:
    /**
     * Prints a selected page from the manual.
     * @param name - Name of a command to be searched for in a manual.
     */
    static void manPrompt(std::string const& name);

private:
    static const std::map<std::string,std::string> manualText;
};
