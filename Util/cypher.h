#pragma once
#include <iostream>

/**
 * Methods used to encrypt and decrypt data using main encryption key.
 */
namespace cypher {
    auto encrypt(std::string & text) -> void;
    auto decrypt(std::string & text) -> void;
}

/**
 * Encryption key used to encrypt and decrypt data.
 */
class key{
public:
    /**
     * Encryption key setter.
     * @param value - value to set as encryption key.
     */
    static auto setKey(std::string const& value) -> void;
    /**
     * Encryption key getter.
     * @return Encryption key.
     */
    static auto getKey() -> std::string;
private:
    static std::string keyValue;
};
