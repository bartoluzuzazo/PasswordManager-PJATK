#pragma once

namespace console{
    /**
    * Starts the command line input.
    */
    auto run_cli() -> void;

    /**
     * Reads the password file path provided by user.
     */
    auto selectFile() -> void;

    /**
     * Reads decryption key provided by user.
     */
    auto keyInput() -> void;
}