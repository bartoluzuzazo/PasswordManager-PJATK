#pragma once

#include <iostream>
#include <vector>
#include "password.h"

/**
 * Password categories created by user.
 */
class password_group{
public:
    password_group(std::string name);

    /**
     * Group name getter.
     * @return Name of a group.
     */
    auto getName() -> std::string;

    /**
     * Adds a group to a vector containing all groups.
     * @param added - A group to add.
     */
    static auto append(password_group const &added) -> void;

    /**
    * Prints all password groups and their contents.
    */
    static auto printGroups() -> void;

    /**
     * Adds a password to a selected group.
     * @param name - Name of a group to add the new password to.
     * @param password - Password added to a selected group.
     */
    static auto addToGroup(std::string name, password password) -> void;

    /**
     * Getter for password groups.
     * @return A vector of all groups.
     */
    static auto getGroups() -> std::vector<password_group>&;

    /**
     * Getter for passwords contained by a group.
     * @return All passwords from a selected group.
     */
    auto getPasswords() -> std::vector<password>&;

private:
    static std::vector<password_group> groups;
    std::string name;
    std::vector<password> passwords;
};
