#include <iostream>
#include <vector>
#include "CMD_find.h"
#include "../Classes/password.h"
#include "../Classes/password_group.h"
#include "../Util/pswdutils.h"


void CMD_find::execute(const std::vector<std::string> &command) {
    auto matchingPasswords = std::vector<password>();
    for (auto g: password_group::getGroups()) {
        for (auto const &p: g.getPasswords()) {
            matchingPasswords.push_back(p);
        }
    }

    for (auto i = 0; i < command.size(); i++) {
        auto option = command.at(i);
        if      (option == "-ne") fieldEquals(field::name, command.at(i + 1), matchingPasswords);
        else if (option == "-pe") fieldEquals(field::pswd, command.at(i + 1), matchingPasswords);
        else if (option == "-ge") fieldEquals(field::group, command.at(i + 1), matchingPasswords);
        else if (option == "-lge") fieldEquals(field::login, command.at(i + 1), matchingPasswords);
        else if (option == "-lne") fieldEquals(field::link, command.at(i + 1), matchingPasswords);
        else if (option == "-cl") contains(filter::lowercase, matchingPasswords);
        else if (option == "-cu") contains(filter::uppercase, matchingPasswords);
        else if (option == "-cd") contains(filter::digits, matchingPasswords);
        else if (option == "-cs") contains(filter::special, matchingPasswords);
        else if (option == "-c") contains(command.at(i+1), matchingPasswords);
    }
    pswdutils::print(matchingPasswords);
}

auto CMD_find::fieldEquals(field field, std::string match, std::vector<password> &matches) -> void {
    for (int i = matches.size()-1; i >=0; i--) {
        auto p = matches.at(i);
        switch (field) {
            case field::name:
                if (p.getName() != match) matches.erase(matches.begin() + i);
                break;
            case field::pswd:
                if (p.getPswd() != match) matches.erase(matches.begin() + i);
                break;
            case field::group:
                if (p.getGroup() != match) matches.erase(matches.begin() + i);
                break;
            case field::login:
                if (p.getLogin() != match) matches.erase(matches.begin() + i);
                break;
            case field::link:
                if (p.getLink() != match) matches.erase(matches.begin() + i);
                break;
        }
    }
}

auto CMD_find::contains(filter filter, std::vector<password> &matches) -> void {
    auto special_chars = std::string("!@#$%^&*()_-+=[]\\:;\"'<,>.?/");
    for (int i = matches.size()-1; i >=0; i--) {
        bool uppercase = false, lowercase = false, special = false, digits = false;
        auto p = matches.at(i);
        for (auto ch : p.getPswd()) {
            if (ch >= 'A' && ch <= 'Z') uppercase = true;
            if (ch >= 'a' && ch <= 'z') lowercase = true;
            if (ch >= '0' && ch <= '9') digits = true;
            if (special_chars.find(ch) != std::string::npos) special = true;
        }
        switch (filter){
            case filter::uppercase:
                if(!uppercase) matches.erase(matches.begin()+i);
                break;
            case filter::lowercase:
                if(!lowercase) matches.erase(matches.begin()+i);
                break;
            case filter::special:
                if(!special) matches.erase(matches.begin()+i);
                break;
            case filter::digits:
                if(!digits) matches.erase(matches.begin()+i);
                break;
        }
    }
}

auto CMD_find::contains(std::string const& filter, std::vector<password> &matches) -> void {
    for (int i = matches.size()-1; i >=0; i--) {
        auto p = matches.at(i);
        if (p.getPswd().find(filter) == std::string::npos) matches.erase(matches.begin()+i);
    }
}

