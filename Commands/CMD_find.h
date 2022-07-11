#pragma once

#include "CMD.h"
#include <iostream>
#include <vector>
#include "../Classes/password.h"

/**
 * Enums determining which password field to check in fieldEquals() method.
 */
enum class field{
    name,
    pswd,
    group,
    link,
    login
};

/**
 * Character types looked for in a contains() method.
 */
enum class filter{
    uppercase,
    lowercase,
    special,
    digits
};

/**
 * Command used to print only the passwords matching selected filters.
 */
class CMD_find : public CMD{
public:
    void execute(const std::vector<std::string> &command) override;

private:
    /**
     * Filters out the passwords without selected field matching "match" string.
     * @param field - enum determining which password field to compare to the "match" string.
     * @param match - string used to select only the passwords matching field text.
     * @param matches - reference to a vector of passwords matching provided criteria.
     */
    auto fieldEquals(field field, std::string match, std::vector<password>& matches) -> void;

    /**
     * Filters out the passwords without selected character types.
     * @param filter - enum determining which character types to look for in a password.
     * @param matches - reference to a vector of passwords matching provided criteria.
     */
    auto contains(filter filter, std::vector<password> &matches) -> void;

    /**
     * Filters out the passwords not including the "filter" string in their key.
     * @param filter - string containing a word looked for in a password key.
     * @param matches - reference to a vector of passwords matching provided criteria.
     */
    auto contains(std::string const& filter, std::vector<password> &matches) -> void;
};