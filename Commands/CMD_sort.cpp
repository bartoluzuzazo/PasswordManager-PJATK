#include <iostream>
#include <vector>

#include "../Classes/password.h"
#include "../Util/pswdutils.h"
#include "../Classes/password_group.h"
#include "CMD_sort.h"


void CMD_sort::execute(std::vector<std::string> const& command) {

    std::vector<password> allpswds;
    for(auto g : password_group::getGroups()){
        allpswds.insert(allpswds.end(), g.getPasswords().begin(), g.getPasswords().end());
    }

    for(int i=command.size()-1;i>1;i--){
        auto const& option = command.at(i);

        if      (option == "-n" || option == "--name")     std::ranges::sort(allpswds, {}, [](password p) -> std::string { return p.getName();});
        else if (option == "-g" || option == "--group")    std::ranges::sort(allpswds, {}, [](password p) -> std::string { return p.getGroup();});
        else if (option == "-p" || option == "--password") std::ranges::sort(allpswds, {}, [](password p) -> std::string { return p.getPswd();});
        else if (option == "-lg" || option == "--login")  std::ranges::sort(allpswds, {}, [](password p) -> std::string { return p.getLogin();});
        else if (option == "-ln" || option == "--link")   std::ranges::sort(allpswds, {}, [](password p) -> std::string { return p.getLink();});
        else throw errorType::invalidOption;

    }
    pswdutils::print(allpswds);
}
