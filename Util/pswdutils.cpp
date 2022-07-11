#include <iostream>
#include <vector>
#include <regex>
#include <iomanip>

#include "../Commands/CMD.h"
#include "../Classes/password.h"
#include "pswdutils.h"

namespace pswdutils {

    auto split(std::string in) -> std::vector<std::string> {
        in+=' ';
        return regexMatcher(in, std::regex("(.*?) "));
    }

    auto regexMatcher(std::string searched, std::regex const& regex) -> std::vector<std::string> {
        std::smatch found;
        std::vector<std::string> returned = {searched};
        while(std::regex_search(searched, found, regex)){
            returned.push_back(found.str(1));
            searched = found.suffix().str();
        }
        return returned;
    }

    auto div_in_load(std::string const& searched) -> std::regex{
        return std::regex("<" + searched + ">\n((.*\n)*?)</" + searched + ">");
    }

    auto div_load_line(std::string const& searched) -> std::regex{
        return std::regex("<"+searched+">(.*)</"+searched+">");
    }

    auto errorPrompt(std::vector<std::string> command, errorType err) -> std::string {
        switch (err) {
            case errorType::invalidCommand:
                return "Unknown command. Use \"help\" to see valid commands.\n";
            case errorType::invalidOption:
                return "No " + command.at(1) + " option such as \"" + command.at(2) +
                       "\". Use manual to see all valid options.\n";
            case errorType::notEnoughArguments:
                return "Not enough arguments provided for " + command.at(1) + ". Use manual to see the correct use.\n";
            case errorType::invalidGroupName:
                return "A group with a provided name does not exist.\n";
            case errorType::tooManyArguments:
                return "Too many arguments provided for " + command.at(1) + ". Use manual to see the correct use.\n";
            default:
                return "Unknown error\n";
        }
    }

    auto print(std::vector<password> const& vec) -> void{
        auto name_width = 4,group_width = 5,pswd_width = 8,link_width = 5,login_width = 5;
        for(auto p:vec){
            if(p.getName().size() > name_width) name_width = p.getName().size();
            if(p.getPswd().size() > pswd_width) pswd_width = p.getPswd().size();
            if(p.getGroup().size() > group_width) group_width = p.getGroup().size();
            if(p.getLink().size() > link_width) link_width = p.getLink().size();
            if(p.getLogin().size() > login_width) login_width = p.getLogin().size();
        }
        name_width+=4; pswd_width+=4; link_width+=4; login_width+=4;
        std::cout << std::setw(group_width) << "GROUP" << std::setw(name_width) << "NAME" << std::setw(pswd_width) << "PASSWORD" << std::setw(link_width) << "LINK" << std::setw(login_width) << "LOGIN\n";
        for(auto p : vec){
            std::cout << std::setw(group_width) << p.getGroup() << std::setw(name_width) << p.getName() << std::setw(pswd_width) << p.getPswd() << std::setw(link_width) << p.getLink() << std::setw(login_width) << p.getLogin() << '\n';
        }
        std::cout << '\n';
    }
}