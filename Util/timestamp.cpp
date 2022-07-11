#include <iostream>
#include <cstdlib>
#include <ctime>

#include "timestamp.h"


auto timestamp::create() -> void {
    srand(time(nullptr));
    auto secs = time(0);
    auto date = localtime(&secs);

    auto year = std::to_string(date->tm_year + 1900);
    auto month = std::to_string(date->tm_mon + 1);
    expand(month);
    auto day = std::to_string(date->tm_mday);
    expand(day);
    auto hour = std::to_string(date->tm_hour);
    expand(hour);
    auto minute = std::to_string(date->tm_min);
    expand(minute);
    auto second = std::to_string(date->tm_sec);
    expand(second);

    auto data = std::string();
    for (auto i = 0; i < 250; i++) {
        switch (i) {
            case 53:
                data += month;
                i += 1;
                break;
            case 58:
                data += second;
                i += 1;
                break;
            case 71:
                data += year;
                i += 3;
                break;
            case 98:
                data += hour;
                i += 1;
                break;
            case 133:
                data += minute;
                i += 1;
                break;
            case 178:
                data += day;
                i += 1;
                break;
            default:
                data += (char) (48 + rand() % 10);
        }
    }

    timestamps.push_back(data);
}

auto timestamp::readLastTimestamp() -> void {

    if (timestamps.back().empty() || timestamps.empty()) {
        std::cout << "No previous application logins detected.\n\n";
        return;
    }

    auto rawtext = timestamps.back();

    std::string year, month, day, hour, minute, second;

    auto data = std::string();
    for (auto i = 0; i < 250; i++) {
        switch (i) {
            case 53:
                month = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                i += 1;
                break;
            case 58:
                second = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                i += 1;
                break;
            case 71:
                year = std::string(rawtext.begin() + i, rawtext.begin() + i + 4);
                i += 3;
                break;
            case 98:
                hour = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                i += 1;
                break;
            case 133:
                minute = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                i += 1;
                break;
            case 178:
                day = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                i += 1;
                break;
        }
    }
    std::cout << "Last login: " << year << '-' << month << '-' << day << '\t' << hour << ':' << minute << ':' << second
              << "\n\n";
}

auto timestamp::expand(std::string &date) -> void {
    if (date.size() == 1) date = "0" + date;
}

auto timestamp::getTimestamps() -> std::vector<std::string> const & {
    return timestamps;
}

auto timestamp::setTimestamps(std::vector<std::string> const& set) -> void {
    timestamps = set;
}

auto timestamp::readAllTimestamps() -> void {
    if (timestamps.back().empty() || timestamps.empty()) {
        std::cout << "No previous application logins detected.\n\n";
        return;
    }
    auto n = 1;
    std::string year, month, day, hour, minute, second;

    for(auto rawtext : timestamps) {
        if (rawtext.empty()) continue;

        auto data = std::string();
        for (auto i = 0; i < 250; i++) {
            switch (i) {
                case 53:
                    month = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                    i += 1;
                    break;
                case 58:
                    second = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                    i += 1;
                    break;
                case 71:
                    year = std::string(rawtext.begin() + i, rawtext.begin() + i + 4);
                    i += 3;
                    break;
                case 98:
                    hour = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                    i += 1;
                    break;
                case 133:
                    minute = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                    i += 1;
                    break;
                case 178:
                    day = std::string(rawtext.begin() + i, rawtext.begin() + i + 2);
                    i += 1;
                    break;
            }
        }
        std::cout << n++ << ":\t" << year << '-' << month << '-' << day << '\t' << hour << ':' << minute << ':' << second
                  << "\n";
    }
    std::cout << '\n';
}

std::vector<std::string> timestamp::timestamps;
