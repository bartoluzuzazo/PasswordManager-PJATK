#pragma once

#include <iostream>

/**
 * Namespace containing methods used to save and load password data.
 */
namespace memory{
    /**
     * Saves all the password data to a text file.
     */
    auto save() -> void;

    /**
     * Loads saved password data from a text file.
     */
    auto load() -> void;

}

/**
 * Class containing path to provided password file.
 */
class filepath{
public:
    /**
     * Password file path getter.
     * @return - String containing a path to the password file.
     */
    auto static getPath() -> std::string;

    /**
     * Password file path setter.
     * @param npath - new file path used to replace path string.
     */
    auto static setPath(std::string const& npath) -> void;

private:
    static std::string path;
};