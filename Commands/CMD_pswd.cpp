#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../Classes/password.h"
#include "../Util/pswdutils.h"
#include "CMD_pswd.h"
#include "../Classes/password_group.h"
#include "../Util/memory.h"

auto CMD_pswd::execute(std::vector<std::string> const &command) -> void {
    auto const &option = command.at(2);
    if (option == "-a" || option == "--add") addPassword(command.at(0));
    else if (option == "-r" || option == "--remove") removePassword(command.at(0));
    else if (option == "-g" || option == "--generate") randomizePassword(command.at(0));
    else if (option == "-e" || option == "--edit") editPassword(command.at(0));
    else throw errorType::invalidOption;
}

auto CMD_pswd::addPassword(std::string const &command) -> void {
    auto matches = pswdutils::regexMatcher(command, pswdutils::div_by_quotation_marks);
    if (matches.size() > 6) throw errorType::tooManyArguments;
    auto group = matches.at(1);
    auto pname = matches.at(2);
    auto pswd = matches.at(3);
    password added = password(pname, pswd, group);
    if (matches.size() >= 5) added.setLink(matches.at(4));
    if (matches.size() == 6) added.setLogin(matches.at(5));

    for(auto g : password_group::getGroups()){
        for(auto p : g.getPasswords()){
            if(p.getPswd() == pswd) std::cout << "Warning! Provided password has already been used for \"" << p.getName() << "\" in group " << g.getName() << '\n';
        }
    }

    password_group::addToGroup(group, added);
    check_strength(pswd);

    std::cout << "New password successfully added under category " << group << '\n';
    memory::save();
}

auto CMD_pswd::randomizePassword(const std::string &command) -> void {
    auto matches = pswdutils::regexMatcher(command, pswdutils::div_by_quotation_marks);
    if (matches.size() > 7) throw errorType::tooManyArguments;
    auto group = matches.at(1);
    auto pname = matches.at(2);
    auto generator = matches.at(3);
    int length = std::stoi(matches.at(4));

    bool lowercase = (generator.find('l') != std::string::npos),
            uppercase = (generator.find('u') != std::string::npos),
            digits = (generator.find('d') != std::string::npos),
            special = (generator.find('s') != std::string::npos);

    if(!lowercase && !uppercase && !digits && !special) throw std::runtime_error("At least 1 option must be provided in generator field\n");

    auto pswd = std::string();
    srand(time(nullptr));

    auto special_chars = std::string("!@#$%^&*()_-+=[]\\:;\"'<,>.?/");

    for (auto i = 0; i < length; i++) {
        int which;
        while (true) {
            which = rand() % 4;
            if (which == 0 && !lowercase) continue;
            if (which == 1 && !uppercase) continue;
            if (which == 2 && !digits) continue;
            if (which == 3 && !special) continue;
            break;
        }
        switch (which) {
            case 0:
                pswd += (char) (97 + rand() % 26);
                break;
            case 1:
                pswd += (char) (65 + rand() % 26);
                break;
            case 2:
                pswd += (char) (48 + rand() % 10);
                break;
            case 3:
                pswd += special_chars.at(rand() % special_chars.size());
                break;
        }
    }

    password added = password(pname, pswd, group);
    if(matches.size()>=6) added.setLink(matches.at(5));
    if(matches.size()==7) added.setLogin(matches.at(6));
    password_group::addToGroup(group, added);
    check_strength(pswd);
    std::cout << "New password " + pswd + " successfully added under category " << group << '\n';
    memory::save();
}

auto CMD_pswd::removePassword(std::string const &command) -> void {
    auto matches = pswdutils::regexMatcher(command, pswdutils::div_by_quotation_marks);
    auto group = matches.at(1);
    auto pname = matches.at(2);
    for (auto &g: password_group::getGroups()) {
        if (g.getName() == group) {
            for (auto i = 0; i < g.getPasswords().size(); i++) {
                auto p = g.getPasswords().at(i);
                if (p.getName() == pname) {
                    std::cout << "You are about to erase password named " << pname << " from " << group << ".\nAre you sure you want to proceed? [Y/N]\n";
                    std::string choice;
                    while(choice!="Y" && choice!="N" && choice!="y" && choice!="n"){
                        std::getline(std::cin, choice);
                        if(choice=="Y" || choice=="y"){
                            g.getPasswords().erase(g.getPasswords().begin() + i);
                            std::cout << pname << " removed from " << group << '\n';
                            memory::save();
                            return;
                        }
                        else if(choice == "N" || choice == "n") return;
                    }
                }
            }
            std::cout << "Password named " << pname << " does not exist.\n";
            return;
        }
    }
    throw errorType::invalidGroupName;
}

auto CMD_pswd::editPassword(const std::string &command) -> void {
    auto matches = pswdutils::regexMatcher(command, pswdutils::div_by_quotation_marks);
    auto group = matches.at(1);
    auto pname = matches.at(2);
    auto field = matches.at(3);
    auto change = matches.at(4);
    for (auto &g: password_group::getGroups()) {
        if (g.getName() == group) {
            for (auto i = 0; i < g.getPasswords().size(); i++) {
                auto &p = g.getPasswords().at(i);
                if (p.getName() == pname) {
                    if(field == "name") p.setName(change);
                    else if(field == "password") p.setPswd(change);
                    else if(field == "login") p.setLogin(change);
                    else if(field == "link") p.setLink(change);
                    else if(field == "group"){
                        p.setGroup(change);
                        password_group::addToGroup(change, p);
                        g.getPasswords().erase(g.getPasswords().begin() + i);
                    }
                }
            }
        }
    }
    std::cout << "Password's data changed successfully!\n";
    memory::save();
}

auto CMD_pswd::check_strength(std::string pswd) -> void {
    auto special_chars = std::string("!@#$%^&*()_-+=[]\\:;\"'<,>.?/");
    auto strength = 0;
    bool lowercase=false, uppercase=false, digits=false, special=false;
    for(auto ch : pswd){
        if(ch>='A' && ch<='Z') uppercase=true;
        if(ch>='a' && ch<='z') lowercase=true;
        if(ch>='0' && ch<='9') digits=true;
        if(special_chars.find(ch)!=std::string::npos) special=true;
    }
    if(lowercase) strength++;
    if(uppercase) strength++;
    if(digits) strength++;
    if(special) strength++;
    if(pswd.size()>=6) strength++;
    if(pswd.size()>=12) strength++;
    std::cout << "Estimated password strength: ";
    if(strength<3) std::cout << "WEAK\n";
    else if(strength<5) std::cout << "MEDIOCRE\n";
    else if(strength<6) std::cout << "STRONG\n";
    else std::cout << "VERY STRONG\n";
}