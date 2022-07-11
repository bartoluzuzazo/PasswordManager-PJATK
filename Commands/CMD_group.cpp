#include <iostream>
#include <vector>

#include "../Classes/password_group.h"
#include "../Util/pswdutils.h"
#include "CMD_group.h"
#include "../Util/memory.h"

auto CMD_group::execute(std::vector<std::string> const& command) -> void {
    auto const& option = command.at(2);
    if      (option == "-a" || option == "--add")    addGroup(command);
    else if (option == "-r" || option == "--remove") removeGroup(command);
    else throw errorType::invalidOption;
}

auto CMD_group::addGroup(std::vector<std::string> const& command) -> void {
    auto gname = getGName(command);
    password_group t = password_group(gname);
    password_group::append(t);
    std::cout << "New password group \"" << t.getName() << "\" successfully added!\n";
    memory::save();
}

auto CMD_group::removeGroup(const std::vector<std::string> &command) -> void {
    auto gname = getGName(command);
    for(auto i = 0; i<password_group::getGroups().size();i++){
        auto t = password_group::getGroups().at(i);
        if(t.getName() == gname){
            std::cout << "You are about to delete a group named " << gname << " containing " << t.getPasswords().size() << " passwords. \nAre you sure you want to proceed? [Y/N]\n";
            std::string choice;
            while(choice!="Y" && choice!="N" && choice!="y" && choice!="n"){
                std::getline(std::cin, choice);
                if(choice=="Y" || choice=="y"){
                    password_group::getGroups().erase(password_group::getGroups().begin()+i);
                    std::cout << "Password group " + gname + " removed successfully.\n";
                    memory::save();
                    return;
                }
                else if(choice == "N" || choice == "n") return;
            }
        }
    }
    throw errorType::invalidGroupName;
}

auto CMD_group::getGName(const std::vector<std::string> &command) -> std::string {
    std::string gname = "";
    for(auto i=3;i<command.size(); i++){
        if(i>3) gname+=' ';
        gname+=command.at(i);
    }
    if (gname.empty()) throw errorType::notEnoughArguments;
    return gname;
}