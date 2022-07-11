#pragma once

#include <iostream>
#include <vector>

/**
 * Class used to read and add new timestamps from a file.
 */
class timestamp {
public:
    /**
     * Creates new timestamp.
     */
    auto static create() -> void;

    /**
     * Reads the newest timestamp.
     */
    auto static readLastTimestamp() -> void;

    /**
     * Prints all recorded timestamps.
     */
    auto static readAllTimestamps() -> void;

    /**
     * Timestamp container getter.
     * @return A reference to a vector of strings containing all the timestamps from current file.
     */
    auto static getTimestamps() -> std::vector<std::string> const&;

    /**
     * Timestamp container setter.
     * @param set - Reference to a vector of strings containing timestamps to replace a timestamp container.
     */
    auto static setTimestamps(std::vector<std::string> const& set) -> void;
private:
    /**
     * Adds a '0' before a date integer if date consists of a single digit.
     * @param date
     */
    auto static expand(std::string &date) -> void;

    static std::vector<std::string>timestamps;
};
