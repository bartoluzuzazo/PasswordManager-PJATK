#include <iostream>
#include <vector>
#include "CMD_help.h"

void CMD_help::execute(const std::vector<std::string> &command) {
    std::cout << prompt << '\n';
}

std::string CMD_help::prompt = R"(
List of all available commands:

    help  -  lists all available commands
    man   -  prints detailed help for selected command
    print -  prints selected data
    group -  allows the user to manage password groups
    pswd  -  allows the user to manage saved passwords
    sort  -  prints all the passwords in selected order
    exit  -  closes the application

For more information on a specific command use "man [command_name]".
)";