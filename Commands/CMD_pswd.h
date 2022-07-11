#pragma once

#include "CMD.h"

/**
 * Command used to manage passwords.
 */
class CMD_pswd : public CMD {
public:
    auto execute(std::vector<std::string> const &command) -> void override;

private:
    /**
    * Function invoked with an option "-a".\n
    * Creates a new password and places it under given password group.
    * @param command - A vector of strings containing command given by user.
    */
    auto static addPassword(std::string const &command) -> void;

    /**
    * Function invoked with an option "-r".\n
    * Creates a new password and places it under given password group.
    * @param command - A vector of strings containing command given by user.
    */
    auto static randomizePassword(std::string const &command) -> void;

    /**
    * Function invoked with an option "-r".\n
    * Removes a password from a password group.
    * @param command - A vector of strings containing command given by user.
    */
    auto static removePassword(std::string const &command) -> void;

    /**
    * Function invoked with an option "-e".\n
    * Changes one of passwords properties to a given value.
    * @param command - A vector of strings containing command given by user.
    */
    auto static editPassword(std::string const &command) -> void;

    /**
     * Method used to check how strong a password is.
     * @param pswd - password key
     */
    auto static check_strength(std::string pswd) -> void;
};