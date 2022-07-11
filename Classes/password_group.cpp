#include <iostream>
#include <vector>
#include "password_group.h"
#include "password.h"
#include "../Util/pswdutils.h"

std::vector<password_group> password_group::groups;

password_group::password_group(std::string name) : name(name) {};

auto password_group::getName() -> std::string {
    return name;
}

auto password_group::append(password_group const &added) -> void {
    groups.push_back(added);
}

auto password_group::printGroups() -> void {
    auto counter = 1;
    for(auto i : password_group::groups){
        std::cout << counter++ << ". " << i.getName() << '\n';
        for(auto p:i.passwords){
            std::cout << '\t' << p.getName() << ": " << p.getPswd();
            if(!p.getLink().empty()) std::cout << "\tWebsite: " << p.getLink();
            if(!p.getLogin().empty()) std::cout << "\tLogin: " << p.getLogin();
            std::cout << "\n\n";
        }
    }
}

auto password_group::addToGroup(std::string name, password password) -> void {
    for(auto& i:groups){
        if(i.getName()==name){
            i.passwords.push_back(password);
            return;
        }
    }
    throw errorType::invalidGroupName;
}

auto password_group::getGroups() -> std::vector<password_group>& {
    return groups;
}

auto password_group::getPasswords() -> std::vector<password>& {
    return passwords;
}
