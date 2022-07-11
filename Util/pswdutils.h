#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include "../Classes/password.h"

/**
 * Types of errors in user input.
 */
enum class errorType{
    invalidCommand,
    invalidOption,
    notEnoughArguments,
    invalidGroupName,
    tooManyArguments
};

/**
 * Various utility methods used in password manager.
 */
namespace pswdutils {

    auto print(std::vector<password> const& vec) -> void;

    /**
    * Takes a string of words separated by space and returns a vector containing said words.
    * @param in - string to split by ' ' (space) delimiter.
    * @return out - a vector of separate strings contained in input string.
    */
    auto split(std::string in) -> std::vector<std::string>;
    /**
    * Method that divides a string to a vector of substrings matching provided regex.
    * @param searched - string used in search for matches.
    * @param regex - regex searched for in string.
    * @return vector of strings matching a regex.
    */
    auto regexMatcher(std::string searched, std::regex const& regex) -> std::vector<std::string>;
    /**
     * Regex used to find data between selected <> marks.
     * @param searched - name of mark to search for.
     * @return Built regex with selected name.
     */
    auto div_in_load(std::string const& searched) -> std::regex;
    /**
     * Regex used to find data between selected <> marks in one line of text.
     * @param searched - name of mark to search for.
     * @return Built regex with selected name.
     */
    auto div_load_line(std::string const& searched) -> std::regex;
    /**
     * Regex used to find words between quotation marks.
     */
    const auto div_by_quotation_marks = std::regex("\"(.*?)\"");

    /**
    * Returns an adequate error prompt for a specific type of error.
    * @param command - A vector of strings containing command given by user.
    * @param err - An error type defining which prompt to return.
    * @return A string informing user of a specific error in his command input.
    */
    auto errorPrompt(std::vector<std::string> command, errorType err) -> std::string;
}