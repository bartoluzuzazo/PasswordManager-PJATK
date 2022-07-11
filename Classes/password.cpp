#include <iostream>
#include "password.h"


password::password(std::string const& name, std::string const& pswd, std::string const& group) :
name(name), pswd(pswd), group(group) {}

auto password::getName() -> std::string {
    return name;
}

auto password::getGroup() -> std::string {
    return group;
}

auto password::getPswd() -> std::string {
    return pswd;
}

auto password::getLink() -> std::string {
    return link;
}

auto password::getLogin() -> std::string {
    return login;
}


auto password::setName(std::string const &input) -> void {
    name = input;
}

auto password::setGroup(std::string const& input) -> void {
    group = input;
}

auto password::setPswd(std::string const &input) -> void {
    pswd = input;
}

auto password::setLink(std::string const &input) -> void {
    link = input;
}

auto password::setLogin(std::string const &input) -> void {
    login = input;
}

auto password::toString() -> std::string {
    return name + ' ' + pswd + ' ' + group + (!link.empty() ? link : "") + ' ' + (!login.empty() ? login : "");
}

