#pragma once

#include <iostream>
#include <vector>

/**
 * Object representing individual passwords.
 */
class password {

public:
    password(std::string const& name, std::string const& pswd, std::string const& group);

    /**
     * Puts all info about one password in one string.
     * @return A string containing password info.
     */
    auto toString() -> std::string;

    //Password property getters

    auto getName() -> std::string;

    auto getGroup() -> std::string;

    auto getPswd() -> std::string;

    auto getLink() -> std::string;

    auto getLogin() -> std::string;

    //Password property setters

    auto setName(std::string const& input) -> void;

    auto setGroup(std::string const& input) -> void;

    auto setPswd(std::string const& input) -> void;

    auto setLink(std::string const& input) -> void;

    auto setLogin(std::string const& input) -> void;

private:
    std::string name;
    std::string pswd;
    std::string group;

    std::string link;
    std::string login;
};

