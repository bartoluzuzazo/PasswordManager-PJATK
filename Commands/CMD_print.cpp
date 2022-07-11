#include "CMD_print.h"
#include "../Classes/password_group.h"
#include "../Util/pswdutils.h"
#include "../Util/timestamp.h"

void CMD_print::execute(const std::vector<std::string> &command) {
    auto const& option = command.at(2);
    if(option == "-a" || option == "--all") password_group::printGroups();
    else if(option == "-t" || option == "--timestamps") timestamp::readAllTimestamps();
    else throw errorType::invalidOption;
}
